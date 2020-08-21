package gorm

import (
	"fmt"
	define "gorm/gorm"

	"github.com/golang/glog"

	"github.com/golang/protobuf/proto"
)

type GET_NON_FLAG int

const (
	GET_NON_FLAG_RETURN GET_NON_FLAG = 0
	GET_NON_FLAG_INSERT GET_NON_FLAG = 1
)

type Request struct {
	tableId     int32           // 请求对应的表id
	reqCmd      define.GORM_CMD // 请求的类型
	records     []*Record       // 请求表结构对应的数据
	reqMsg      proto.Message
	marshalData []byte
	flag        byte
	cbID        uint32
	getFlag     GET_NON_FLAG
}

func (this *Request) AddRecord() (r *Record, ret define.GORM_CODE) {
	ret = define.GORM_CODE_OK
	r = &Record{}
	ret = r.Init(this.tableId)
	if ret != define.GORM_CODE_OK {
		return nil, ret
	}
	this.records = append(this.records, r)
	return
}

func (this *Request) Init() bool {
	switch this.reqCmd {
	case define.GORM_CMD_GORM_CMD_HEART:
		this.reqMsg = &define.GORM_PB_HEART_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_GET_CLIENT_ID:
		this.reqMsg = &define.GORM_PB_GET_CLIENT_ID_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_INSERT:
		this.reqMsg = &define.GORM_PB_INSERT_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_REPLACE:
		this.reqMsg = &define.GORM_PB_REPLACE_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_INCREASE:
		this.reqMsg = &define.GORM_PB_INCREASE_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_GET:
		this.reqMsg = &define.GORM_PB_GET_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_DELETE:
		this.reqMsg = &define.GORM_PB_DELETE_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_BATCH_GET:
		this.reqMsg = &define.GORM_PB_BATCH_GET_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_GET_BY_PARTKEY:
		this.reqMsg = &define.GORM_PB_GET_BY_PARTKEY_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_UPDATE:
		this.reqMsg = &define.GORM_PB_UPDATE_REQ{}
		return true
	case define.GORM_CMD_GORM_CMD_GET_BY_NON_PRIMARY_KEY:
		this.reqMsg = &define.GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ{}
		return true
	}
	return false
}

func (this *Request) PackRequest() define.GORM_CODE {
	switch this.reqCmd {
	case define.GORM_CMD_GORM_CMD_HEART:
		var reqMsg *define.GORM_PB_HEART_REQ = this.reqMsg.(*define.GORM_PB_HEART_REQ)
		_ = reqMsg
		return define.GORM_CODE_OK
	case define.GORM_CMD_GORM_CMD_GET_CLIENT_ID:
		var reqMsg *define.GORM_PB_GET_CLIENT_ID_REQ = this.reqMsg.(*define.GORM_PB_GET_CLIENT_ID_REQ)
		_ = reqMsg
		return define.GORM_CODE_OK
	case define.GORM_CMD_GORM_CMD_INSERT:
		var reqMsg *define.GORM_PB_INSERT_REQ = this.reqMsg.(*define.GORM_PB_INSERT_REQ)
		if reqMsg == nil {
			panic("insert message nil")
		}
		_ = reqMsg
		reqMsg.Header = &define.GORM_PB_REQ_HEADER{}
		if define.GORM_CODE_OK != this.setReqHeader(reqMsg.Header) {
			return define.GORM_CODE_PACK_REQ_ERROR
		}

		if len(this.records) == 0 {
			return define.GORM_CODE_REQ_NO_RECORDS
		}
		var pbTable *define.GORM_PB_TABLE = &define.GORM_PB_TABLE{}
		reqMsg.Tables = append(reqMsg.Tables, pbTable)
		packRet := define.GORM_AddRecordToReqPbMsgDefine(pbTable, this.records[0].msg, this.tableId)
		if packRet != define.GORM_CODE_OK {
			return packRet
		}
	case define.GORM_CMD_GORM_CMD_REPLACE:
		var reqMsg *define.GORM_PB_REPLACE_REQ = this.reqMsg.(*define.GORM_PB_REPLACE_REQ)
		if reqMsg == nil {
			panic("replace message nil")
		}
		_ = reqMsg
		reqMsg.Header = &define.GORM_PB_REQ_HEADER{}
		if define.GORM_CODE_OK != this.setReqHeader(reqMsg.Header) {
			return define.GORM_CODE_PACK_REQ_ERROR
		}
		var pbTable *define.GORM_PB_TABLE = &define.GORM_PB_TABLE{}
		reqMsg.Tables = append(reqMsg.Tables, pbTable)
		packRet := define.GORM_AddRecordToReqPbMsgDefine(pbTable, this.records[0].msg, this.tableId)
		if packRet != define.GORM_CODE_OK {
			return packRet
		}
	case define.GORM_CMD_GORM_CMD_INCREASE:
		var reqMsg *define.GORM_PB_INCREASE_REQ = this.reqMsg.(*define.GORM_PB_INCREASE_REQ)
		if reqMsg == nil {
			panic("increase message nil")
		}
		_ = reqMsg
		reqMsg.Header = &define.GORM_PB_REQ_HEADER{}
		if define.GORM_CODE_OK != this.setReqHeader(reqMsg.Header) {
			return define.GORM_CODE_PACK_REQ_ERROR
		}
		var pbTable *define.GORM_PB_TABLE = &define.GORM_PB_TABLE{}
		reqMsg.Tables = append(reqMsg.Tables, pbTable)
		packRet := define.GORM_AddRecordToReqPbMsgDefine(pbTable, this.records[0].msg, this.tableId)
		if packRet != define.GORM_CODE_OK {
			return packRet
		}
	case define.GORM_CMD_GORM_CMD_GET:
		var reqMsg *define.GORM_PB_GET_REQ = this.reqMsg.(*define.GORM_PB_GET_REQ)
		if reqMsg == nil {
			panic("get message nil")
		}
		_ = reqMsg
		reqMsg.Header = &define.GORM_PB_REQ_HEADER{}
		if define.GORM_CODE_OK != this.setReqHeader(reqMsg.Header) {
			return define.GORM_CODE_PACK_REQ_ERROR
		}
		reqMsg.GetFlag = int32(this.getFlag)
		var pbTable *define.GORM_PB_TABLE = &define.GORM_PB_TABLE{}
		reqMsg.Table = pbTable
		packRet := define.GORM_AddRecordToReqPbMsgDefine(pbTable, this.records[0].msg, this.tableId)
		if packRet != define.GORM_CODE_OK {
			return packRet
		}
	case define.GORM_CMD_GORM_CMD_DELETE:
		var reqMsg *define.GORM_PB_DELETE_REQ = this.reqMsg.(*define.GORM_PB_DELETE_REQ)
		if reqMsg == nil {
			panic("delete message nil")
		}
		_ = reqMsg
		reqMsg.Header = &define.GORM_PB_REQ_HEADER{}
		if define.GORM_CODE_OK != this.setReqHeader(reqMsg.Header) {
			return define.GORM_CODE_PACK_REQ_ERROR
		}
		var pbTable *define.GORM_PB_TABLE = &define.GORM_PB_TABLE{}
		reqMsg.Table = pbTable
		packRet := define.GORM_AddRecordToReqPbMsgDefine(pbTable, this.records[0].msg, this.tableId)
		if packRet != define.GORM_CODE_OK {
			return packRet
		}
	case define.GORM_CMD_GORM_CMD_BATCH_GET:
		var reqMsg *define.GORM_PB_BATCH_GET_REQ = this.reqMsg.(*define.GORM_PB_BATCH_GET_REQ)
		if reqMsg == nil {
			panic("batch_get message nil")
		}
		_ = reqMsg
		reqMsg.Header = &define.GORM_PB_REQ_HEADER{}
		if define.GORM_CODE_OK != this.setReqHeader(reqMsg.Header) {
			return define.GORM_CODE_PACK_REQ_ERROR
		}
		var pbTable *define.GORM_PB_TABLE = &define.GORM_PB_TABLE{}
		reqMsg.Tables = append(reqMsg.Tables, pbTable)
		packRet := define.GORM_AddRecordToReqPbMsgDefine(pbTable, this.records[0].msg, this.tableId)
		if packRet != define.GORM_CODE_OK {
			return packRet
		}
	case define.GORM_CMD_GORM_CMD_GET_BY_PARTKEY:
		var reqMsg *define.GORM_PB_GET_BY_PARTKEY_REQ = this.reqMsg.(*define.GORM_PB_GET_BY_PARTKEY_REQ)
		if reqMsg == nil {
			panic("get_by_partkey message nil")
		}
		_ = reqMsg
		reqMsg.Header = &define.GORM_PB_REQ_HEADER{}
		if define.GORM_CODE_OK != this.setReqHeader(reqMsg.Header) {
			return define.GORM_CODE_PACK_REQ_ERROR
		}
		var pbTable *define.GORM_PB_TABLE = &define.GORM_PB_TABLE{}
		reqMsg.Tables = append(reqMsg.Tables, pbTable)
		packRet := define.GORM_AddRecordToReqPbMsgDefine(pbTable, this.records[0].msg, this.tableId)
		if packRet != define.GORM_CODE_OK {
			return packRet
		}
	case define.GORM_CMD_GORM_CMD_UPDATE:
		var reqMsg *define.GORM_PB_UPDATE_REQ = this.reqMsg.(*define.GORM_PB_UPDATE_REQ)
		if reqMsg == nil {
			panic("update message nil")
		}
		_ = reqMsg
		reqMsg.Header = &define.GORM_PB_REQ_HEADER{}
		if define.GORM_CODE_OK != this.setReqHeader(reqMsg.Header) {
			return define.GORM_CODE_PACK_REQ_ERROR
		}
		var pbTable *define.GORM_PB_TABLE = &define.GORM_PB_TABLE{}
		reqMsg.Tables = append(reqMsg.Tables, pbTable)
		packRet := define.GORM_AddRecordToReqPbMsgDefine(pbTable, this.records[0].msg, this.tableId)
		if packRet != define.GORM_CODE_OK {
			return packRet
		}
	case define.GORM_CMD_GORM_CMD_GET_BY_NON_PRIMARY_KEY:
		var reqMsg *define.GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ = this.reqMsg.(*define.GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ)
		if reqMsg == nil {
			panic("get_by_non_primary_key message nil")
		}
		_ = reqMsg
		reqMsg.Header = &define.GORM_PB_REQ_HEADER{}
		if define.GORM_CODE_OK != this.setReqHeader(reqMsg.Header) {
			return define.GORM_CODE_PACK_REQ_ERROR
		}
		var pbTable *define.GORM_PB_TABLE = &define.GORM_PB_TABLE{}
		reqMsg.Tables = append(reqMsg.Tables, pbTable)
		packRet := define.GORM_AddRecordToReqPbMsgDefine(pbTable, this.records[0].msg, this.tableId)
		if packRet != define.GORM_CODE_OK {
			return packRet
		}
	}

	var err error
	this.marshalData, err = proto.Marshal(this.reqMsg)
	if err != nil {
		glog.Error("[gorm] proto marshal failed:", err)
		return define.GORM_CODE_PACK_REQ_ERROR
	}
	fmt.Println("protobuf length:", len(this.marshalData))
	return define.GORM_CODE_OK
}

func (this *Request) setReqHeader(header *define.GORM_PB_REQ_HEADER) define.GORM_CODE {
	header.VerPolice = CHECKDATAVERSION_AUTOINCREASE
	header.TableId = this.tableId
	if len(this.records) == 0 {
		return define.GORM_CODE_REQ_NO_RECORDS
	}
	var iLen int = this.records[0].fieldMode.usedIdx
	header.FieldMode = this.records[0].fieldMode.fieldCollections[:iLen]
	return define.GORM_CODE_OK
}
