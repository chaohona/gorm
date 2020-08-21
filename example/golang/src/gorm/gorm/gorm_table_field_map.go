package gorm

import (
	"strings"

	"github.com/golang/protobuf/proto"
)

var g_tablename_to_tableid_map map[string]int32 = map[string]int32{
    "role": int32(GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE),
}
var g_tableid_to_tablename_map map[int32]string = map[int32]string{
    int32(GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE): "role",
}
func GORM_GetTableId(strTable string) int32 {
	return g_tablename_to_tableid_map[strings.ToLower(strTable)]
}

func GORM_GetTableName(tableId int32) string {
	return g_tableid_to_tablename_map[tableId]
}
func GORM_GetTablePbMsgDefind(tableId int32) (msg proto.Message) {
    switch GORM_PB_TABLE_INDEX(tableId) {
        case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
            return &GORM_PB_TableRole{}
    }
    return nil
}
var GORM_Table_FieldName_To_Id_Map []map[string]int32 = []map[string]int32{
    0: map[string]int32{
        "version": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_VERSION),
        "roleid": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLEID),
        "rolename": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLENAME),
        "level": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_LEVEL),
        "exp": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_EXP),
        "characterid": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CHARACTERID),
        "gold": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_GOLD),
        "offlinetime": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_OFFLINETIME),
        "inited": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_INITED),
        "createtime": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CREATETIME),
        "face": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_FACE),
        "online": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ONLINE),
        "blob": int32(GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_BLOB),
    },
}

func GORM_GetTableFieldId(tableId int32, fieldName string) (int32, GORM_CODE) {
	if tableId <= int32(GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_MIN__) || tableId >= int32(GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_MAX__) {
		return 0, GORM_CODE_INVALID_FIELD
	}
	fieldId, ok := GORM_Table_FieldName_To_Id_Map[tableId-1][strings.ToLower(fieldName)]
	if !ok {
		return 0, GORM_CODE_INVALID_FIELD
	}

	return fieldId, GORM_CODE_OK
}
func GORM_SetTableFieldIntValue(msg proto.Message, tableId int32, fieldId int32, value int64) GORM_CODE {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_VERSION:
            role.Version = uint64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLEID:
            role.Roleid = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_LEVEL:
            role.Level = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_EXP:
            role.Exp = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CHARACTERID:
            role.Characterid = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_GOLD:
            role.Gold = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_OFFLINETIME:
            role.Offlinetime = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_INITED:
            role.Inited = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CREATETIME:
            role.Createtime = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ONLINE:
            role.Online = int64(value)
            return GORM_CODE_OK
        }
    }
    return GORM_CODE_INVALID_FIELD
}
func GORM_SetTableFieldUintValue(msg proto.Message, tableId int32, fieldId int32, value uint64) GORM_CODE {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_VERSION:
            role.Version = uint64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLEID:
            role.Roleid = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_LEVEL:
            role.Level = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_EXP:
            role.Exp = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CHARACTERID:
            role.Characterid = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_GOLD:
            role.Gold = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_OFFLINETIME:
            role.Offlinetime = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_INITED:
            role.Inited = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CREATETIME:
            role.Createtime = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ONLINE:
            role.Online = int64(value)
            return GORM_CODE_OK
        }
    }
    return GORM_CODE_INVALID_FIELD
}
func GORM_SetTableFieldDoubleValue(msg proto.Message, tableId int32, fieldId int32, value float64) GORM_CODE {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_VERSION:
            role.Version = uint64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLEID:
            role.Roleid = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_LEVEL:
            role.Level = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_EXP:
            role.Exp = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CHARACTERID:
            role.Characterid = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_GOLD:
            role.Gold = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_OFFLINETIME:
            role.Offlinetime = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_INITED:
            role.Inited = int32(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CREATETIME:
            role.Createtime = int64(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ONLINE:
            role.Online = int64(value)
            return GORM_CODE_OK
        }
    }
    return GORM_CODE_INVALID_FIELD
}
func GORM_SetTableFieldStrValue(msg proto.Message, tableId int32, fieldId int32, value string) GORM_CODE {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLENAME:
            role.Rolename = string(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_FACE:
            role.Face = string(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_BLOB:
            role.Blob = []byte(value)
            return GORM_CODE_OK
        }
    }
    return GORM_CODE_INVALID_FIELD
}
func GORM_SetTableFieldBytesValue(msg proto.Message, tableId int32, fieldId int32, value []byte) GORM_CODE {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLENAME:
            role.Rolename = string(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_FACE:
            role.Face = string(value)
            return GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_BLOB:
            role.Blob = []byte(value)
            return GORM_CODE_OK
        }
    }
    return GORM_CODE_INVALID_FIELD
}
func GORM_GetFieldIntValueByID(msg proto.Message, tableId int32, fieldId int32) (int64, GORM_CODE) {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_VERSION:
            return int64(role.Version), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLEID:
            return int64(role.Roleid), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_LEVEL:
            return int64(role.Level), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_EXP:
            return int64(role.Exp), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CHARACTERID:
            return int64(role.Characterid), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_GOLD:
            return int64(role.Gold), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_OFFLINETIME:
            return int64(role.Offlinetime), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_INITED:
            return int64(role.Inited), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CREATETIME:
            return int64(role.Createtime), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ONLINE:
            return int64(role.Online), GORM_CODE_OK
        }
    }
    return  0, GORM_CODE_INVALID_FIELD
}
func GORM_GetFieldUintValueByID(msg proto.Message, tableId int32, fieldId int32) (uint64, GORM_CODE) {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_VERSION:
            return uint64(role.Version), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLEID:
            return uint64(role.Roleid), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_LEVEL:
            return uint64(role.Level), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_EXP:
            return uint64(role.Exp), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CHARACTERID:
            return uint64(role.Characterid), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_GOLD:
            return uint64(role.Gold), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_OFFLINETIME:
            return uint64(role.Offlinetime), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_INITED:
            return uint64(role.Inited), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CREATETIME:
            return uint64(role.Createtime), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ONLINE:
            return uint64(role.Online), GORM_CODE_OK
        }
    }
    return  0, GORM_CODE_INVALID_FIELD
}
func GORM_GetFieldDoubleValueByID(msg proto.Message, tableId int32, fieldId int32) (float64, GORM_CODE) {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_VERSION:
            return float64(role.Version), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLEID:
            return float64(role.Roleid), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_LEVEL:
            return float64(role.Level), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_EXP:
            return float64(role.Exp), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CHARACTERID:
            return float64(role.Characterid), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_GOLD:
            return float64(role.Gold), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_OFFLINETIME:
            return float64(role.Offlinetime), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_INITED:
            return float64(role.Inited), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_CREATETIME:
            return float64(role.Createtime), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ONLINE:
            return float64(role.Online), GORM_CODE_OK
        }
    }
    return  0, GORM_CODE_INVALID_FIELD
}
func GORM_GetFieldStrValueByID(msg proto.Message, tableId int32, fieldId int32) (string, GORM_CODE) {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLENAME:
            return string(role.Rolename), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_FACE:
            return string(role.Face), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_BLOB:
            return string(role.Blob), GORM_CODE_OK
        }
    }
    return string(""), GORM_CODE_INVALID_FIELD
}
func GORM_GetFieldBytesValueByID(msg proto.Message, tableId int32, fieldId int32) ([]byte, GORM_CODE) {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        var role *GORM_PB_TableRole =  msg.(*GORM_PB_TableRole)
        switch GORM_PB_ROLE_FIELD_INDEX(fieldId) {
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_ROLENAME:
            return []byte(role.Rolename), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_FACE:
            return []byte(role.Face), GORM_CODE_OK
        case GORM_PB_ROLE_FIELD_INDEX_GORM_PB_FIELD_ROLE_BLOB:
            return []byte(role.Blob), GORM_CODE_OK
        }
    }
    return []byte(""), GORM_CODE_INVALID_FIELD
}
func GORM_AddRecordToReqPbMsgDefine(pbTable *GORM_PB_TABLE, recordMsg proto.Message, tableId int32) GORM_CODE {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        pbTable.Role = recordMsg.(*GORM_PB_TableRole)
    }
    return GORM_CODE_OK
}
func GORM_GetTableSrcPbMsg(tableId int32, pbTable *GORM_PB_TABLE) proto.Message {
    switch GORM_PB_TABLE_INDEX(tableId) {
    case GORM_PB_TABLE_INDEX_GORM_PB_TABLE_IDX_ROLE:
        return pbTable.Role
    }
    return nil
}
