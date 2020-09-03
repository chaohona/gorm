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
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " currency_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " cycleevent_%d ", uiHashCode%2);
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
        iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`+1");
        break;
    }
    case NOCHECKDATAVERSION_OVERWRITE:
    {
        iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=%llu", ulVersion);
        break;
    }
    case NOCHECKDATAVERSION_AUTOINCREASE:
    {
        iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`+1", ulVersion);
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
        //iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " and `version`=%llu", ulVersion);
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
#define CURRENCYINSERTSQL "insert into currency_%d(`version`, `roleid`, `snakeid`, `currency1`, `currency2`, `currency3`, `currency4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\");"
int GORM_PackInsertSQLCURRENCY_ONE(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_currency &table_currency, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 193;
    int iTmpLen = 0;

    const uint64 currency_version = table_currency.version();

    const int64 currency_roleid = table_currency.roleid();

    const int32 currency_snakeid = table_currency.snakeid();

    const string &currency_currency1 = table_currency.currency1();
    char *sz_currency_currency1 = "";
    int len_currency_currency1 = 0;
    GORM_MemPoolData *buffer_currency_currency1 = nullptr;
    if(currency_currency1.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency1, currency_currency1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency1->m_uszData, currency_currency1.c_str(), currency_currency1.size());
        buffer_currency_currency1->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency1->m_sUsedSize = iTmpLen;
        sz_currency_currency1 = buffer_currency_currency1->m_uszData;
        len_currency_currency1 = iTmpLen;
    }

    const string &currency_currency2 = table_currency.currency2();
    char *sz_currency_currency2 = "";
    int len_currency_currency2 = 0;
    GORM_MemPoolData *buffer_currency_currency2 = nullptr;
    if(currency_currency2.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency2, currency_currency2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency2->m_uszData, currency_currency2.c_str(), currency_currency2.size());
        buffer_currency_currency2->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency2->m_sUsedSize = iTmpLen;
        sz_currency_currency2 = buffer_currency_currency2->m_uszData;
        len_currency_currency2 = iTmpLen;
    }

    const string &currency_currency3 = table_currency.currency3();
    char *sz_currency_currency3 = "";
    int len_currency_currency3 = 0;
    GORM_MemPoolData *buffer_currency_currency3 = nullptr;
    if(currency_currency3.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency3, currency_currency3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency3->m_uszData, currency_currency3.c_str(), currency_currency3.size());
        buffer_currency_currency3->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency3->m_sUsedSize = iTmpLen;
        sz_currency_currency3 = buffer_currency_currency3->m_uszData;
        len_currency_currency3 = iTmpLen;
    }

    const string &currency_currency4 = table_currency.currency4();
    char *sz_currency_currency4 = "";
    int len_currency_currency4 = 0;
    GORM_MemPoolData *buffer_currency_currency4 = nullptr;
    if(currency_currency4.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency4, currency_currency4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency4->m_uszData, currency_currency4.c_str(), currency_currency4.size());
        buffer_currency_currency4->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency4->m_sUsedSize = iTmpLen;
        sz_currency_currency4 = buffer_currency_currency4->m_uszData;
        len_currency_currency4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_currency_currency1 + len_currency_currency2 + len_currency_currency3 + len_currency_currency4;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CURRENCYINSERTSQL, iTableIndex, currency_version, currency_roleid, currency_snakeid, sz_currency_currency1, sz_currency_currency2, sz_currency_currency3, sz_currency_currency4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_currency_currency1 != nullptr)
        buffer_currency_currency1->Release();
    if (buffer_currency_currency2 != nullptr)
        buffer_currency_currency2->Release();
    if (buffer_currency_currency3 != nullptr)
        buffer_currency_currency3->Release();
    if (buffer_currency_currency4 != nullptr)
        buffer_currency_currency4->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLCURRENCY(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_currency())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_currency &table_currency = table.currency();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "currency", table.custom_columns());
#endif
        return GORM_PackInsertSQLCURRENCY_ONE(pMemPool, pMySQLEvent, mysql, iTableIndex, table_currency, pReqData);
    }
    return GORM_OK;
}
#define CYCLEEVENTINSERTSQL "insert into cycleevent_%d(`version`, `roleid`, `events`) values (%llu, %lld, \"%s\");"
int GORM_PackInsertSQLCYCLEEVENT_ONE(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 116;
    int iTmpLen = 0;

    const uint64 cycleevent_version = table_cycleevent.version();

    const int64 cycleevent_roleid = table_cycleevent.roleid();

    const string &cycleevent_events = table_cycleevent.events();
    char *sz_cycleevent_events = "";
    int len_cycleevent_events = 0;
    GORM_MemPoolData *buffer_cycleevent_events = nullptr;
    if(cycleevent_events.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_cycleevent_events, cycleevent_events.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_cycleevent_events->m_uszData, cycleevent_events.c_str(), cycleevent_events.size());
        buffer_cycleevent_events->m_uszData[iTmpLen] = '\0';
        buffer_cycleevent_events->m_sUsedSize = iTmpLen;
        sz_cycleevent_events = buffer_cycleevent_events->m_uszData;
        len_cycleevent_events = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + len_cycleevent_events;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTINSERTSQL, iTableIndex, cycleevent_version, cycleevent_roleid, sz_cycleevent_events);
    pReqData->m_sUsedSize = iLen;

    if (buffer_cycleevent_events != nullptr)
        buffer_cycleevent_events->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLCYCLEEVENT(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_cycleevent())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_cycleevent &table_cycleevent = table.cycleevent();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
#endif
        return GORM_PackInsertSQLCYCLEEVENT_ONE(pMemPool, pMySQLEvent, mysql, iTableIndex, table_cycleevent, pReqData);
    }
    return GORM_OK;
}
int GORM_PackInsertSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackInsertSQLCURRENCY(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackInsertSQLCYCLEEVENT(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

int GORM_PackInsertSQLTable(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_TABLE& table, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        if (!table.has_currency())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "currency", table.custom_columns());
#endif
        return GORM_PackInsertSQLCURRENCY_ONE(pMemPool, pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.currency(), pReqData);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        if (!table.has_cycleevent())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
#endif
        return GORM_PackInsertSQLCYCLEEVENT_ONE(pMemPool, pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.cycleevent(), pReqData);
    }
    }
    return GORM_INVALID_TABLE;
}
#define CURRENCYGETSQL "select `version`, `roleid`, `snakeid`, `currency1`, `currency2`, `currency3`, `currency4` from currency_%d where  `roleid`=%lld;"
int GORM_PackGetSQLCURRENCY_ONE(shared_ptr<GORM_MemPool> &pMemPool, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_currency &table_currency, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 153;
    int iTmpLen = 0;

    const int64 currency_roleid = table_currency.roleid();
    int iLen = iSqlLen + 128 + 8 + table_currency.ByteSizeLong();
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CURRENCYGETSQL, iTableIndex, currency_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define CURRENCYGETSQL_DEBUG_WHERE " from currency_%d where  `roleid`=%lld;"
int GORM_PackGetSQLCURRENCY_ONE_DEBUG(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_currency &table_currency, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("currency"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("currency table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_currency.ByteSizeLong();
    int iLen = 7;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["currency"];
    if (vectorColumns.size() != columnMap.size())
        return GORM_ERROR;
    for (auto c : vectorColumns)
    {
        auto itr = columnMap.find(c);
        if (itr == columnMap.end())
            return GORM_ERROR;
        if (idx++ != 0)
            iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ",`%s`", (char*)(c.c_str()));
        else
            iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`%s`", (char*)(c.c_str()));
    }
    const int64 currency_roleid = table_currency.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, CURRENCYGETSQL_DEBUG_WHERE, iTableIndex, currency_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLCURRENCY(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_currency())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_currency &table_currency = table.currency();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_CURRENCY_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "currency", table.custom_columns());
    return GORM_PackGetSQLCURRENCY_ONE_DEBUG(pMemPool, pMySQLEvent, iTableIndex, table_currency, pReqData);
#endif
    return GORM_PackGetSQLCURRENCY_ONE(pMemPool, mysql, iTableIndex, table_currency, pReqData);
}
#define CYCLEEVENTGETSQL "select `version`, `roleid`, `events` from cycleevent_%d where  `roleid`=%lld;"
int GORM_PackGetSQLCYCLEEVENT_ONE(shared_ptr<GORM_MemPool> &pMemPool, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 104;
    int iTmpLen = 0;

    const int64 cycleevent_roleid = table_cycleevent.roleid();
    int iLen = iSqlLen + 128 + 8 + table_cycleevent.ByteSizeLong();
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTGETSQL, iTableIndex, cycleevent_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define CYCLEEVENTGETSQL_DEBUG_WHERE " from cycleevent_%d where  `roleid`=%lld;"
int GORM_PackGetSQLCYCLEEVENT_ONE_DEBUG(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("cycleevent"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("cycleevent table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_cycleevent.ByteSizeLong();
    int iLen = 7;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["cycleevent"];
    if (vectorColumns.size() != columnMap.size())
        return GORM_ERROR;
    for (auto c : vectorColumns)
    {
        auto itr = columnMap.find(c);
        if (itr == columnMap.end())
            return GORM_ERROR;
        if (idx++ != 0)
            iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ",`%s`", (char*)(c.c_str()));
        else
            iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`%s`", (char*)(c.c_str()));
    }
    const int64 cycleevent_roleid = table_cycleevent.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, CYCLEEVENTGETSQL_DEBUG_WHERE, iTableIndex, cycleevent_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLCYCLEEVENT(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_cycleevent())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_cycleevent &table_cycleevent = table.cycleevent();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_CYCLEEVENT_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
    return GORM_PackGetSQLCYCLEEVENT_ONE_DEBUG(pMemPool, pMySQLEvent, iTableIndex, table_cycleevent, pReqData);
#endif
    return GORM_PackGetSQLCYCLEEVENT_ONE(pMemPool, mysql, iTableIndex, table_cycleevent, pReqData);
}
int GORM_PackGetSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackGetSQLCURRENCY(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackGetSQLCYCLEEVENT(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define CURRENCYDELETESQL "delete  from currency_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLCURRENCY(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_currency())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = 74;
    int iTmpLen = 0;

    GORM_PB_Table_currency table_currency = table.currency();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_CURRENCY_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 currency_roleid = table_currency.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CURRENCYDELETESQL, iTableIndex, currency_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "currency", table.custom_columns());
#endif
    return GORM_OK;
}
#define CYCLEEVENTDELETESQL "delete  from cycleevent_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLCYCLEEVENT(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_cycleevent())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = 78;
    int iTmpLen = 0;

    GORM_PB_Table_cycleevent table_cycleevent = table.cycleevent();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_CYCLEEVENT_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 cycleevent_roleid = table_cycleevent.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTDELETESQL, iTableIndex, cycleevent_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
#endif
    return GORM_OK;
}
int GORM_PackDeleteSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackDeleteSQLCURRENCY(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackDeleteSQLCYCLEEVENT(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define CURRENCYUPDATESQL "update currency_%d set "
#define CURRENCYUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLCURRENCY(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_currency())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(CURRENCYUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_currency &table_currency = table.currency();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_CURRENCY_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 currency_version = table_currency.version();
    const int64 currency_roleid = table_currency.roleid();
    const int32 currency_snakeid = table_currency.snakeid();
    const string &currency_currency1 = table_currency.currency1();
    char *sz_currency_currency1 = "";
    int len_currency_currency1 = 0;
    GORM_MemPoolData *buffer_currency_currency1 = nullptr;
    if(currency_currency1.size() > 0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency1, currency_currency1.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_currency_currency1->m_uszData, currency_currency1.c_str(), currency_currency1.size());
        buffer_currency_currency1->m_uszData[iTmpLen] = 0;
        buffer_currency_currency1->m_sUsedSize = iTmpLen;
        sz_currency_currency1 = buffer_currency_currency1->m_uszData;
        len_currency_currency1 = iTmpLen;
    }

    const string &currency_currency2 = table_currency.currency2();
    char *sz_currency_currency2 = "";
    int len_currency_currency2 = 0;
    GORM_MemPoolData *buffer_currency_currency2 = nullptr;
    if(currency_currency2.size() > 0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency2, currency_currency2.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_currency_currency2->m_uszData, currency_currency2.c_str(), currency_currency2.size());
        buffer_currency_currency2->m_uszData[iTmpLen] = 0;
        buffer_currency_currency2->m_sUsedSize = iTmpLen;
        sz_currency_currency2 = buffer_currency_currency2->m_uszData;
        len_currency_currency2 = iTmpLen;
    }

    const string &currency_currency3 = table_currency.currency3();
    char *sz_currency_currency3 = "";
    int len_currency_currency3 = 0;
    GORM_MemPoolData *buffer_currency_currency3 = nullptr;
    if(currency_currency3.size() > 0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency3, currency_currency3.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_currency_currency3->m_uszData, currency_currency3.c_str(), currency_currency3.size());
        buffer_currency_currency3->m_uszData[iTmpLen] = 0;
        buffer_currency_currency3->m_sUsedSize = iTmpLen;
        sz_currency_currency3 = buffer_currency_currency3->m_uszData;
        len_currency_currency3 = iTmpLen;
    }

    const string &currency_currency4 = table_currency.currency4();
    char *sz_currency_currency4 = "";
    int len_currency_currency4 = 0;
    GORM_MemPoolData *buffer_currency_currency4 = nullptr;
    if(currency_currency4.size() > 0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency4, currency_currency4.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_currency_currency4->m_uszData, currency_currency4.c_str(), currency_currency4.size());
        buffer_currency_currency4->m_uszData[iTmpLen] = 0;
        buffer_currency_currency4->m_sUsedSize = iTmpLen;
        sz_currency_currency4 = buffer_currency_currency4->m_uszData;
        len_currency_currency4 = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_currency_currency1 + len_currency_currency2 + len_currency_currency3 + len_currency_currency4 + 24;
    GORM_MemPoolData *buffer_currency_where = nullptr;
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_where, iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_currency_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_currency_where->m_sCapacity, CURRENCYUPDATEWHERESQL , currency_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_currency_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), currency_version);
    buffer_currency_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_currency_currency1+ len_currency_currency2+ len_currency_currency3+ len_currency_currency4+24;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, CURRENCYUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), currency_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_CURRENCY_VERSION == iFieldId || GORM_PB_FIELD_CURRENCY_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", currency_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", currency_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", currency_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", currency_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=%d", currency_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`snakeid`=%d", currency_snakeid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `currency1`=\"%s\"", sz_currency_currency1);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`currency1`=\"%s\"", sz_currency_currency1);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `currency2`=\"%s\"", sz_currency_currency2);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`currency2`=\"%s\"", sz_currency_currency2);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `currency3`=\"%s\"", sz_currency_currency3);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`currency3`=\"%s\"", sz_currency_currency3);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `currency4`=\"%s\"", sz_currency_currency4);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`currency4`=\"%s\"", sz_currency_currency4);
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

    if (buffer_currency_currency1 != nullptr)
        buffer_currency_currency1->Release();
    if (buffer_currency_currency2 != nullptr)
        buffer_currency_currency2->Release();
    if (buffer_currency_currency3 != nullptr)
        buffer_currency_currency3->Release();
    if (buffer_currency_currency4 != nullptr)
        buffer_currency_currency4->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "currency", table.custom_columns());
#endif
    return GORM_OK;
}
#define CYCLEEVENTUPDATESQL "update cycleevent_%d set "
#define CYCLEEVENTUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLCYCLEEVENT(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_cycleevent())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(CYCLEEVENTUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_cycleevent &table_cycleevent = table.cycleevent();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_CYCLEEVENT_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 cycleevent_version = table_cycleevent.version();
    const int64 cycleevent_roleid = table_cycleevent.roleid();
    const string &cycleevent_events = table_cycleevent.events();
    char *sz_cycleevent_events = "";
    int len_cycleevent_events = 0;
    GORM_MemPoolData *buffer_cycleevent_events = nullptr;
    if(cycleevent_events.size() > 0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_cycleevent_events, cycleevent_events.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_cycleevent_events->m_uszData, cycleevent_events.c_str(), cycleevent_events.size());
        buffer_cycleevent_events->m_uszData[iTmpLen] = 0;
        buffer_cycleevent_events->m_sUsedSize = iTmpLen;
        sz_cycleevent_events = buffer_cycleevent_events->m_uszData;
        len_cycleevent_events = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_cycleevent_events + 16;
    GORM_MemPoolData *buffer_cycleevent_where = nullptr;
    GORM_MallocFromSharedPool(pMemPool, buffer_cycleevent_where, iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_cycleevent_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_cycleevent_where->m_sCapacity, CYCLEEVENTUPDATEWHERESQL , cycleevent_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_cycleevent_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), cycleevent_version);
    buffer_cycleevent_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_cycleevent_events+16;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), cycleevent_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_CYCLEEVENT_VERSION == iFieldId || GORM_PB_FIELD_CYCLEEVENT_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", cycleevent_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", cycleevent_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", cycleevent_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", cycleevent_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `events`=\"%s\"", sz_cycleevent_events);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`events`=\"%s\"", sz_cycleevent_events);
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

    if (buffer_cycleevent_events != nullptr)
        buffer_cycleevent_events->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
#endif
    return GORM_OK;
}
int GORM_PackUpdateSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackUpdateSQLCURRENCY(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackUpdateSQLCYCLEEVENT(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define CURRENCYINCREASESQL "update currency_%d set "
#define CURRENCYINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLCURRENCY(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_currency())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(CURRENCYINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_currency table_currency = table.currency();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_CURRENCY_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 currency_version = table_currency.version();
    const int64 currency_roleid = table_currency.roleid();
    const int32 currency_snakeid = table_currency.snakeid();

    int iWhereLen = iSqlLen + 128  + 24;
    GORM_MemPoolData *buffer_currency_where = nullptr;
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_where, iWhereLen);
    char *szWhereBegin = buffer_currency_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_currency_where->m_sCapacity, CURRENCYINCREASEWHERESQL , currency_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_currency_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), currency_version);
    buffer_currency_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +100;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, CURRENCYUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, CURRENCYINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), currency_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_CURRENCY_VERSION == iFieldId || GORM_PB_FIELD_CURRENCY_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_CURRENCY_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, currency_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, currency_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_CURRENCY_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, currency_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, currency_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_CURRENCY_SNAKEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=`snakeid`%c%d", cOpt, currency_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `snakeid`=`snakeid`%c%d", cOpt, currency_snakeid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "currency", table.custom_columns());
#endif
    return GORM_OK;
}
#define CYCLEEVENTINCREASESQL "update cycleevent_%d set "
#define CYCLEEVENTINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLCYCLEEVENT(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_cycleevent())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(CYCLEEVENTINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_cycleevent table_cycleevent = table.cycleevent();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_CYCLEEVENT_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 cycleevent_version = table_cycleevent.version();
    const int64 cycleevent_roleid = table_cycleevent.roleid();

    int iWhereLen = iSqlLen + 128  + 16;
    GORM_MemPoolData *buffer_cycleevent_where = nullptr;
    GORM_MallocFromSharedPool(pMemPool, buffer_cycleevent_where, iWhereLen);
    char *szWhereBegin = buffer_cycleevent_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_cycleevent_where->m_sCapacity, CYCLEEVENTINCREASEWHERESQL , cycleevent_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_cycleevent_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), cycleevent_version);
    buffer_cycleevent_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +32;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, CYCLEEVENTUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), cycleevent_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_CYCLEEVENT_VERSION == iFieldId || GORM_PB_FIELD_CYCLEEVENT_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_CYCLEEVENT_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, cycleevent_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, cycleevent_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_CYCLEEVENT_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, cycleevent_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, cycleevent_roleid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
#endif
    return GORM_OK;
}
int GORM_PackIncreaseSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackIncreaseSQLCURRENCY(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackIncreaseSQLCYCLEEVENT(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define CURRENCYREPLACESQL "insert into currency_%d(`version`, `roleid`, `snakeid`, `currency1`, `currency2`, `currency3`, `currency4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `snakeid`=%d, `currency1`=\"%s\", `currency2`=\"%s\", `currency3`=\"%s\", `currency4`=\"%s\";"
int GORM_PackReplaceSQLCURRENCY_One(shared_ptr<GORM_MemPool> &pMemPool, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_currency &table_currency, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 334;
    int iTmpLen = 0;

    const uint64 currency_version = table_currency.version();

    const int64 currency_roleid = table_currency.roleid();

    const int32 currency_snakeid = table_currency.snakeid();

    const string &currency_currency1 = table_currency.currency1();
    char *sz_currency_currency1 = "";
    int len_currency_currency1 = 0;
    GORM_MemPoolData *buffer_currency_currency1 = nullptr;
    if(currency_currency1.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency1, currency_currency1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency1->m_uszData, currency_currency1.c_str(), currency_currency1.size());
        buffer_currency_currency1->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency1->m_sUsedSize = iTmpLen;
        sz_currency_currency1 = buffer_currency_currency1->m_uszData;
        len_currency_currency1 = iTmpLen;
    }

    const string &currency_currency2 = table_currency.currency2();
    char *sz_currency_currency2 = "";
    int len_currency_currency2 = 0;
    GORM_MemPoolData *buffer_currency_currency2 = nullptr;
    if(currency_currency2.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency2, currency_currency2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency2->m_uszData, currency_currency2.c_str(), currency_currency2.size());
        buffer_currency_currency2->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency2->m_sUsedSize = iTmpLen;
        sz_currency_currency2 = buffer_currency_currency2->m_uszData;
        len_currency_currency2 = iTmpLen;
    }

    const string &currency_currency3 = table_currency.currency3();
    char *sz_currency_currency3 = "";
    int len_currency_currency3 = 0;
    GORM_MemPoolData *buffer_currency_currency3 = nullptr;
    if(currency_currency3.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency3, currency_currency3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency3->m_uszData, currency_currency3.c_str(), currency_currency3.size());
        buffer_currency_currency3->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency3->m_sUsedSize = iTmpLen;
        sz_currency_currency3 = buffer_currency_currency3->m_uszData;
        len_currency_currency3 = iTmpLen;
    }

    const string &currency_currency4 = table_currency.currency4();
    char *sz_currency_currency4 = "";
    int len_currency_currency4 = 0;
    GORM_MemPoolData *buffer_currency_currency4 = nullptr;
    if(currency_currency4.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_currency_currency4, currency_currency4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency4->m_uszData, currency_currency4.c_str(), currency_currency4.size());
        buffer_currency_currency4->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency4->m_sUsedSize = iTmpLen;
        sz_currency_currency4 = buffer_currency_currency4->m_uszData;
        len_currency_currency4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_currency_currency1 + len_currency_currency2 + len_currency_currency3 + len_currency_currency4;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CURRENCYREPLACESQL, iTableIndex, currency_version, currency_roleid, currency_snakeid, sz_currency_currency1, sz_currency_currency2, sz_currency_currency3, sz_currency_currency4,currency_snakeid, sz_currency_currency1, sz_currency_currency2, sz_currency_currency3, sz_currency_currency4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_currency_currency1 != nullptr)
        buffer_currency_currency1->Release();
    if (buffer_currency_currency2 != nullptr)
        buffer_currency_currency2->Release();
    if (buffer_currency_currency3 != nullptr)
        buffer_currency_currency3->Release();
    if (buffer_currency_currency4 != nullptr)
        buffer_currency_currency4->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLCURRENCY(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_currency())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_currency &table_currency = table.currency();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "currency", table.custom_columns());
#endif
        return GORM_PackReplaceSQLCURRENCY_One(mysql, iTableIndex, table_currency, pReqData);
    }
    return GORM_OK;
}
#define CYCLEEVENTREPLACESQL "insert into cycleevent_%d(`version`, `roleid`, `events`) values (%llu, %lld, \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `events`=\"%s\";"
int GORM_PackReplaceSQLCYCLEEVENT_One(shared_ptr<GORM_MemPool> &pMemPool, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 180;
    int iTmpLen = 0;

    const uint64 cycleevent_version = table_cycleevent.version();

    const int64 cycleevent_roleid = table_cycleevent.roleid();

    const string &cycleevent_events = table_cycleevent.events();
    char *sz_cycleevent_events = "";
    int len_cycleevent_events = 0;
    GORM_MemPoolData *buffer_cycleevent_events = nullptr;
    if(cycleevent_events.size()>0)
    {
    GORM_MallocFromSharedPool(pMemPool, buffer_cycleevent_events, cycleevent_events.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_cycleevent_events->m_uszData, cycleevent_events.c_str(), cycleevent_events.size());
        buffer_cycleevent_events->m_uszData[iTmpLen] = '\0';
        buffer_cycleevent_events->m_sUsedSize = iTmpLen;
        sz_cycleevent_events = buffer_cycleevent_events->m_uszData;
        len_cycleevent_events = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + len_cycleevent_events;
    GORM_MallocFromSharedPool(pMemPool, pReqData, iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTREPLACESQL, iTableIndex, cycleevent_version, cycleevent_roleid, sz_cycleevent_events, sz_cycleevent_events);
    pReqData->m_sUsedSize = iLen;

    if (buffer_cycleevent_events != nullptr)
        buffer_cycleevent_events->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLCYCLEEVENT(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_cycleevent())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_cycleevent &table_cycleevent = table.cycleevent();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
#endif
        return GORM_PackReplaceSQLCYCLEEVENT_One(mysql, iTableIndex, table_cycleevent, pReqData);
    }
    return GORM_OK;
}
int GORM_PackReplaceSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackReplaceSQLCURRENCY(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackReplaceSQLCYCLEEVENT(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

int GORM_PackGetSQLTable(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_TABLE& table, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
        if (!table.has_currency())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMemPool, pMySQLEvent, "currency", table.custom_columns());
#endif
        return GORM_PackGetSQLCURRENCY_ONE(pMemPool, pMemPool, mysql, uiHashValue, table.currency(), pReqData);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        if (!table.has_cycleevent())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMemPool, pMySQLEvent, "cycleevent", table.custom_columns());
#endif
        return GORM_PackGetSQLCYCLEEVENT_ONE(pMemPool, pMemPool, mysql, uiHashValue, table.cycleevent(), pReqData);
    }
    }
    return GORM_INVALID_TABLE;
}
#define GetByNonPrimaySQL_CURRENCY "select `version`,`roleid`,`snakeid`,`currency1`,`currency2`,`currency3`,`currency4` from currency_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLCURRENCY_One(shared_ptr<GORM_MemPool> &pMemPool, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_currency &table_currency, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_CURRENCY);
    int iTotalLen = 64*vFields.size() + iLen + table_currency.ByteSizeLong();
    GORM_MallocFromSharedPool(pMemPool, pReqData, iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_CURRENCY, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_currency.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_currency.version());
            break;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_currency.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_currency.roleid());
            break;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_currency.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_currency.snakeid());
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            char *szData = "";
            const string &strData = table_currency.currency1();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`currency1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `currency1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            char *szData = "";
            const string &strData = table_currency.currency2();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`currency2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `currency2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            char *szData = "";
            const string &strData = table_currency.currency3();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`currency3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `currency3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            char *szData = "";
            const string &strData = table_currency.currency4();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`currency4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `currency4`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#ifdef GORM_DEBUG
#define GetByNonPrimaySQL_CURRENCY_DEBUG "select `version`,`roleid`,`snakeid`,`currency1`,`currency2`,`currency3`,`currency4`"
int GORM_PackGet_By_Non_Primary_KeySQLCURRENCY_One_DEBUG(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_currency &table_currency, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_CURRENCY_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_currency.ByteSizeLong();
    GORM_MallocFromSharedPool(pMemPool, pReqData, iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_CURRENCY_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["currency"];
    for (int i=7; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from currency where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_CURRENCY_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_currency.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_currency.version());
            break;
        }
        case GORM_PB_FIELD_CURRENCY_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_currency.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_currency.roleid());
            break;
        }
        case GORM_PB_FIELD_CURRENCY_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_currency.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_currency.snakeid());
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY1:
        {
            char *szData = "";
            const string &strData = table_currency.currency1();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`currency1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `currency1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY2:
        {
            char *szData = "";
            const string &strData = table_currency.currency2();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`currency2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `currency2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY3:
        {
            char *szData = "";
            const string &strData = table_currency.currency3();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`currency3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `currency3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_CURRENCY_CURRENCY4:
        {
            char *szData = "";
            const string &strData = table_currency.currency4();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`currency4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `currency4`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#endif
int GORM_PackGet_By_Non_Primary_KeySQLCURRENCY(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_currency())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_currency &table_currency = table.currency();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "currency", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLCURRENCY_One_DEBUG(pMemPool, pMySQLEvent, iTableIndex, table.custom_columns(), table_currency, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLCURRENCY_One(pMemPool, mysql, iTableIndex, table_currency, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_CYCLEEVENT "select `version`,`roleid`,`events` from cycleevent_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT_One(shared_ptr<GORM_MemPool> &pMemPool, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_CYCLEEVENT);
    int iTotalLen = 64*vFields.size() + iLen + table_cycleevent.ByteSizeLong();
    GORM_MallocFromSharedPool(pMemPool, pReqData, iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_CYCLEEVENT, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_cycleevent.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_cycleevent.version());
            break;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_cycleevent.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_cycleevent.roleid());
            break;
        }
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            char *szData = "";
            const string &strData = table_cycleevent.events();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`events`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `events`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#ifdef GORM_DEBUG
#define GetByNonPrimaySQL_CYCLEEVENT_DEBUG "select `version`,`roleid`,`events`"
int GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT_One_DEBUG(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_cycleevent &table_cycleevent, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_CYCLEEVENT_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_cycleevent.ByteSizeLong();
    GORM_MallocFromSharedPool(pMemPool, pReqData, iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_CYCLEEVENT_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["cycleevent"];
    for (int i=3; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from cycleevent where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_CYCLEEVENT_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_cycleevent.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_cycleevent.version());
            break;
        }
        case GORM_PB_FIELD_CYCLEEVENT_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_cycleevent.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_cycleevent.roleid());
            break;
        }
        case GORM_PB_FIELD_CYCLEEVENT_EVENTS:
        {
            char *szData = "";
            const string &strData = table_cycleevent.events();
            GORM_MemPoolData *pDataBuffer = nullptr;
            int iTmpLen = 0;
            if (strData.size() > 0)
            {
    GORM_MallocFromSharedPool(pMemPool, pDataBuffer, strData.size()<<1);
                    iTmpLen=mysql_real_escape_string(mysql, pDataBuffer->m_uszData, strData.c_str(), strData.size());
                pDataBuffer->m_uszData[iTmpLen] = 0;
                pDataBuffer->m_sUsedSize = iTmpLen;
                szData = pDataBuffer->m_uszData;
            }
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`events`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `events`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#endif
int GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_cycleevent())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_cycleevent &table_cycleevent = table.cycleevent();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT_One_DEBUG(pMemPool, pMySQLEvent, iTableIndex, table.custom_columns(), table_cycleevent, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT_One(pMemPool, mysql, iTableIndex, table_cycleevent, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
int GORM_PackGet_By_Non_Primary_KeySQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackGet_By_Non_Primary_KeySQLCURRENCY(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT(pMemPool, pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

int GORM_MySQLResult2PbMSG_CURRENCY(GORM_PB_Table_currency *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_snakeid(strtol(row[2], (char **)NULL,10));
    else
        pPbTable->set_snakeid(0);

    if (nullptr != row[3] && lengths[3] > 0)
        pPbTable->set_currency1(row[3], lengths[3]);
    else
        pPbTable->set_currency1("");

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_currency2(row[4], lengths[4]);
    else
        pPbTable->set_currency2("");

    if (nullptr != row[5] && lengths[5] > 0)
        pPbTable->set_currency3(row[5], lengths[5]);
    else
        pPbTable->set_currency3("");

    if (nullptr != row[6] && lengths[6] > 0)
        pPbTable->set_currency4(row[6], lengths[6]);
    else
        pPbTable->set_currency4("");

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_CYCLEEVENT(GORM_PB_Table_cycleevent *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_events(row[2], lengths[2]);
    else
        pPbTable->set_events("");

    return GORM_OK;
}
#ifdef GORM_DEBUG
int GORM_MySQLResult2PbMSG_CURRENCY_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_currency *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_CURRENCY(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["currency"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["currency"];
    for (int i=7; i<vTablesColumnOrder.size(); i++)
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
#ifdef GORM_DEBUG
int GORM_MySQLResult2PbMSG_CYCLEEVENT_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_cycleevent *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_CYCLEEVENT(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["cycleevent"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["cycleevent"];
    for (int i=3; i<vTablesColumnOrder.size(); i++)
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
    case GORM_PB_TABLE_IDX_CURRENCY:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_currency *pSrcTable = pPbTable->mutable_currency();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_CURRENCY_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_currency *pSrcTable = pPbTable->mutable_currency();
        return GORM_MySQLResult2PbMSG_CURRENCY(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_cycleevent *pSrcTable = pPbTable->mutable_cycleevent();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_CYCLEEVENT_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_cycleevent *pSrcTable = pPbTable->mutable_cycleevent();
        return GORM_MySQLResult2PbMSG_CYCLEEVENT(pSrcTable, row, lengths);
    #endif
    }
    default:
        return GORM_INVALID_TABLE;
    }

    return GORM_OK;
}
