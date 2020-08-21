package gorm

import (
	"errors"
	"fmt"
	"glog"
	"io"
	"net"
	"runtime/debug"
	"sync"
	"sync/atomic"
	"time"
)

var sessionClosedError = errors.New("session is closed")

type ITcpTask interface {
	ParseMsg(data []byte) bool
	OnClose()
}

const (
	recvbuff_max_size = 8*1024*1024 + 256
	cmd_max_size      = 8 * 1024 * 1024
	sendcmd_max_size  = 8*1024*1024 + 256
	cmd_header_size   = 4 // 3字节指令长度 1字节是否压缩
	cmd_verify_time   = 30
)

type TcpTask struct {
	closed          int32
	verified        uint32
	stopedChan      chan struct{}
	stopFlag        int32
	recvBuff        *ByteBuffer
	sendBuff        *ByteBuffer
	sendMutex       sync.Mutex
	Conn            net.Conn
	derived         ITcpTask
	signal          chan struct{}
	needCheckrecv   int32
	recvTimeout     int64
	keepAliveSecond int64
	Index           int64
	request_cbid    uint32
}

func newTcpTask(conn net.Conn, derived ITcpTask) *TcpTask {
	index := time.Now().Unix()
	return &TcpTask{
		closed:     -1,
		Conn:       conn,
		stopedChan: make(chan struct{}, 1),
		stopFlag:   0,
		recvBuff:   NewByteBuffer(),
		sendBuff:   NewByteBuffer(),
		signal:     make(chan struct{}, 1),
		derived:    derived,
		Index:      index,
	}
}

func newTcpTaskTimeout(conn net.Conn, derived ITcpTask, timeout int64) *TcpTask {
	return &TcpTask{
		closed:          -1,
		Conn:            conn,
		stopedChan:      make(chan struct{}, 1),
		stopFlag:        0,
		recvBuff:        NewByteBuffer(),
		sendBuff:        NewByteBuffer(),
		signal:          make(chan struct{}, 1),
		derived:         derived,
		Index:           time.Now().Unix(),
		keepAliveSecond: timeout,
	}
}

func (this *TcpTask) Signal() {
	select {
	case this.signal <- struct{}{}:
	default:
	}
}

func (this *TcpTask) RemoteAddr() string {
	if this.Conn == nil {
		return ""
	}
	return this.Conn.RemoteAddr().String()
}

func (this *TcpTask) LocalAddr() string {
	if this.Conn == nil {
		return ""
	}
	return this.Conn.LocalAddr().String()
}

func (this *TcpTask) Stop() bool {
	atomic.StoreInt32(&this.stopFlag, 1)
	if this.IsClosed() {
		glog.Info("[连接] 关闭失败 ", this.RemoteAddr())
		return false
	}
	select {
	case this.stopedChan <- struct{}{}:
	default:
		glog.Info("[连接] 关闭失败 ", this.RemoteAddr())
		return false
	}
	return true
}

func (this *TcpTask) Start() {
	if !atomic.CompareAndSwapInt32(&this.closed, -1, 0) {
		return
	}
	job := &sync.WaitGroup{}
	job.Add(1)
	go this.sendloop(job)
	go this.recvloop()
	job.Wait()
	glog.Info("[连接] 收到连接 ", this.RemoteAddr(), ",", this.Index)
}

func (this *TcpTask) Close() {
	if !atomic.CompareAndSwapInt32(&this.closed, 0, -1) {
		return
	}
	glog.Info("[连接] 断开连接 ", this.RemoteAddr())
	this.Conn.Close()
	this.recvBuff.Reset()
	this.sendBuff.Reset()
	close(this.stopedChan)
	this.derived.OnClose()
}

func (this *TcpTask) IsClosed() bool {
	return atomic.LoadInt32(&this.closed) != 0
}

func (this *TcpTask) Verify() {
	atomic.StoreUint32(&this.verified, 1)
}

func (this *TcpTask) IsVerified() bool {
	return atomic.LoadUint32(&this.verified) == 1
}

func (this *TcpTask) SendRequest(request *Request) (uint32, bool) {
	if this.IsClosed() {
		return 0, false
	}

	bsize := uint32(len(request.marshalData)) + 9
	this.sendBuff.Append(byte(bsize>>24), byte(bsize>>16), byte(bsize>>8), byte(bsize), byte(request.reqCmd))
	this.request_cbid += 1
	if this.request_cbid >= 0xEFFFFF {
		this.request_cbid = 1
	}
	this.sendBuff.Append(byte(this.request_cbid>>16), byte(this.request_cbid>>8), byte(this.request_cbid))
	this.sendBuff.Append(request.flag)
	this.sendBuff.Append(request.marshalData...)
	this.Signal()
	return this.request_cbid, true
}

func (this *TcpTask) readAtLeast(buff *ByteBuffer, neednum int) error {
	buff.WrGrow(neednum)
	n, err := io.ReadAtLeast(this.Conn, buff.WrBuf(), neednum)
	buff.WrFlip(n)
	return err
}

func (this *TcpTask) recvloop() {
	defer func() {
		if err := recover(); err != nil {
			glog.Error("[异常] ", this.RemoteAddr(), ",", err, "\n", string(debug.Stack()))
		}
	}()
	defer this.Close()

	var (
		neednum   int
		err       error
		totalsize int
		datasize  int
		msgbuff   []byte
	)

	for {
		totalsize = this.recvBuff.RdSize()

		if totalsize < cmd_header_size {
			neednum = cmd_header_size - totalsize
			err = this.readAtLeast(this.recvBuff, neednum)
			if err != nil {
				if !this.IsClosed() {
					glog.Error("[连接] 接收失败 ", this.RemoteAddr(), ",", err)
				}
				return
			}
			totalsize = this.recvBuff.RdSize()
		}

		msgbuff = this.recvBuff.RdBuf()

		datasize = int(int(msgbuff[0])<<24 | int(msgbuff[1])<<16 | int(msgbuff[2])<<8 | int(msgbuff[3]))
		fmt.Println("recv need datasize:", datasize, ", totalsize:", totalsize)
		if datasize <= 0 || datasize > cmd_max_size {
			glog.Error("[连接] 数据超过最大值 ", this.RemoteAddr(), ",", datasize)
			return
		}

		if totalsize < datasize {
			neednum = datasize - totalsize
			err = this.readAtLeast(this.recvBuff, neednum)
			if err != nil {
				glog.Error("[连接] 接收失败 ", this.RemoteAddr(), ",", err)
				return
			}
			msgbuff = this.recvBuff.RdBuf()
		}

		this.derived.ParseMsg(msgbuff[cmd_header_size:datasize])
		this.recvBuff.RdFlip(datasize)
	}
}

func (this *TcpTask) sendloop(job *sync.WaitGroup) {
	defer func() {
		if err := recover(); err != nil {
			glog.Error("[异常] ", err, "\n", string(debug.Stack()))
		}
	}()
	defer this.Close()

	var (
		tmpByte  = NewByteBuffer()
		timeout  *time.Timer
		writenum int
		err      error
	)
	if this.keepAliveSecond != 0 {
		timeout = time.NewTimer(time.Second * time.Duration(this.keepAliveSecond))
	} else {
		timeout = time.NewTimer(time.Second * cmd_verify_time)
	}

	defer timeout.Stop()

	job.Done()

	for {
		select {
		case <-this.signal:
			for {
				this.sendMutex.Lock()
				if this.sendBuff.RdReady() {
					tmpByte.Append(this.sendBuff.RdBuf()[:this.sendBuff.RdSize()]...)
					this.sendBuff.Reset()
				}
				this.sendMutex.Unlock()

				if !tmpByte.RdReady() {
					break
				}

				writenum, err = this.Conn.Write(tmpByte.RdBuf()[:tmpByte.RdSize()])
				if err != nil {
					glog.Error("[连接] 发送失败 ", this.RemoteAddr(), ",", err)
					return
				}
				tmpByte.RdFlip(writenum)
			}
		case <-this.stopedChan:
			return
		case <-timeout.C:
			if !this.IsVerified() {
				glog.Error("[连接] 验证超时 ", this.RemoteAddr(), ",", this.Index)
				return
			}
		}
	}
}

func tcpDial(address string) (*net.TCPConn, error) {
	tcpAddr, err := net.ResolveTCPAddr("tcp4", address)
	if err != nil {
		glog.Error("[连接] 解析失败 ", address)
		return nil, err
	}

	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		glog.Error("[连接] 连接失败 ", address)
		return nil, err
	}

	conn.SetKeepAlive(true)
	conn.SetKeepAlivePeriod(1 * time.Minute)
	conn.SetNoDelay(true)
	conn.SetWriteBuffer(128 * 1024)
	conn.SetReadBuffer(128 * 1024)

	glog.Info("[连接] 连接成功 ", address)
	return conn, nil
}
