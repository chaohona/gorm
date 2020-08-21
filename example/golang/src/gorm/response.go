package gorm

import (
	"fmt"
	"glog"
	define "gorm/gorm"

	"github.com/golang/protobuf/proto"
)

type Response struct {
	cbID        uint32
	reqCmd      define.GORM_CMD
	errCode     define.GORM_CODE
	tableId     int32
	rspCodeInfo ResponseCode
	records     []*Record
	nextIdx     int
}

type ResponseCode struct {
	ErrCode   define.GORM_CODE
	DBError   int32
	DBErrInfo string
}

func (this *ResponseCode) Print() {
	fmt.Println("errCode:", this.ErrCode)
	fmt.Println("dbError:", this.DBError)
	fmt.Println("errInfo:", this.DBErrInfo)
}

func (this *Response) GetTableName() (string, define.GORM_CODE) {
	return "", define.GORM_CODE_OK
}

func (this *Response) GetSrcPbMsg() (proto.Message, define.GORM_CODE) {
	return nil, define.GORM_CODE_OK
}

func (this *Response) GetResultCode() *ResponseCode {
	return &this.rspCodeInfo
}

func (this *Response) GetRecord() *Record {
	if len(this.records) != 0 {
		return this.records[0]
	}
	return nil
}

func (this *Response) GetNextRecord() (r *Record, code define.GORM_CODE) {
	if this.nextIdx >= len(this.records) {
		return nil, define.GORM_CODE_NO_MORE_RECORD
	}
	code = define.GORM_CODE_OK
	r = this.records[this.nextIdx]
	this.nextIdx += 1
	return
}

func (this *Response) GetCBID() uint32 {
	return this.cbID
}

func (this *Response) UnPack(data []byte) bool {
	// 2、根据不同的消息解压
	fmt.Println("unpack response for cmd:", this.reqCmd, ", data len:", len(data))
	switch define.GORM_CMD(this.reqCmd) {
	case define.GORM_CMD_GORM_CMD_HEART:
	case define.GORM_CMD_GORM_CMD_GET_CLIENT_ID:
	case define.GORM_CMD_GORM_CMD_INSERT:
		var rspMsg *define.GORM_PB_INSERT_RSP = &define.GORM_PB_INSERT_RSP{}
		err := proto.Unmarshal(data, rspMsg)
		if err != nil {
			glog.Error("[gorm] unmarshal insert rsp failed, cbid:", this.cbID, ", err:", err)
			fmt.Println(err)
			this.errCode = define.GORM_CODE_RSP_UNPACK_FAILED
			return false
		}
		this.unpackRspCode(rspMsg.RetCode)
		if this.rspCodeInfo.ErrCode != define.GORM_CODE_OK {
			return false
		}
		this.unpackRecords(this.tableId, rspMsg.Tables)
	case define.GORM_CMD_GORM_CMD_REPLACE:
		var rspMsg *define.GORM_PB_REPLACE_RSP = &define.GORM_PB_REPLACE_RSP{}
		err := proto.Unmarshal(data, rspMsg)
		if err != nil {
			glog.Error("[gorm] unmarshal insert rsp failed, cbid:", this.cbID)
			this.errCode = define.GORM_CODE_RSP_UNPACK_FAILED
			return false
		}
		this.unpackRspCode(rspMsg.RetCode)
		if this.rspCodeInfo.ErrCode != define.GORM_CODE_OK {
			return false
		}
		this.unpackRecords(this.tableId, rspMsg.Tables)
	case define.GORM_CMD_GORM_CMD_INCREASE:
		var rspMsg *define.GORM_PB_INCREASE_RSP = &define.GORM_PB_INCREASE_RSP{}
		err := proto.Unmarshal(data, rspMsg)
		if err != nil {
			glog.Error("[gorm] unmarshal insert rsp failed, cbid:", this.cbID)
			this.errCode = define.GORM_CODE_RSP_UNPACK_FAILED
			return false
		}
		this.unpackRspCode(rspMsg.RetCode)
		if this.rspCodeInfo.ErrCode != define.GORM_CODE_OK {
			return false
		}
		this.unpackRecords(this.tableId, rspMsg.Tables)
	case define.GORM_CMD_GORM_CMD_GET:
		fmt.Println("unpack get result")
		var rspMsg *define.GORM_PB_GET_RSP = &define.GORM_PB_GET_RSP{}
		err := proto.Unmarshal(data, rspMsg)
		if err != nil {
			glog.Error("[gorm] unmarshal insert rsp failed, cbid:", this.cbID)
			this.errCode = define.GORM_CODE_RSP_UNPACK_FAILED
			return false
		}
		this.unpackRspCode(rspMsg.RetCode)
		if this.rspCodeInfo.ErrCode != define.GORM_CODE_OK {
			return false
		}
		this.unpackRecord(this.tableId, rspMsg.Table)
	case define.GORM_CMD_GORM_CMD_DELETE:
		var rspMsg *define.GORM_PB_DELETE_RSP = &define.GORM_PB_DELETE_RSP{}
		err := proto.Unmarshal(data, rspMsg)
		if err != nil {
			glog.Error("[gorm] unmarshal insert rsp failed, cbid:", this.cbID)
			this.errCode = define.GORM_CODE_RSP_UNPACK_FAILED
			return false
		}
		this.unpackRspCode(rspMsg.RetCode)
		if this.rspCodeInfo.ErrCode != define.GORM_CODE_OK {
			return false
		}
	case define.GORM_CMD_GORM_CMD_BATCH_GET:
		var rspMsg *define.GORM_PB_BATCH_GET_RSP = &define.GORM_PB_BATCH_GET_RSP{}
		err := proto.Unmarshal(data, rspMsg)
		if err != nil {
			glog.Error("[gorm] unmarshal insert rsp failed, cbid:", this.cbID)
			this.errCode = define.GORM_CODE_RSP_UNPACK_FAILED
			return false
		}
		this.unpackRspCode(rspMsg.RetCode)
		if this.rspCodeInfo.ErrCode != define.GORM_CODE_OK {
			return false
		}
		this.unpackRecords(this.tableId, rspMsg.Tables)
	case define.GORM_CMD_GORM_CMD_GET_BY_PARTKEY:
		var rspMsg *define.GORM_PB_GET_BY_PARTKEY_RSP = &define.GORM_PB_GET_BY_PARTKEY_RSP{}
		err := proto.Unmarshal(data, rspMsg)
		if err != nil {
			glog.Error("[gorm] unmarshal insert rsp failed, cbid:", this.cbID)
			this.errCode = define.GORM_CODE_RSP_UNPACK_FAILED
			return false
		}
		this.unpackRspCode(rspMsg.RetCode)
		if this.rspCodeInfo.ErrCode != define.GORM_CODE_OK {
			return false
		}
		this.unpackRecords(this.tableId, rspMsg.Tables)
	case define.GORM_CMD_GORM_CMD_UPDATE:
		var rspMsg *define.GORM_PB_UPDATE_RSP = &define.GORM_PB_UPDATE_RSP{}
		err := proto.Unmarshal(data, rspMsg)
		if err != nil {
			glog.Error("[gorm] unmarshal insert rsp failed, cbid:", this.cbID)
			this.errCode = define.GORM_CODE_RSP_UNPACK_FAILED
			return false
		}
		this.unpackRspCode(rspMsg.RetCode)
		if this.rspCodeInfo.ErrCode != define.GORM_CODE_OK {
			return false
		}
		this.unpackRecords(this.tableId, rspMsg.Tables)
	case define.GORM_CMD_GORM_CMD_GET_BY_NON_PRIMARY_KEY:
		var rspMsg *define.GORM_PB_GET_BY_NON_PRIMARY_KEY_RSP = &define.GORM_PB_GET_BY_NON_PRIMARY_KEY_RSP{}
		err := proto.Unmarshal(data, rspMsg)
		if err != nil {
			glog.Error("[gorm] unmarshal insert rsp failed, cbid:", this.cbID)
			this.errCode = define.GORM_CODE_RSP_UNPACK_FAILED
			return false
		}
		this.unpackRspCode(rspMsg.RetCode)
		if this.rspCodeInfo.ErrCode != define.GORM_CODE_OK {
			return false
		}
		this.unpackRecords(this.tableId, rspMsg.Tables)
	}

	return true
}

func (this *Response) unpackRspCode(rspPbCode *define.GORM_PB_Ret_Code) {
	if rspPbCode == nil {
		this.rspCodeInfo.ErrCode = define.GORM_CODE_ERROR
		return
	}
	fmt.Println(*rspPbCode)
	this.rspCodeInfo.ErrCode = define.GORM_CODE(rspPbCode.Code)
	this.rspCodeInfo.DBError = rspPbCode.DBCode
	this.rspCodeInfo.DBErrInfo = rspPbCode.DBErrInfo
}

func (this *Response) unpackRecord(tableId int32, table *define.GORM_PB_TABLE) {
	var retRecord *Record = &Record{tableId: tableId}
	retRecord.msg = define.GORM_GetTableSrcPbMsg(tableId, table)
	//	fmt.Println("tableId:", tableId, "unpackRecord:", retRecord.msg, ", source table:", table.Account)
	this.records = append(this.records, retRecord)
	return
}

func (this *Response) unpackRecords(tableId int32, pbTables []*define.GORM_PB_TABLE) {
	for _, table := range pbTables {
		_ = table
		var retRecord *Record = &Record{tableId: tableId}
		retRecord.msg = define.GORM_GetTableSrcPbMsg(tableId, table)
		this.records = append(this.records, retRecord)
	}
	return
}
