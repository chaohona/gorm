#include "gorm_inc.h"
#include "gorm_log.h"
#include "gorm_table_field_map.h"
#include "gorm_table_field_map_define.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_define.h"
#include "gorm_msg_helper.h"

namespace gorm{

bool GORM_InvalidTableCheck(int iTableId)
{
    return iTableId > GORM_PB_TABLE_IDX_MIN__ && iTableId < GORM_PB_TABLE_IDX_MAX__;
}


int GORM_GetFieldID(int iTableId, const char* szFiledName, OUT int &iFieldId)
{
    FieldName2Id &name2id = GORM_TableFieldMapInstance::mapName2Id[iTableId];
    // 判断元素是否存在
    auto itr = name2id.find(szFiledName);
    if (itr == name2id.end())
    {
        return GORM_INVALID_FIELD;
    }
    
    iFieldId = itr->second;

    return 0;
}

int GORM_GetFieldID(const char* szTable, const char* szFiledName, OUT int &iFieldId)
{
    int iTableId = 0;
    if (GORM_OK != GORM_GetTableId(szTable, iTableId))
    {
        return GORM_INVALID_TABLE;
    }

    return GORM_GetFieldID(iTableId, szFiledName, iFieldId);
}

int GORM_GetFieldName(int iTableId, int iFieldId, OUT char *&szFieldName)
{
    if (iTableId <= GORM_PB_TABLE_IDX_MIN__ || iTableId >= GORM_PB_TABLE_IDX_MAX__)
    {
        return GORM_INVALID_TABLE;
    }

    FieldId2Name &id2name = GORM_TableFieldMapInstance::mapId2Name[iTableId];
        // 判断元素是否存在
    auto itr = id2name.find(iFieldId);
    if (itr == id2name.end())
    {
        return GORM_INVALID_FIELD;
    }
    
    szFieldName = (char*)itr->second.c_str();

    return GORM_OK;
}

int GORM_GetFieldName(const char* szTable, int iFieldId, OUT char *&szFieldName)
{
    int iTableId = 0;
    if (GORM_OK != GORM_GetTableId(szTable, iTableId))
    {
        return GORM_INVALID_TABLE;
    }

    return GORM_GetFieldName(iTableId, iFieldId, szFieldName);
}

int GORM_GetTableVersion(int iTableId, OUT uint64 &ulVersion)
{
    if (iTableId <= GORM_PB_TABLE_IDX_MIN__ || iTableId >= GORM_PB_TABLE_IDX_MAX__)
    {
        return GORM_INVALID_TABLE;
    }

    ulVersion = GORM_TableFieldMapInstance::mapTableVersion->at(iTableId);
    return GORM_OK;
}

int GORM_GetTableVersion(const char *szTable, OUT uint64 &ulVersion)
{
    int iTableId = 0;
    if (GORM_OK != GORM_GetTableId(szTable, iTableId))
    {
        return GORM_INVALID_TABLE;
    }
    
    return GORM_GetTableVersion(iTableId, ulVersion);
}

int GORM_GetTableId(const char *szTableName, OUT int &iTableId)
{
    iTableId = GORM_TableFieldMapInstance::mapTableName2Id->at(szTableName);

    if (iTableId <= GORM_PB_TABLE_IDX_MIN__)
    {
        return GORM_INVALID_TABLE;
    }
    return GORM_OK;
}

int GORM_GetTableName(int iTableId, OUT char *&szTableName)
{
    if (iTableId <= GORM_PB_TABLE_IDX_MIN__ || iTableId >= GORM_PB_TABLE_IDX_MAX__)
    {
        return GORM_INVALID_TABLE;
    }

    szTableName = (char*)GORM_TableFieldMapInstance::mapTableId2Name->at(iTableId).c_str();
    return GORM_OK;
}

int GORM_AddRecordToReqPbMsg(int iTableId, GORM_PB_TABLE *pPbTable, PB_MSG_PTR pPbMsg)
{
    return GORM_AddRecordToReqPbMsgDefine(iTableId, pPbTable, pPbMsg);
}

#define GORM_SET_CUSTOM_COLUMN_PRE()                                            \
GORM_PB_CUSTEM_COLUMNS *pMsg = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pPbMsg);   \
if (pMsg == nullptr)                                                            \
    return GORM_ERROR;                                                          \
GORM_PB_COLUMN *pColumn = pMsg->add_columns();                                  \
if (nullptr == pColumn)                                                         \
    return GORM_ERROR;                                                          \
pColumn->set_name(szField);                                                     \
GORM_PB_COLUMN_VALUE *pColumnValue = pColumn->mutable_value();                        \
if (pColumnValue == nullptr)                                                          \
    return GORM_ERROR;

int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char* szField, const char * pValue, const size_t sSize)
{
    GORM_SET_CUSTOM_COLUMN_PRE();
    
    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumnValue->set_stringvalue(pValue, sSize);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char* szField, const char * pValue)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumnValue->set_stringvalue(pValue);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, int8 i8Value)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_INT);
    pColumnValue->set_intvalue(i8Value);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, int16 i16Value)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_INT);
    pColumnValue->set_intvalue(i16Value);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, int32 iValue)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_INT);
    pColumnValue->set_intvalue(iValue);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, int64 lValue)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_INT);
    pColumnValue->set_intvalue(lValue);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, double flValue)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_DOUBLE);
    pColumnValue->set_doublevalue(flValue);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, uint8 i8Value)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_UINT);
    pColumnValue->set_uintvalue(i8Value);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, uint16 i16Value)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_UINT);
    pColumnValue->set_uintvalue(i16Value);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, uint32 iValue)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_UINT);
    pColumnValue->set_uintvalue(iValue);
    return GORM_OK;
}
int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, uint64 lValue)
{
    GORM_SET_CUSTOM_COLUMN_PRE();

    pColumnValue->set_type(GORM_PB_COLUMN_TYPE_UINT);
    pColumnValue->set_uintvalue(lValue);
    return GORM_OK;
}

#define GORM_GET_CUSTOM_COLUMN_PRE(szField)                                     \
GORM_PB_CUSTEM_COLUMNS *pMsg = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pPbMsg);   \
GORM_PB_COLUMN *pColumn = nullptr;                                              \
if (pMsg != nullptr)                                                            \
{                                                                               \
    int iSize = pMsg->columns_size();                                           \
    for (int i=0; i<iSize; i++)                                                 \
    {                                                                           \
        pColumn = pMsg->mutable_columns(i);                                     \
        if (pColumn->name() == szField)                                      \
            break;                                                              \
        pColumn = nullptr;                                                      \
    }                                                                           \
}                                                                               \
if (pColumn == nullptr)                                                         \
    return GORM_NO_VALUE;                                                       \
const GORM_PB_COLUMN_VALUE &columnValue = pColumn->value();                           \
GORM_PB_COLUMN_TYPE columnType = columnValue.type();

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT string &strValue)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    if (columnType != GORM_PB_COLUMN_TYPE_STRING)
    {
        return GORM_INVALID_VALUE_TYPE;
    }
    strValue = columnValue.stringvalue();
    return GORM_OK;
}

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char* szField, OUT uint8 *&pValue, OUT size_t &sSize)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    if (columnType != GORM_PB_COLUMN_TYPE_STRING)
    {
        return GORM_INVALID_VALUE_TYPE;
    }
    const string &strValue = columnValue.stringvalue();
    pValue = (uint8*)strValue.c_str();
    sSize = strValue.length();
    return GORM_OK;
}

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, OUT int8 &value)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    switch (columnType)
    {
    case GORM_PB_COLUMN_TYPE_INT:
    {
        value = columnValue.intvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_UINT:
    {
        value = columnValue.uintvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_DOUBLE:
    {
        value = columnValue.doublevalue();
        break;
    }
    default:
        return GORM_INVALID_VALUE_TYPE;
    }
    
    return GORM_OK;
}

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT int16 &value)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    switch (columnType)
    {
    case GORM_PB_COLUMN_TYPE_INT:
    {
        value = columnValue.intvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_UINT:
    {
        value = columnValue.uintvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_DOUBLE:
    {
        value = columnValue.doublevalue();
        break;
    }
    default:
        return GORM_INVALID_VALUE_TYPE;
    }
    
    return GORM_OK;
}

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT int32 &value)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    switch (columnType)
    {
    case GORM_PB_COLUMN_TYPE_INT:
    {
        value = columnValue.intvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_UINT:
    {
        value = columnValue.uintvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_DOUBLE:
    {
        value = columnValue.doublevalue();
        break;
    }
    default:
        return GORM_INVALID_VALUE_TYPE;
    }
    
    return GORM_OK;
}

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT int64 &value)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    switch (columnType)
    {
    case GORM_PB_COLUMN_TYPE_INT:
    {
        value = columnValue.intvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_UINT:
    {
        value = columnValue.uintvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_DOUBLE:
    {
        value = columnValue.doublevalue();
        break;
    }
    default:
        return GORM_INVALID_VALUE_TYPE;
    }
    
    return GORM_OK;
}

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT uint8 &value)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    switch (columnType)
    {
    case GORM_PB_COLUMN_TYPE_INT:
    {
        value = columnValue.intvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_UINT:
    {
        value = columnValue.uintvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_DOUBLE:
    {
        value = columnValue.doublevalue();
        break;
    }
    default:
        return GORM_INVALID_VALUE_TYPE;
    }
    
    return GORM_OK;
}

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT uint16 &value)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    switch (columnType)
    {
    case GORM_PB_COLUMN_TYPE_INT:
    {
        value = columnValue.intvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_UINT:
    {
        value = columnValue.uintvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_DOUBLE:
    {
        value = columnValue.doublevalue();
        break;
    }
    default:
        return GORM_INVALID_VALUE_TYPE;
    }
    
    return GORM_OK;
}

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT uint32 &value)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    switch (columnType)
    {
    case GORM_PB_COLUMN_TYPE_INT:
    {
        value = columnValue.intvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_UINT:
    {
        value = columnValue.uintvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_DOUBLE:
    {
        value = columnValue.doublevalue();
        break;
    }
    default:
        return GORM_INVALID_VALUE_TYPE;
    }
    
    return GORM_OK;
}

int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT uint64 &value)
{
    GORM_GET_CUSTOM_COLUMN_PRE(szField);
    switch (columnType)
    {
    case GORM_PB_COLUMN_TYPE_INT:
    {
        value = columnValue.intvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_UINT:
    {
        value = columnValue.uintvalue();
        break;
    }
    case GORM_PB_COLUMN_TYPE_DOUBLE:
    {
        value = columnValue.doublevalue();
        break;
    }
    default:
        return GORM_INVALID_VALUE_TYPE;
    }
    
    return GORM_OK;
}

FieldId2Name *GORM_TableFieldMapInstance::mapId2Name = nullptr;
FieldName2Id *GORM_TableFieldMapInstance::mapName2Id = nullptr;
TableName2Id *GORM_TableFieldMapInstance::mapTableName2Id = nullptr;
TableId2Name *GORM_TableFieldMapInstance::mapTableId2Name = nullptr;
TableVersionMap *GORM_TableFieldMapInstance::mapTableVersion = nullptr;
PB_MSG_PTR GORM_TableFieldMapInstance::pTableInfo = nullptr;

GORM_TableFieldMapInstance* GORM_TableFieldMapInstance::pInstance = new GORM_TableFieldMapInstance;

GORM_TableFieldMapInstance* GORM_TableFieldMapInstance::Instance()
{
	return pInstance;
}

int GORM_TableFieldMapInstance::Init(GORM_Log *pLogger)
{
    if (mapId2Name != nullptr)
    {
        delete []mapId2Name;
    }
    mapId2Name = new FieldId2Name[GORM_DB_MAX_TABLE_NUM];
    
    if (mapName2Id != nullptr)
    {
        delete []mapName2Id;
    }
    mapName2Id = new FieldName2Id[GORM_DB_MAX_TABLE_NUM];
    
    if (mapTableId2Name != nullptr)
    {
        delete mapTableId2Name;
    }
    mapTableId2Name = new TableId2Name();
    
    if (mapTableName2Id != nullptr)
    {
        delete mapTableName2Id;
    }
    mapTableName2Id = new TableName2Id();
            
    if (mapTableVersion != nullptr)
    {
        delete mapTableVersion;
    }
    mapTableVersion= new TableVersionMap();

    if (pTableInfo != nullptr)
    {
        delete pTableInfo;
        pTableInfo = nullptr;
    }
    if (GORM_OK != GetPbReqMsg(GORM_CMD_HAND_SHAKE, pTableInfo))
        return GORM_ERROR;
    if (GORM_OK != GORM_InitTableSchemaInfo(pTableInfo))
        return GORM_ERROR;

    // 设置每一个表明的映射关系
    for (int i=1; i<GORM_PB_TABLE_IDX_MAX__; i++)
    {
        if (GORM_OK != GORM_SetTableFieldId2Name(i, mapId2Name[i]))
        {
            GORM_CUSTOM_LOGE(pLogger, "set table filed id 2 name map failed.");
            return GORM_ERROR;
        }
        if (GORM_OK != GORM_SetTableFieldName2Id(i, mapName2Id[i]))
        {
            GORM_CUSTOM_LOGE(pLogger, "set table filed id 2 name map failed.");
            return GORM_ERROR;
        }
        if (GORM_OK != GORM_SetTableName2Id(*mapTableName2Id))
        {
            GORM_CUSTOM_LOGE(pLogger, "set table name 2 id failed.");
            return GORM_ERROR;
        }
        if (GORM_OK != GORM_SetTableId2Name(*mapTableId2Name))
        {
            GORM_CUSTOM_LOGE(pLogger, "set table id 2 name failed.");
            return GORM_ERROR;
        }
        if (GORM_OK != GORM_SetTableVersion(*mapTableVersion))
        {
            GORM_CUSTOM_LOGE(pLogger, "set table version failed.");
            return GORM_ERROR;
        }
    }
    return GORM_OK;
}


}

