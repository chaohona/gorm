package gorm

import (
	"fmt"
	"glog"
	define "gorm/gorm"
	"strings"
	"sync/atomic"
)

/*
Server 为和GORM连接的管理类
Init:			和GORM服务器建立连接的初始化函数
Start:			建立连接成功之后，启动服务
Fini:			结束GORM服务
RecvResponse:	获取从GORM服务器返回的结果
SendRequest:	发送请求
*/

type Server struct {
	TcpTask
	strNowAddr   string   // 当前连接的地址
	addrList     []string // 可用地址列表
	responseChan chan *Response
	requestChan  chan *Request
}

// 地址"127.0.0.1:8806/127.0.0.1:8807"
func (this *Server) Init(addrList string) define.GORM_CODE {
	this.addrList = strings.Split(addrList, "/")
	if len(addrList) == 0 {
		glog.Error("[gorm] invalid gorm server addr:", addrList)
		return define.GORM_CODE_ERROR
	}
	this.strNowAddr = this.addrList[0]

	if 0 != this.connectToServer(this.strNowAddr) {
		glog.Error("[gorm] connect to gorm server failed:", this.strNowAddr)
		return define.GORM_CODE_ERROR
	}

	this.responseChan = make(chan *Response, 1024*2)
	this.requestChan = make(chan *Request, 1024)
	return define.GORM_CODE_OK
}

func (this *Server) Start() bool {
	this.TcpTask.Start()
	this.Verify()

	return true
}

func (this *Server) connectToServer(addr string) define.GORM_CODE {
	glog.Info("[gorm] begin to connect to gorm server:", addr)
	conn, err := tcpDial(addr)
	if err != nil {
		glog.Error("[gorm] connect to gorm server failed, gorm server:", addr, ", error info:", err)
		return define.GORM_CODE_ERROR
	}

	this.TcpTask = *newTcpTask(conn, this)

	glog.Info("[gorm] connect to gorm server success:", addr)
	return define.GORM_CODE_OK
}

// TODO
func (this *Server) OnClose() {
	if atomic.LoadInt32(&this.stopFlag) == 1 { // 主动关闭
		close(this.requestChan)
		close(this.responseChan)
	} else {
		// 重置请求与响应

	}
}

func (this *Server) ParseMsg(data []byte) bool {
	fmt.Println("Server.ParseMsg(data len):", len(data))
	// 1、解析消息头
	if len(data) < 6 {
		this.Close()
		return false
	}
	var reqCmd define.GORM_CMD = define.GORM_CMD(data[0])
	var cbID uint32 = uint32(data[1])<<16 | uint32(data[2])<<8 | uint32(data[3])
	_ = cbID
	var errCode byte = data[4]
	_ = errCode
	var flag byte = data[5]
	_ = flag
	fmt.Println("recv rsp from server, cmd:", reqCmd, ", cbID:", cbID, ", errCode:", errCode, ", flag:", flag)
	var request *Request
	select {
	case request = <-this.requestChan:
		if request.cbID != cbID {
			glog.Error("[gorm] recv cbid not match request cbid, req cbid:", request.cbID, ", rsp cbdid:", cbID)
			this.Close()
		}
		fmt.Println("recv rsp for request:", request.reqCmd)
	default:
		fmt.Println("there is no request for rsp")
		this.Close()
	}
	var rsp *Response = &Response{
		cbID:    cbID,
		reqCmd:  reqCmd,
		errCode: define.GORM_CODE(errCode),
		tableId: request.tableId,
	}
	defer func() {
		this.responseChan <- rsp
	}()

	/*if errCode != 0 {
		fmt.Println("errCode:", errCode)
		return true
	}*/

	return rsp.UnPack(data[6:])
}

func (this *Server) Fini() {
	this.Close()
}

func (this *Server) RecvResponse() (rsp *Response) {
	select {
	case rsp = <-this.responseChan:
		return rsp
	default:
	}

	return nil
}

func (this *Server) GetRequestForUpdate(strTable string) (result *Request, ret define.GORM_CODE) {
	var tableId int32 = define.GORM_GetTableId(strTable)
	if tableId == 0 {
		return nil, define.GORM_CODE_INVALID_TABLE
	}
	return this.GetRequestForUpdateByTableID(tableId)
}

func (this *Server) GetRequestForUpdateByTableID(tableId int32) (result *Request, ret define.GORM_CODE) {
	result = &Request{
		tableId: tableId,
		reqCmd:  define.GORM_CMD_GORM_CMD_UPDATE,
	}
	ret = define.GORM_CODE_OK

	if !result.Init() {
		ret = define.GORM_CODE_ERROR
	}
	return
}

func (this *Server) GetRequestForGet(strTable string) (result *Request, ret define.GORM_CODE) {
	var tableId int32 = define.GORM_GetTableId(strTable)
	if tableId == 0 {
		return nil, define.GORM_CODE_INVALID_TABLE
	}
	return this.GetRequestForGetByTableID(tableId)
}

func (this *Server) GetRequestForGetOrInsert(strTable string) (result *Request, ret define.GORM_CODE) {
	var tableId int32 = define.GORM_GetTableId(strTable)
	if tableId == 0 {
		return nil, define.GORM_CODE_INVALID_TABLE
	}
	result, ret = this.GetRequestForGetByTableID(tableId)
	if result != nil {
		result.getFlag = GET_NON_FLAG_INSERT
	}
	return
}

func (this *Server) GetRequestForGetByTableID(tableId int32) (result *Request, ret define.GORM_CODE) {
	result = &Request{
		tableId: tableId,
		reqCmd:  define.GORM_CMD_GORM_CMD_GET,
	}
	ret = define.GORM_CODE_OK

	if !result.Init() {
		ret = define.GORM_CODE_ERROR
	}
	return
}

func (this *Server) GetRequestForDelete(strTable string) (result *Request, ret define.GORM_CODE) {
	var tableId int32 = define.GORM_GetTableId(strTable)
	if tableId == 0 {
		return nil, define.GORM_CODE_INVALID_TABLE
	}
	return this.GetRequestForDeleteByTableID(tableId)
}

func (this *Server) GetRequestForDeleteByTableID(tableId int32) (result *Request, ret define.GORM_CODE) {
	result = &Request{
		tableId: tableId,
		reqCmd:  define.GORM_CMD_GORM_CMD_DELETE,
	}
	ret = define.GORM_CODE_OK

	if !result.Init() {
		ret = define.GORM_CODE_ERROR
	}
	return
}

func (this *Server) GetRequestForInsert(strTable string) (result *Request, ret define.GORM_CODE) {
	var tableId int32 = define.GORM_GetTableId(strTable)
	if tableId == 0 {
		return nil, define.GORM_CODE_INVALID_TABLE
	}
	return this.GetRequestForInsertByTableID(tableId)
}

func (this *Server) GetRequestForInsertByTableID(tableId int32) (result *Request, ret define.GORM_CODE) {
	result = &Request{
		tableId: tableId,
		reqCmd:  define.GORM_CMD_GORM_CMD_INSERT,
	}
	ret = define.GORM_CODE_OK

	if !result.Init() {
		ret = define.GORM_CODE_ERROR
	}
	return
}

func (this *Server) GetRequestForGetByNonPrimaryKey(strTable string) (result *Request, ret define.GORM_CODE) {
	var tableId int32 = define.GORM_GetTableId(strTable)
	if tableId == 0 {
		return nil, define.GORM_CODE_INVALID_TABLE
	}
	return this.GetRequestForGetByNonPrimaryKeyByTableID(tableId)
}

func (this *Server) GetRequestForGetByNonPrimaryKeyByTableID(tableId int32) (result *Request, ret define.GORM_CODE) {
	result = &Request{
		tableId: tableId,
		reqCmd:  define.GORM_CMD_GORM_CMD_GET_BY_NON_PRIMARY_KEY,
	}
	ret = define.GORM_CODE_OK

	if !result.Init() {
		ret = define.GORM_CODE_ERROR
	}
	return
}

// 返回值: 回调id,错误码
func (this *Server) SendRequest(request *Request) (uint32, define.GORM_CODE) {
	if ret := request.PackRequest(); ret != define.GORM_CODE_OK {
		return 0, ret
	}
	this.sendMutex.Lock()
	defer this.sendMutex.Unlock()
	cbID, ret := this.TcpTask.SendRequest(request)
	if !ret {
		return 0, define.GORM_CODE_ERROR
	}

	fmt.Println("send cbid:", cbID)
	request.cbID = cbID
	this.requestChan <- request
	return cbID, define.GORM_CODE_OK
}
