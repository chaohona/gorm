#include "gorm_table_field_map_define.h"
#include "gorm_pb_tables_inc.pb.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_mempool.h"
#include "gorm_hash.h"

namespace gorm{

int GORM_SetTableCURRENCYId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableCURRENCYName2Id(OUT FieldName2Id &mapName2Id);
int GORM_SetTableCYCLEEVENTId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableCYCLEEVENTName2Id(OUT FieldName2Id &mapName2Id);


int GORM_InitTableSchemaInfo(PB_MSG_PTR pMsgPtr)
{
    GORM_PB_HAND_SHAKE_REQ *pHandShake = dynamic_cast<GORM_PB_HAND_SHAKE_REQ*>(pMsgPtr);
    if (pHandShake == nullptr)
        return GORM_ERROR;
    GORM_PB_TABLE_SCHEMA_INFO *pInfo;
    GORM_PB_TABLE_SCHEMA_INFO_COLUMN *pColumn;
    pHandShake->mutable_header();
    pHandShake->set_version(1);
    pHandShake->set_md5(0);
    // for table currency
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("currency");
    pInfo->set_tableidx(1);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("snakeid");
    pColumn->set_typedesc("int32");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT32);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("currency1");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("currency2");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("currency3");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("currency4");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    // for table cycleevent
    pInfo = pHandShake->add_schemas();
    if (pInfo == nullptr)
        return GORM_ERROR;
    pInfo->set_version(1);
    pInfo->set_tablename("cycleevent");
    pInfo->set_tableidx(2);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("version");
    pColumn->set_typedesc("uint64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_UINT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("roleid");
    pColumn->set_typedesc("int64");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_INT64);
    pColumn = pInfo->add_columns();
    if (pColumn == nullptr)
        return GORM_ERROR;
    pColumn->set_version(0);
    pColumn->set_name("events");
    pColumn->set_typedesc("string");
    pColumn->set_type(GORM_PB_COLUMN_TYPE_STRING);
    return GORM_OK;
}
uint32 GORM_TableHash(int iTableId, const GORM_PB_TABLE &pbTable)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        if (!pbTable.has_currency())
            return 0;
        const GORM_PB_Table_currency& currency = pbTable.currency();
        int64 tmp_ROLEID = currency.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        if (!pbTable.has_cycleevent())
            return 0;
        const GORM_PB_Table_cycleevent& cycleevent = pbTable.cycleevent();
        int64 tmp_ROLEID = cycleevent.roleid();
        char szSrcHash[1024];
        int iTotalLen = GORM_SafeSnprintf(szSrcHash, 1024, "%lld_" , tmp_ROLEID);
        if (iTotalLen > 1024)
            iTotalLen = 1024;
        return GORM_Hash::Crc32_1((const char*)szSrcHash, iTotalLen);
    }
    default:
        return 0;
    }
    return 0;
}

int GORM_GetCustomPbMsg(PB_MSG_PTR &pMsgPtr)
{
    pMsgPtr = new GORM_PB_CUSTEM_COLUMNS();
    return GORM_OK;
}
int GetTablePbMsgDefine(int iTableId, PB_MSG_PTR &pMsgPtr)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        pMsgPtr = new GORM_PB_Table_currency();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        pMsgPtr = new GORM_PB_Table_cycleevent();
        return GORM_OK;
    }
    }
    return GORM_INVALID_TABLE;
}
bool GORM_TableHasData(GORM_PB_TABLE *pTable, int iTableId)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return pTable->has_currency();
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return pTable->has_cycleevent();
    }

    return false;
}
int GORM_GetTableSrcPbMsg(int iTableId, GORM_PB_TABLE *pTable, PB_MSG_PTR &pMsgPtr)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        pMsgPtr = pTable->mutable_currency();
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        pMsgPtr = pTable->mutable_cycleevent();
        return GORM_OK;
    }
    }

    return false;
}
int GORM_AddRecordToReqPbMsgDefine(int iTableId, GORM_PB_TABLE *pPbTable, PB_MSG_PTR pPbMsg)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        GORM_PB_Table_currency *pTableMsg = dynamic_cast<GORM_PB_Table_currency*>(pPbMsg);
        pPbTable->set_allocated_currency(pTableMsg);
        return GORM_OK;
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        GORM_PB_Table_cycleevent *pTableMsg = dynamic_cast<GORM_PB_Table_cycleevent*>(pPbMsg);
        pPbTable->set_allocated_cycleevent(pTableMsg);
        return GORM_OK;
    }
    }
    return GORM_INVALID_TABLE;
}
int GORM_SetTableVersion(OUT TableVersionMap& mapTableVersion)
{
    mapTableVersion[GORM_PB_TABLE_IDX_CURRENCY] = 1;
    mapTableVersion[GORM_PB_TABLE_IDX_CYCLEEVENT] = 1;
    return GORM_OK;
}

int GORM_SetTableName2Id(OUT TableName2Id &mapName2Id)
{
    mapName2Id["currency"] = GORM_PB_TABLE_IDX_CURRENCY;
    mapName2Id["cycleevent"] = GORM_PB_TABLE_IDX_CYCLEEVENT;
    return GORM_OK;
}

int GORM_SetTableId2Name(OUT TableId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_TABLE_IDX_CURRENCY] = "currency";
    mapId2Name[GORM_PB_TABLE_IDX_CYCLEEVENT] = "cycleevent";
    return GORM_OK;
}

int GORM_SetTableFieldId2Name(int iTableType, OUT FieldId2Name &mapId2Name)
{
    switch (iTableType)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        return GORM_SetTableCURRENCYId2Name(mapId2Name);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        return GORM_SetTableCYCLEEVENTId2Name(mapId2Name);
    }
    default:
        return GORM_ERROR;
    }

    return GORM_OK;
}
int GORM_SetTableFieldName2Id(int iTableType, OUT FieldName2Id &mapName2Id)
{
    switch (iTableType)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        return GORM_SetTableCURRENCYName2Id(mapName2Id);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        return GORM_SetTableCYCLEEVENTName2Id(mapName2Id);
    }
    default:
        return GORM_ERROR;
    }

    return GORM_OK;
}
int GORM_SetTableCURRENCYId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_CURRENCY_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_CURRENCY_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_CURRENCY_SNAKEID] = "snakeid";
    mapId2Name[GORM_PB_FIELD_CURRENCY_CURRENCY1] = "currency1";
    mapId2Name[GORM_PB_FIELD_CURRENCY_CURRENCY2] = "currency2";
    mapId2Name[GORM_PB_FIELD_CURRENCY_CURRENCY3] = "currency3";
    mapId2Name[GORM_PB_FIELD_CURRENCY_CURRENCY4] = "currency4";
    return GORM_OK;
}
int GORM_SetTableCYCLEEVENTId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_CYCLEEVENT_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_CYCLEEVENT_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_CYCLEEVENT_EVENTS] = "events";
    return GORM_OK;
}
int GORM_SetTableCURRENCYName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_CURRENCY_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_CURRENCY_ROLEID;
    mapName2Id["snakeid"] = GORM_PB_FIELD_CURRENCY_SNAKEID;
    mapName2Id["currency1"] = GORM_PB_FIELD_CURRENCY_CURRENCY1;
    mapName2Id["currency2"] = GORM_PB_FIELD_CURRENCY_CURRENCY2;
    mapName2Id["currency3"] = GORM_PB_FIELD_CURRENCY_CURRENCY3;
    mapName2Id["currency4"] = GORM_PB_FIELD_CURRENCY_CURRENCY4;
    return GORM_OK;
}
int GORM_SetTableCYCLEEVENTName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_CYCLEEVENT_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_CYCLEEVENT_ROLEID;
    mapName2Id["events"] = GORM_PB_FIELD_CYCLEEVENT_EVENTS;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_currency(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","snakeid","currency1","currency2","currency3","currency4"};
    mapTablesColumnOrder["currency"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"snakeid", GORM_PB_COLUMN_TYPE_INT},
        {"currency1", GORM_PB_COLUMN_TYPE_STRING},
        {"currency2", GORM_PB_COLUMN_TYPE_STRING},
        {"currency3", GORM_PB_COLUMN_TYPE_STRING},
        {"currency4", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["currency"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_cycleevent(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","events"};
    mapTablesColumnOrder["cycleevent"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"events", GORM_PB_COLUMN_TYPE_STRING},
    };
    mapTablesColumnInfo["cycleevent"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    if (GORM_InitTableColumnInfo_currency(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    if (GORM_InitTableColumnInfo_cycleevent(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    return GORM_OK;
}
void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, const char * value, const size_t size)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency1((const char*)value, size);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency2((const char*)value, size);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency3((const char*)value, size);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency4((const char*)value, size);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_events((const char*)value, size);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, const char * value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency1((const char*)value);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency2((const char*)value);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency3((const char*)value);
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_currency4((const char*)value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_events((const char*)value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int8 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int16 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int32 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int64 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, double value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint16 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint32 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint64 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            return pPbReal->set_snakeid(value);
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        }
    }
    }
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, string &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->currency1();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->currency2();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->currency3();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->currency4();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->events();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 *&value, size_t &size)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            string strValue = pPbReal->currency1();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            string strValue = pPbReal->currency2();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            string strValue = pPbReal->currency3();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            string strValue = pPbReal->currency4();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            string strValue = pPbReal->events();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int8 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int16 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int32 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int64 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, double &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint16 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint32 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint64 &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            GORM_PB_Table_currency* pPbReal = dynamic_cast<GORM_PB_Table_currency*>(pMsg);
            value = pPbReal->snakeid();
            return GORM_OK;
        }
        }
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            GORM_PB_Table_cycleevent* pPbReal = dynamic_cast<GORM_PB_Table_cycleevent*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}


}