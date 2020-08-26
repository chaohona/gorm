#include "gorm_table_field_map_define.h"
#include "gorm_pb_tables_inc.pb.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_mempool.h"
#include "gorm_hash.h"

namespace gorm{

int GORM_SetTableROLEId2Name(OUT FieldId2Name &mapId2Name);
int GORM_SetTableROLEName2Id(OUT FieldName2Id &mapName2Id);


uint32 GORM_TableHash(int iTableId, const GORM_PB_TABLE &pbTable)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        if (!pbTable.has_role())
            return 0;
        const GORM_PB_Table_role& role = pbTable.role();
        int64 numROLEID = role.roleid();
        char szSrcHash[1024];
        int iTotalLen = snprintf(szSrcHash, 1024, "%ll:%s", numROLEID);
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        pMsgPtr = new GORM_PB_Table_role();
        return GORM_OK;
    }
    }
    return GORM_INVALID_TABLE;
}
bool GORM_TableHasData(GORM_PB_TABLE *pTable, int iTableId)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
        return pTable->has_role();
    }

    return false;
}
int GORM_GetTableSrcPbMsg(int iTableId, GORM_PB_TABLE *pTable, PB_MSG_PTR &pMsgPtr)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        pMsgPtr = pTable->mutable_role();
        return GORM_OK;
    }
    }

    return false;
}
int GORM_AddRecordToReqPbMsgDefine(int iTableId, GORM_PB_TABLE *pPbTable, PB_MSG_PTR pPbMsg)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        GORM_PB_Table_role *pTableMsg = dynamic_cast<GORM_PB_Table_role*>(pPbMsg);
        pPbTable->set_allocated_role(pTableMsg);
        return GORM_OK;
    }
    }
    return GORM_INVALID_TABLE;
}
int GORM_SetTableVersion(OUT TableVersionMap& mapTableVersion)
{
    mapTableVersion[GORM_PB_TABLE_IDX_ROLE] = 1;
    return GORM_OK;
}

int GORM_SetTableName2Id(OUT TableName2Id &mapName2Id)
{
    mapName2Id["role"] = GORM_PB_TABLE_IDX_ROLE;
    return GORM_OK;
}

int GORM_SetTableId2Name(OUT TableId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_TABLE_IDX_ROLE] = "role";
    return GORM_OK;
}

int GORM_SetTableFieldId2Name(int iTableType, OUT FieldId2Name &mapId2Name)
{
    switch (iTableType)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        return GORM_SetTableROLEId2Name(mapId2Name);
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        return GORM_SetTableROLEName2Id(mapName2Id);
    }
    default:
        return GORM_ERROR;
    }

    return GORM_OK;
}
int GORM_SetTableROLEId2Name(OUT FieldId2Name &mapId2Name)
{
    mapId2Name[GORM_PB_FIELD_ROLE_VERSION] = "version";
    mapId2Name[GORM_PB_FIELD_ROLE_ROLEID] = "roleid";
    mapId2Name[GORM_PB_FIELD_ROLE_ROLENAME] = "rolename";
    mapId2Name[GORM_PB_FIELD_ROLE_LEVEL] = "level";
    mapId2Name[GORM_PB_FIELD_ROLE_EXP] = "exp";
    mapId2Name[GORM_PB_FIELD_ROLE_CHARACTERID] = "characterid";
    mapId2Name[GORM_PB_FIELD_ROLE_GOLD] = "gold";
    mapId2Name[GORM_PB_FIELD_ROLE_OFFLINETIME] = "offlinetime";
    mapId2Name[GORM_PB_FIELD_ROLE_INITED] = "inited";
    mapId2Name[GORM_PB_FIELD_ROLE_CREATETIME] = "createtime";
    mapId2Name[GORM_PB_FIELD_ROLE_FACE] = "face";
    mapId2Name[GORM_PB_FIELD_ROLE_ONLINE] = "online";
    return GORM_OK;
}
int GORM_SetTableROLEName2Id(OUT FieldName2Id &mapName2Id)
{
    mapName2Id["version"] = GORM_PB_FIELD_ROLE_VERSION;
    mapName2Id["roleid"] = GORM_PB_FIELD_ROLE_ROLEID;
    mapName2Id["rolename"] = GORM_PB_FIELD_ROLE_ROLENAME;
    mapName2Id["level"] = GORM_PB_FIELD_ROLE_LEVEL;
    mapName2Id["exp"] = GORM_PB_FIELD_ROLE_EXP;
    mapName2Id["characterid"] = GORM_PB_FIELD_ROLE_CHARACTERID;
    mapName2Id["gold"] = GORM_PB_FIELD_ROLE_GOLD;
    mapName2Id["offlinetime"] = GORM_PB_FIELD_ROLE_OFFLINETIME;
    mapName2Id["inited"] = GORM_PB_FIELD_ROLE_INITED;
    mapName2Id["createtime"] = GORM_PB_FIELD_ROLE_CREATETIME;
    mapName2Id["face"] = GORM_PB_FIELD_ROLE_FACE;
    mapName2Id["online"] = GORM_PB_FIELD_ROLE_ONLINE;
    return GORM_OK;
}
int GORM_InitTableColumnInfo_role(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    vector<string> vColumns = {"version","roleid","rolename","level","exp","characterid","gold","offlinetime","inited","createtime","face","online"};
    mapTablesColumnOrder["role"] = vColumns;
    unordered_map<string, GORM_PB_COLUMN_TYPE> mapColumnType = {
        {"version", GORM_PB_COLUMN_TYPE_UINT},
        {"roleid", GORM_PB_COLUMN_TYPE_INT},
        {"rolename", GORM_PB_COLUMN_TYPE_STRING},
        {"level", GORM_PB_COLUMN_TYPE_INT},
        {"exp", GORM_PB_COLUMN_TYPE_INT},
        {"characterid", GORM_PB_COLUMN_TYPE_INT},
        {"gold", GORM_PB_COLUMN_TYPE_INT},
        {"offlinetime", GORM_PB_COLUMN_TYPE_INT},
        {"inited", GORM_PB_COLUMN_TYPE_INT},
        {"createtime", GORM_PB_COLUMN_TYPE_INT},
        {"face", GORM_PB_COLUMN_TYPE_STRING},
        {"online", GORM_PB_COLUMN_TYPE_INT},
    };
    mapTablesColumnInfo["role"] = mapColumnType;
    return GORM_OK;
}
int GORM_InitTableColumnInfo(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo)
{
    if (GORM_InitTableColumnInfo_role(mapTablesColumnOrder, mapTablesColumnInfo))
        return GORM_ERROR;
    return GORM_OK;
}
void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, const char * value, const size_t size)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_rolename((const char*)value, size);
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_face((const char*)value, size);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, const char * value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_rolename((const char*)value);
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_face((const char*)value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int8 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int16 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int32 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int64 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, double value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint16 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint32 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    }
}

void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint64 value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_version(value);
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_roleid(value);
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_level(value);
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_exp(value);
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_characterid(value);
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_gold(value);
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_offlinetime(value);
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_inited(value);
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_createtime(value);
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            return pPbReal->set_online(value);
        }
        }
    }
    }
}

int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, string &value)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->rolename();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->face();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            string strValue = pPbReal->rolename();
            value=(uint8*)strValue.c_str();
            size=strValue.size();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            string strValue = pPbReal->face();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
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
    case GORM_PB_TABLE_IDX_ROLE:
    {
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->version();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->roleid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->level();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->exp();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->characterid();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->gold();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->offlinetime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->inited();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->createtime();
            return GORM_OK;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            GORM_PB_Table_role* pPbReal = dynamic_cast<GORM_PB_Table_role*>(pMsg);
            value = pPbReal->online();
            return GORM_OK;
        }
        }
    }
    }

    return GORM_ERROR;
}


}