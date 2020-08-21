package gorm

import (
	"fmt"
	define "gorm/gorm"

	"github.com/golang/protobuf/proto"
)

type Record struct {
	msg     proto.Message
	tableId int32
	fieldMode FieldsOpt
}

var (
	FIELDS_OPT_COLLECTIONS_MAX_LEN int = 128
)

type FieldsOpt struct {
	fieldCollections []byte
	usedIdx          int
}

func (this *FieldsOpt) Init() {
	this.fieldCollections = make([]byte, FIELDS_OPT_COLLECTIONS_MAX_LEN)
	this.usedIdx = 0
}

func (this *FieldsOpt) AddField(fieldId int32) define.GORM_CODE {
	if fieldId >= 1024 {
		return define.GORM_CODE_INVALID_FIELD
	}

	var idx int = int(fieldId) >> 3
	this.fieldCollections[int(idx)] |= 1 << (fieldId & 0x07)
	if this.usedIdx <= idx {
		this.usedIdx = idx + 1
	}
	return define.GORM_CODE_OK
}

func FieldMode2FieldList(fieldModes []byte) (result []int32) {
	var len int = len(fieldModes)
	var iField int32 = 0
	var cField byte = 0
	for i := 0; i < len; i++ {
		iField = (int32(i) << 3)
		cField = fieldModes[i]
		if (cField & 0b1) > 0{
            result = append(result, iField)
        }
        if (cField & 0b10) > 0{
            result = append(result, iField+1)
        }
        if (cField & 0b100) > 0{
            result = append(result, iField+2)
        }
        if (cField & 0b1000) > 0{
            result = append(result, iField+3)
        }
        if (cField & 0b10000) > 0{
            result = append(result, iField+4)
        }
        if (cField & 0b100000) > 0{
            result = append(result, iField+5)
        }
        if (cField & 0b1000000) > 0{
            result = append(result, iField+6)
        }
        if (cField & 0b10000000) > 0{
            result = append(result, iField+7)
        }
	}
	return 
}

func (this *FieldsOpt) GetFields() []int32 {
	return FieldMode2FieldList(this.fieldCollections)
}

func (this *Record) Init(tableId int32) define.GORM_CODE {
	this.tableId = tableId
	this.msg = define.GORM_GetTablePbMsgDefind(tableId)
	if this.msg == nil {
		return define.GORM_CODE_INVALID_TABLE
	}
	this.fieldMode.Init()
	return define.GORM_CODE_OK
}

func (this *Record) SetFieldIntValue(field string, value int64) define.GORM_CODE {
	fieldId, retCode := define.GORM_GetTableFieldId(this.tableId, field)
	fmt.Println("SetFieldIntValue tableid:", this.tableId, ", fieldid:", fieldId)
	if retCode != define.GORM_CODE_OK {
		fmt.Println("get fieldid failed.")
		return retCode
	}
	return this.SetFieldIntValueByID(fieldId, value)
}

func (this *Record) SetFieldUintValue(field string, value uint64) define.GORM_CODE {
	fieldId, retCode := define.GORM_GetTableFieldId(this.tableId, field)
	if retCode != define.GORM_CODE_OK {
		return retCode
	}
	return this.SetFieldUintValueByID(fieldId, value)
}

func (this *Record) SetFieldDoubleValue(field string, value float64) define.GORM_CODE {
	fieldId, retCode := define.GORM_GetTableFieldId(this.tableId, field)
	if retCode != define.GORM_CODE_OK {
		return retCode
	}
	return this.SetFieldDoubleValueByID(fieldId, value)
}

func (this *Record) SetFieldStrValue(field string, value string) define.GORM_CODE {
	fieldId, retCode := define.GORM_GetTableFieldId(this.tableId, field)
	if retCode != define.GORM_CODE_OK {
		return retCode
	}
	return this.SetFieldStrValueByID(fieldId, value)
}

func (this *Record) SetFieldIntValueByID(field int32, value int64) (retCode define.GORM_CODE) {
	retCode = define.GORM_SetTableFieldIntValue(this.msg, this.tableId, field, value)
	if retCode != define.GORM_CODE_OK {
		return retCode
	}
	
	return this.fieldMode.AddField(field)
}

func (this *Record) SetFieldUintValueByID(field int32, value uint64) (retCode define.GORM_CODE) {
	retCode = define.GORM_SetTableFieldUintValue(this.msg, this.tableId, field, value)
	if retCode != define.GORM_CODE_OK {
		return retCode
	}
	
	return this.fieldMode.AddField(field)
}

func (this *Record) SetFieldDoubleValueByID(field int32, value float64) (retCode define.GORM_CODE) {
	retCode = define.GORM_SetTableFieldDoubleValue(this.msg, this.tableId, field, value)
	if retCode != define.GORM_CODE_OK {
		return retCode
	}
	
	return this.fieldMode.AddField(field)
}

func (this *Record) SetFieldStrValueByID(field int32, value string) (retCode define.GORM_CODE) {
	retCode = define.GORM_SetTableFieldStrValue(this.msg, this.tableId, field, value)
	if retCode != define.GORM_CODE_OK {
		return retCode
	}
	
	return this.fieldMode.AddField(field)
}

func (this *Record) GetFieldIntValue(field string) (int64, define.GORM_CODE) {
	fieldId, retCode := define.GORM_GetTableFieldId(this.tableId, field)
	if retCode != define.GORM_CODE_OK {
		return 0, retCode
	}
	return this.GetFieldIntValueByID(fieldId)
}

func (this *Record) GetFieldUintValue(field string) (uint64, define.GORM_CODE) {
	fieldId, retCode := define.GORM_GetTableFieldId(this.tableId, field)
	if retCode != define.GORM_CODE_OK {
		return 0, retCode
	}
	return this.GetFieldUintValueByID(fieldId)
}

func (this *Record) GetFieldDoubleValue(field string) (float64, define.GORM_CODE) {
	fieldId, retCode := define.GORM_GetTableFieldId(this.tableId, field)
	if retCode != define.GORM_CODE_OK {
		return 0, retCode
	}
	return this.GetFieldDoubleValueByID(fieldId)
}

func (this *Record) GetFieldStrValue(field string) (string, define.GORM_CODE) {
	fieldId, retCode := define.GORM_GetTableFieldId(this.tableId, field)
	if retCode != define.GORM_CODE_OK {
		return "", retCode
	}
	return this.GetFieldStrValueByID(fieldId)
}

func (this *Record) GetFieldIntValueByID(field int32) (int64, define.GORM_CODE) {
	return define.GORM_GetFieldIntValueByID(this.msg, this.tableId, field)
}

func (this *Record) GetFieldUintValueByID(field int32) (uint64, define.GORM_CODE) {
	return define.GORM_GetFieldUintValueByID(this.msg, this.tableId, field)
}

func (this *Record) GetFieldDoubleValueByID(field int32) (float64, define.GORM_CODE) {
	return define.GORM_GetFieldDoubleValueByID(this.msg, this.tableId, field)
}

func (this *Record) GetFieldStrValueByID(field int32) (string, define.GORM_CODE) {
	return define.GORM_GetFieldStrValueByID(this.msg, this.tableId, field)
}

func (this *Record) GetData() (proto.Message, define.GORM_CODE) {
	return this.msg, define.GORM_CODE_OK
}
