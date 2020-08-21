#include "gorm_server_table_define.h"
#include "gorm_table_field_map_define.h"
#include "gorm_server_table_stable.h"
#include "gorm_mysql_conn_pool.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_mempool.h"
#include "gorm_hash.h"
#include "mysql.h"

using namespace gorm;
int GORM_GetSplitTableName(int iTableId, uint32 uiHashCode, char *szOutTableName, int iInBuffLen, int &iUsedBuffLen)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        iUsedBuffLen = snprintf(szOutTableName, iInBuffLen, " role_%d ", uiHashCode%128);
        break;
    }
    default:
        return GORM_INVALID_TABLE;
    }
    return GORM_OK;
}
int GORM_GETVERSION_SET(char *szSQLBegin, int iLen, GORM_CheckDataVerType vType, uint64 ulVersion)
{
    int iDataLen = 0;
    switch (vType)
    {
    case CHECKDATAVERSION_AUTOINCREASE:
    {
        iDataLen = snprintf(szSQLBegin, iLen, " `version`=`version`+1");
        break;
    }
    case NOCHECKDATAVERSION_OVERWRITE:
    {
        iDataLen = snprintf(szSQLBegin, iLen, " `version`=%llu", ulVersion);
        break;
    }
    case NOCHECKDATAVERSION_AUTOINCREASE:
    {
        iDataLen = snprintf(szSQLBegin, iLen, " `version`=`version`+1", ulVersion);
        break;
    }
    }
    return iDataLen;
}
int GORM_GETVERSION_WHERE(char *szSQLBegin, int iLen, GORM_CheckDataVerType vType, uint64 ulVersion)
{
    int iDataLen = 0;
    switch (vType)
    {
    case CHECKDATAVERSION_AUTOINCREASE:
    {
        //iDataLen = snprintf(szSQLBegin, iLen, " and `version`=%llu", ulVersion);
        break;
    }
    case NOCHECKDATAVERSION_OVERWRITE:
    {
        break;
    }
    case NOCHECKDATAVERSION_AUTOINCREASE:
    {
        break;
    }
    }
    return iDataLen;
}
#define ROLEINSERTSQL "insert into role_%d(`version`, `roleid`, `rolename`, `level`, `exp`, `characterid`, `gold`, `offlinetime`, `inited`, `createtime`, `face`, `online`) values (%llu, %lld, \"%s\", %d, %lld, %d, %d, %lld, %d, %lld, \"%s\", %lld);"
int GORM_PackInsertSQLROLE_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_role &table_role, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 250;
    int iTmpLen = 0;

    const uint64 role_version = table_role.version();

    const int64 role_roleid = table_role.roleid();

    const string &role_rolename = table_role.rolename();
    char *sz_role_rolename = "";
    int len_role_rolename = 0;
    GORM_MemPoolData *buffer_role_rolename = nullptr;
    if(role_rolename.size()>0)
    {
        buffer_role_rolename = GORM_MemPool::Instance()->GetData(role_rolename.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_role_rolename->m_uszData, role_rolename.c_str(), role_rolename.size());
        buffer_role_rolename->m_uszData[iTmpLen] = '\0';
        buffer_role_rolename->m_sUsedSize = iTmpLen;
        sz_role_rolename = buffer_role_rolename->m_uszData;
        len_role_rolename = iTmpLen;
    }

    const int32 role_level = table_role.level();

    const int64 role_exp = table_role.exp();

    const int32 role_characterid = table_role.characterid();

    const int32 role_gold = table_role.gold();

    const int64 role_offlinetime = table_role.offlinetime();

    const int32 role_inited = table_role.inited();

    const int64 role_createtime = table_role.createtime();

    const string &role_face = table_role.face();
    char *sz_role_face = "";
    int len_role_face = 0;
    GORM_MemPoolData *buffer_role_face = nullptr;
    if(role_face.size()>0)
    {
        buffer_role_face = GORM_MemPool::Instance()->GetData(role_face.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_role_face->m_uszData, role_face.c_str(), role_face.size());
        buffer_role_face->m_uszData[iTmpLen] = '\0';
        buffer_role_face->m_sUsedSize = iTmpLen;
        sz_role_face = buffer_role_face->m_uszData;
        len_role_face = iTmpLen;
    }

    const int64 role_online = table_role.online();

    int iLen = iSqlLen + 128 + 8 + 8 + len_role_rolename + 8 + 8 + 8 + 8 + 8 + 8 + 8 + len_role_face + 8;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = snprintf(szSQLBegin, iLen, ROLEINSERTSQL, iTableIndex, role_version, role_roleid, sz_role_rolename, role_level, role_exp, role_characterid, role_gold, role_offlinetime, role_inited, role_createtime, sz_role_face, role_online);
    pReqData->m_sUsedSize = iLen;

    if (buffer_role_rolename != nullptr)
        buffer_role_rolename->Release();
    if (buffer_role_face != nullptr)
        buffer_role_face->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLROLE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_role())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_role &table_role = table.role();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
        return GORM_PackInsertSQLROLE_ONE(pMySQLEvent, mysql, iTableIndex, table_role, pReqData);
    }
    return GORM_OK;
}
int GORM_PackInsertSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackInsertSQLROLE(pMySQLEvent, mysql, uiHashValue%128, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

int GORM_PackInsertSQLTable(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_TABLE& table, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        if (!table.has_role())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
        return GORM_PackInsertSQLROLE_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue%128, table.role(), pReqData);
    }
    }
    return GORM_INVALID_TABLE;
}
#define ROLEGETSQL "select `version`, `roleid`, `rolename`, `level`, `exp`, `characterid`, `gold`, `offlinetime`, `inited`, `createtime`, `face`, `online` from role_%d where  `roleid`=%lld;"
int GORM_PackGetSQLROLE_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_role &table_role, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 190;
    int iTmpLen = 0;

    const int64 role_roleid = table_role.roleid();
    int iLen = iSqlLen + 128 + 8 + table_role.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = snprintf(szSQLBegin, iLen, ROLEGETSQL, iTableIndex, role_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define ROLEGETSQL_DEBUG_WHERE " from role_%d where  `roleid`=%lld;"
int GORM_PackGetSQLROLE_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_role &table_role, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("role"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("role table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_role.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["role"];
    if (vectorColumns.size() != columnMap.size())
        return GORM_ERROR;
    for (auto c : vectorColumns)
    {
        auto itr = columnMap.find(c);
        if (itr == columnMap.end())
            return GORM_ERROR;
        if (idx++ != 0)
            iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, ",`%s`", (char*)(c.c_str()));
        else
            iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`%s`", (char*)(c.c_str()));
    }
    const int64 role_roleid = table_role.roleid();
    iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, ROLEGETSQL_DEBUG_WHERE, iTableIndex, role_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLROLE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_role())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_role &table_role = table.role();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLE_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
    return GORM_PackGetSQLROLE_ONE_DEBUG(pMySQLEvent, iTableIndex, table_role, pReqData);
#endif
    return GORM_PackGetSQLROLE_ONE(mysql, iTableIndex, table_role, pReqData);
}
int GORM_PackGetSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackGetSQLROLE(pMySQLEvent, mysql, uiHashValue%128, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define ROLEDELETESQL "delete  from role_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLROLE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_role())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = 66;
    int iTmpLen = 0;

    GORM_PB_Table_role table_role = table.role();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLE_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 role_roleid = table_role.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = snprintf(szSQLBegin, iLen, ROLEDELETESQL, iTableIndex, role_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
    return GORM_OK;
}
int GORM_PackDeleteSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackDeleteSQLROLE(pMySQLEvent, mysql, uiHashValue%128, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define ROLEUPDATESQL "update role_%d set "
#define ROLEUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLROLE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_role())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(ROLEUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_role &table_role = table.role();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLE_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 role_version = table_role.version();
    const int64 role_roleid = table_role.roleid();
    const string &role_rolename = table_role.rolename();
    char *sz_role_rolename = "";
    int len_role_rolename = 0;
    GORM_MemPoolData *buffer_role_rolename = nullptr;
    if(role_rolename.size() > 0)
    {
        buffer_role_rolename = GORM_MemPool::Instance()->GetData(role_rolename.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_role_rolename->m_uszData, role_rolename.c_str(), role_rolename.size());
        buffer_role_rolename->m_uszData[iTmpLen] = 0;
        buffer_role_rolename->m_sUsedSize = iTmpLen;
        sz_role_rolename = buffer_role_rolename->m_uszData;
        len_role_rolename = iTmpLen;
    }

    const int32 role_level = table_role.level();
    const int64 role_exp = table_role.exp();
    const int32 role_characterid = table_role.characterid();
    const int32 role_gold = table_role.gold();
    const int64 role_offlinetime = table_role.offlinetime();
    const int32 role_inited = table_role.inited();
    const int64 role_createtime = table_role.createtime();
    const string &role_face = table_role.face();
    char *sz_role_face = "";
    int len_role_face = 0;
    GORM_MemPoolData *buffer_role_face = nullptr;
    if(role_face.size() > 0)
    {
        buffer_role_face = GORM_MemPool::Instance()->GetData(role_face.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_role_face->m_uszData, role_face.c_str(), role_face.size());
        buffer_role_face->m_uszData[iTmpLen] = 0;
        buffer_role_face->m_sUsedSize = iTmpLen;
        sz_role_face = buffer_role_face->m_uszData;
        len_role_face = iTmpLen;
    }

    const int64 role_online = table_role.online();

    int iWhereLen = iSqlLen + 128  + len_role_rolename + len_role_face + 80;
    GORM_MemPoolData *buffer_role_where = nullptr;
    buffer_role_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_role_where->m_uszData;
    iWhereLen += snprintf(szWhereBegin+iWhereLen,  buffer_role_where->m_sCapacity, ROLEUPDATEWHERESQL , role_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_role_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), role_version);
    buffer_role_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_role_rolename+ len_role_face+80;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = snprintf(szSQLBegin, iLen, ROLEUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), role_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_ROLE_VERSION == iFieldId || GORM_PB_FIELD_ROLE_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `version`=%llu", role_version);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`version`=%llu", role_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `roleid`=%lld", role_roleid);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`roleid`=%lld", role_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `rolename`=\"%s\"", sz_role_rolename);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`rolename`=\"%s\"", sz_role_rolename);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `level`=%d", role_level);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`level`=%d", role_level);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `exp`=%lld", role_exp);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`exp`=%lld", role_exp);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `characterid`=%d", role_characterid);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`characterid`=%d", role_characterid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `gold`=%d", role_gold);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`gold`=%d", role_gold);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `offlinetime`=%lld", role_offlinetime);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`offlinetime`=%lld", role_offlinetime);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `inited`=%d", role_inited);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`inited`=%d", role_inited);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `createtime`=%lld", role_createtime);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`createtime`=%lld", role_createtime);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `face`=\"%s\"", sz_role_face);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`face`=\"%s\"", sz_role_face);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `online`=%lld", role_online);
            else
                iDataLen = snprintf(szSQLBegin, iLen, "`online`=%lld", role_online);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        default:
            return GORM_INVALID_FIELD;
        }
        pReqData->m_sUsedSize += iDataLen;
        if (iLen <= 0)
            break;
    }
    memcpy(pReqData->m_uszData+pReqData->m_sUsedSize, szWhereBegin, iWhereLen);
    pReqData->m_sUsedSize += iWhereLen;
    pReqData->m_uszData[pReqData->m_sUsedSize] = ';';
    pReqData->m_sUsedSize += 1;

    if (buffer_role_rolename != nullptr)
        buffer_role_rolename->Release();
    if (buffer_role_face != nullptr)
        buffer_role_face->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
    return GORM_OK;
}
int GORM_PackUpdateSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackUpdateSQLROLE(pMySQLEvent, mysql, uiHashValue%128, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define ROLEINCREASESQL "update role_%d set "
#define ROLEINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLROLE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_role())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(ROLEINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_role table_role = table.role();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLE_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 role_version = table_role.version();
    const int64 role_roleid = table_role.roleid();
    const int32 role_level = table_role.level();
    const int64 role_exp = table_role.exp();
    const int32 role_characterid = table_role.characterid();
    const int32 role_gold = table_role.gold();
    const int64 role_offlinetime = table_role.offlinetime();
    const int32 role_inited = table_role.inited();
    const int64 role_createtime = table_role.createtime();
    const int64 role_online = table_role.online();

    int iWhereLen = iSqlLen + 128  + 80;
    GORM_MemPoolData *buffer_role_where = nullptr;
    buffer_role_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_role_where->m_uszData;
    iWhereLen += snprintf(szWhereBegin+iWhereLen, buffer_role_where->m_sCapacity, ROLEINCREASEWHERESQL , role_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_role_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), role_version);
    buffer_role_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +112;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, ROLEUPDATESQL, iSqlLen);
    int iDataLen = snprintf(szSQLBegin, iLen, ROLEINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), role_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_ROLE_VERSION == iFieldId || GORM_PB_FIELD_ROLE_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, role_version);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, role_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, role_roleid);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, role_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_LEVEL))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `level`=`level`%c%d", cOpt, role_level);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `level`=`level`%c%d", cOpt, role_level);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_EXP))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `exp`=`exp`%c%lld", cOpt, role_exp);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `exp`=`exp`%c%lld", cOpt, role_exp);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_CHARACTERID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `characterid`=`characterid`%c%d", cOpt, role_characterid);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `characterid`=`characterid`%c%d", cOpt, role_characterid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_GOLD))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `gold`=`gold`%c%d", cOpt, role_gold);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `gold`=`gold`%c%d", cOpt, role_gold);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_OFFLINETIME))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `offlinetime`=`offlinetime`%c%lld", cOpt, role_offlinetime);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `offlinetime`=`offlinetime`%c%lld", cOpt, role_offlinetime);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_INITED))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `inited`=`inited`%c%d", cOpt, role_inited);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `inited`=`inited`%c%d", cOpt, role_inited);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_CREATETIME))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `createtime`=`createtime`%c%lld", cOpt, role_createtime);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `createtime`=`createtime`%c%lld", cOpt, role_createtime);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLE_ONLINE))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = snprintf(szSQLBegin, iLen, ", `online`=`online`%c%lld", cOpt, role_online);
            else
                iDataLen = snprintf(szSQLBegin, iLen, " `online`=`online`%c%lld", cOpt, role_online);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        default:
            continue;
        }
        pReqData->m_sUsedSize += iDataLen;
        if (iLen <= 0)
            break;
    }
    memcpy(pReqData->m_uszData+pReqData->m_sUsedSize, szWhereBegin, iWhereLen);
    pReqData->m_sUsedSize += iWhereLen;
    pReqData->m_uszData[pReqData->m_sUsedSize] = ';';
    pReqData->m_sUsedSize += 1;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
    return GORM_OK;
}
int GORM_PackIncreaseSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackIncreaseSQLROLE(pMySQLEvent, mysql, uiHashValue%128, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define ROLEREPLACESQL "insert into role_%d(`version`, `roleid`, `rolename`, `level`, `exp`, `characterid`, `gold`, `offlinetime`, `inited`, `createtime`, `face`, `online`) values (%llu, %lld, \"%s\", %d, %lld, %d, %d, %lld, %d, %lld, \"%s\", %lld) ON DUPLICATE KEY UPDATE `version`=`version`+1, `rolename`=\"%s\", `level`=%d, `exp`=%lld, `characterid`=%d, `gold`=%d, `offlinetime`=%lld, `inited`=%d, `createtime`=%lld, `face`=\"%s\", `online`=%lld;"
int GORM_PackReplaceSQLROLE_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_role &table_role, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 451;
    int iTmpLen = 0;

    const uint64 role_version = table_role.version();

    const int64 role_roleid = table_role.roleid();

    const string &role_rolename = table_role.rolename();
    char *sz_role_rolename = "";
    int len_role_rolename = 0;
    GORM_MemPoolData *buffer_role_rolename = nullptr;
    if(role_rolename.size()>0)
    {
        buffer_role_rolename = GORM_MemPool::Instance()->GetData(role_rolename.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_role_rolename->m_uszData, role_rolename.c_str(), role_rolename.size());
        buffer_role_rolename->m_uszData[iTmpLen] = '\0';
        buffer_role_rolename->m_sUsedSize = iTmpLen;
        sz_role_rolename = buffer_role_rolename->m_uszData;
        len_role_rolename = iTmpLen;
    }

    const int32 role_level = table_role.level();

    const int64 role_exp = table_role.exp();

    const int32 role_characterid = table_role.characterid();

    const int32 role_gold = table_role.gold();

    const int64 role_offlinetime = table_role.offlinetime();

    const int32 role_inited = table_role.inited();

    const int64 role_createtime = table_role.createtime();

    const string &role_face = table_role.face();
    char *sz_role_face = "";
    int len_role_face = 0;
    GORM_MemPoolData *buffer_role_face = nullptr;
    if(role_face.size()>0)
    {
        buffer_role_face = GORM_MemPool::Instance()->GetData(role_face.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_role_face->m_uszData, role_face.c_str(), role_face.size());
        buffer_role_face->m_uszData[iTmpLen] = '\0';
        buffer_role_face->m_sUsedSize = iTmpLen;
        sz_role_face = buffer_role_face->m_uszData;
        len_role_face = iTmpLen;
    }

    const int64 role_online = table_role.online();

    int iLen = iSqlLen + 128 + 8 + 8 + len_role_rolename + 8 + 8 + 8 + 8 + 8 + 8 + 8 + len_role_face + 8;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = snprintf(szSQLBegin, iLen, ROLEREPLACESQL, iTableIndex, role_version, role_roleid, sz_role_rolename, role_level, role_exp, role_characterid, role_gold, role_offlinetime, role_inited, role_createtime, sz_role_face, role_online, sz_role_rolename,role_level,role_exp,role_characterid,role_gold,role_offlinetime,role_inited,role_createtime, sz_role_face,role_online);
    pReqData->m_sUsedSize = iLen;

    if (buffer_role_rolename != nullptr)
        buffer_role_rolename->Release();
    if (buffer_role_face != nullptr)
        buffer_role_face->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLROLE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_role())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_role &table_role = table.role();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
        return GORM_PackReplaceSQLROLE_One(mysql, iTableIndex, table_role, pReqData);
    }
    return GORM_OK;
}
int GORM_PackReplaceSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackReplaceSQLROLE(pMySQLEvent, mysql, uiHashValue%128, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

int GORM_PackGetSQLTable(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_TABLE& table, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        if (!table.has_role())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
        return GORM_PackGetSQLROLE_ONE(mysql, uiHashValue%128, table.role(), pReqData);
    }
    }
    return GORM_INVALID_TABLE;
}
#define GetByNonPrimaySQL_ROLE "select `version`,`roleid`,`rolename`,`level`,`exp`,`characterid`,`gold`,`offlinetime`,`inited`,`createtime`,`face`,`online` from role_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLROLE_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_role &table_role, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_ROLE);
    int iTotalLen = 64*vFields.size() + iLen + table_role.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = snprintf(szSQLBegin, iLen, GetByNonPrimaySQL_ROLE, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_role.version());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_role.version());
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_role.roleid());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_role.roleid());
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            char *szData = "";
            const string &strData = table_role.rolename();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
                iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`rolename`=`%s`", szData);
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `rolename`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`level`=%d", table_role.level());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `level`=%d", table_role.level());
            break;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`exp`=%lld", table_role.exp());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `exp`=%lld", table_role.exp());
            break;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`characterid`=%d", table_role.characterid());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `characterid`=%d", table_role.characterid());
            break;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`gold`=%d", table_role.gold());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `gold`=%d", table_role.gold());
            break;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`offlinetime`=%lld", table_role.offlinetime());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `offlinetime`=%lld", table_role.offlinetime());
            break;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`inited`=%d", table_role.inited());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `inited`=%d", table_role.inited());
            break;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`createtime`=%lld", table_role.createtime());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `createtime`=%lld", table_role.createtime());
            break;
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            char *szData = "";
            const string &strData = table_role.face();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
                iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`face`=`%s`", szData);
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `face`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`online`=%lld", table_role.online());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `online`=%lld", table_role.online());
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#ifdef GORM_DEBUG
#define GetByNonPrimaySQL_ROLE_DEBUG "select `version`,`roleid`,`rolename`,`level`,`exp`,`characterid`,`gold`,`offlinetime`,`inited`,`createtime`,`face`,`online`"
int GORM_PackGet_By_Non_Primary_KeySQLROLE_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_role &table_role, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_ROLE_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_role.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_ROLE_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["role"];
    for (int i=12; i<vColumns.size(); i++)
    {
        iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, " from role where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_role.version());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_role.version());
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_role.roleid());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_role.roleid());
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            char *szData = "";
            const string &strData = table_role.rolename();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
                iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`rolename`=`%s`", szData);
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `rolename`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`level`=%d", table_role.level());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `level`=%d", table_role.level());
            break;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`exp`=%lld", table_role.exp());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `exp`=%lld", table_role.exp());
            break;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`characterid`=%d", table_role.characterid());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `characterid`=%d", table_role.characterid());
            break;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`gold`=%d", table_role.gold());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `gold`=%d", table_role.gold());
            break;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`offlinetime`=%lld", table_role.offlinetime());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `offlinetime`=%lld", table_role.offlinetime());
            break;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`inited`=%d", table_role.inited());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `inited`=%d", table_role.inited());
            break;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`createtime`=%lld", table_role.createtime());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `createtime`=%lld", table_role.createtime());
            break;
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            char *szData = "";
            const string &strData = table_role.face();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
                iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`face`=`%s`", szData);
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `face`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            if (i==0)
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "`online`=%lld", table_role.online());
            else
                iLen += snprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `online`=%lld", table_role.online());
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#endif
int GORM_PackGet_By_Non_Primary_KeySQLROLE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_role())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_role &table_role = table.role();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLROLE_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_role, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLROLE_One(mysql, iTableIndex, table_role, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
int GORM_PackGet_By_Non_Primary_KeySQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackGet_By_Non_Primary_KeySQLROLE(pMySQLEvent, mysql, uiHashValue%128, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

int GORM_MySQLResult2PbMSG_ROLE(GORM_PB_Table_role *pPbTable, MYSQL_ROW row, unsigned long *lengths)
{
    if (nullptr != row[0] && lengths[0] > 0)
        pPbTable->set_version(strtoull(row[0], (char **)NULL,10));
    else
        pPbTable->set_version(0);

    if (nullptr != row[1] && lengths[1] > 0)
        pPbTable->set_roleid(strtoll(row[1], (char **)NULL,10));
    else
        pPbTable->set_roleid(0);

    if (nullptr != row[2] && lengths[2] > 0)
        pPbTable->set_rolename(row[2], lengths[2]);
    else
        pPbTable->set_rolename("");

    if (nullptr != row[3] && lengths[3] > 0)
        pPbTable->set_level(strtol(row[3], (char **)NULL,10));
    else
        pPbTable->set_level(0);

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_exp(strtoll(row[4], (char **)NULL,10));
    else
        pPbTable->set_exp(0);

    if (nullptr != row[5] && lengths[5] > 0)
        pPbTable->set_characterid(strtol(row[5], (char **)NULL,10));
    else
        pPbTable->set_characterid(0);

    if (nullptr != row[6] && lengths[6] > 0)
        pPbTable->set_gold(strtol(row[6], (char **)NULL,10));
    else
        pPbTable->set_gold(0);

    if (nullptr != row[7] && lengths[7] > 0)
        pPbTable->set_offlinetime(strtoll(row[7], (char **)NULL,10));
    else
        pPbTable->set_offlinetime(0);

    if (nullptr != row[8] && lengths[8] > 0)
        pPbTable->set_inited(strtol(row[8], (char **)NULL,10));
    else
        pPbTable->set_inited(0);

    if (nullptr != row[9] && lengths[9] > 0)
        pPbTable->set_createtime(strtoll(row[9], (char **)NULL,10));
    else
        pPbTable->set_createtime(0);

    if (nullptr != row[10] && lengths[10] > 0)
        pPbTable->set_face(row[10], lengths[10]);
    else
        pPbTable->set_face("");

    if (nullptr != row[11] && lengths[11] > 0)
        pPbTable->set_online(strtoll(row[11], (char **)NULL,10));
    else
        pPbTable->set_online(0);

    return GORM_OK;
}
#ifdef GORM_DEBUG
int GORM_MySQLResult2PbMSG_ROLE_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_role *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_ROLE(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["role"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["role"];
    for (int i=12; i<vTablesColumnOrder.size(); i++)
    {
        GORM_PB_COLUMN *pColumn = pColumns->add_columns();
        string &strColumn = vTablesColumnOrder[i];
        pColumn->set_name(strColumn);
        GORM_PB_COLUMN_VALUE *pColumnValue = pColumn->mutable_value();
        GORM_PB_COLUMN_TYPE iType = mapTablesColumnType[strColumn];
        pColumnValue->set_type(iType);
        switch (iType)
        {
        case GORM_PB_COLUMN_TYPE_INT:
        {
            // 转成int
            if (row[i] == nullptr || lengths[i] == 0)
                pColumnValue->set_intvalue(0);
            else
                pColumnValue->set_intvalue(strtol(row[i], (char **)NULL,10));
            break;
        }
        case GORM_PB_COLUMN_TYPE_UINT:
        {
            if (row[i] == nullptr || lengths[i] == 0)
                pColumnValue->set_uintvalue(0);
            else
                pColumnValue->set_uintvalue(strtoull(row[i], (char **)NULL,10));
            break;
        }
        case GORM_PB_COLUMN_TYPE_DOUBLE:
        {
            char* pEnd;
            if (row[i] == nullptr || lengths[i] == 0)
                pColumnValue->set_uintvalue(0);
            else
                pColumnValue->set_uintvalue(strtod(row[i], &pEnd));
            break;
        }
        case GORM_PB_COLUMN_TYPE_STRING:
        {
            if (row[i] == nullptr || lengths[i] == 0)
                pColumnValue->set_stringvalue("");
            else
                pColumnValue->set_stringvalue(row[i], lengths[i]);
            break;
        }
        }
    }
    return GORM_OK;
}
#endif
int GORM_MySQLResult2PbMSG(GORM_MySQLEvent *pMySQLEvent, int iTableId, GORM_PB_TABLE *pPbTable, MYSQL_ROW row, unsigned long *lengths)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_role *pSrcTable = pPbTable->mutable_role();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_ROLE_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_role *pSrcTable = pPbTable->mutable_role();
        return GORM_MySQLResult2PbMSG_ROLE(pSrcTable, row, lengths);
    #endif
    }
    default:
        return GORM_INVALID_TABLE;
    }

    return GORM_OK;
}
