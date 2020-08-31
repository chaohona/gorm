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
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " equip_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " food_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " hero_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " mail_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " material_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " npc_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " role_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " scene_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " skill_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " interaction_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " user_%d ", uiHashCode%2);
        break;
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        iUsedBuffLen = GORM_SafeSnprintf(szOutTableName, iInBuffLen, " roles_%d ", uiHashCode%2);
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
int GORM_PackInsertSQLCURRENCY_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_currency &table_currency, GORM_MemPoolData *&pReqData)
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
        buffer_currency_currency1 = GORM_MemPool::Instance()->GetData(currency_currency1.size()<<1);
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
        buffer_currency_currency2 = GORM_MemPool::Instance()->GetData(currency_currency2.size()<<1);
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
        buffer_currency_currency3 = GORM_MemPool::Instance()->GetData(currency_currency3.size()<<1);
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
        buffer_currency_currency4 = GORM_MemPool::Instance()->GetData(currency_currency4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency4->m_uszData, currency_currency4.c_str(), currency_currency4.size());
        buffer_currency_currency4->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency4->m_sUsedSize = iTmpLen;
        sz_currency_currency4 = buffer_currency_currency4->m_uszData;
        len_currency_currency4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_currency_currency1 + len_currency_currency2 + len_currency_currency3 + len_currency_currency4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
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
int GORM_PackInsertSQLCURRENCY(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
        return GORM_PackInsertSQLCURRENCY_ONE(pMySQLEvent, mysql, iTableIndex, table_currency, pReqData);
    }
    return GORM_OK;
}
#define CYCLEEVENTINSERTSQL "insert into cycleevent_%d(`version`, `roleid`, `events`) values (%llu, %lld, \"%s\");"
int GORM_PackInsertSQLCYCLEEVENT_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, GORM_MemPoolData *&pReqData)
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
        buffer_cycleevent_events = GORM_MemPool::Instance()->GetData(cycleevent_events.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_cycleevent_events->m_uszData, cycleevent_events.c_str(), cycleevent_events.size());
        buffer_cycleevent_events->m_uszData[iTmpLen] = '\0';
        buffer_cycleevent_events->m_sUsedSize = iTmpLen;
        sz_cycleevent_events = buffer_cycleevent_events->m_uszData;
        len_cycleevent_events = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + len_cycleevent_events;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTINSERTSQL, iTableIndex, cycleevent_version, cycleevent_roleid, sz_cycleevent_events);
    pReqData->m_sUsedSize = iLen;

    if (buffer_cycleevent_events != nullptr)
        buffer_cycleevent_events->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLCYCLEEVENT(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
        return GORM_PackInsertSQLCYCLEEVENT_ONE(pMySQLEvent, mysql, iTableIndex, table_cycleevent, pReqData);
    }
    return GORM_OK;
}
#define EQUIPINSERTSQL "insert into equip_%d(`version`, `roleid`, `snakeid`, `equip1`, `equip2`, `equip3`, `equip4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\");"
int GORM_PackInsertSQLEQUIP_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_equip &table_equip, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 175;
    int iTmpLen = 0;

    const uint64 equip_version = table_equip.version();

    const int64 equip_roleid = table_equip.roleid();

    const int32 equip_snakeid = table_equip.snakeid();

    const string &equip_equip1 = table_equip.equip1();
    char *sz_equip_equip1 = "";
    int len_equip_equip1 = 0;
    GORM_MemPoolData *buffer_equip_equip1 = nullptr;
    if(equip_equip1.size()>0)
    {
        buffer_equip_equip1 = GORM_MemPool::Instance()->GetData(equip_equip1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_equip_equip1->m_uszData, equip_equip1.c_str(), equip_equip1.size());
        buffer_equip_equip1->m_uszData[iTmpLen] = '\0';
        buffer_equip_equip1->m_sUsedSize = iTmpLen;
        sz_equip_equip1 = buffer_equip_equip1->m_uszData;
        len_equip_equip1 = iTmpLen;
    }

    const string &equip_equip2 = table_equip.equip2();
    char *sz_equip_equip2 = "";
    int len_equip_equip2 = 0;
    GORM_MemPoolData *buffer_equip_equip2 = nullptr;
    if(equip_equip2.size()>0)
    {
        buffer_equip_equip2 = GORM_MemPool::Instance()->GetData(equip_equip2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_equip_equip2->m_uszData, equip_equip2.c_str(), equip_equip2.size());
        buffer_equip_equip2->m_uszData[iTmpLen] = '\0';
        buffer_equip_equip2->m_sUsedSize = iTmpLen;
        sz_equip_equip2 = buffer_equip_equip2->m_uszData;
        len_equip_equip2 = iTmpLen;
    }

    const string &equip_equip3 = table_equip.equip3();
    char *sz_equip_equip3 = "";
    int len_equip_equip3 = 0;
    GORM_MemPoolData *buffer_equip_equip3 = nullptr;
    if(equip_equip3.size()>0)
    {
        buffer_equip_equip3 = GORM_MemPool::Instance()->GetData(equip_equip3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_equip_equip3->m_uszData, equip_equip3.c_str(), equip_equip3.size());
        buffer_equip_equip3->m_uszData[iTmpLen] = '\0';
        buffer_equip_equip3->m_sUsedSize = iTmpLen;
        sz_equip_equip3 = buffer_equip_equip3->m_uszData;
        len_equip_equip3 = iTmpLen;
    }

    const string &equip_equip4 = table_equip.equip4();
    char *sz_equip_equip4 = "";
    int len_equip_equip4 = 0;
    GORM_MemPoolData *buffer_equip_equip4 = nullptr;
    if(equip_equip4.size()>0)
    {
        buffer_equip_equip4 = GORM_MemPool::Instance()->GetData(equip_equip4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_equip_equip4->m_uszData, equip_equip4.c_str(), equip_equip4.size());
        buffer_equip_equip4->m_uszData[iTmpLen] = '\0';
        buffer_equip_equip4->m_sUsedSize = iTmpLen;
        sz_equip_equip4 = buffer_equip_equip4->m_uszData;
        len_equip_equip4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_equip_equip1 + len_equip_equip2 + len_equip_equip3 + len_equip_equip4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, EQUIPINSERTSQL, iTableIndex, equip_version, equip_roleid, equip_snakeid, sz_equip_equip1, sz_equip_equip2, sz_equip_equip3, sz_equip_equip4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_equip_equip1 != nullptr)
        buffer_equip_equip1->Release();
    if (buffer_equip_equip2 != nullptr)
        buffer_equip_equip2->Release();
    if (buffer_equip_equip3 != nullptr)
        buffer_equip_equip3->Release();
    if (buffer_equip_equip4 != nullptr)
        buffer_equip_equip4->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLEQUIP(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_equip())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_equip &table_equip = table.equip();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "equip", table.custom_columns());
#endif
        return GORM_PackInsertSQLEQUIP_ONE(pMySQLEvent, mysql, iTableIndex, table_equip, pReqData);
    }
    return GORM_OK;
}
#define FOODINSERTSQL "insert into food_%d(`version`, `roleid`, `snakeid`, `food1`, `food2`, `food3`, `food4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\");"
int GORM_PackInsertSQLFOOD_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_food &table_food, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 169;
    int iTmpLen = 0;

    const uint64 food_version = table_food.version();

    const int64 food_roleid = table_food.roleid();

    const int32 food_snakeid = table_food.snakeid();

    const string &food_food1 = table_food.food1();
    char *sz_food_food1 = "";
    int len_food_food1 = 0;
    GORM_MemPoolData *buffer_food_food1 = nullptr;
    if(food_food1.size()>0)
    {
        buffer_food_food1 = GORM_MemPool::Instance()->GetData(food_food1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_food_food1->m_uszData, food_food1.c_str(), food_food1.size());
        buffer_food_food1->m_uszData[iTmpLen] = '\0';
        buffer_food_food1->m_sUsedSize = iTmpLen;
        sz_food_food1 = buffer_food_food1->m_uszData;
        len_food_food1 = iTmpLen;
    }

    const string &food_food2 = table_food.food2();
    char *sz_food_food2 = "";
    int len_food_food2 = 0;
    GORM_MemPoolData *buffer_food_food2 = nullptr;
    if(food_food2.size()>0)
    {
        buffer_food_food2 = GORM_MemPool::Instance()->GetData(food_food2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_food_food2->m_uszData, food_food2.c_str(), food_food2.size());
        buffer_food_food2->m_uszData[iTmpLen] = '\0';
        buffer_food_food2->m_sUsedSize = iTmpLen;
        sz_food_food2 = buffer_food_food2->m_uszData;
        len_food_food2 = iTmpLen;
    }

    const string &food_food3 = table_food.food3();
    char *sz_food_food3 = "";
    int len_food_food3 = 0;
    GORM_MemPoolData *buffer_food_food3 = nullptr;
    if(food_food3.size()>0)
    {
        buffer_food_food3 = GORM_MemPool::Instance()->GetData(food_food3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_food_food3->m_uszData, food_food3.c_str(), food_food3.size());
        buffer_food_food3->m_uszData[iTmpLen] = '\0';
        buffer_food_food3->m_sUsedSize = iTmpLen;
        sz_food_food3 = buffer_food_food3->m_uszData;
        len_food_food3 = iTmpLen;
    }

    const string &food_food4 = table_food.food4();
    char *sz_food_food4 = "";
    int len_food_food4 = 0;
    GORM_MemPoolData *buffer_food_food4 = nullptr;
    if(food_food4.size()>0)
    {
        buffer_food_food4 = GORM_MemPool::Instance()->GetData(food_food4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_food_food4->m_uszData, food_food4.c_str(), food_food4.size());
        buffer_food_food4->m_uszData[iTmpLen] = '\0';
        buffer_food_food4->m_sUsedSize = iTmpLen;
        sz_food_food4 = buffer_food_food4->m_uszData;
        len_food_food4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_food_food1 + len_food_food2 + len_food_food3 + len_food_food4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, FOODINSERTSQL, iTableIndex, food_version, food_roleid, food_snakeid, sz_food_food1, sz_food_food2, sz_food_food3, sz_food_food4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_food_food1 != nullptr)
        buffer_food_food1->Release();
    if (buffer_food_food2 != nullptr)
        buffer_food_food2->Release();
    if (buffer_food_food3 != nullptr)
        buffer_food_food3->Release();
    if (buffer_food_food4 != nullptr)
        buffer_food_food4->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLFOOD(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_food())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_food &table_food = table.food();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "food", table.custom_columns());
#endif
        return GORM_PackInsertSQLFOOD_ONE(pMySQLEvent, mysql, iTableIndex, table_food, pReqData);
    }
    return GORM_OK;
}
#define HEROINSERTSQL "insert into hero_%d(`version`, `roleid`, `snakeid`, `heros`) values (%llu, %lld, %d, \"%s\");"
int GORM_PackInsertSQLHERO_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_hero &table_hero, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 118;
    int iTmpLen = 0;

    const uint64 hero_version = table_hero.version();

    const int64 hero_roleid = table_hero.roleid();

    const int32 hero_snakeid = table_hero.snakeid();

    const string &hero_heros = table_hero.heros();
    char *sz_hero_heros = "";
    int len_hero_heros = 0;
    GORM_MemPoolData *buffer_hero_heros = nullptr;
    if(hero_heros.size()>0)
    {
        buffer_hero_heros = GORM_MemPool::Instance()->GetData(hero_heros.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_hero_heros->m_uszData, hero_heros.c_str(), hero_heros.size());
        buffer_hero_heros->m_uszData[iTmpLen] = '\0';
        buffer_hero_heros->m_sUsedSize = iTmpLen;
        sz_hero_heros = buffer_hero_heros->m_uszData;
        len_hero_heros = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_hero_heros;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, HEROINSERTSQL, iTableIndex, hero_version, hero_roleid, hero_snakeid, sz_hero_heros);
    pReqData->m_sUsedSize = iLen;

    if (buffer_hero_heros != nullptr)
        buffer_hero_heros->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLHERO(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_hero())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_hero &table_hero = table.hero();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "hero", table.custom_columns());
#endif
        return GORM_PackInsertSQLHERO_ONE(pMySQLEvent, mysql, iTableIndex, table_hero, pReqData);
    }
    return GORM_OK;
}
#define MAILINSERTSQL "insert into mail_%d(`version`, `roleid`, `mail1`, `mail2`, `mail3`, `mail4`, `mail5`, `lastmailid`, `snakeid`) values (%llu, %lld, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %d, %d);"
int GORM_PackInsertSQLMAIL_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_mail &table_mail, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 204;
    int iTmpLen = 0;

    const uint64 mail_version = table_mail.version();

    const int64 mail_roleid = table_mail.roleid();

    const string &mail_mail1 = table_mail.mail1();
    char *sz_mail_mail1 = "";
    int len_mail_mail1 = 0;
    GORM_MemPoolData *buffer_mail_mail1 = nullptr;
    if(mail_mail1.size()>0)
    {
        buffer_mail_mail1 = GORM_MemPool::Instance()->GetData(mail_mail1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail1->m_uszData, mail_mail1.c_str(), mail_mail1.size());
        buffer_mail_mail1->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail1->m_sUsedSize = iTmpLen;
        sz_mail_mail1 = buffer_mail_mail1->m_uszData;
        len_mail_mail1 = iTmpLen;
    }

    const string &mail_mail2 = table_mail.mail2();
    char *sz_mail_mail2 = "";
    int len_mail_mail2 = 0;
    GORM_MemPoolData *buffer_mail_mail2 = nullptr;
    if(mail_mail2.size()>0)
    {
        buffer_mail_mail2 = GORM_MemPool::Instance()->GetData(mail_mail2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail2->m_uszData, mail_mail2.c_str(), mail_mail2.size());
        buffer_mail_mail2->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail2->m_sUsedSize = iTmpLen;
        sz_mail_mail2 = buffer_mail_mail2->m_uszData;
        len_mail_mail2 = iTmpLen;
    }

    const string &mail_mail3 = table_mail.mail3();
    char *sz_mail_mail3 = "";
    int len_mail_mail3 = 0;
    GORM_MemPoolData *buffer_mail_mail3 = nullptr;
    if(mail_mail3.size()>0)
    {
        buffer_mail_mail3 = GORM_MemPool::Instance()->GetData(mail_mail3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail3->m_uszData, mail_mail3.c_str(), mail_mail3.size());
        buffer_mail_mail3->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail3->m_sUsedSize = iTmpLen;
        sz_mail_mail3 = buffer_mail_mail3->m_uszData;
        len_mail_mail3 = iTmpLen;
    }

    const string &mail_mail4 = table_mail.mail4();
    char *sz_mail_mail4 = "";
    int len_mail_mail4 = 0;
    GORM_MemPoolData *buffer_mail_mail4 = nullptr;
    if(mail_mail4.size()>0)
    {
        buffer_mail_mail4 = GORM_MemPool::Instance()->GetData(mail_mail4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail4->m_uszData, mail_mail4.c_str(), mail_mail4.size());
        buffer_mail_mail4->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail4->m_sUsedSize = iTmpLen;
        sz_mail_mail4 = buffer_mail_mail4->m_uszData;
        len_mail_mail4 = iTmpLen;
    }

    const string &mail_mail5 = table_mail.mail5();
    char *sz_mail_mail5 = "";
    int len_mail_mail5 = 0;
    GORM_MemPoolData *buffer_mail_mail5 = nullptr;
    if(mail_mail5.size()>0)
    {
        buffer_mail_mail5 = GORM_MemPool::Instance()->GetData(mail_mail5.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail5->m_uszData, mail_mail5.c_str(), mail_mail5.size());
        buffer_mail_mail5->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail5->m_sUsedSize = iTmpLen;
        sz_mail_mail5 = buffer_mail_mail5->m_uszData;
        len_mail_mail5 = iTmpLen;
    }

    const int32 mail_lastmailid = table_mail.lastmailid();

    const int32 mail_snakeid = table_mail.snakeid();

    int iLen = iSqlLen + 128 + 8 + 8 + len_mail_mail1 + len_mail_mail2 + len_mail_mail3 + len_mail_mail4 + len_mail_mail5 + 8 + 8;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, MAILINSERTSQL, iTableIndex, mail_version, mail_roleid, sz_mail_mail1, sz_mail_mail2, sz_mail_mail3, sz_mail_mail4, sz_mail_mail5, mail_lastmailid, mail_snakeid);
    pReqData->m_sUsedSize = iLen;

    if (buffer_mail_mail1 != nullptr)
        buffer_mail_mail1->Release();
    if (buffer_mail_mail2 != nullptr)
        buffer_mail_mail2->Release();
    if (buffer_mail_mail3 != nullptr)
        buffer_mail_mail3->Release();
    if (buffer_mail_mail4 != nullptr)
        buffer_mail_mail4->Release();
    if (buffer_mail_mail5 != nullptr)
        buffer_mail_mail5->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLMAIL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_mail())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_mail &table_mail = table.mail();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "mail", table.custom_columns());
#endif
        return GORM_PackInsertSQLMAIL_ONE(pMySQLEvent, mysql, iTableIndex, table_mail, pReqData);
    }
    return GORM_OK;
}
#define MATERIALINSERTSQL "insert into material_%d(`version`, `roleid`, `snakeid`, `material1`, `material2`, `material3`, `material4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\");"
int GORM_PackInsertSQLMATERIAL_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_material &table_material, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 193;
    int iTmpLen = 0;

    const uint64 material_version = table_material.version();

    const int64 material_roleid = table_material.roleid();

    const int32 material_snakeid = table_material.snakeid();

    const string &material_material1 = table_material.material1();
    char *sz_material_material1 = "";
    int len_material_material1 = 0;
    GORM_MemPoolData *buffer_material_material1 = nullptr;
    if(material_material1.size()>0)
    {
        buffer_material_material1 = GORM_MemPool::Instance()->GetData(material_material1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_material_material1->m_uszData, material_material1.c_str(), material_material1.size());
        buffer_material_material1->m_uszData[iTmpLen] = '\0';
        buffer_material_material1->m_sUsedSize = iTmpLen;
        sz_material_material1 = buffer_material_material1->m_uszData;
        len_material_material1 = iTmpLen;
    }

    const string &material_material2 = table_material.material2();
    char *sz_material_material2 = "";
    int len_material_material2 = 0;
    GORM_MemPoolData *buffer_material_material2 = nullptr;
    if(material_material2.size()>0)
    {
        buffer_material_material2 = GORM_MemPool::Instance()->GetData(material_material2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_material_material2->m_uszData, material_material2.c_str(), material_material2.size());
        buffer_material_material2->m_uszData[iTmpLen] = '\0';
        buffer_material_material2->m_sUsedSize = iTmpLen;
        sz_material_material2 = buffer_material_material2->m_uszData;
        len_material_material2 = iTmpLen;
    }

    const string &material_material3 = table_material.material3();
    char *sz_material_material3 = "";
    int len_material_material3 = 0;
    GORM_MemPoolData *buffer_material_material3 = nullptr;
    if(material_material3.size()>0)
    {
        buffer_material_material3 = GORM_MemPool::Instance()->GetData(material_material3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_material_material3->m_uszData, material_material3.c_str(), material_material3.size());
        buffer_material_material3->m_uszData[iTmpLen] = '\0';
        buffer_material_material3->m_sUsedSize = iTmpLen;
        sz_material_material3 = buffer_material_material3->m_uszData;
        len_material_material3 = iTmpLen;
    }

    const string &material_material4 = table_material.material4();
    char *sz_material_material4 = "";
    int len_material_material4 = 0;
    GORM_MemPoolData *buffer_material_material4 = nullptr;
    if(material_material4.size()>0)
    {
        buffer_material_material4 = GORM_MemPool::Instance()->GetData(material_material4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_material_material4->m_uszData, material_material4.c_str(), material_material4.size());
        buffer_material_material4->m_uszData[iTmpLen] = '\0';
        buffer_material_material4->m_sUsedSize = iTmpLen;
        sz_material_material4 = buffer_material_material4->m_uszData;
        len_material_material4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_material_material1 + len_material_material2 + len_material_material3 + len_material_material4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, MATERIALINSERTSQL, iTableIndex, material_version, material_roleid, material_snakeid, sz_material_material1, sz_material_material2, sz_material_material3, sz_material_material4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_material_material1 != nullptr)
        buffer_material_material1->Release();
    if (buffer_material_material2 != nullptr)
        buffer_material_material2->Release();
    if (buffer_material_material3 != nullptr)
        buffer_material_material3->Release();
    if (buffer_material_material4 != nullptr)
        buffer_material_material4->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLMATERIAL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_material())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_material &table_material = table.material();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "material", table.custom_columns());
#endif
        return GORM_PackInsertSQLMATERIAL_ONE(pMySQLEvent, mysql, iTableIndex, table_material, pReqData);
    }
    return GORM_OK;
}
#define NPCINSERTSQL "insert into npc_%d(`version`, `roleid`, `snakeid`, `npcs`) values (%llu, %lld, %d, \"%s\");"
int GORM_PackInsertSQLNPC_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_npc &table_npc, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 115;
    int iTmpLen = 0;

    const uint64 npc_version = table_npc.version();

    const int64 npc_roleid = table_npc.roleid();

    const int32 npc_snakeid = table_npc.snakeid();

    const string &npc_npcs = table_npc.npcs();
    char *sz_npc_npcs = "";
    int len_npc_npcs = 0;
    GORM_MemPoolData *buffer_npc_npcs = nullptr;
    if(npc_npcs.size()>0)
    {
        buffer_npc_npcs = GORM_MemPool::Instance()->GetData(npc_npcs.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_npc_npcs->m_uszData, npc_npcs.c_str(), npc_npcs.size());
        buffer_npc_npcs->m_uszData[iTmpLen] = '\0';
        buffer_npc_npcs->m_sUsedSize = iTmpLen;
        sz_npc_npcs = buffer_npc_npcs->m_uszData;
        len_npc_npcs = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_npc_npcs;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, NPCINSERTSQL, iTableIndex, npc_version, npc_roleid, npc_snakeid, sz_npc_npcs);
    pReqData->m_sUsedSize = iLen;

    if (buffer_npc_npcs != nullptr)
        buffer_npc_npcs->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLNPC(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_npc())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_npc &table_npc = table.npc();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "npc", table.custom_columns());
#endif
        return GORM_PackInsertSQLNPC_ONE(pMySQLEvent, mysql, iTableIndex, table_npc, pReqData);
    }
    return GORM_OK;
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
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLEINSERTSQL, iTableIndex, role_version, role_roleid, sz_role_rolename, role_level, role_exp, role_characterid, role_gold, role_offlinetime, role_inited, role_createtime, sz_role_face, role_online);
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
#define SCENEINSERTSQL "insert into scene_%d(`version`, `roleid`, `sceneid`, `collects`) values (%llu, %lld, %d, \"%s\");"
int GORM_PackInsertSQLSCENE_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_scene &table_scene, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 123;
    int iTmpLen = 0;

    const uint64 scene_version = table_scene.version();

    const int64 scene_roleid = table_scene.roleid();

    const int32 scene_sceneid = table_scene.sceneid();

    const string &scene_collects = table_scene.collects();
    char *sz_scene_collects = "";
    int len_scene_collects = 0;
    GORM_MemPoolData *buffer_scene_collects = nullptr;
    if(scene_collects.size()>0)
    {
        buffer_scene_collects = GORM_MemPool::Instance()->GetData(scene_collects.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_scene_collects->m_uszData, scene_collects.c_str(), scene_collects.size());
        buffer_scene_collects->m_uszData[iTmpLen] = '\0';
        buffer_scene_collects->m_sUsedSize = iTmpLen;
        sz_scene_collects = buffer_scene_collects->m_uszData;
        len_scene_collects = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_scene_collects;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, SCENEINSERTSQL, iTableIndex, scene_version, scene_roleid, scene_sceneid, sz_scene_collects);
    pReqData->m_sUsedSize = iLen;

    if (buffer_scene_collects != nullptr)
        buffer_scene_collects->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLSCENE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_scene())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_scene &table_scene = table.scene();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "scene", table.custom_columns());
#endif
        return GORM_PackInsertSQLSCENE_ONE(pMySQLEvent, mysql, iTableIndex, table_scene, pReqData);
    }
    return GORM_OK;
}
#define SKILLINSERTSQL "insert into skill_%d(`version`, `roleid`, `snakeid`, `skill1`, `skill2`, `skill3`, `skill4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\");"
int GORM_PackInsertSQLSKILL_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_skill &table_skill, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 175;
    int iTmpLen = 0;

    const uint64 skill_version = table_skill.version();

    const int64 skill_roleid = table_skill.roleid();

    const int32 skill_snakeid = table_skill.snakeid();

    const string &skill_skill1 = table_skill.skill1();
    char *sz_skill_skill1 = "";
    int len_skill_skill1 = 0;
    GORM_MemPoolData *buffer_skill_skill1 = nullptr;
    if(skill_skill1.size()>0)
    {
        buffer_skill_skill1 = GORM_MemPool::Instance()->GetData(skill_skill1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_skill_skill1->m_uszData, skill_skill1.c_str(), skill_skill1.size());
        buffer_skill_skill1->m_uszData[iTmpLen] = '\0';
        buffer_skill_skill1->m_sUsedSize = iTmpLen;
        sz_skill_skill1 = buffer_skill_skill1->m_uszData;
        len_skill_skill1 = iTmpLen;
    }

    const string &skill_skill2 = table_skill.skill2();
    char *sz_skill_skill2 = "";
    int len_skill_skill2 = 0;
    GORM_MemPoolData *buffer_skill_skill2 = nullptr;
    if(skill_skill2.size()>0)
    {
        buffer_skill_skill2 = GORM_MemPool::Instance()->GetData(skill_skill2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_skill_skill2->m_uszData, skill_skill2.c_str(), skill_skill2.size());
        buffer_skill_skill2->m_uszData[iTmpLen] = '\0';
        buffer_skill_skill2->m_sUsedSize = iTmpLen;
        sz_skill_skill2 = buffer_skill_skill2->m_uszData;
        len_skill_skill2 = iTmpLen;
    }

    const string &skill_skill3 = table_skill.skill3();
    char *sz_skill_skill3 = "";
    int len_skill_skill3 = 0;
    GORM_MemPoolData *buffer_skill_skill3 = nullptr;
    if(skill_skill3.size()>0)
    {
        buffer_skill_skill3 = GORM_MemPool::Instance()->GetData(skill_skill3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_skill_skill3->m_uszData, skill_skill3.c_str(), skill_skill3.size());
        buffer_skill_skill3->m_uszData[iTmpLen] = '\0';
        buffer_skill_skill3->m_sUsedSize = iTmpLen;
        sz_skill_skill3 = buffer_skill_skill3->m_uszData;
        len_skill_skill3 = iTmpLen;
    }

    const string &skill_skill4 = table_skill.skill4();
    char *sz_skill_skill4 = "";
    int len_skill_skill4 = 0;
    GORM_MemPoolData *buffer_skill_skill4 = nullptr;
    if(skill_skill4.size()>0)
    {
        buffer_skill_skill4 = GORM_MemPool::Instance()->GetData(skill_skill4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_skill_skill4->m_uszData, skill_skill4.c_str(), skill_skill4.size());
        buffer_skill_skill4->m_uszData[iTmpLen] = '\0';
        buffer_skill_skill4->m_sUsedSize = iTmpLen;
        sz_skill_skill4 = buffer_skill_skill4->m_uszData;
        len_skill_skill4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_skill_skill1 + len_skill_skill2 + len_skill_skill3 + len_skill_skill4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, SKILLINSERTSQL, iTableIndex, skill_version, skill_roleid, skill_snakeid, sz_skill_skill1, sz_skill_skill2, sz_skill_skill3, sz_skill_skill4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_skill_skill1 != nullptr)
        buffer_skill_skill1->Release();
    if (buffer_skill_skill2 != nullptr)
        buffer_skill_skill2->Release();
    if (buffer_skill_skill3 != nullptr)
        buffer_skill_skill3->Release();
    if (buffer_skill_skill4 != nullptr)
        buffer_skill_skill4->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLSKILL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_skill())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_skill &table_skill = table.skill();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "skill", table.custom_columns());
#endif
        return GORM_PackInsertSQLSKILL_ONE(pMySQLEvent, mysql, iTableIndex, table_skill, pReqData);
    }
    return GORM_OK;
}
#define INTERACTIONINSERTSQL "insert into interaction_%d(`version`, `roleid`, `snakeid`, `interaction1`, `interaction2`, `interaction3`, `interaction4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\");"
int GORM_PackInsertSQLINTERACTION_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_interaction &table_interaction, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 211;
    int iTmpLen = 0;

    const uint64 interaction_version = table_interaction.version();

    const int64 interaction_roleid = table_interaction.roleid();

    const int32 interaction_snakeid = table_interaction.snakeid();

    const string &interaction_interaction1 = table_interaction.interaction1();
    char *sz_interaction_interaction1 = "";
    int len_interaction_interaction1 = 0;
    GORM_MemPoolData *buffer_interaction_interaction1 = nullptr;
    if(interaction_interaction1.size()>0)
    {
        buffer_interaction_interaction1 = GORM_MemPool::Instance()->GetData(interaction_interaction1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_interaction_interaction1->m_uszData, interaction_interaction1.c_str(), interaction_interaction1.size());
        buffer_interaction_interaction1->m_uszData[iTmpLen] = '\0';
        buffer_interaction_interaction1->m_sUsedSize = iTmpLen;
        sz_interaction_interaction1 = buffer_interaction_interaction1->m_uszData;
        len_interaction_interaction1 = iTmpLen;
    }

    const string &interaction_interaction2 = table_interaction.interaction2();
    char *sz_interaction_interaction2 = "";
    int len_interaction_interaction2 = 0;
    GORM_MemPoolData *buffer_interaction_interaction2 = nullptr;
    if(interaction_interaction2.size()>0)
    {
        buffer_interaction_interaction2 = GORM_MemPool::Instance()->GetData(interaction_interaction2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_interaction_interaction2->m_uszData, interaction_interaction2.c_str(), interaction_interaction2.size());
        buffer_interaction_interaction2->m_uszData[iTmpLen] = '\0';
        buffer_interaction_interaction2->m_sUsedSize = iTmpLen;
        sz_interaction_interaction2 = buffer_interaction_interaction2->m_uszData;
        len_interaction_interaction2 = iTmpLen;
    }

    const string &interaction_interaction3 = table_interaction.interaction3();
    char *sz_interaction_interaction3 = "";
    int len_interaction_interaction3 = 0;
    GORM_MemPoolData *buffer_interaction_interaction3 = nullptr;
    if(interaction_interaction3.size()>0)
    {
        buffer_interaction_interaction3 = GORM_MemPool::Instance()->GetData(interaction_interaction3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_interaction_interaction3->m_uszData, interaction_interaction3.c_str(), interaction_interaction3.size());
        buffer_interaction_interaction3->m_uszData[iTmpLen] = '\0';
        buffer_interaction_interaction3->m_sUsedSize = iTmpLen;
        sz_interaction_interaction3 = buffer_interaction_interaction3->m_uszData;
        len_interaction_interaction3 = iTmpLen;
    }

    const string &interaction_interaction4 = table_interaction.interaction4();
    char *sz_interaction_interaction4 = "";
    int len_interaction_interaction4 = 0;
    GORM_MemPoolData *buffer_interaction_interaction4 = nullptr;
    if(interaction_interaction4.size()>0)
    {
        buffer_interaction_interaction4 = GORM_MemPool::Instance()->GetData(interaction_interaction4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_interaction_interaction4->m_uszData, interaction_interaction4.c_str(), interaction_interaction4.size());
        buffer_interaction_interaction4->m_uszData[iTmpLen] = '\0';
        buffer_interaction_interaction4->m_sUsedSize = iTmpLen;
        sz_interaction_interaction4 = buffer_interaction_interaction4->m_uszData;
        len_interaction_interaction4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_interaction_interaction1 + len_interaction_interaction2 + len_interaction_interaction3 + len_interaction_interaction4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, INTERACTIONINSERTSQL, iTableIndex, interaction_version, interaction_roleid, interaction_snakeid, sz_interaction_interaction1, sz_interaction_interaction2, sz_interaction_interaction3, sz_interaction_interaction4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_interaction_interaction1 != nullptr)
        buffer_interaction_interaction1->Release();
    if (buffer_interaction_interaction2 != nullptr)
        buffer_interaction_interaction2->Release();
    if (buffer_interaction_interaction3 != nullptr)
        buffer_interaction_interaction3->Release();
    if (buffer_interaction_interaction4 != nullptr)
        buffer_interaction_interaction4->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLINTERACTION(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_interaction())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_interaction &table_interaction = table.interaction();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "interaction", table.custom_columns());
#endif
        return GORM_PackInsertSQLINTERACTION_ONE(pMySQLEvent, mysql, iTableIndex, table_interaction, pReqData);
    }
    return GORM_OK;
}
#define USERINSERTSQL "insert into user_%d(`version`, `userid`, `ptid`, `pttype`, `createtime`) values (%llu, %lld, \"%s\", %d, %lld);"
int GORM_PackInsertSQLUSER_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_user &table_user, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 136;
    int iTmpLen = 0;

    const uint64 user_version = table_user.version();

    const int64 user_userid = table_user.userid();

    const string &user_ptid = table_user.ptid();
    char *sz_user_ptid = "";
    int len_user_ptid = 0;
    GORM_MemPoolData *buffer_user_ptid = nullptr;
    if(user_ptid.size()>0)
    {
        buffer_user_ptid = GORM_MemPool::Instance()->GetData(user_ptid.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_user_ptid->m_uszData, user_ptid.c_str(), user_ptid.size());
        buffer_user_ptid->m_uszData[iTmpLen] = '\0';
        buffer_user_ptid->m_sUsedSize = iTmpLen;
        sz_user_ptid = buffer_user_ptid->m_uszData;
        len_user_ptid = iTmpLen;
    }

    const int32 user_pttype = table_user.pttype();

    const int64 user_createtime = table_user.createtime();

    int iLen = iSqlLen + 128 + 8 + 8 + len_user_ptid + 8 + 8;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, USERINSERTSQL, iTableIndex, user_version, user_userid, sz_user_ptid, user_pttype, user_createtime);
    pReqData->m_sUsedSize = iLen;

    if (buffer_user_ptid != nullptr)
        buffer_user_ptid->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLUSER(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_user())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_user &table_user = table.user();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "user", table.custom_columns());
#endif
        return GORM_PackInsertSQLUSER_ONE(pMySQLEvent, mysql, iTableIndex, table_user, pReqData);
    }
    return GORM_OK;
}
#define ROLESINSERTSQL "insert into roles_%d(`version`, `roleid`, `userid`, `worldid`, `dbid`, `name`, `charid`, `face`, `createtime`) values (%llu, %lld, %lld, %lld, %d, \"%s\", %d, \"%s\", %lld);"
int GORM_PackInsertSQLROLES_ONE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_Table_roles &table_roles, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 199;
    int iTmpLen = 0;

    const uint64 roles_version = table_roles.version();

    const int64 roles_roleid = table_roles.roleid();

    const int64 roles_userid = table_roles.userid();

    const int64 roles_worldid = table_roles.worldid();

    const int32 roles_dbid = table_roles.dbid();

    const string &roles_name = table_roles.name();
    char *sz_roles_name = "";
    int len_roles_name = 0;
    GORM_MemPoolData *buffer_roles_name = nullptr;
    if(roles_name.size()>0)
    {
        buffer_roles_name = GORM_MemPool::Instance()->GetData(roles_name.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_roles_name->m_uszData, roles_name.c_str(), roles_name.size());
        buffer_roles_name->m_uszData[iTmpLen] = '\0';
        buffer_roles_name->m_sUsedSize = iTmpLen;
        sz_roles_name = buffer_roles_name->m_uszData;
        len_roles_name = iTmpLen;
    }

    const int32 roles_charid = table_roles.charid();

    const string &roles_face = table_roles.face();
    char *sz_roles_face = "";
    int len_roles_face = 0;
    GORM_MemPoolData *buffer_roles_face = nullptr;
    if(roles_face.size()>0)
    {
        buffer_roles_face = GORM_MemPool::Instance()->GetData(roles_face.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_roles_face->m_uszData, roles_face.c_str(), roles_face.size());
        buffer_roles_face->m_uszData[iTmpLen] = '\0';
        buffer_roles_face->m_sUsedSize = iTmpLen;
        sz_roles_face = buffer_roles_face->m_uszData;
        len_roles_face = iTmpLen;
    }

    const int64 roles_createtime = table_roles.createtime();

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + 8 + 8 + len_roles_name + 8 + len_roles_face + 8;
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLESINSERTSQL, iTableIndex, roles_version, roles_roleid, roles_userid, roles_worldid, roles_dbid, sz_roles_name, roles_charid, sz_roles_face, roles_createtime);
    pReqData->m_sUsedSize = iLen;

    if (buffer_roles_name != nullptr)
        buffer_roles_name->Release();
    if (buffer_roles_face != nullptr)
        buffer_roles_face->Release();

    return GORM_OK;
}
int GORM_PackInsertSQLROLES(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_roles())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_roles &table_roles = table.roles();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "roles", table.custom_columns());
#endif
        return GORM_PackInsertSQLROLES_ONE(pMySQLEvent, mysql, iTableIndex, table_roles, pReqData);
    }
    return GORM_OK;
}
int GORM_PackInsertSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackInsertSQLCURRENCY(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackInsertSQLCYCLEEVENT(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_EQUIP:
        return GORM_PackInsertSQLEQUIP(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_FOOD:
        return GORM_PackInsertSQLFOOD(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_HERO:
        return GORM_PackInsertSQLHERO(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MAIL:
        return GORM_PackInsertSQLMAIL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MATERIAL:
        return GORM_PackInsertSQLMATERIAL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_NPC:
        return GORM_PackInsertSQLNPC(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackInsertSQLROLE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SCENE:
        return GORM_PackInsertSQLSCENE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SKILL:
        return GORM_PackInsertSQLSKILL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_INTERACTION:
        return GORM_PackInsertSQLINTERACTION(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_USER:
        return GORM_PackInsertSQLUSER(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLES:
        return GORM_PackInsertSQLROLES(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

int GORM_PackInsertSQLTable(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_TABLE& table, GORM_MemPoolData *&pReqData)
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
        return GORM_PackInsertSQLCURRENCY_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.currency(), pReqData);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        if (!table.has_cycleevent())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
#endif
        return GORM_PackInsertSQLCYCLEEVENT_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.cycleevent(), pReqData);
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        if (!table.has_equip())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "equip", table.custom_columns());
#endif
        return GORM_PackInsertSQLEQUIP_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.equip(), pReqData);
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        if (!table.has_food())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "food", table.custom_columns());
#endif
        return GORM_PackInsertSQLFOOD_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.food(), pReqData);
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        if (!table.has_hero())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "hero", table.custom_columns());
#endif
        return GORM_PackInsertSQLHERO_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.hero(), pReqData);
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        if (!table.has_mail())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "mail", table.custom_columns());
#endif
        return GORM_PackInsertSQLMAIL_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.mail(), pReqData);
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        if (!table.has_material())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "material", table.custom_columns());
#endif
        return GORM_PackInsertSQLMATERIAL_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.material(), pReqData);
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        if (!table.has_npc())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "npc", table.custom_columns());
#endif
        return GORM_PackInsertSQLNPC_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.npc(), pReqData);
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        if (!table.has_role())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
        return GORM_PackInsertSQLROLE_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.role(), pReqData);
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        if (!table.has_scene())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "scene", table.custom_columns());
#endif
        return GORM_PackInsertSQLSCENE_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.scene(), pReqData);
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        if (!table.has_skill())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "skill", table.custom_columns());
#endif
        return GORM_PackInsertSQLSKILL_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.skill(), pReqData);
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        if (!table.has_interaction())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "interaction", table.custom_columns());
#endif
        return GORM_PackInsertSQLINTERACTION_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.interaction(), pReqData);
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        if (!table.has_user())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "user", table.custom_columns());
#endif
        return GORM_PackInsertSQLUSER_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.user(), pReqData);
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        if (!table.has_roles())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "roles", table.custom_columns());
#endif
        return GORM_PackInsertSQLROLES_ONE(pMySQLEvent, pMySQLEvent->m_pMySQL, uiHashValue, table.roles(), pReqData);
    }
    }
    return GORM_INVALID_TABLE;
}
#define CURRENCYGETSQL "select `version`, `roleid`, `snakeid`, `currency1`, `currency2`, `currency3`, `currency4` from currency_%d where  `roleid`=%lld;"
int GORM_PackGetSQLCURRENCY_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_currency &table_currency, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 153;
    int iTmpLen = 0;

    const int64 currency_roleid = table_currency.roleid();
    int iLen = iSqlLen + 128 + 8 + table_currency.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CURRENCYGETSQL, iTableIndex, currency_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define CURRENCYGETSQL_DEBUG_WHERE " from currency_%d where  `roleid`=%lld;"
int GORM_PackGetSQLCURRENCY_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_currency &table_currency, GORM_MemPoolData *&pReqData)
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
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
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
int GORM_PackGetSQLCURRENCY(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
    return GORM_PackGetSQLCURRENCY_ONE_DEBUG(pMySQLEvent, iTableIndex, table_currency, pReqData);
#endif
    return GORM_PackGetSQLCURRENCY_ONE(mysql, iTableIndex, table_currency, pReqData);
}
#define CYCLEEVENTGETSQL "select `version`, `roleid`, `events` from cycleevent_%d where  `roleid`=%lld;"
int GORM_PackGetSQLCYCLEEVENT_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 104;
    int iTmpLen = 0;

    const int64 cycleevent_roleid = table_cycleevent.roleid();
    int iLen = iSqlLen + 128 + 8 + table_cycleevent.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTGETSQL, iTableIndex, cycleevent_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define CYCLEEVENTGETSQL_DEBUG_WHERE " from cycleevent_%d where  `roleid`=%lld;"
int GORM_PackGetSQLCYCLEEVENT_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, GORM_MemPoolData *&pReqData)
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
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
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
int GORM_PackGetSQLCYCLEEVENT(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
    return GORM_PackGetSQLCYCLEEVENT_ONE_DEBUG(pMySQLEvent, iTableIndex, table_cycleevent, pReqData);
#endif
    return GORM_PackGetSQLCYCLEEVENT_ONE(mysql, iTableIndex, table_cycleevent, pReqData);
}
#define EQUIPGETSQL "select `version`, `roleid`, `snakeid`, `equip1`, `equip2`, `equip3`, `equip4` from equip_%d where  `roleid`=%lld;"
int GORM_PackGetSQLEQUIP_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_equip &table_equip, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 135;
    int iTmpLen = 0;

    const int64 equip_roleid = table_equip.roleid();
    int iLen = iSqlLen + 128 + 8 + table_equip.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, EQUIPGETSQL, iTableIndex, equip_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define EQUIPGETSQL_DEBUG_WHERE " from equip_%d where  `roleid`=%lld;"
int GORM_PackGetSQLEQUIP_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_equip &table_equip, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("equip"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("equip table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_equip.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["equip"];
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
    const int64 equip_roleid = table_equip.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, EQUIPGETSQL_DEBUG_WHERE, iTableIndex, equip_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLEQUIP(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_equip())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_equip &table_equip = table.equip();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_EQUIP_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "equip", table.custom_columns());
    return GORM_PackGetSQLEQUIP_ONE_DEBUG(pMySQLEvent, iTableIndex, table_equip, pReqData);
#endif
    return GORM_PackGetSQLEQUIP_ONE(mysql, iTableIndex, table_equip, pReqData);
}
#define FOODGETSQL "select `version`, `roleid`, `snakeid`, `food1`, `food2`, `food3`, `food4` from food_%d where  `roleid`=%lld;"
int GORM_PackGetSQLFOOD_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_food &table_food, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 129;
    int iTmpLen = 0;

    const int64 food_roleid = table_food.roleid();
    int iLen = iSqlLen + 128 + 8 + table_food.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, FOODGETSQL, iTableIndex, food_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define FOODGETSQL_DEBUG_WHERE " from food_%d where  `roleid`=%lld;"
int GORM_PackGetSQLFOOD_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_food &table_food, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("food"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("food table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_food.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["food"];
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
    const int64 food_roleid = table_food.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, FOODGETSQL_DEBUG_WHERE, iTableIndex, food_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLFOOD(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_food())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_food &table_food = table.food();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_FOOD_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "food", table.custom_columns());
    return GORM_PackGetSQLFOOD_ONE_DEBUG(pMySQLEvent, iTableIndex, table_food, pReqData);
#endif
    return GORM_PackGetSQLFOOD_ONE(mysql, iTableIndex, table_food, pReqData);
}
#define HEROGETSQL "select `version`, `roleid`, `snakeid`, `heros` from hero_%d where  `roleid`=%lld;"
int GORM_PackGetSQLHERO_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_hero &table_hero, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 102;
    int iTmpLen = 0;

    const int64 hero_roleid = table_hero.roleid();
    int iLen = iSqlLen + 128 + 8 + table_hero.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, HEROGETSQL, iTableIndex, hero_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define HEROGETSQL_DEBUG_WHERE " from hero_%d where  `roleid`=%lld;"
int GORM_PackGetSQLHERO_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_hero &table_hero, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("hero"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("hero table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_hero.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["hero"];
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
    const int64 hero_roleid = table_hero.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, HEROGETSQL_DEBUG_WHERE, iTableIndex, hero_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLHERO(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_hero())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_hero &table_hero = table.hero();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_HERO_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "hero", table.custom_columns());
    return GORM_PackGetSQLHERO_ONE_DEBUG(pMySQLEvent, iTableIndex, table_hero, pReqData);
#endif
    return GORM_PackGetSQLHERO_ONE(mysql, iTableIndex, table_hero, pReqData);
}
#define MAILGETSQL "select `version`, `roleid`, `mail1`, `mail2`, `mail3`, `mail4`, `mail5`, `lastmailid`, `snakeid` from mail_%d where  `roleid`=%lld;"
int GORM_PackGetSQLMAIL_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_mail &table_mail, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 152;
    int iTmpLen = 0;

    const int64 mail_roleid = table_mail.roleid();
    int iLen = iSqlLen + 128 + 8 + table_mail.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, MAILGETSQL, iTableIndex, mail_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define MAILGETSQL_DEBUG_WHERE " from mail_%d where  `roleid`=%lld;"
int GORM_PackGetSQLMAIL_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_mail &table_mail, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("mail"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("mail table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_mail.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["mail"];
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
    const int64 mail_roleid = table_mail.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, MAILGETSQL_DEBUG_WHERE, iTableIndex, mail_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLMAIL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_mail())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_mail &table_mail = table.mail();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_MAIL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "mail", table.custom_columns());
    return GORM_PackGetSQLMAIL_ONE_DEBUG(pMySQLEvent, iTableIndex, table_mail, pReqData);
#endif
    return GORM_PackGetSQLMAIL_ONE(mysql, iTableIndex, table_mail, pReqData);
}
#define MATERIALGETSQL "select `version`, `roleid`, `snakeid`, `material1`, `material2`, `material3`, `material4` from material_%d where  `roleid`=%lld;"
int GORM_PackGetSQLMATERIAL_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_material &table_material, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 153;
    int iTmpLen = 0;

    const int64 material_roleid = table_material.roleid();
    int iLen = iSqlLen + 128 + 8 + table_material.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, MATERIALGETSQL, iTableIndex, material_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define MATERIALGETSQL_DEBUG_WHERE " from material_%d where  `roleid`=%lld;"
int GORM_PackGetSQLMATERIAL_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_material &table_material, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("material"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("material table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_material.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["material"];
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
    const int64 material_roleid = table_material.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, MATERIALGETSQL_DEBUG_WHERE, iTableIndex, material_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLMATERIAL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_material())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_material &table_material = table.material();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_MATERIAL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "material", table.custom_columns());
    return GORM_PackGetSQLMATERIAL_ONE_DEBUG(pMySQLEvent, iTableIndex, table_material, pReqData);
#endif
    return GORM_PackGetSQLMATERIAL_ONE(mysql, iTableIndex, table_material, pReqData);
}
#define NPCGETSQL "select `version`, `roleid`, `snakeid`, `npcs` from npc_%d where  `roleid`=%lld;"
int GORM_PackGetSQLNPC_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_npc &table_npc, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 99;
    int iTmpLen = 0;

    const int64 npc_roleid = table_npc.roleid();
    int iLen = iSqlLen + 128 + 8 + table_npc.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, NPCGETSQL, iTableIndex, npc_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define NPCGETSQL_DEBUG_WHERE " from npc_%d where  `roleid`=%lld;"
int GORM_PackGetSQLNPC_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_npc &table_npc, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("npc"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("npc table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_npc.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["npc"];
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
    const int64 npc_roleid = table_npc.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, NPCGETSQL_DEBUG_WHERE, iTableIndex, npc_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLNPC(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_npc())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_npc &table_npc = table.npc();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_NPC_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "npc", table.custom_columns());
    return GORM_PackGetSQLNPC_ONE_DEBUG(pMySQLEvent, iTableIndex, table_npc, pReqData);
#endif
    return GORM_PackGetSQLNPC_ONE(mysql, iTableIndex, table_npc, pReqData);
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
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLEGETSQL, iTableIndex, role_roleid);
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
            iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ",`%s`", (char*)(c.c_str()));
        else
            iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`%s`", (char*)(c.c_str()));
    }
    const int64 role_roleid = table_role.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ROLEGETSQL_DEBUG_WHERE, iTableIndex, role_roleid);
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
#define SCENEGETSQL "select `version`, `roleid`, `sceneid`, `collects` from scene_%d where  `roleid`=%lld;"
int GORM_PackGetSQLSCENE_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_scene &table_scene, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 107;
    int iTmpLen = 0;

    const int64 scene_roleid = table_scene.roleid();
    int iLen = iSqlLen + 128 + 8 + table_scene.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, SCENEGETSQL, iTableIndex, scene_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define SCENEGETSQL_DEBUG_WHERE " from scene_%d where  `roleid`=%lld;"
int GORM_PackGetSQLSCENE_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_scene &table_scene, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("scene"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("scene table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_scene.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["scene"];
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
    const int64 scene_roleid = table_scene.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, SCENEGETSQL_DEBUG_WHERE, iTableIndex, scene_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLSCENE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_scene())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_scene &table_scene = table.scene();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_SCENE_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "scene", table.custom_columns());
    return GORM_PackGetSQLSCENE_ONE_DEBUG(pMySQLEvent, iTableIndex, table_scene, pReqData);
#endif
    return GORM_PackGetSQLSCENE_ONE(mysql, iTableIndex, table_scene, pReqData);
}
#define SKILLGETSQL "select `version`, `roleid`, `snakeid`, `skill1`, `skill2`, `skill3`, `skill4` from skill_%d where  `roleid`=%lld;"
int GORM_PackGetSQLSKILL_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_skill &table_skill, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 135;
    int iTmpLen = 0;

    const int64 skill_roleid = table_skill.roleid();
    int iLen = iSqlLen + 128 + 8 + table_skill.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, SKILLGETSQL, iTableIndex, skill_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define SKILLGETSQL_DEBUG_WHERE " from skill_%d where  `roleid`=%lld;"
int GORM_PackGetSQLSKILL_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_skill &table_skill, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("skill"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("skill table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_skill.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["skill"];
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
    const int64 skill_roleid = table_skill.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, SKILLGETSQL_DEBUG_WHERE, iTableIndex, skill_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLSKILL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_skill())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_skill &table_skill = table.skill();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_SKILL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "skill", table.custom_columns());
    return GORM_PackGetSQLSKILL_ONE_DEBUG(pMySQLEvent, iTableIndex, table_skill, pReqData);
#endif
    return GORM_PackGetSQLSKILL_ONE(mysql, iTableIndex, table_skill, pReqData);
}
#define INTERACTIONGETSQL "select `version`, `roleid`, `snakeid`, `interaction1`, `interaction2`, `interaction3`, `interaction4` from interaction_%d where  `roleid`=%lld;"
int GORM_PackGetSQLINTERACTION_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_interaction &table_interaction, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 171;
    int iTmpLen = 0;

    const int64 interaction_roleid = table_interaction.roleid();
    int iLen = iSqlLen + 128 + 8 + table_interaction.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, INTERACTIONGETSQL, iTableIndex, interaction_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define INTERACTIONGETSQL_DEBUG_WHERE " from interaction_%d where  `roleid`=%lld;"
int GORM_PackGetSQLINTERACTION_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_interaction &table_interaction, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("interaction"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("interaction table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_interaction.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["interaction"];
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
    const int64 interaction_roleid = table_interaction.roleid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, INTERACTIONGETSQL_DEBUG_WHERE, iTableIndex, interaction_roleid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLINTERACTION(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_interaction())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_interaction &table_interaction = table.interaction();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_INTERACTION_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "interaction", table.custom_columns());
    return GORM_PackGetSQLINTERACTION_ONE_DEBUG(pMySQLEvent, iTableIndex, table_interaction, pReqData);
#endif
    return GORM_PackGetSQLINTERACTION_ONE(mysql, iTableIndex, table_interaction, pReqData);
}
#define USERGETSQL "select `version`, `userid`, `ptid`, `pttype`, `createtime` from user_%d where  `userid`=%lld;"
int GORM_PackGetSQLUSER_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_user &table_user, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 114;
    int iTmpLen = 0;

    const int64 user_userid = table_user.userid();
    int iLen = iSqlLen + 128 + 8 + table_user.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, USERGETSQL, iTableIndex, user_userid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define USERGETSQL_DEBUG_WHERE " from user_%d where  `userid`=%lld;"
int GORM_PackGetSQLUSER_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_user &table_user, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("user"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("user table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_user.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["user"];
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
    const int64 user_userid = table_user.userid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, USERGETSQL_DEBUG_WHERE, iTableIndex, user_userid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLUSER(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_user())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_user &table_user = table.user();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_USER_USERID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "user", table.custom_columns());
    return GORM_PackGetSQLUSER_ONE_DEBUG(pMySQLEvent, iTableIndex, table_user, pReqData);
#endif
    return GORM_PackGetSQLUSER_ONE(mysql, iTableIndex, table_user, pReqData);
}
#define ROLESGETSQL "select `version`, `roleid`, `userid`, `worldid`, `dbid`, `name`, `charid`, `face`, `createtime` from roles_%d where  `roleid`=%lld and `userid`=%lld;"
int GORM_PackGetSQLROLES_ONE(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_roles &table_roles, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 171;
    int iTmpLen = 0;

    const int64 roles_roleid = table_roles.roleid();
    const int64 roles_userid = table_roles.userid();
    int iLen = iSqlLen + 128 + 8 + 8 + table_roles.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLESGETSQL, iTableIndex, roles_roleid, roles_userid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
#define ROLESGETSQL_DEBUG_WHERE " from roles_%d where  `roleid`=%lld and `userid`=%lld;"
int GORM_PackGetSQLROLES_ONE_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_Table_roles &table_roles, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
    char *szSQLBegin = nullptr;
    int iSqlLen = 93;
    int iTmpLen = 0;
    auto itr = pMySQLEvent->m_mapTablesColumnInfo.find(string("roles"));
    if (itr == pMySQLEvent->m_mapTablesColumnInfo.end())
    {
        GORM_LOGE("roles table info not inited");
        return GORM_ERROR;
    }
    unordered_map<string, GORM_PB_COLUMN_TYPE> &columnMap = itr->second;
    if (columnMap.size() == 0)
        return GORM_ERROR;
    int iTotalLen = iSqlLen + 128 + 64*columnMap.size() + table_roles.ByteSizeLong();
    int iLen = 7;
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, "select ", 7);
    int idx = 0;
    vector<string> &vectorColumns = pMySQLEvent->m_mapTablesColumnOrder["roles"];
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
    const int64 roles_roleid = table_roles.roleid();
    const int64 roles_userid = table_roles.userid();
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ROLESGETSQL_DEBUG_WHERE, iTableIndex, roles_roleid, roles_userid);
    pReqData->m_sUsedSize = iLen;


    return GORM_OK;
}
int GORM_PackGetSQLROLES(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_roles())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    const GORM_PB_Table_roles &table_roles = table.roles();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLES_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLES_USERID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    
#ifdef GORM_DEBUG
    GORM_MySQLUpdateTableSchema(pMySQLEvent, "roles", table.custom_columns());
    return GORM_PackGetSQLROLES_ONE_DEBUG(pMySQLEvent, iTableIndex, table_roles, pReqData);
#endif
    return GORM_PackGetSQLROLES_ONE(mysql, iTableIndex, table_roles, pReqData);
}
int GORM_PackGetSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackGetSQLCURRENCY(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackGetSQLCYCLEEVENT(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_EQUIP:
        return GORM_PackGetSQLEQUIP(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_FOOD:
        return GORM_PackGetSQLFOOD(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_HERO:
        return GORM_PackGetSQLHERO(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MAIL:
        return GORM_PackGetSQLMAIL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MATERIAL:
        return GORM_PackGetSQLMATERIAL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_NPC:
        return GORM_PackGetSQLNPC(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackGetSQLROLE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SCENE:
        return GORM_PackGetSQLSCENE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SKILL:
        return GORM_PackGetSQLSKILL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_INTERACTION:
        return GORM_PackGetSQLINTERACTION(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_USER:
        return GORM_PackGetSQLUSER(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLES:
        return GORM_PackGetSQLROLES(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define CURRENCYDELETESQL "delete  from currency_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLCURRENCY(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CURRENCYDELETESQL, iTableIndex, currency_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "currency", table.custom_columns());
#endif
    return GORM_OK;
}
#define CYCLEEVENTDELETESQL "delete  from cycleevent_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLCYCLEEVENT(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTDELETESQL, iTableIndex, cycleevent_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
#endif
    return GORM_OK;
}
#define EQUIPDELETESQL "delete  from equip_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLEQUIP(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_equip())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = 68;
    int iTmpLen = 0;

    GORM_PB_Table_equip table_equip = table.equip();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_EQUIP_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 equip_roleid = table_equip.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, EQUIPDELETESQL, iTableIndex, equip_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "equip", table.custom_columns());
#endif
    return GORM_OK;
}
#define FOODDELETESQL "delete  from food_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLFOOD(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_food())
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

    GORM_PB_Table_food table_food = table.food();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_FOOD_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 food_roleid = table_food.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, FOODDELETESQL, iTableIndex, food_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "food", table.custom_columns());
#endif
    return GORM_OK;
}
#define HERODELETESQL "delete  from hero_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLHERO(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_hero())
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

    GORM_PB_Table_hero table_hero = table.hero();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_HERO_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 hero_roleid = table_hero.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, HERODELETESQL, iTableIndex, hero_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "hero", table.custom_columns());
#endif
    return GORM_OK;
}
#define MAILDELETESQL "delete  from mail_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLMAIL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_mail())
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

    GORM_PB_Table_mail table_mail = table.mail();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_MAIL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 mail_roleid = table_mail.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, MAILDELETESQL, iTableIndex, mail_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "mail", table.custom_columns());
#endif
    return GORM_OK;
}
#define MATERIALDELETESQL "delete  from material_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLMATERIAL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_material())
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

    GORM_PB_Table_material table_material = table.material();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_MATERIAL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 material_roleid = table_material.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, MATERIALDELETESQL, iTableIndex, material_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "material", table.custom_columns());
#endif
    return GORM_OK;
}
#define NPCDELETESQL "delete  from npc_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLNPC(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_npc())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = 64;
    int iTmpLen = 0;

    GORM_PB_Table_npc table_npc = table.npc();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_NPC_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 npc_roleid = table_npc.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, NPCDELETESQL, iTableIndex, npc_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "npc", table.custom_columns());
#endif
    return GORM_OK;
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
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLEDELETESQL, iTableIndex, role_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
    return GORM_OK;
}
#define SCENEDELETESQL "delete  from scene_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLSCENE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_scene())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = 68;
    int iTmpLen = 0;

    GORM_PB_Table_scene table_scene = table.scene();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_SCENE_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 scene_roleid = table_scene.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, SCENEDELETESQL, iTableIndex, scene_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "scene", table.custom_columns());
#endif
    return GORM_OK;
}
#define SKILLDELETESQL "delete  from skill_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLSKILL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_skill())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = 68;
    int iTmpLen = 0;

    GORM_PB_Table_skill table_skill = table.skill();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_SKILL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 skill_roleid = table_skill.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, SKILLDELETESQL, iTableIndex, skill_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "skill", table.custom_columns());
#endif
    return GORM_OK;
}
#define INTERACTIONDELETESQL "delete  from interaction_%d where  `roleid`=%lld;"
int GORM_PackDeleteSQLINTERACTION(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_interaction())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = 80;
    int iTmpLen = 0;

    GORM_PB_Table_interaction table_interaction = table.interaction();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_INTERACTION_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 interaction_roleid = table_interaction.roleid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, INTERACTIONDELETESQL, iTableIndex, interaction_roleid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "interaction", table.custom_columns());
#endif
    return GORM_OK;
}
#define USERDELETESQL "delete  from user_%d where  `userid`=%lld;"
int GORM_PackDeleteSQLUSER(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_user())
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

    GORM_PB_Table_user table_user = table.user();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_USER_USERID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 user_userid = table_user.userid();
    int iLen = iSqlLen + 128 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, USERDELETESQL, iTableIndex, user_userid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "user", table.custom_columns());
#endif
    return GORM_OK;
}
#define ROLESDELETESQL "delete  from roles_%d where  `roleid`=%lld and  `userid`=%lld;"
int GORM_PackDeleteSQLROLES(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (!pMsg->has_table())
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->table();
    if (!table.has_roles())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = 87;
    int iTmpLen = 0;

    GORM_PB_Table_roles table_roles = table.roles();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLES_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLES_USERID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const int64 roles_roleid = table_roles.roleid();
    const int64 roles_userid = table_roles.userid();
    int iLen = iSqlLen + 128 + 8 + 8 + pMsg->ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iLen);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLESDELETESQL, iTableIndex, roles_roleid, roles_userid);
    pReqData->m_sUsedSize = iLen;

    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "roles", table.custom_columns());
#endif
    return GORM_OK;
}
int GORM_PackDeleteSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackDeleteSQLCURRENCY(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackDeleteSQLCYCLEEVENT(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_EQUIP:
        return GORM_PackDeleteSQLEQUIP(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_FOOD:
        return GORM_PackDeleteSQLFOOD(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_HERO:
        return GORM_PackDeleteSQLHERO(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MAIL:
        return GORM_PackDeleteSQLMAIL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MATERIAL:
        return GORM_PackDeleteSQLMATERIAL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_NPC:
        return GORM_PackDeleteSQLNPC(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackDeleteSQLROLE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SCENE:
        return GORM_PackDeleteSQLSCENE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SKILL:
        return GORM_PackDeleteSQLSKILL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_INTERACTION:
        return GORM_PackDeleteSQLINTERACTION(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_USER:
        return GORM_PackDeleteSQLUSER(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLES:
        return GORM_PackDeleteSQLROLES(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define CURRENCYUPDATESQL "update currency_%d set "
#define CURRENCYUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLCURRENCY(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
        buffer_currency_currency1 = GORM_MemPool::Instance()->GetData(currency_currency1.size()<<1);
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
        buffer_currency_currency2 = GORM_MemPool::Instance()->GetData(currency_currency2.size()<<1);
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
        buffer_currency_currency3 = GORM_MemPool::Instance()->GetData(currency_currency3.size()<<1);
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
        buffer_currency_currency4 = GORM_MemPool::Instance()->GetData(currency_currency4.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_currency_currency4->m_uszData, currency_currency4.c_str(), currency_currency4.size());
        buffer_currency_currency4->m_uszData[iTmpLen] = 0;
        buffer_currency_currency4->m_sUsedSize = iTmpLen;
        sz_currency_currency4 = buffer_currency_currency4->m_uszData;
        len_currency_currency4 = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_currency_currency1 + len_currency_currency2 + len_currency_currency3 + len_currency_currency4 + 24;
    GORM_MemPoolData *buffer_currency_where = nullptr;
    buffer_currency_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_currency_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_currency_where->m_sCapacity, CURRENCYUPDATEWHERESQL , currency_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_currency_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), currency_version);
    buffer_currency_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_currency_currency1+ len_currency_currency2+ len_currency_currency3+ len_currency_currency4+24;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
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
int GORM_PackUpdateSQLCYCLEEVENT(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
        buffer_cycleevent_events = GORM_MemPool::Instance()->GetData(cycleevent_events.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_cycleevent_events->m_uszData, cycleevent_events.c_str(), cycleevent_events.size());
        buffer_cycleevent_events->m_uszData[iTmpLen] = 0;
        buffer_cycleevent_events->m_sUsedSize = iTmpLen;
        sz_cycleevent_events = buffer_cycleevent_events->m_uszData;
        len_cycleevent_events = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_cycleevent_events + 16;
    GORM_MemPoolData *buffer_cycleevent_where = nullptr;
    buffer_cycleevent_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_cycleevent_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_cycleevent_where->m_sCapacity, CYCLEEVENTUPDATEWHERESQL , cycleevent_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_cycleevent_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), cycleevent_version);
    buffer_cycleevent_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_cycleevent_events+16;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
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
#define EQUIPUPDATESQL "update equip_%d set "
#define EQUIPUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLEQUIP(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_equip())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(EQUIPUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_equip &table_equip = table.equip();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_EQUIP_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 equip_version = table_equip.version();
    const int64 equip_roleid = table_equip.roleid();
    const int32 equip_snakeid = table_equip.snakeid();
    const string &equip_equip1 = table_equip.equip1();
    char *sz_equip_equip1 = "";
    int len_equip_equip1 = 0;
    GORM_MemPoolData *buffer_equip_equip1 = nullptr;
    if(equip_equip1.size() > 0)
    {
        buffer_equip_equip1 = GORM_MemPool::Instance()->GetData(equip_equip1.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_equip_equip1->m_uszData, equip_equip1.c_str(), equip_equip1.size());
        buffer_equip_equip1->m_uszData[iTmpLen] = 0;
        buffer_equip_equip1->m_sUsedSize = iTmpLen;
        sz_equip_equip1 = buffer_equip_equip1->m_uszData;
        len_equip_equip1 = iTmpLen;
    }

    const string &equip_equip2 = table_equip.equip2();
    char *sz_equip_equip2 = "";
    int len_equip_equip2 = 0;
    GORM_MemPoolData *buffer_equip_equip2 = nullptr;
    if(equip_equip2.size() > 0)
    {
        buffer_equip_equip2 = GORM_MemPool::Instance()->GetData(equip_equip2.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_equip_equip2->m_uszData, equip_equip2.c_str(), equip_equip2.size());
        buffer_equip_equip2->m_uszData[iTmpLen] = 0;
        buffer_equip_equip2->m_sUsedSize = iTmpLen;
        sz_equip_equip2 = buffer_equip_equip2->m_uszData;
        len_equip_equip2 = iTmpLen;
    }

    const string &equip_equip3 = table_equip.equip3();
    char *sz_equip_equip3 = "";
    int len_equip_equip3 = 0;
    GORM_MemPoolData *buffer_equip_equip3 = nullptr;
    if(equip_equip3.size() > 0)
    {
        buffer_equip_equip3 = GORM_MemPool::Instance()->GetData(equip_equip3.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_equip_equip3->m_uszData, equip_equip3.c_str(), equip_equip3.size());
        buffer_equip_equip3->m_uszData[iTmpLen] = 0;
        buffer_equip_equip3->m_sUsedSize = iTmpLen;
        sz_equip_equip3 = buffer_equip_equip3->m_uszData;
        len_equip_equip3 = iTmpLen;
    }

    const string &equip_equip4 = table_equip.equip4();
    char *sz_equip_equip4 = "";
    int len_equip_equip4 = 0;
    GORM_MemPoolData *buffer_equip_equip4 = nullptr;
    if(equip_equip4.size() > 0)
    {
        buffer_equip_equip4 = GORM_MemPool::Instance()->GetData(equip_equip4.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_equip_equip4->m_uszData, equip_equip4.c_str(), equip_equip4.size());
        buffer_equip_equip4->m_uszData[iTmpLen] = 0;
        buffer_equip_equip4->m_sUsedSize = iTmpLen;
        sz_equip_equip4 = buffer_equip_equip4->m_uszData;
        len_equip_equip4 = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_equip_equip1 + len_equip_equip2 + len_equip_equip3 + len_equip_equip4 + 24;
    GORM_MemPoolData *buffer_equip_where = nullptr;
    buffer_equip_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_equip_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_equip_where->m_sCapacity, EQUIPUPDATEWHERESQL , equip_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_equip_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), equip_version);
    buffer_equip_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_equip_equip1+ len_equip_equip2+ len_equip_equip3+ len_equip_equip4+24;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, EQUIPUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), equip_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_EQUIP_VERSION == iFieldId || GORM_PB_FIELD_EQUIP_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", equip_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", equip_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", equip_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", equip_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=%d", equip_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`snakeid`=%d", equip_snakeid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP1:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `equip1`=\"%s\"", sz_equip_equip1);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`equip1`=\"%s\"", sz_equip_equip1);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP2:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `equip2`=\"%s\"", sz_equip_equip2);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`equip2`=\"%s\"", sz_equip_equip2);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP3:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `equip3`=\"%s\"", sz_equip_equip3);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`equip3`=\"%s\"", sz_equip_equip3);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP4:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `equip4`=\"%s\"", sz_equip_equip4);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`equip4`=\"%s\"", sz_equip_equip4);
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

    if (buffer_equip_equip1 != nullptr)
        buffer_equip_equip1->Release();
    if (buffer_equip_equip2 != nullptr)
        buffer_equip_equip2->Release();
    if (buffer_equip_equip3 != nullptr)
        buffer_equip_equip3->Release();
    if (buffer_equip_equip4 != nullptr)
        buffer_equip_equip4->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "equip", table.custom_columns());
#endif
    return GORM_OK;
}
#define FOODUPDATESQL "update food_%d set "
#define FOODUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLFOOD(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_food())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(FOODUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_food &table_food = table.food();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_FOOD_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 food_version = table_food.version();
    const int64 food_roleid = table_food.roleid();
    const int32 food_snakeid = table_food.snakeid();
    const string &food_food1 = table_food.food1();
    char *sz_food_food1 = "";
    int len_food_food1 = 0;
    GORM_MemPoolData *buffer_food_food1 = nullptr;
    if(food_food1.size() > 0)
    {
        buffer_food_food1 = GORM_MemPool::Instance()->GetData(food_food1.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_food_food1->m_uszData, food_food1.c_str(), food_food1.size());
        buffer_food_food1->m_uszData[iTmpLen] = 0;
        buffer_food_food1->m_sUsedSize = iTmpLen;
        sz_food_food1 = buffer_food_food1->m_uszData;
        len_food_food1 = iTmpLen;
    }

    const string &food_food2 = table_food.food2();
    char *sz_food_food2 = "";
    int len_food_food2 = 0;
    GORM_MemPoolData *buffer_food_food2 = nullptr;
    if(food_food2.size() > 0)
    {
        buffer_food_food2 = GORM_MemPool::Instance()->GetData(food_food2.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_food_food2->m_uszData, food_food2.c_str(), food_food2.size());
        buffer_food_food2->m_uszData[iTmpLen] = 0;
        buffer_food_food2->m_sUsedSize = iTmpLen;
        sz_food_food2 = buffer_food_food2->m_uszData;
        len_food_food2 = iTmpLen;
    }

    const string &food_food3 = table_food.food3();
    char *sz_food_food3 = "";
    int len_food_food3 = 0;
    GORM_MemPoolData *buffer_food_food3 = nullptr;
    if(food_food3.size() > 0)
    {
        buffer_food_food3 = GORM_MemPool::Instance()->GetData(food_food3.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_food_food3->m_uszData, food_food3.c_str(), food_food3.size());
        buffer_food_food3->m_uszData[iTmpLen] = 0;
        buffer_food_food3->m_sUsedSize = iTmpLen;
        sz_food_food3 = buffer_food_food3->m_uszData;
        len_food_food3 = iTmpLen;
    }

    const string &food_food4 = table_food.food4();
    char *sz_food_food4 = "";
    int len_food_food4 = 0;
    GORM_MemPoolData *buffer_food_food4 = nullptr;
    if(food_food4.size() > 0)
    {
        buffer_food_food4 = GORM_MemPool::Instance()->GetData(food_food4.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_food_food4->m_uszData, food_food4.c_str(), food_food4.size());
        buffer_food_food4->m_uszData[iTmpLen] = 0;
        buffer_food_food4->m_sUsedSize = iTmpLen;
        sz_food_food4 = buffer_food_food4->m_uszData;
        len_food_food4 = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_food_food1 + len_food_food2 + len_food_food3 + len_food_food4 + 24;
    GORM_MemPoolData *buffer_food_where = nullptr;
    buffer_food_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_food_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_food_where->m_sCapacity, FOODUPDATEWHERESQL , food_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_food_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), food_version);
    buffer_food_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_food_food1+ len_food_food2+ len_food_food3+ len_food_food4+24;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, FOODUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), food_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_FOOD_VERSION == iFieldId || GORM_PB_FIELD_FOOD_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", food_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", food_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", food_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", food_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=%d", food_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`snakeid`=%d", food_snakeid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD1:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `food1`=\"%s\"", sz_food_food1);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`food1`=\"%s\"", sz_food_food1);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD2:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `food2`=\"%s\"", sz_food_food2);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`food2`=\"%s\"", sz_food_food2);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD3:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `food3`=\"%s\"", sz_food_food3);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`food3`=\"%s\"", sz_food_food3);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD4:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `food4`=\"%s\"", sz_food_food4);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`food4`=\"%s\"", sz_food_food4);
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

    if (buffer_food_food1 != nullptr)
        buffer_food_food1->Release();
    if (buffer_food_food2 != nullptr)
        buffer_food_food2->Release();
    if (buffer_food_food3 != nullptr)
        buffer_food_food3->Release();
    if (buffer_food_food4 != nullptr)
        buffer_food_food4->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "food", table.custom_columns());
#endif
    return GORM_OK;
}
#define HEROUPDATESQL "update hero_%d set "
#define HEROUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLHERO(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_hero())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(HEROUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_hero &table_hero = table.hero();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_HERO_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 hero_version = table_hero.version();
    const int64 hero_roleid = table_hero.roleid();
    const int32 hero_snakeid = table_hero.snakeid();
    const string &hero_heros = table_hero.heros();
    char *sz_hero_heros = "";
    int len_hero_heros = 0;
    GORM_MemPoolData *buffer_hero_heros = nullptr;
    if(hero_heros.size() > 0)
    {
        buffer_hero_heros = GORM_MemPool::Instance()->GetData(hero_heros.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_hero_heros->m_uszData, hero_heros.c_str(), hero_heros.size());
        buffer_hero_heros->m_uszData[iTmpLen] = 0;
        buffer_hero_heros->m_sUsedSize = iTmpLen;
        sz_hero_heros = buffer_hero_heros->m_uszData;
        len_hero_heros = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_hero_heros + 24;
    GORM_MemPoolData *buffer_hero_where = nullptr;
    buffer_hero_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_hero_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_hero_where->m_sCapacity, HEROUPDATEWHERESQL , hero_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_hero_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), hero_version);
    buffer_hero_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_hero_heros+24;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, HEROUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), hero_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_HERO_VERSION == iFieldId || GORM_PB_FIELD_HERO_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", hero_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", hero_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", hero_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", hero_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=%d", hero_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`snakeid`=%d", hero_snakeid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_HERO_HEROS:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `heros`=\"%s\"", sz_hero_heros);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`heros`=\"%s\"", sz_hero_heros);
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

    if (buffer_hero_heros != nullptr)
        buffer_hero_heros->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "hero", table.custom_columns());
#endif
    return GORM_OK;
}
#define MAILUPDATESQL "update mail_%d set "
#define MAILUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLMAIL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_mail())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(MAILUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_mail &table_mail = table.mail();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_MAIL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 mail_version = table_mail.version();
    const int64 mail_roleid = table_mail.roleid();
    const string &mail_mail1 = table_mail.mail1();
    char *sz_mail_mail1 = "";
    int len_mail_mail1 = 0;
    GORM_MemPoolData *buffer_mail_mail1 = nullptr;
    if(mail_mail1.size() > 0)
    {
        buffer_mail_mail1 = GORM_MemPool::Instance()->GetData(mail_mail1.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_mail_mail1->m_uszData, mail_mail1.c_str(), mail_mail1.size());
        buffer_mail_mail1->m_uszData[iTmpLen] = 0;
        buffer_mail_mail1->m_sUsedSize = iTmpLen;
        sz_mail_mail1 = buffer_mail_mail1->m_uszData;
        len_mail_mail1 = iTmpLen;
    }

    const string &mail_mail2 = table_mail.mail2();
    char *sz_mail_mail2 = "";
    int len_mail_mail2 = 0;
    GORM_MemPoolData *buffer_mail_mail2 = nullptr;
    if(mail_mail2.size() > 0)
    {
        buffer_mail_mail2 = GORM_MemPool::Instance()->GetData(mail_mail2.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_mail_mail2->m_uszData, mail_mail2.c_str(), mail_mail2.size());
        buffer_mail_mail2->m_uszData[iTmpLen] = 0;
        buffer_mail_mail2->m_sUsedSize = iTmpLen;
        sz_mail_mail2 = buffer_mail_mail2->m_uszData;
        len_mail_mail2 = iTmpLen;
    }

    const string &mail_mail3 = table_mail.mail3();
    char *sz_mail_mail3 = "";
    int len_mail_mail3 = 0;
    GORM_MemPoolData *buffer_mail_mail3 = nullptr;
    if(mail_mail3.size() > 0)
    {
        buffer_mail_mail3 = GORM_MemPool::Instance()->GetData(mail_mail3.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_mail_mail3->m_uszData, mail_mail3.c_str(), mail_mail3.size());
        buffer_mail_mail3->m_uszData[iTmpLen] = 0;
        buffer_mail_mail3->m_sUsedSize = iTmpLen;
        sz_mail_mail3 = buffer_mail_mail3->m_uszData;
        len_mail_mail3 = iTmpLen;
    }

    const string &mail_mail4 = table_mail.mail4();
    char *sz_mail_mail4 = "";
    int len_mail_mail4 = 0;
    GORM_MemPoolData *buffer_mail_mail4 = nullptr;
    if(mail_mail4.size() > 0)
    {
        buffer_mail_mail4 = GORM_MemPool::Instance()->GetData(mail_mail4.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_mail_mail4->m_uszData, mail_mail4.c_str(), mail_mail4.size());
        buffer_mail_mail4->m_uszData[iTmpLen] = 0;
        buffer_mail_mail4->m_sUsedSize = iTmpLen;
        sz_mail_mail4 = buffer_mail_mail4->m_uszData;
        len_mail_mail4 = iTmpLen;
    }

    const string &mail_mail5 = table_mail.mail5();
    char *sz_mail_mail5 = "";
    int len_mail_mail5 = 0;
    GORM_MemPoolData *buffer_mail_mail5 = nullptr;
    if(mail_mail5.size() > 0)
    {
        buffer_mail_mail5 = GORM_MemPool::Instance()->GetData(mail_mail5.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_mail_mail5->m_uszData, mail_mail5.c_str(), mail_mail5.size());
        buffer_mail_mail5->m_uszData[iTmpLen] = 0;
        buffer_mail_mail5->m_sUsedSize = iTmpLen;
        sz_mail_mail5 = buffer_mail_mail5->m_uszData;
        len_mail_mail5 = iTmpLen;
    }

    const int32 mail_lastmailid = table_mail.lastmailid();
    const int32 mail_snakeid = table_mail.snakeid();

    int iWhereLen = iSqlLen + 128  + len_mail_mail1 + len_mail_mail2 + len_mail_mail3 + len_mail_mail4 + len_mail_mail5 + 32;
    GORM_MemPoolData *buffer_mail_where = nullptr;
    buffer_mail_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_mail_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_mail_where->m_sCapacity, MAILUPDATEWHERESQL , mail_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_mail_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), mail_version);
    buffer_mail_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_mail_mail1+ len_mail_mail2+ len_mail_mail3+ len_mail_mail4+ len_mail_mail5+32;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, MAILUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), mail_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_MAIL_VERSION == iFieldId || GORM_PB_FIELD_MAIL_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", mail_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", mail_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", mail_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", mail_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL1:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `mail1`=\"%s\"", sz_mail_mail1);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`mail1`=\"%s\"", sz_mail_mail1);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL2:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `mail2`=\"%s\"", sz_mail_mail2);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`mail2`=\"%s\"", sz_mail_mail2);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL3:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `mail3`=\"%s\"", sz_mail_mail3);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`mail3`=\"%s\"", sz_mail_mail3);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL4:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `mail4`=\"%s\"", sz_mail_mail4);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`mail4`=\"%s\"", sz_mail_mail4);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL5:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `mail5`=\"%s\"", sz_mail_mail5);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`mail5`=\"%s\"", sz_mail_mail5);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `lastmailid`=%d", mail_lastmailid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`lastmailid`=%d", mail_lastmailid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=%d", mail_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`snakeid`=%d", mail_snakeid);
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

    if (buffer_mail_mail1 != nullptr)
        buffer_mail_mail1->Release();
    if (buffer_mail_mail2 != nullptr)
        buffer_mail_mail2->Release();
    if (buffer_mail_mail3 != nullptr)
        buffer_mail_mail3->Release();
    if (buffer_mail_mail4 != nullptr)
        buffer_mail_mail4->Release();
    if (buffer_mail_mail5 != nullptr)
        buffer_mail_mail5->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "mail", table.custom_columns());
#endif
    return GORM_OK;
}
#define MATERIALUPDATESQL "update material_%d set "
#define MATERIALUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLMATERIAL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_material())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(MATERIALUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_material &table_material = table.material();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_MATERIAL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 material_version = table_material.version();
    const int64 material_roleid = table_material.roleid();
    const int32 material_snakeid = table_material.snakeid();
    const string &material_material1 = table_material.material1();
    char *sz_material_material1 = "";
    int len_material_material1 = 0;
    GORM_MemPoolData *buffer_material_material1 = nullptr;
    if(material_material1.size() > 0)
    {
        buffer_material_material1 = GORM_MemPool::Instance()->GetData(material_material1.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_material_material1->m_uszData, material_material1.c_str(), material_material1.size());
        buffer_material_material1->m_uszData[iTmpLen] = 0;
        buffer_material_material1->m_sUsedSize = iTmpLen;
        sz_material_material1 = buffer_material_material1->m_uszData;
        len_material_material1 = iTmpLen;
    }

    const string &material_material2 = table_material.material2();
    char *sz_material_material2 = "";
    int len_material_material2 = 0;
    GORM_MemPoolData *buffer_material_material2 = nullptr;
    if(material_material2.size() > 0)
    {
        buffer_material_material2 = GORM_MemPool::Instance()->GetData(material_material2.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_material_material2->m_uszData, material_material2.c_str(), material_material2.size());
        buffer_material_material2->m_uszData[iTmpLen] = 0;
        buffer_material_material2->m_sUsedSize = iTmpLen;
        sz_material_material2 = buffer_material_material2->m_uszData;
        len_material_material2 = iTmpLen;
    }

    const string &material_material3 = table_material.material3();
    char *sz_material_material3 = "";
    int len_material_material3 = 0;
    GORM_MemPoolData *buffer_material_material3 = nullptr;
    if(material_material3.size() > 0)
    {
        buffer_material_material3 = GORM_MemPool::Instance()->GetData(material_material3.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_material_material3->m_uszData, material_material3.c_str(), material_material3.size());
        buffer_material_material3->m_uszData[iTmpLen] = 0;
        buffer_material_material3->m_sUsedSize = iTmpLen;
        sz_material_material3 = buffer_material_material3->m_uszData;
        len_material_material3 = iTmpLen;
    }

    const string &material_material4 = table_material.material4();
    char *sz_material_material4 = "";
    int len_material_material4 = 0;
    GORM_MemPoolData *buffer_material_material4 = nullptr;
    if(material_material4.size() > 0)
    {
        buffer_material_material4 = GORM_MemPool::Instance()->GetData(material_material4.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_material_material4->m_uszData, material_material4.c_str(), material_material4.size());
        buffer_material_material4->m_uszData[iTmpLen] = 0;
        buffer_material_material4->m_sUsedSize = iTmpLen;
        sz_material_material4 = buffer_material_material4->m_uszData;
        len_material_material4 = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_material_material1 + len_material_material2 + len_material_material3 + len_material_material4 + 24;
    GORM_MemPoolData *buffer_material_where = nullptr;
    buffer_material_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_material_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_material_where->m_sCapacity, MATERIALUPDATEWHERESQL , material_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_material_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), material_version);
    buffer_material_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_material_material1+ len_material_material2+ len_material_material3+ len_material_material4+24;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, MATERIALUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), material_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_MATERIAL_VERSION == iFieldId || GORM_PB_FIELD_MATERIAL_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", material_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", material_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", material_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", material_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=%d", material_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`snakeid`=%d", material_snakeid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL1:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `material1`=\"%s\"", sz_material_material1);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`material1`=\"%s\"", sz_material_material1);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL2:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `material2`=\"%s\"", sz_material_material2);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`material2`=\"%s\"", sz_material_material2);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL3:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `material3`=\"%s\"", sz_material_material3);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`material3`=\"%s\"", sz_material_material3);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL4:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `material4`=\"%s\"", sz_material_material4);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`material4`=\"%s\"", sz_material_material4);
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

    if (buffer_material_material1 != nullptr)
        buffer_material_material1->Release();
    if (buffer_material_material2 != nullptr)
        buffer_material_material2->Release();
    if (buffer_material_material3 != nullptr)
        buffer_material_material3->Release();
    if (buffer_material_material4 != nullptr)
        buffer_material_material4->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "material", table.custom_columns());
#endif
    return GORM_OK;
}
#define NPCUPDATESQL "update npc_%d set "
#define NPCUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLNPC(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_npc())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(NPCUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_npc &table_npc = table.npc();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_NPC_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 npc_version = table_npc.version();
    const int64 npc_roleid = table_npc.roleid();
    const int32 npc_snakeid = table_npc.snakeid();
    const string &npc_npcs = table_npc.npcs();
    char *sz_npc_npcs = "";
    int len_npc_npcs = 0;
    GORM_MemPoolData *buffer_npc_npcs = nullptr;
    if(npc_npcs.size() > 0)
    {
        buffer_npc_npcs = GORM_MemPool::Instance()->GetData(npc_npcs.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_npc_npcs->m_uszData, npc_npcs.c_str(), npc_npcs.size());
        buffer_npc_npcs->m_uszData[iTmpLen] = 0;
        buffer_npc_npcs->m_sUsedSize = iTmpLen;
        sz_npc_npcs = buffer_npc_npcs->m_uszData;
        len_npc_npcs = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_npc_npcs + 24;
    GORM_MemPoolData *buffer_npc_where = nullptr;
    buffer_npc_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_npc_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_npc_where->m_sCapacity, NPCUPDATEWHERESQL , npc_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_npc_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), npc_version);
    buffer_npc_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_npc_npcs+24;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, NPCUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), npc_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_NPC_VERSION == iFieldId || GORM_PB_FIELD_NPC_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", npc_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", npc_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", npc_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", npc_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=%d", npc_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`snakeid`=%d", npc_snakeid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_NPC_NPCS:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `npcs`=\"%s\"", sz_npc_npcs);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`npcs`=\"%s\"", sz_npc_npcs);
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

    if (buffer_npc_npcs != nullptr)
        buffer_npc_npcs->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "npc", table.custom_columns());
#endif
    return GORM_OK;
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
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_role_where->m_sCapacity, ROLEUPDATEWHERESQL , role_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_role_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), role_version);
    buffer_role_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_role_rolename+ len_role_face+80;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLEUPDATESQL, iTableIndex);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", role_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", role_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", role_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", role_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLENAME:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `rolename`=\"%s\"", sz_role_rolename);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`rolename`=\"%s\"", sz_role_rolename);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `level`=%d", role_level);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`level`=%d", role_level);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `exp`=%lld", role_exp);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`exp`=%lld", role_exp);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `characterid`=%d", role_characterid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`characterid`=%d", role_characterid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `gold`=%d", role_gold);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`gold`=%d", role_gold);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `offlinetime`=%lld", role_offlinetime);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`offlinetime`=%lld", role_offlinetime);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `inited`=%d", role_inited);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`inited`=%d", role_inited);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `createtime`=%lld", role_createtime);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`createtime`=%lld", role_createtime);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_FACE:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `face`=\"%s\"", sz_role_face);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`face`=\"%s\"", sz_role_face);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `online`=%lld", role_online);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`online`=%lld", role_online);
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
#define SCENEUPDATESQL "update scene_%d set "
#define SCENEUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLSCENE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_scene())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(SCENEUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_scene &table_scene = table.scene();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_SCENE_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 scene_version = table_scene.version();
    const int64 scene_roleid = table_scene.roleid();
    const int32 scene_sceneid = table_scene.sceneid();
    const string &scene_collects = table_scene.collects();
    char *sz_scene_collects = "";
    int len_scene_collects = 0;
    GORM_MemPoolData *buffer_scene_collects = nullptr;
    if(scene_collects.size() > 0)
    {
        buffer_scene_collects = GORM_MemPool::Instance()->GetData(scene_collects.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_scene_collects->m_uszData, scene_collects.c_str(), scene_collects.size());
        buffer_scene_collects->m_uszData[iTmpLen] = 0;
        buffer_scene_collects->m_sUsedSize = iTmpLen;
        sz_scene_collects = buffer_scene_collects->m_uszData;
        len_scene_collects = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_scene_collects + 24;
    GORM_MemPoolData *buffer_scene_where = nullptr;
    buffer_scene_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_scene_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_scene_where->m_sCapacity, SCENEUPDATEWHERESQL , scene_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_scene_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), scene_version);
    buffer_scene_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_scene_collects+24;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, SCENEUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), scene_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_SCENE_VERSION == iFieldId || GORM_PB_FIELD_SCENE_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", scene_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", scene_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", scene_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", scene_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `sceneid`=%d", scene_sceneid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`sceneid`=%d", scene_sceneid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SCENE_COLLECTS:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `collects`=\"%s\"", sz_scene_collects);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`collects`=\"%s\"", sz_scene_collects);
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

    if (buffer_scene_collects != nullptr)
        buffer_scene_collects->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "scene", table.custom_columns());
#endif
    return GORM_OK;
}
#define SKILLUPDATESQL "update skill_%d set "
#define SKILLUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLSKILL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_skill())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(SKILLUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_skill &table_skill = table.skill();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_SKILL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 skill_version = table_skill.version();
    const int64 skill_roleid = table_skill.roleid();
    const int32 skill_snakeid = table_skill.snakeid();
    const string &skill_skill1 = table_skill.skill1();
    char *sz_skill_skill1 = "";
    int len_skill_skill1 = 0;
    GORM_MemPoolData *buffer_skill_skill1 = nullptr;
    if(skill_skill1.size() > 0)
    {
        buffer_skill_skill1 = GORM_MemPool::Instance()->GetData(skill_skill1.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_skill_skill1->m_uszData, skill_skill1.c_str(), skill_skill1.size());
        buffer_skill_skill1->m_uszData[iTmpLen] = 0;
        buffer_skill_skill1->m_sUsedSize = iTmpLen;
        sz_skill_skill1 = buffer_skill_skill1->m_uszData;
        len_skill_skill1 = iTmpLen;
    }

    const string &skill_skill2 = table_skill.skill2();
    char *sz_skill_skill2 = "";
    int len_skill_skill2 = 0;
    GORM_MemPoolData *buffer_skill_skill2 = nullptr;
    if(skill_skill2.size() > 0)
    {
        buffer_skill_skill2 = GORM_MemPool::Instance()->GetData(skill_skill2.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_skill_skill2->m_uszData, skill_skill2.c_str(), skill_skill2.size());
        buffer_skill_skill2->m_uszData[iTmpLen] = 0;
        buffer_skill_skill2->m_sUsedSize = iTmpLen;
        sz_skill_skill2 = buffer_skill_skill2->m_uszData;
        len_skill_skill2 = iTmpLen;
    }

    const string &skill_skill3 = table_skill.skill3();
    char *sz_skill_skill3 = "";
    int len_skill_skill3 = 0;
    GORM_MemPoolData *buffer_skill_skill3 = nullptr;
    if(skill_skill3.size() > 0)
    {
        buffer_skill_skill3 = GORM_MemPool::Instance()->GetData(skill_skill3.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_skill_skill3->m_uszData, skill_skill3.c_str(), skill_skill3.size());
        buffer_skill_skill3->m_uszData[iTmpLen] = 0;
        buffer_skill_skill3->m_sUsedSize = iTmpLen;
        sz_skill_skill3 = buffer_skill_skill3->m_uszData;
        len_skill_skill3 = iTmpLen;
    }

    const string &skill_skill4 = table_skill.skill4();
    char *sz_skill_skill4 = "";
    int len_skill_skill4 = 0;
    GORM_MemPoolData *buffer_skill_skill4 = nullptr;
    if(skill_skill4.size() > 0)
    {
        buffer_skill_skill4 = GORM_MemPool::Instance()->GetData(skill_skill4.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_skill_skill4->m_uszData, skill_skill4.c_str(), skill_skill4.size());
        buffer_skill_skill4->m_uszData[iTmpLen] = 0;
        buffer_skill_skill4->m_sUsedSize = iTmpLen;
        sz_skill_skill4 = buffer_skill_skill4->m_uszData;
        len_skill_skill4 = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_skill_skill1 + len_skill_skill2 + len_skill_skill3 + len_skill_skill4 + 24;
    GORM_MemPoolData *buffer_skill_where = nullptr;
    buffer_skill_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_skill_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_skill_where->m_sCapacity, SKILLUPDATEWHERESQL , skill_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_skill_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), skill_version);
    buffer_skill_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_skill_skill1+ len_skill_skill2+ len_skill_skill3+ len_skill_skill4+24;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, SKILLUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), skill_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_SKILL_VERSION == iFieldId || GORM_PB_FIELD_SKILL_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", skill_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", skill_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", skill_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", skill_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=%d", skill_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`snakeid`=%d", skill_snakeid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL1:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `skill1`=\"%s\"", sz_skill_skill1);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`skill1`=\"%s\"", sz_skill_skill1);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL2:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `skill2`=\"%s\"", sz_skill_skill2);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`skill2`=\"%s\"", sz_skill_skill2);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL3:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `skill3`=\"%s\"", sz_skill_skill3);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`skill3`=\"%s\"", sz_skill_skill3);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL4:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `skill4`=\"%s\"", sz_skill_skill4);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`skill4`=\"%s\"", sz_skill_skill4);
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

    if (buffer_skill_skill1 != nullptr)
        buffer_skill_skill1->Release();
    if (buffer_skill_skill2 != nullptr)
        buffer_skill_skill2->Release();
    if (buffer_skill_skill3 != nullptr)
        buffer_skill_skill3->Release();
    if (buffer_skill_skill4 != nullptr)
        buffer_skill_skill4->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "skill", table.custom_columns());
#endif
    return GORM_OK;
}
#define INTERACTIONUPDATESQL "update interaction_%d set "
#define INTERACTIONUPDATEWHERESQL " where `roleid`=%lld"
int GORM_PackUpdateSQLINTERACTION(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_interaction())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(INTERACTIONUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_interaction &table_interaction = table.interaction();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_INTERACTION_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 interaction_version = table_interaction.version();
    const int64 interaction_roleid = table_interaction.roleid();
    const int32 interaction_snakeid = table_interaction.snakeid();
    const string &interaction_interaction1 = table_interaction.interaction1();
    char *sz_interaction_interaction1 = "";
    int len_interaction_interaction1 = 0;
    GORM_MemPoolData *buffer_interaction_interaction1 = nullptr;
    if(interaction_interaction1.size() > 0)
    {
        buffer_interaction_interaction1 = GORM_MemPool::Instance()->GetData(interaction_interaction1.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_interaction_interaction1->m_uszData, interaction_interaction1.c_str(), interaction_interaction1.size());
        buffer_interaction_interaction1->m_uszData[iTmpLen] = 0;
        buffer_interaction_interaction1->m_sUsedSize = iTmpLen;
        sz_interaction_interaction1 = buffer_interaction_interaction1->m_uszData;
        len_interaction_interaction1 = iTmpLen;
    }

    const string &interaction_interaction2 = table_interaction.interaction2();
    char *sz_interaction_interaction2 = "";
    int len_interaction_interaction2 = 0;
    GORM_MemPoolData *buffer_interaction_interaction2 = nullptr;
    if(interaction_interaction2.size() > 0)
    {
        buffer_interaction_interaction2 = GORM_MemPool::Instance()->GetData(interaction_interaction2.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_interaction_interaction2->m_uszData, interaction_interaction2.c_str(), interaction_interaction2.size());
        buffer_interaction_interaction2->m_uszData[iTmpLen] = 0;
        buffer_interaction_interaction2->m_sUsedSize = iTmpLen;
        sz_interaction_interaction2 = buffer_interaction_interaction2->m_uszData;
        len_interaction_interaction2 = iTmpLen;
    }

    const string &interaction_interaction3 = table_interaction.interaction3();
    char *sz_interaction_interaction3 = "";
    int len_interaction_interaction3 = 0;
    GORM_MemPoolData *buffer_interaction_interaction3 = nullptr;
    if(interaction_interaction3.size() > 0)
    {
        buffer_interaction_interaction3 = GORM_MemPool::Instance()->GetData(interaction_interaction3.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_interaction_interaction3->m_uszData, interaction_interaction3.c_str(), interaction_interaction3.size());
        buffer_interaction_interaction3->m_uszData[iTmpLen] = 0;
        buffer_interaction_interaction3->m_sUsedSize = iTmpLen;
        sz_interaction_interaction3 = buffer_interaction_interaction3->m_uszData;
        len_interaction_interaction3 = iTmpLen;
    }

    const string &interaction_interaction4 = table_interaction.interaction4();
    char *sz_interaction_interaction4 = "";
    int len_interaction_interaction4 = 0;
    GORM_MemPoolData *buffer_interaction_interaction4 = nullptr;
    if(interaction_interaction4.size() > 0)
    {
        buffer_interaction_interaction4 = GORM_MemPool::Instance()->GetData(interaction_interaction4.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_interaction_interaction4->m_uszData, interaction_interaction4.c_str(), interaction_interaction4.size());
        buffer_interaction_interaction4->m_uszData[iTmpLen] = 0;
        buffer_interaction_interaction4->m_sUsedSize = iTmpLen;
        sz_interaction_interaction4 = buffer_interaction_interaction4->m_uszData;
        len_interaction_interaction4 = iTmpLen;
    }


    int iWhereLen = iSqlLen + 128  + len_interaction_interaction1 + len_interaction_interaction2 + len_interaction_interaction3 + len_interaction_interaction4 + 24;
    GORM_MemPoolData *buffer_interaction_where = nullptr;
    buffer_interaction_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_interaction_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_interaction_where->m_sCapacity, INTERACTIONUPDATEWHERESQL , interaction_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_interaction_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), interaction_version);
    buffer_interaction_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_interaction_interaction1+ len_interaction_interaction2+ len_interaction_interaction3+ len_interaction_interaction4+24;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, INTERACTIONUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), interaction_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_INTERACTION_VERSION == iFieldId || GORM_PB_FIELD_INTERACTION_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", interaction_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", interaction_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", interaction_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", interaction_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=%d", interaction_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`snakeid`=%d", interaction_snakeid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION1:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `interaction1`=\"%s\"", sz_interaction_interaction1);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`interaction1`=\"%s\"", sz_interaction_interaction1);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION2:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `interaction2`=\"%s\"", sz_interaction_interaction2);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`interaction2`=\"%s\"", sz_interaction_interaction2);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION3:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `interaction3`=\"%s\"", sz_interaction_interaction3);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`interaction3`=\"%s\"", sz_interaction_interaction3);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION4:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `interaction4`=\"%s\"", sz_interaction_interaction4);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`interaction4`=\"%s\"", sz_interaction_interaction4);
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

    if (buffer_interaction_interaction1 != nullptr)
        buffer_interaction_interaction1->Release();
    if (buffer_interaction_interaction2 != nullptr)
        buffer_interaction_interaction2->Release();
    if (buffer_interaction_interaction3 != nullptr)
        buffer_interaction_interaction3->Release();
    if (buffer_interaction_interaction4 != nullptr)
        buffer_interaction_interaction4->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "interaction", table.custom_columns());
#endif
    return GORM_OK;
}
#define USERUPDATESQL "update user_%d set "
#define USERUPDATEWHERESQL " where `userid`=%lld"
int GORM_PackUpdateSQLUSER(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_user())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(USERUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_user &table_user = table.user();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_USER_USERID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 user_version = table_user.version();
    const int64 user_userid = table_user.userid();
    const string &user_ptid = table_user.ptid();
    char *sz_user_ptid = "";
    int len_user_ptid = 0;
    GORM_MemPoolData *buffer_user_ptid = nullptr;
    if(user_ptid.size() > 0)
    {
        buffer_user_ptid = GORM_MemPool::Instance()->GetData(user_ptid.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_user_ptid->m_uszData, user_ptid.c_str(), user_ptid.size());
        buffer_user_ptid->m_uszData[iTmpLen] = 0;
        buffer_user_ptid->m_sUsedSize = iTmpLen;
        sz_user_ptid = buffer_user_ptid->m_uszData;
        len_user_ptid = iTmpLen;
    }

    const int32 user_pttype = table_user.pttype();
    const int64 user_createtime = table_user.createtime();

    int iWhereLen = iSqlLen + 128  + len_user_ptid + 32;
    GORM_MemPoolData *buffer_user_where = nullptr;
    buffer_user_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_user_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_user_where->m_sCapacity, USERUPDATEWHERESQL , user_userid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_user_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), user_version);
    buffer_user_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_user_ptid+32;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, USERUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), user_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_USER_VERSION == iFieldId || GORM_PB_FIELD_USER_USERID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", user_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", user_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `userid`=%lld", user_userid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`userid`=%lld", user_userid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_USER_PTID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `ptid`=\"%s\"", sz_user_ptid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`ptid`=\"%s\"", sz_user_ptid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `pttype`=%d", user_pttype);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`pttype`=%d", user_pttype);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `createtime`=%lld", user_createtime);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`createtime`=%lld", user_createtime);
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

    if (buffer_user_ptid != nullptr)
        buffer_user_ptid->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "user", table.custom_columns());
#endif
    return GORM_OK;
}
#define ROLESUPDATESQL "update roles_%d set "
#define ROLESUPDATEWHERESQL " where `roleid`=%lld and `userid`=%lld"
int GORM_PackUpdateSQLROLES(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_TABLE &table = pMsg->tables(0);
    if (!table.has_roles())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(ROLESUPDATESQL);
    int iTmpLen = 0;

    const GORM_PB_Table_roles &table_roles = table.roles();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLES_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLES_USERID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 roles_version = table_roles.version();
    const int64 roles_roleid = table_roles.roleid();
    const int64 roles_userid = table_roles.userid();
    const int64 roles_worldid = table_roles.worldid();
    const int32 roles_dbid = table_roles.dbid();
    const string &roles_name = table_roles.name();
    char *sz_roles_name = "";
    int len_roles_name = 0;
    GORM_MemPoolData *buffer_roles_name = nullptr;
    if(roles_name.size() > 0)
    {
        buffer_roles_name = GORM_MemPool::Instance()->GetData(roles_name.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_roles_name->m_uszData, roles_name.c_str(), roles_name.size());
        buffer_roles_name->m_uszData[iTmpLen] = 0;
        buffer_roles_name->m_sUsedSize = iTmpLen;
        sz_roles_name = buffer_roles_name->m_uszData;
        len_roles_name = iTmpLen;
    }

    const int32 roles_charid = table_roles.charid();
    const string &roles_face = table_roles.face();
    char *sz_roles_face = "";
    int len_roles_face = 0;
    GORM_MemPoolData *buffer_roles_face = nullptr;
    if(roles_face.size() > 0)
    {
        buffer_roles_face = GORM_MemPool::Instance()->GetData(roles_face.size()<<1);
        iTmpLen=mysql_real_escape_string(mysql, buffer_roles_face->m_uszData, roles_face.c_str(), roles_face.size());
        buffer_roles_face->m_uszData[iTmpLen] = 0;
        buffer_roles_face->m_sUsedSize = iTmpLen;
        sz_roles_face = buffer_roles_face->m_uszData;
        len_roles_face = iTmpLen;
    }

    const int64 roles_createtime = table_roles.createtime();

    int iWhereLen = iSqlLen + 128  + len_roles_name + len_roles_face + 56;
    GORM_MemPoolData *buffer_roles_where = nullptr;
    buffer_roles_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    iWhereLen = 0;
    char *szWhereBegin = buffer_roles_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen,  buffer_roles_where->m_sCapacity, ROLESUPDATEWHERESQL , roles_roleid, roles_userid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_roles_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), roles_version);
    buffer_roles_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() + len_roles_name+ len_roles_face+56;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    int iUpdateLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLESUPDATESQL, iTableIndex);
    szSQLBegin += iUpdateLen;
    pReqData->m_sUsedSize = iUpdateLen;
    int iDataLen = 0;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen, GORM_CheckDataVerType(header.verpolice()), roles_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_ROLES_VERSION == iFieldId || GORM_PB_FIELD_ROLES_ROLEID == iFieldId || GORM_PB_FIELD_ROLES_USERID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=%llu", roles_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`version`=%llu", roles_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=%lld", roles_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`roleid`=%lld", roles_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `userid`=%lld", roles_userid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`userid`=%lld", roles_userid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `worldid`=%lld", roles_worldid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`worldid`=%lld", roles_worldid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `dbid`=%d", roles_dbid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`dbid`=%d", roles_dbid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_NAME:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `name`=\"%s\"", sz_roles_name);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`name`=\"%s\"", sz_roles_name);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `charid`=%d", roles_charid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`charid`=%d", roles_charid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_FACE:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `face`=\"%s\"", sz_roles_face);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`face`=\"%s\"", sz_roles_face);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `createtime`=%lld", roles_createtime);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, "`createtime`=%lld", roles_createtime);
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

    if (buffer_roles_name != nullptr)
        buffer_roles_name->Release();
    if (buffer_roles_face != nullptr)
        buffer_roles_face->Release();
    
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "roles", table.custom_columns());
#endif
    return GORM_OK;
}
int GORM_PackUpdateSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackUpdateSQLCURRENCY(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackUpdateSQLCYCLEEVENT(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_EQUIP:
        return GORM_PackUpdateSQLEQUIP(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_FOOD:
        return GORM_PackUpdateSQLFOOD(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_HERO:
        return GORM_PackUpdateSQLHERO(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MAIL:
        return GORM_PackUpdateSQLMAIL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MATERIAL:
        return GORM_PackUpdateSQLMATERIAL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_NPC:
        return GORM_PackUpdateSQLNPC(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackUpdateSQLROLE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SCENE:
        return GORM_PackUpdateSQLSCENE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SKILL:
        return GORM_PackUpdateSQLSKILL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_INTERACTION:
        return GORM_PackUpdateSQLINTERACTION(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_USER:
        return GORM_PackUpdateSQLUSER(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLES:
        return GORM_PackUpdateSQLROLES(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define CURRENCYINCREASESQL "update currency_%d set "
#define CURRENCYINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLCURRENCY(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
    buffer_currency_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_currency_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_currency_where->m_sCapacity, CURRENCYINCREASEWHERESQL , currency_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_currency_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), currency_version);
    buffer_currency_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +100;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
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
int GORM_PackIncreaseSQLCYCLEEVENT(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
    buffer_cycleevent_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_cycleevent_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_cycleevent_where->m_sCapacity, CYCLEEVENTINCREASEWHERESQL , cycleevent_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_cycleevent_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), cycleevent_version);
    buffer_cycleevent_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +32;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
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
#define EQUIPINCREASESQL "update equip_%d set "
#define EQUIPINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLEQUIP(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_equip())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(EQUIPINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_equip table_equip = table.equip();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_EQUIP_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 equip_version = table_equip.version();
    const int64 equip_roleid = table_equip.roleid();
    const int32 equip_snakeid = table_equip.snakeid();

    int iWhereLen = iSqlLen + 128  + 24;
    GORM_MemPoolData *buffer_equip_where = nullptr;
    buffer_equip_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_equip_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_equip_where->m_sCapacity, EQUIPINCREASEWHERESQL , equip_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_equip_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), equip_version);
    buffer_equip_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +88;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, EQUIPUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, EQUIPINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), equip_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_EQUIP_VERSION == iFieldId || GORM_PB_FIELD_EQUIP_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_EQUIP_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, equip_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, equip_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_EQUIP_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, equip_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, equip_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_EQUIP_SNAKEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=`snakeid`%c%d", cOpt, equip_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `snakeid`=`snakeid`%c%d", cOpt, equip_snakeid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "equip", table.custom_columns());
#endif
    return GORM_OK;
}
#define FOODINCREASESQL "update food_%d set "
#define FOODINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLFOOD(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_food())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(FOODINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_food table_food = table.food();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_FOOD_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 food_version = table_food.version();
    const int64 food_roleid = table_food.roleid();
    const int32 food_snakeid = table_food.snakeid();

    int iWhereLen = iSqlLen + 128  + 24;
    GORM_MemPoolData *buffer_food_where = nullptr;
    buffer_food_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_food_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_food_where->m_sCapacity, FOODINCREASEWHERESQL , food_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_food_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), food_version);
    buffer_food_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +84;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, FOODUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, FOODINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), food_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_FOOD_VERSION == iFieldId || GORM_PB_FIELD_FOOD_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_FOOD_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, food_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, food_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_FOOD_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, food_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, food_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_FOOD_SNAKEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=`snakeid`%c%d", cOpt, food_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `snakeid`=`snakeid`%c%d", cOpt, food_snakeid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "food", table.custom_columns());
#endif
    return GORM_OK;
}
#define HEROINCREASESQL "update hero_%d set "
#define HEROINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLHERO(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_hero())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(HEROINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_hero table_hero = table.hero();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_HERO_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 hero_version = table_hero.version();
    const int64 hero_roleid = table_hero.roleid();
    const int32 hero_snakeid = table_hero.snakeid();

    int iWhereLen = iSqlLen + 128  + 24;
    GORM_MemPoolData *buffer_hero_where = nullptr;
    buffer_hero_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_hero_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_hero_where->m_sCapacity, HEROINCREASEWHERESQL , hero_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_hero_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), hero_version);
    buffer_hero_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +39;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, HEROUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, HEROINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), hero_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_HERO_VERSION == iFieldId || GORM_PB_FIELD_HERO_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_HERO_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, hero_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, hero_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_HERO_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, hero_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, hero_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_HERO_SNAKEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=`snakeid`%c%d", cOpt, hero_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `snakeid`=`snakeid`%c%d", cOpt, hero_snakeid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "hero", table.custom_columns());
#endif
    return GORM_OK;
}
#define MAILINCREASESQL "update mail_%d set "
#define MAILINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLMAIL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_mail())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(MAILINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_mail table_mail = table.mail();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_MAIL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 mail_version = table_mail.version();
    const int64 mail_roleid = table_mail.roleid();
    const int32 mail_lastmailid = table_mail.lastmailid();
    const int32 mail_snakeid = table_mail.snakeid();

    int iWhereLen = iSqlLen + 128  + 32;
    GORM_MemPoolData *buffer_mail_where = nullptr;
    buffer_mail_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_mail_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_mail_where->m_sCapacity, MAILINCREASEWHERESQL , mail_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_mail_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), mail_version);
    buffer_mail_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +107;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, MAILUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, MAILINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), mail_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_MAIL_VERSION == iFieldId || GORM_PB_FIELD_MAIL_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_MAIL_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, mail_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, mail_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_MAIL_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, mail_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, mail_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_MAIL_LASTMAILID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `lastmailid`=`lastmailid`%c%d", cOpt, mail_lastmailid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `lastmailid`=`lastmailid`%c%d", cOpt, mail_lastmailid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_MAIL_SNAKEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=`snakeid`%c%d", cOpt, mail_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `snakeid`=`snakeid`%c%d", cOpt, mail_snakeid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "mail", table.custom_columns());
#endif
    return GORM_OK;
}
#define MATERIALINCREASESQL "update material_%d set "
#define MATERIALINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLMATERIAL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_material())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(MATERIALINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_material table_material = table.material();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_MATERIAL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 material_version = table_material.version();
    const int64 material_roleid = table_material.roleid();
    const int32 material_snakeid = table_material.snakeid();

    int iWhereLen = iSqlLen + 128  + 24;
    GORM_MemPoolData *buffer_material_where = nullptr;
    buffer_material_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_material_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_material_where->m_sCapacity, MATERIALINCREASEWHERESQL , material_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_material_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), material_version);
    buffer_material_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +100;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, MATERIALUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, MATERIALINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), material_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_MATERIAL_VERSION == iFieldId || GORM_PB_FIELD_MATERIAL_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_MATERIAL_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, material_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, material_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_MATERIAL_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, material_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, material_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_MATERIAL_SNAKEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=`snakeid`%c%d", cOpt, material_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `snakeid`=`snakeid`%c%d", cOpt, material_snakeid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "material", table.custom_columns());
#endif
    return GORM_OK;
}
#define NPCINCREASESQL "update npc_%d set "
#define NPCINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLNPC(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_npc())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(NPCINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_npc table_npc = table.npc();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_NPC_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 npc_version = table_npc.version();
    const int64 npc_roleid = table_npc.roleid();
    const int32 npc_snakeid = table_npc.snakeid();

    int iWhereLen = iSqlLen + 128  + 24;
    GORM_MemPoolData *buffer_npc_where = nullptr;
    buffer_npc_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_npc_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_npc_where->m_sCapacity, NPCINCREASEWHERESQL , npc_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_npc_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), npc_version);
    buffer_npc_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +38;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, NPCUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, NPCINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), npc_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_NPC_VERSION == iFieldId || GORM_PB_FIELD_NPC_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_NPC_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, npc_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, npc_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_NPC_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, npc_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, npc_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_NPC_SNAKEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=`snakeid`%c%d", cOpt, npc_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `snakeid`=`snakeid`%c%d", cOpt, npc_snakeid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "npc", table.custom_columns());
#endif
    return GORM_OK;
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
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_role_where->m_sCapacity, ROLEINCREASEWHERESQL , role_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_role_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), role_version);
    buffer_role_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +112;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, ROLEUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLEINCREASESQL, iTableIndex);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, role_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, role_version);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, role_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, role_roleid);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `level`=`level`%c%d", cOpt, role_level);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `level`=`level`%c%d", cOpt, role_level);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `exp`=`exp`%c%lld", cOpt, role_exp);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `exp`=`exp`%c%lld", cOpt, role_exp);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `characterid`=`characterid`%c%d", cOpt, role_characterid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `characterid`=`characterid`%c%d", cOpt, role_characterid);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `gold`=`gold`%c%d", cOpt, role_gold);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `gold`=`gold`%c%d", cOpt, role_gold);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `offlinetime`=`offlinetime`%c%lld", cOpt, role_offlinetime);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `offlinetime`=`offlinetime`%c%lld", cOpt, role_offlinetime);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `inited`=`inited`%c%d", cOpt, role_inited);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `inited`=`inited`%c%d", cOpt, role_inited);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `createtime`=`createtime`%c%lld", cOpt, role_createtime);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `createtime`=`createtime`%c%lld", cOpt, role_createtime);
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
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `online`=`online`%c%lld", cOpt, role_online);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `online`=`online`%c%lld", cOpt, role_online);
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
#define SCENEINCREASESQL "update scene_%d set "
#define SCENEINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLSCENE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_scene())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(SCENEINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_scene table_scene = table.scene();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_SCENE_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 scene_version = table_scene.version();
    const int64 scene_roleid = table_scene.roleid();
    const int32 scene_sceneid = table_scene.sceneid();

    int iWhereLen = iSqlLen + 128  + 24;
    GORM_MemPoolData *buffer_scene_where = nullptr;
    buffer_scene_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_scene_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_scene_where->m_sCapacity, SCENEINCREASEWHERESQL , scene_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_scene_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), scene_version);
    buffer_scene_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +42;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, SCENEUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, SCENEINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), scene_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_SCENE_VERSION == iFieldId || GORM_PB_FIELD_SCENE_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_SCENE_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, scene_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, scene_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_SCENE_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, scene_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, scene_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_SCENE_SCENEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `sceneid`=`sceneid`%c%d", cOpt, scene_sceneid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `sceneid`=`sceneid`%c%d", cOpt, scene_sceneid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "scene", table.custom_columns());
#endif
    return GORM_OK;
}
#define SKILLINCREASESQL "update skill_%d set "
#define SKILLINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLSKILL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_skill())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(SKILLINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_skill table_skill = table.skill();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_SKILL_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 skill_version = table_skill.version();
    const int64 skill_roleid = table_skill.roleid();
    const int32 skill_snakeid = table_skill.snakeid();

    int iWhereLen = iSqlLen + 128  + 24;
    GORM_MemPoolData *buffer_skill_where = nullptr;
    buffer_skill_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_skill_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_skill_where->m_sCapacity, SKILLINCREASEWHERESQL , skill_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_skill_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), skill_version);
    buffer_skill_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +88;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, SKILLUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, SKILLINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), skill_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_SKILL_VERSION == iFieldId || GORM_PB_FIELD_SKILL_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_SKILL_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, skill_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, skill_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_SKILL_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, skill_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, skill_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_SKILL_SNAKEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=`snakeid`%c%d", cOpt, skill_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `snakeid`=`snakeid`%c%d", cOpt, skill_snakeid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "skill", table.custom_columns());
#endif
    return GORM_OK;
}
#define INTERACTIONINCREASESQL "update interaction_%d set "
#define INTERACTIONINCREASEWHERESQL " where `roleid`=%lld"
int GORM_PackIncreaseSQLINTERACTION(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_interaction())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(INTERACTIONINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_interaction table_interaction = table.interaction();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_INTERACTION_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 interaction_version = table_interaction.version();
    const int64 interaction_roleid = table_interaction.roleid();
    const int32 interaction_snakeid = table_interaction.snakeid();

    int iWhereLen = iSqlLen + 128  + 24;
    GORM_MemPoolData *buffer_interaction_where = nullptr;
    buffer_interaction_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_interaction_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_interaction_where->m_sCapacity, INTERACTIONINCREASEWHERESQL , interaction_roleid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_interaction_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), interaction_version);
    buffer_interaction_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +112;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, INTERACTIONUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, INTERACTIONINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), interaction_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_INTERACTION_VERSION == iFieldId || GORM_PB_FIELD_INTERACTION_ROLEID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_INTERACTION_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, interaction_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, interaction_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_INTERACTION_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, interaction_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, interaction_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_INTERACTION_SNAKEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `snakeid`=`snakeid`%c%d", cOpt, interaction_snakeid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `snakeid`=`snakeid`%c%d", cOpt, interaction_snakeid);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "interaction", table.custom_columns());
#endif
    return GORM_OK;
}
#define USERINCREASESQL "update user_%d set "
#define USERINCREASEWHERESQL " where `userid`=%lld"
int GORM_PackIncreaseSQLUSER(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_user())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(USERINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_user table_user = table.user();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_USER_USERID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 user_version = table_user.version();
    const int64 user_userid = table_user.userid();
    const int32 user_pttype = table_user.pttype();
    const int64 user_createtime = table_user.createtime();

    int iWhereLen = iSqlLen + 128  + 32;
    GORM_MemPoolData *buffer_user_where = nullptr;
    buffer_user_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_user_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_user_where->m_sCapacity, USERINCREASEWHERESQL , user_userid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_user_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), user_version);
    buffer_user_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +46;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, USERUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, USERINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), user_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_USER_VERSION == iFieldId || GORM_PB_FIELD_USER_USERID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_USER_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, user_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, user_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_USER_USERID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `userid`=`userid`%c%lld", cOpt, user_userid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `userid`=`userid`%c%lld", cOpt, user_userid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_USER_PTTYPE))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `pttype`=`pttype`%c%d", cOpt, user_pttype);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `pttype`=`pttype`%c%d", cOpt, user_pttype);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_USER_CREATETIME))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `createtime`=`createtime`%c%lld", cOpt, user_createtime);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `createtime`=`createtime`%c%lld", cOpt, user_createtime);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "user", table.custom_columns());
#endif
    return GORM_OK;
}
#define ROLESINCREASESQL "update roles_%d set "
#define ROLESINCREASEWHERESQL " where `roleid`=%lld and `userid`=%lld"
int GORM_PackIncreaseSQLROLES(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    if (pMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;

    GORM_PB_TABLE table = pMsg->tables(0);
    if (!table.has_roles())
        return GORM_REQ_NO_RECORDS;

    const GORM_PB_REQ_HEADER &header = pMsg->header();
    const string &fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());

    const string &strMinusFieldsMode = pMsg->minuscolumns();
    bool bMatch = false;
    char *szSQLBegin = nullptr;
    int iSqlLen = strlen(ROLESINCREASESQL);
    int iTmpLen = 0;

    GORM_PB_Table_roles table_roles = table.roles();

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLES_ROLEID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    bMatch = false;
    for(int i=0; i<vFields.size(); i++)
    {
        if (GORM_PB_FIELD_ROLES_USERID == vFields[i])
        {
            bMatch = true;
            break;
        }
    }
    if (!bMatch)
        return GORM_REQ_NEED_SPLIT;

    const uint64 roles_version = table_roles.version();
    const int64 roles_roleid = table_roles.roleid();
    const int64 roles_userid = table_roles.userid();
    const int64 roles_worldid = table_roles.worldid();
    const int32 roles_dbid = table_roles.dbid();
    const int32 roles_charid = table_roles.charid();
    const int64 roles_createtime = table_roles.createtime();

    int iWhereLen = iSqlLen + 128  + 56;
    GORM_MemPoolData *buffer_roles_where = nullptr;
    buffer_roles_where = GORM_MemPool::Instance()->GetData(iWhereLen);
    char *szWhereBegin = buffer_roles_where->m_uszData;
    iWhereLen += GORM_SafeSnprintf(szWhereBegin+iWhereLen, buffer_roles_where->m_sCapacity, ROLESINCREASEWHERESQL , roles_roleid, roles_userid);
    iWhereLen += GORM_GETVERSION_WHERE(szWhereBegin+iWhereLen, buffer_roles_where->m_sCapacity-iWhereLen, GORM_CheckDataVerType(header.verpolice()), roles_version);
    buffer_roles_where->m_sUsedSize = iWhereLen;

    int iLen = iSqlLen + 128 + pMsg->ByteSizeLong() +84;
    pReqData = GORM_MemPool::Instance()->GetData(iLen+iWhereLen+1);
    szSQLBegin = pReqData->m_uszData;
    memcpy(szSQLBegin, ROLESUPDATESQL, iSqlLen);
    int iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLESINCREASESQL, iTableIndex);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize = iDataLen;
    int iSetField = 1;
    iDataLen  = GORM_GETVERSION_SET(szSQLBegin, iLen-pReqData->m_sUsedSize, GORM_CheckDataVerType(header.verpolice()), roles_version);
    szSQLBegin += iDataLen;
    pReqData->m_sUsedSize += iDataLen;
    iLen -= iDataLen;
    iDataLen = 0;
    for (int i=0; i<vFields.size(); i++)
    {
        int iFieldId = vFields[i];
        if (GORM_PB_FIELD_ROLES_VERSION == iFieldId || GORM_PB_FIELD_ROLES_ROLEID == iFieldId || GORM_PB_FIELD_ROLES_USERID == iFieldId)
            continue;
        iSetField += 1;
        switch (iFieldId)
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLES_VERSION))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `version`=`version`%c%llu", cOpt, roles_version);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `version`=`version`%c%llu", cOpt, roles_version);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLES_ROLEID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `roleid`=`roleid`%c%lld", cOpt, roles_roleid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `roleid`=`roleid`%c%lld", cOpt, roles_roleid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLES_USERID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `userid`=`userid`%c%lld", cOpt, roles_userid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `userid`=`userid`%c%lld", cOpt, roles_userid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLES_WORLDID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `worldid`=`worldid`%c%lld", cOpt, roles_worldid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `worldid`=`worldid`%c%lld", cOpt, roles_worldid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLES_DBID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `dbid`=`dbid`%c%d", cOpt, roles_dbid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `dbid`=`dbid`%c%d", cOpt, roles_dbid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLES_CHARID))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `charid`=`charid`%c%d", cOpt, roles_charid);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `charid`=`charid`%c%d", cOpt, roles_charid);
            iLen -= iDataLen;
            szSQLBegin += iDataLen;
            break;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            char cOpt = '+';
            if (GORM_FieldsOpt::FieldInMode(strMinusFieldsMode.c_str(), strMinusFieldsMode.size(), GORM_PB_FIELD_ROLES_CREATETIME))
                cOpt = '-';
            if (iSetField != 1)
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, ", `createtime`=`createtime`%c%lld", cOpt, roles_createtime);
            else
                iDataLen = GORM_SafeSnprintf(szSQLBegin, iLen, " `createtime`=`createtime`%c%lld", cOpt, roles_createtime);
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
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "roles", table.custom_columns());
#endif
    return GORM_OK;
}
int GORM_PackIncreaseSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackIncreaseSQLCURRENCY(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackIncreaseSQLCYCLEEVENT(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_EQUIP:
        return GORM_PackIncreaseSQLEQUIP(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_FOOD:
        return GORM_PackIncreaseSQLFOOD(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_HERO:
        return GORM_PackIncreaseSQLHERO(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MAIL:
        return GORM_PackIncreaseSQLMAIL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MATERIAL:
        return GORM_PackIncreaseSQLMATERIAL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_NPC:
        return GORM_PackIncreaseSQLNPC(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackIncreaseSQLROLE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SCENE:
        return GORM_PackIncreaseSQLSCENE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SKILL:
        return GORM_PackIncreaseSQLSKILL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_INTERACTION:
        return GORM_PackIncreaseSQLINTERACTION(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_USER:
        return GORM_PackIncreaseSQLUSER(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLES:
        return GORM_PackIncreaseSQLROLES(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

#define CURRENCYREPLACESQL "insert into currency_%d(`version`, `roleid`, `snakeid`, `currency1`, `currency2`, `currency3`, `currency4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `snakeid`=%d, `currency1`=\"%s\", `currency2`=\"%s\", `currency3`=\"%s\", `currency4`=\"%s\";"
int GORM_PackReplaceSQLCURRENCY_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_currency &table_currency, GORM_MemPoolData *&pReqData)
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
        buffer_currency_currency1 = GORM_MemPool::Instance()->GetData(currency_currency1.size()<<1);
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
        buffer_currency_currency2 = GORM_MemPool::Instance()->GetData(currency_currency2.size()<<1);
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
        buffer_currency_currency3 = GORM_MemPool::Instance()->GetData(currency_currency3.size()<<1);
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
        buffer_currency_currency4 = GORM_MemPool::Instance()->GetData(currency_currency4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_currency_currency4->m_uszData, currency_currency4.c_str(), currency_currency4.size());
        buffer_currency_currency4->m_uszData[iTmpLen] = '\0';
        buffer_currency_currency4->m_sUsedSize = iTmpLen;
        sz_currency_currency4 = buffer_currency_currency4->m_uszData;
        len_currency_currency4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_currency_currency1 + len_currency_currency2 + len_currency_currency3 + len_currency_currency4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
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
int GORM_PackReplaceSQLCURRENCY(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
int GORM_PackReplaceSQLCYCLEEVENT_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, GORM_MemPoolData *&pReqData)
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
        buffer_cycleevent_events = GORM_MemPool::Instance()->GetData(cycleevent_events.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_cycleevent_events->m_uszData, cycleevent_events.c_str(), cycleevent_events.size());
        buffer_cycleevent_events->m_uszData[iTmpLen] = '\0';
        buffer_cycleevent_events->m_sUsedSize = iTmpLen;
        sz_cycleevent_events = buffer_cycleevent_events->m_uszData;
        len_cycleevent_events = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + len_cycleevent_events;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, CYCLEEVENTREPLACESQL, iTableIndex, cycleevent_version, cycleevent_roleid, sz_cycleevent_events, sz_cycleevent_events);
    pReqData->m_sUsedSize = iLen;

    if (buffer_cycleevent_events != nullptr)
        buffer_cycleevent_events->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLCYCLEEVENT(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
#define EQUIPREPLACESQL "insert into equip_%d(`version`, `roleid`, `snakeid`, `equip1`, `equip2`, `equip3`, `equip4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `snakeid`=%d, `equip1`=\"%s\", `equip2`=\"%s\", `equip3`=\"%s\", `equip4`=\"%s\";"
int GORM_PackReplaceSQLEQUIP_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_equip &table_equip, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 304;
    int iTmpLen = 0;

    const uint64 equip_version = table_equip.version();

    const int64 equip_roleid = table_equip.roleid();

    const int32 equip_snakeid = table_equip.snakeid();

    const string &equip_equip1 = table_equip.equip1();
    char *sz_equip_equip1 = "";
    int len_equip_equip1 = 0;
    GORM_MemPoolData *buffer_equip_equip1 = nullptr;
    if(equip_equip1.size()>0)
    {
        buffer_equip_equip1 = GORM_MemPool::Instance()->GetData(equip_equip1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_equip_equip1->m_uszData, equip_equip1.c_str(), equip_equip1.size());
        buffer_equip_equip1->m_uszData[iTmpLen] = '\0';
        buffer_equip_equip1->m_sUsedSize = iTmpLen;
        sz_equip_equip1 = buffer_equip_equip1->m_uszData;
        len_equip_equip1 = iTmpLen;
    }

    const string &equip_equip2 = table_equip.equip2();
    char *sz_equip_equip2 = "";
    int len_equip_equip2 = 0;
    GORM_MemPoolData *buffer_equip_equip2 = nullptr;
    if(equip_equip2.size()>0)
    {
        buffer_equip_equip2 = GORM_MemPool::Instance()->GetData(equip_equip2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_equip_equip2->m_uszData, equip_equip2.c_str(), equip_equip2.size());
        buffer_equip_equip2->m_uszData[iTmpLen] = '\0';
        buffer_equip_equip2->m_sUsedSize = iTmpLen;
        sz_equip_equip2 = buffer_equip_equip2->m_uszData;
        len_equip_equip2 = iTmpLen;
    }

    const string &equip_equip3 = table_equip.equip3();
    char *sz_equip_equip3 = "";
    int len_equip_equip3 = 0;
    GORM_MemPoolData *buffer_equip_equip3 = nullptr;
    if(equip_equip3.size()>0)
    {
        buffer_equip_equip3 = GORM_MemPool::Instance()->GetData(equip_equip3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_equip_equip3->m_uszData, equip_equip3.c_str(), equip_equip3.size());
        buffer_equip_equip3->m_uszData[iTmpLen] = '\0';
        buffer_equip_equip3->m_sUsedSize = iTmpLen;
        sz_equip_equip3 = buffer_equip_equip3->m_uszData;
        len_equip_equip3 = iTmpLen;
    }

    const string &equip_equip4 = table_equip.equip4();
    char *sz_equip_equip4 = "";
    int len_equip_equip4 = 0;
    GORM_MemPoolData *buffer_equip_equip4 = nullptr;
    if(equip_equip4.size()>0)
    {
        buffer_equip_equip4 = GORM_MemPool::Instance()->GetData(equip_equip4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_equip_equip4->m_uszData, equip_equip4.c_str(), equip_equip4.size());
        buffer_equip_equip4->m_uszData[iTmpLen] = '\0';
        buffer_equip_equip4->m_sUsedSize = iTmpLen;
        sz_equip_equip4 = buffer_equip_equip4->m_uszData;
        len_equip_equip4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_equip_equip1 + len_equip_equip2 + len_equip_equip3 + len_equip_equip4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, EQUIPREPLACESQL, iTableIndex, equip_version, equip_roleid, equip_snakeid, sz_equip_equip1, sz_equip_equip2, sz_equip_equip3, sz_equip_equip4,equip_snakeid, sz_equip_equip1, sz_equip_equip2, sz_equip_equip3, sz_equip_equip4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_equip_equip1 != nullptr)
        buffer_equip_equip1->Release();
    if (buffer_equip_equip2 != nullptr)
        buffer_equip_equip2->Release();
    if (buffer_equip_equip3 != nullptr)
        buffer_equip_equip3->Release();
    if (buffer_equip_equip4 != nullptr)
        buffer_equip_equip4->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLEQUIP(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_equip())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_equip &table_equip = table.equip();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "equip", table.custom_columns());
#endif
        return GORM_PackReplaceSQLEQUIP_One(mysql, iTableIndex, table_equip, pReqData);
    }
    return GORM_OK;
}
#define FOODREPLACESQL "insert into food_%d(`version`, `roleid`, `snakeid`, `food1`, `food2`, `food3`, `food4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `snakeid`=%d, `food1`=\"%s\", `food2`=\"%s\", `food3`=\"%s\", `food4`=\"%s\";"
int GORM_PackReplaceSQLFOOD_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_food &table_food, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 294;
    int iTmpLen = 0;

    const uint64 food_version = table_food.version();

    const int64 food_roleid = table_food.roleid();

    const int32 food_snakeid = table_food.snakeid();

    const string &food_food1 = table_food.food1();
    char *sz_food_food1 = "";
    int len_food_food1 = 0;
    GORM_MemPoolData *buffer_food_food1 = nullptr;
    if(food_food1.size()>0)
    {
        buffer_food_food1 = GORM_MemPool::Instance()->GetData(food_food1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_food_food1->m_uszData, food_food1.c_str(), food_food1.size());
        buffer_food_food1->m_uszData[iTmpLen] = '\0';
        buffer_food_food1->m_sUsedSize = iTmpLen;
        sz_food_food1 = buffer_food_food1->m_uszData;
        len_food_food1 = iTmpLen;
    }

    const string &food_food2 = table_food.food2();
    char *sz_food_food2 = "";
    int len_food_food2 = 0;
    GORM_MemPoolData *buffer_food_food2 = nullptr;
    if(food_food2.size()>0)
    {
        buffer_food_food2 = GORM_MemPool::Instance()->GetData(food_food2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_food_food2->m_uszData, food_food2.c_str(), food_food2.size());
        buffer_food_food2->m_uszData[iTmpLen] = '\0';
        buffer_food_food2->m_sUsedSize = iTmpLen;
        sz_food_food2 = buffer_food_food2->m_uszData;
        len_food_food2 = iTmpLen;
    }

    const string &food_food3 = table_food.food3();
    char *sz_food_food3 = "";
    int len_food_food3 = 0;
    GORM_MemPoolData *buffer_food_food3 = nullptr;
    if(food_food3.size()>0)
    {
        buffer_food_food3 = GORM_MemPool::Instance()->GetData(food_food3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_food_food3->m_uszData, food_food3.c_str(), food_food3.size());
        buffer_food_food3->m_uszData[iTmpLen] = '\0';
        buffer_food_food3->m_sUsedSize = iTmpLen;
        sz_food_food3 = buffer_food_food3->m_uszData;
        len_food_food3 = iTmpLen;
    }

    const string &food_food4 = table_food.food4();
    char *sz_food_food4 = "";
    int len_food_food4 = 0;
    GORM_MemPoolData *buffer_food_food4 = nullptr;
    if(food_food4.size()>0)
    {
        buffer_food_food4 = GORM_MemPool::Instance()->GetData(food_food4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_food_food4->m_uszData, food_food4.c_str(), food_food4.size());
        buffer_food_food4->m_uszData[iTmpLen] = '\0';
        buffer_food_food4->m_sUsedSize = iTmpLen;
        sz_food_food4 = buffer_food_food4->m_uszData;
        len_food_food4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_food_food1 + len_food_food2 + len_food_food3 + len_food_food4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, FOODREPLACESQL, iTableIndex, food_version, food_roleid, food_snakeid, sz_food_food1, sz_food_food2, sz_food_food3, sz_food_food4,food_snakeid, sz_food_food1, sz_food_food2, sz_food_food3, sz_food_food4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_food_food1 != nullptr)
        buffer_food_food1->Release();
    if (buffer_food_food2 != nullptr)
        buffer_food_food2->Release();
    if (buffer_food_food3 != nullptr)
        buffer_food_food3->Release();
    if (buffer_food_food4 != nullptr)
        buffer_food_food4->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLFOOD(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_food())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_food &table_food = table.food();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "food", table.custom_columns());
#endif
        return GORM_PackReplaceSQLFOOD_One(mysql, iTableIndex, table_food, pReqData);
    }
    return GORM_OK;
}
#define HEROREPLACESQL "insert into hero_%d(`version`, `roleid`, `snakeid`, `heros`) values (%llu, %lld, %d, \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `snakeid`=%d, `heros`=\"%s\";"
int GORM_PackReplaceSQLHERO_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_hero &table_hero, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 195;
    int iTmpLen = 0;

    const uint64 hero_version = table_hero.version();

    const int64 hero_roleid = table_hero.roleid();

    const int32 hero_snakeid = table_hero.snakeid();

    const string &hero_heros = table_hero.heros();
    char *sz_hero_heros = "";
    int len_hero_heros = 0;
    GORM_MemPoolData *buffer_hero_heros = nullptr;
    if(hero_heros.size()>0)
    {
        buffer_hero_heros = GORM_MemPool::Instance()->GetData(hero_heros.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_hero_heros->m_uszData, hero_heros.c_str(), hero_heros.size());
        buffer_hero_heros->m_uszData[iTmpLen] = '\0';
        buffer_hero_heros->m_sUsedSize = iTmpLen;
        sz_hero_heros = buffer_hero_heros->m_uszData;
        len_hero_heros = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_hero_heros;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, HEROREPLACESQL, iTableIndex, hero_version, hero_roleid, hero_snakeid, sz_hero_heros,hero_snakeid, sz_hero_heros);
    pReqData->m_sUsedSize = iLen;

    if (buffer_hero_heros != nullptr)
        buffer_hero_heros->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLHERO(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_hero())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_hero &table_hero = table.hero();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "hero", table.custom_columns());
#endif
        return GORM_PackReplaceSQLHERO_One(mysql, iTableIndex, table_hero, pReqData);
    }
    return GORM_OK;
}
#define MAILREPLACESQL "insert into mail_%d(`version`, `roleid`, `mail1`, `mail2`, `mail3`, `mail4`, `mail5`, `lastmailid`, `snakeid`) values (%llu, %lld, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %d, %d) ON DUPLICATE KEY UPDATE `version`=`version`+1, `mail1`=\"%s\", `mail2`=\"%s\", `mail3`=\"%s\", `mail4`=\"%s\", `mail5`=\"%s\", `lastmailid`=%d, `snakeid`=%d;"
int GORM_PackReplaceSQLMAIL_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_mail &table_mail, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 362;
    int iTmpLen = 0;

    const uint64 mail_version = table_mail.version();

    const int64 mail_roleid = table_mail.roleid();

    const string &mail_mail1 = table_mail.mail1();
    char *sz_mail_mail1 = "";
    int len_mail_mail1 = 0;
    GORM_MemPoolData *buffer_mail_mail1 = nullptr;
    if(mail_mail1.size()>0)
    {
        buffer_mail_mail1 = GORM_MemPool::Instance()->GetData(mail_mail1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail1->m_uszData, mail_mail1.c_str(), mail_mail1.size());
        buffer_mail_mail1->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail1->m_sUsedSize = iTmpLen;
        sz_mail_mail1 = buffer_mail_mail1->m_uszData;
        len_mail_mail1 = iTmpLen;
    }

    const string &mail_mail2 = table_mail.mail2();
    char *sz_mail_mail2 = "";
    int len_mail_mail2 = 0;
    GORM_MemPoolData *buffer_mail_mail2 = nullptr;
    if(mail_mail2.size()>0)
    {
        buffer_mail_mail2 = GORM_MemPool::Instance()->GetData(mail_mail2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail2->m_uszData, mail_mail2.c_str(), mail_mail2.size());
        buffer_mail_mail2->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail2->m_sUsedSize = iTmpLen;
        sz_mail_mail2 = buffer_mail_mail2->m_uszData;
        len_mail_mail2 = iTmpLen;
    }

    const string &mail_mail3 = table_mail.mail3();
    char *sz_mail_mail3 = "";
    int len_mail_mail3 = 0;
    GORM_MemPoolData *buffer_mail_mail3 = nullptr;
    if(mail_mail3.size()>0)
    {
        buffer_mail_mail3 = GORM_MemPool::Instance()->GetData(mail_mail3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail3->m_uszData, mail_mail3.c_str(), mail_mail3.size());
        buffer_mail_mail3->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail3->m_sUsedSize = iTmpLen;
        sz_mail_mail3 = buffer_mail_mail3->m_uszData;
        len_mail_mail3 = iTmpLen;
    }

    const string &mail_mail4 = table_mail.mail4();
    char *sz_mail_mail4 = "";
    int len_mail_mail4 = 0;
    GORM_MemPoolData *buffer_mail_mail4 = nullptr;
    if(mail_mail4.size()>0)
    {
        buffer_mail_mail4 = GORM_MemPool::Instance()->GetData(mail_mail4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail4->m_uszData, mail_mail4.c_str(), mail_mail4.size());
        buffer_mail_mail4->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail4->m_sUsedSize = iTmpLen;
        sz_mail_mail4 = buffer_mail_mail4->m_uszData;
        len_mail_mail4 = iTmpLen;
    }

    const string &mail_mail5 = table_mail.mail5();
    char *sz_mail_mail5 = "";
    int len_mail_mail5 = 0;
    GORM_MemPoolData *buffer_mail_mail5 = nullptr;
    if(mail_mail5.size()>0)
    {
        buffer_mail_mail5 = GORM_MemPool::Instance()->GetData(mail_mail5.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_mail_mail5->m_uszData, mail_mail5.c_str(), mail_mail5.size());
        buffer_mail_mail5->m_uszData[iTmpLen] = '\0';
        buffer_mail_mail5->m_sUsedSize = iTmpLen;
        sz_mail_mail5 = buffer_mail_mail5->m_uszData;
        len_mail_mail5 = iTmpLen;
    }

    const int32 mail_lastmailid = table_mail.lastmailid();

    const int32 mail_snakeid = table_mail.snakeid();

    int iLen = iSqlLen + 128 + 8 + 8 + len_mail_mail1 + len_mail_mail2 + len_mail_mail3 + len_mail_mail4 + len_mail_mail5 + 8 + 8;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, MAILREPLACESQL, iTableIndex, mail_version, mail_roleid, sz_mail_mail1, sz_mail_mail2, sz_mail_mail3, sz_mail_mail4, sz_mail_mail5, mail_lastmailid, mail_snakeid, sz_mail_mail1, sz_mail_mail2, sz_mail_mail3, sz_mail_mail4, sz_mail_mail5,mail_lastmailid,mail_snakeid);
    pReqData->m_sUsedSize = iLen;

    if (buffer_mail_mail1 != nullptr)
        buffer_mail_mail1->Release();
    if (buffer_mail_mail2 != nullptr)
        buffer_mail_mail2->Release();
    if (buffer_mail_mail3 != nullptr)
        buffer_mail_mail3->Release();
    if (buffer_mail_mail4 != nullptr)
        buffer_mail_mail4->Release();
    if (buffer_mail_mail5 != nullptr)
        buffer_mail_mail5->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLMAIL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_mail())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_mail &table_mail = table.mail();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "mail", table.custom_columns());
#endif
        return GORM_PackReplaceSQLMAIL_One(mysql, iTableIndex, table_mail, pReqData);
    }
    return GORM_OK;
}
#define MATERIALREPLACESQL "insert into material_%d(`version`, `roleid`, `snakeid`, `material1`, `material2`, `material3`, `material4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `snakeid`=%d, `material1`=\"%s\", `material2`=\"%s\", `material3`=\"%s\", `material4`=\"%s\";"
int GORM_PackReplaceSQLMATERIAL_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_material &table_material, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 334;
    int iTmpLen = 0;

    const uint64 material_version = table_material.version();

    const int64 material_roleid = table_material.roleid();

    const int32 material_snakeid = table_material.snakeid();

    const string &material_material1 = table_material.material1();
    char *sz_material_material1 = "";
    int len_material_material1 = 0;
    GORM_MemPoolData *buffer_material_material1 = nullptr;
    if(material_material1.size()>0)
    {
        buffer_material_material1 = GORM_MemPool::Instance()->GetData(material_material1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_material_material1->m_uszData, material_material1.c_str(), material_material1.size());
        buffer_material_material1->m_uszData[iTmpLen] = '\0';
        buffer_material_material1->m_sUsedSize = iTmpLen;
        sz_material_material1 = buffer_material_material1->m_uszData;
        len_material_material1 = iTmpLen;
    }

    const string &material_material2 = table_material.material2();
    char *sz_material_material2 = "";
    int len_material_material2 = 0;
    GORM_MemPoolData *buffer_material_material2 = nullptr;
    if(material_material2.size()>0)
    {
        buffer_material_material2 = GORM_MemPool::Instance()->GetData(material_material2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_material_material2->m_uszData, material_material2.c_str(), material_material2.size());
        buffer_material_material2->m_uszData[iTmpLen] = '\0';
        buffer_material_material2->m_sUsedSize = iTmpLen;
        sz_material_material2 = buffer_material_material2->m_uszData;
        len_material_material2 = iTmpLen;
    }

    const string &material_material3 = table_material.material3();
    char *sz_material_material3 = "";
    int len_material_material3 = 0;
    GORM_MemPoolData *buffer_material_material3 = nullptr;
    if(material_material3.size()>0)
    {
        buffer_material_material3 = GORM_MemPool::Instance()->GetData(material_material3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_material_material3->m_uszData, material_material3.c_str(), material_material3.size());
        buffer_material_material3->m_uszData[iTmpLen] = '\0';
        buffer_material_material3->m_sUsedSize = iTmpLen;
        sz_material_material3 = buffer_material_material3->m_uszData;
        len_material_material3 = iTmpLen;
    }

    const string &material_material4 = table_material.material4();
    char *sz_material_material4 = "";
    int len_material_material4 = 0;
    GORM_MemPoolData *buffer_material_material4 = nullptr;
    if(material_material4.size()>0)
    {
        buffer_material_material4 = GORM_MemPool::Instance()->GetData(material_material4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_material_material4->m_uszData, material_material4.c_str(), material_material4.size());
        buffer_material_material4->m_uszData[iTmpLen] = '\0';
        buffer_material_material4->m_sUsedSize = iTmpLen;
        sz_material_material4 = buffer_material_material4->m_uszData;
        len_material_material4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_material_material1 + len_material_material2 + len_material_material3 + len_material_material4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, MATERIALREPLACESQL, iTableIndex, material_version, material_roleid, material_snakeid, sz_material_material1, sz_material_material2, sz_material_material3, sz_material_material4,material_snakeid, sz_material_material1, sz_material_material2, sz_material_material3, sz_material_material4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_material_material1 != nullptr)
        buffer_material_material1->Release();
    if (buffer_material_material2 != nullptr)
        buffer_material_material2->Release();
    if (buffer_material_material3 != nullptr)
        buffer_material_material3->Release();
    if (buffer_material_material4 != nullptr)
        buffer_material_material4->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLMATERIAL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_material())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_material &table_material = table.material();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "material", table.custom_columns());
#endif
        return GORM_PackReplaceSQLMATERIAL_One(mysql, iTableIndex, table_material, pReqData);
    }
    return GORM_OK;
}
#define NPCREPLACESQL "insert into npc_%d(`version`, `roleid`, `snakeid`, `npcs`) values (%llu, %lld, %d, \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `snakeid`=%d, `npcs`=\"%s\";"
int GORM_PackReplaceSQLNPC_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_npc &table_npc, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 191;
    int iTmpLen = 0;

    const uint64 npc_version = table_npc.version();

    const int64 npc_roleid = table_npc.roleid();

    const int32 npc_snakeid = table_npc.snakeid();

    const string &npc_npcs = table_npc.npcs();
    char *sz_npc_npcs = "";
    int len_npc_npcs = 0;
    GORM_MemPoolData *buffer_npc_npcs = nullptr;
    if(npc_npcs.size()>0)
    {
        buffer_npc_npcs = GORM_MemPool::Instance()->GetData(npc_npcs.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_npc_npcs->m_uszData, npc_npcs.c_str(), npc_npcs.size());
        buffer_npc_npcs->m_uszData[iTmpLen] = '\0';
        buffer_npc_npcs->m_sUsedSize = iTmpLen;
        sz_npc_npcs = buffer_npc_npcs->m_uszData;
        len_npc_npcs = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_npc_npcs;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, NPCREPLACESQL, iTableIndex, npc_version, npc_roleid, npc_snakeid, sz_npc_npcs,npc_snakeid, sz_npc_npcs);
    pReqData->m_sUsedSize = iLen;

    if (buffer_npc_npcs != nullptr)
        buffer_npc_npcs->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLNPC(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_npc())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_npc &table_npc = table.npc();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "npc", table.custom_columns());
#endif
        return GORM_PackReplaceSQLNPC_One(mysql, iTableIndex, table_npc, pReqData);
    }
    return GORM_OK;
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
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLEREPLACESQL, iTableIndex, role_version, role_roleid, sz_role_rolename, role_level, role_exp, role_characterid, role_gold, role_offlinetime, role_inited, role_createtime, sz_role_face, role_online, sz_role_rolename,role_level,role_exp,role_characterid,role_gold,role_offlinetime,role_inited,role_createtime, sz_role_face,role_online);
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
#define SCENEREPLACESQL "insert into scene_%d(`version`, `roleid`, `sceneid`, `collects`) values (%llu, %lld, %d, \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `sceneid`=%d, `collects`=\"%s\";"
int GORM_PackReplaceSQLSCENE_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_scene &table_scene, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 203;
    int iTmpLen = 0;

    const uint64 scene_version = table_scene.version();

    const int64 scene_roleid = table_scene.roleid();

    const int32 scene_sceneid = table_scene.sceneid();

    const string &scene_collects = table_scene.collects();
    char *sz_scene_collects = "";
    int len_scene_collects = 0;
    GORM_MemPoolData *buffer_scene_collects = nullptr;
    if(scene_collects.size()>0)
    {
        buffer_scene_collects = GORM_MemPool::Instance()->GetData(scene_collects.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_scene_collects->m_uszData, scene_collects.c_str(), scene_collects.size());
        buffer_scene_collects->m_uszData[iTmpLen] = '\0';
        buffer_scene_collects->m_sUsedSize = iTmpLen;
        sz_scene_collects = buffer_scene_collects->m_uszData;
        len_scene_collects = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_scene_collects;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, SCENEREPLACESQL, iTableIndex, scene_version, scene_roleid, scene_sceneid, sz_scene_collects,scene_sceneid, sz_scene_collects);
    pReqData->m_sUsedSize = iLen;

    if (buffer_scene_collects != nullptr)
        buffer_scene_collects->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLSCENE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_scene())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_scene &table_scene = table.scene();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "scene", table.custom_columns());
#endif
        return GORM_PackReplaceSQLSCENE_One(mysql, iTableIndex, table_scene, pReqData);
    }
    return GORM_OK;
}
#define SKILLREPLACESQL "insert into skill_%d(`version`, `roleid`, `snakeid`, `skill1`, `skill2`, `skill3`, `skill4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `snakeid`=%d, `skill1`=\"%s\", `skill2`=\"%s\", `skill3`=\"%s\", `skill4`=\"%s\";"
int GORM_PackReplaceSQLSKILL_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_skill &table_skill, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 304;
    int iTmpLen = 0;

    const uint64 skill_version = table_skill.version();

    const int64 skill_roleid = table_skill.roleid();

    const int32 skill_snakeid = table_skill.snakeid();

    const string &skill_skill1 = table_skill.skill1();
    char *sz_skill_skill1 = "";
    int len_skill_skill1 = 0;
    GORM_MemPoolData *buffer_skill_skill1 = nullptr;
    if(skill_skill1.size()>0)
    {
        buffer_skill_skill1 = GORM_MemPool::Instance()->GetData(skill_skill1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_skill_skill1->m_uszData, skill_skill1.c_str(), skill_skill1.size());
        buffer_skill_skill1->m_uszData[iTmpLen] = '\0';
        buffer_skill_skill1->m_sUsedSize = iTmpLen;
        sz_skill_skill1 = buffer_skill_skill1->m_uszData;
        len_skill_skill1 = iTmpLen;
    }

    const string &skill_skill2 = table_skill.skill2();
    char *sz_skill_skill2 = "";
    int len_skill_skill2 = 0;
    GORM_MemPoolData *buffer_skill_skill2 = nullptr;
    if(skill_skill2.size()>0)
    {
        buffer_skill_skill2 = GORM_MemPool::Instance()->GetData(skill_skill2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_skill_skill2->m_uszData, skill_skill2.c_str(), skill_skill2.size());
        buffer_skill_skill2->m_uszData[iTmpLen] = '\0';
        buffer_skill_skill2->m_sUsedSize = iTmpLen;
        sz_skill_skill2 = buffer_skill_skill2->m_uszData;
        len_skill_skill2 = iTmpLen;
    }

    const string &skill_skill3 = table_skill.skill3();
    char *sz_skill_skill3 = "";
    int len_skill_skill3 = 0;
    GORM_MemPoolData *buffer_skill_skill3 = nullptr;
    if(skill_skill3.size()>0)
    {
        buffer_skill_skill3 = GORM_MemPool::Instance()->GetData(skill_skill3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_skill_skill3->m_uszData, skill_skill3.c_str(), skill_skill3.size());
        buffer_skill_skill3->m_uszData[iTmpLen] = '\0';
        buffer_skill_skill3->m_sUsedSize = iTmpLen;
        sz_skill_skill3 = buffer_skill_skill3->m_uszData;
        len_skill_skill3 = iTmpLen;
    }

    const string &skill_skill4 = table_skill.skill4();
    char *sz_skill_skill4 = "";
    int len_skill_skill4 = 0;
    GORM_MemPoolData *buffer_skill_skill4 = nullptr;
    if(skill_skill4.size()>0)
    {
        buffer_skill_skill4 = GORM_MemPool::Instance()->GetData(skill_skill4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_skill_skill4->m_uszData, skill_skill4.c_str(), skill_skill4.size());
        buffer_skill_skill4->m_uszData[iTmpLen] = '\0';
        buffer_skill_skill4->m_sUsedSize = iTmpLen;
        sz_skill_skill4 = buffer_skill_skill4->m_uszData;
        len_skill_skill4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_skill_skill1 + len_skill_skill2 + len_skill_skill3 + len_skill_skill4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, SKILLREPLACESQL, iTableIndex, skill_version, skill_roleid, skill_snakeid, sz_skill_skill1, sz_skill_skill2, sz_skill_skill3, sz_skill_skill4,skill_snakeid, sz_skill_skill1, sz_skill_skill2, sz_skill_skill3, sz_skill_skill4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_skill_skill1 != nullptr)
        buffer_skill_skill1->Release();
    if (buffer_skill_skill2 != nullptr)
        buffer_skill_skill2->Release();
    if (buffer_skill_skill3 != nullptr)
        buffer_skill_skill3->Release();
    if (buffer_skill_skill4 != nullptr)
        buffer_skill_skill4->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLSKILL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_skill())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_skill &table_skill = table.skill();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "skill", table.custom_columns());
#endif
        return GORM_PackReplaceSQLSKILL_One(mysql, iTableIndex, table_skill, pReqData);
    }
    return GORM_OK;
}
#define INTERACTIONREPLACESQL "insert into interaction_%d(`version`, `roleid`, `snakeid`, `interaction1`, `interaction2`, `interaction3`, `interaction4`) values (%llu, %lld, %d, \"%s\", \"%s\", \"%s\", \"%s\") ON DUPLICATE KEY UPDATE `version`=`version`+1, `snakeid`=%d, `interaction1`=\"%s\", `interaction2`=\"%s\", `interaction3`=\"%s\", `interaction4`=\"%s\";"
int GORM_PackReplaceSQLINTERACTION_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_interaction &table_interaction, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 364;
    int iTmpLen = 0;

    const uint64 interaction_version = table_interaction.version();

    const int64 interaction_roleid = table_interaction.roleid();

    const int32 interaction_snakeid = table_interaction.snakeid();

    const string &interaction_interaction1 = table_interaction.interaction1();
    char *sz_interaction_interaction1 = "";
    int len_interaction_interaction1 = 0;
    GORM_MemPoolData *buffer_interaction_interaction1 = nullptr;
    if(interaction_interaction1.size()>0)
    {
        buffer_interaction_interaction1 = GORM_MemPool::Instance()->GetData(interaction_interaction1.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_interaction_interaction1->m_uszData, interaction_interaction1.c_str(), interaction_interaction1.size());
        buffer_interaction_interaction1->m_uszData[iTmpLen] = '\0';
        buffer_interaction_interaction1->m_sUsedSize = iTmpLen;
        sz_interaction_interaction1 = buffer_interaction_interaction1->m_uszData;
        len_interaction_interaction1 = iTmpLen;
    }

    const string &interaction_interaction2 = table_interaction.interaction2();
    char *sz_interaction_interaction2 = "";
    int len_interaction_interaction2 = 0;
    GORM_MemPoolData *buffer_interaction_interaction2 = nullptr;
    if(interaction_interaction2.size()>0)
    {
        buffer_interaction_interaction2 = GORM_MemPool::Instance()->GetData(interaction_interaction2.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_interaction_interaction2->m_uszData, interaction_interaction2.c_str(), interaction_interaction2.size());
        buffer_interaction_interaction2->m_uszData[iTmpLen] = '\0';
        buffer_interaction_interaction2->m_sUsedSize = iTmpLen;
        sz_interaction_interaction2 = buffer_interaction_interaction2->m_uszData;
        len_interaction_interaction2 = iTmpLen;
    }

    const string &interaction_interaction3 = table_interaction.interaction3();
    char *sz_interaction_interaction3 = "";
    int len_interaction_interaction3 = 0;
    GORM_MemPoolData *buffer_interaction_interaction3 = nullptr;
    if(interaction_interaction3.size()>0)
    {
        buffer_interaction_interaction3 = GORM_MemPool::Instance()->GetData(interaction_interaction3.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_interaction_interaction3->m_uszData, interaction_interaction3.c_str(), interaction_interaction3.size());
        buffer_interaction_interaction3->m_uszData[iTmpLen] = '\0';
        buffer_interaction_interaction3->m_sUsedSize = iTmpLen;
        sz_interaction_interaction3 = buffer_interaction_interaction3->m_uszData;
        len_interaction_interaction3 = iTmpLen;
    }

    const string &interaction_interaction4 = table_interaction.interaction4();
    char *sz_interaction_interaction4 = "";
    int len_interaction_interaction4 = 0;
    GORM_MemPoolData *buffer_interaction_interaction4 = nullptr;
    if(interaction_interaction4.size()>0)
    {
        buffer_interaction_interaction4 = GORM_MemPool::Instance()->GetData(interaction_interaction4.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_interaction_interaction4->m_uszData, interaction_interaction4.c_str(), interaction_interaction4.size());
        buffer_interaction_interaction4->m_uszData[iTmpLen] = '\0';
        buffer_interaction_interaction4->m_sUsedSize = iTmpLen;
        sz_interaction_interaction4 = buffer_interaction_interaction4->m_uszData;
        len_interaction_interaction4 = iTmpLen;
    }

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + len_interaction_interaction1 + len_interaction_interaction2 + len_interaction_interaction3 + len_interaction_interaction4;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, INTERACTIONREPLACESQL, iTableIndex, interaction_version, interaction_roleid, interaction_snakeid, sz_interaction_interaction1, sz_interaction_interaction2, sz_interaction_interaction3, sz_interaction_interaction4,interaction_snakeid, sz_interaction_interaction1, sz_interaction_interaction2, sz_interaction_interaction3, sz_interaction_interaction4);
    pReqData->m_sUsedSize = iLen;

    if (buffer_interaction_interaction1 != nullptr)
        buffer_interaction_interaction1->Release();
    if (buffer_interaction_interaction2 != nullptr)
        buffer_interaction_interaction2->Release();
    if (buffer_interaction_interaction3 != nullptr)
        buffer_interaction_interaction3->Release();
    if (buffer_interaction_interaction4 != nullptr)
        buffer_interaction_interaction4->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLINTERACTION(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_interaction())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_interaction &table_interaction = table.interaction();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "interaction", table.custom_columns());
#endif
        return GORM_PackReplaceSQLINTERACTION_One(mysql, iTableIndex, table_interaction, pReqData);
    }
    return GORM_OK;
}
#define USERREPLACESQL "insert into user_%d(`version`, `userid`, `ptid`, `pttype`, `createtime`) values (%llu, %lld, \"%s\", %d, %lld) ON DUPLICATE KEY UPDATE `version`=`version`+1, `ptid`=\"%s\", `pttype`=%d, `createtime`=%lld;"
int GORM_PackReplaceSQLUSER_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_user &table_user, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 230;
    int iTmpLen = 0;

    const uint64 user_version = table_user.version();

    const int64 user_userid = table_user.userid();

    const string &user_ptid = table_user.ptid();
    char *sz_user_ptid = "";
    int len_user_ptid = 0;
    GORM_MemPoolData *buffer_user_ptid = nullptr;
    if(user_ptid.size()>0)
    {
        buffer_user_ptid = GORM_MemPool::Instance()->GetData(user_ptid.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_user_ptid->m_uszData, user_ptid.c_str(), user_ptid.size());
        buffer_user_ptid->m_uszData[iTmpLen] = '\0';
        buffer_user_ptid->m_sUsedSize = iTmpLen;
        sz_user_ptid = buffer_user_ptid->m_uszData;
        len_user_ptid = iTmpLen;
    }

    const int32 user_pttype = table_user.pttype();

    const int64 user_createtime = table_user.createtime();

    int iLen = iSqlLen + 128 + 8 + 8 + len_user_ptid + 8 + 8;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, USERREPLACESQL, iTableIndex, user_version, user_userid, sz_user_ptid, user_pttype, user_createtime, sz_user_ptid,user_pttype,user_createtime);
    pReqData->m_sUsedSize = iLen;

    if (buffer_user_ptid != nullptr)
        buffer_user_ptid->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLUSER(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_user())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_user &table_user = table.user();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "user", table.custom_columns());
#endif
        return GORM_PackReplaceSQLUSER_One(mysql, iTableIndex, table_user, pReqData);
    }
    return GORM_OK;
}
#define ROLESREPLACESQL "insert into roles_%d(`version`, `roleid`, `userid`, `worldid`, `dbid`, `name`, `charid`, `face`, `createtime`) values (%llu, %lld, %lld, %lld, %d, \"%s\", %d, \"%s\", %lld) ON DUPLICATE KEY UPDATE `version`=`version`+1, `worldid`=%lld, `dbid`=%d, `name`=\"%s\", `charid`=%d, `face`=\"%s\", `createtime`=%lld;"
int GORM_PackReplaceSQLROLES_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_roles &table_roles, GORM_MemPoolData *&pReqData)
{
    char *szSQLBegin = nullptr;
    int iSqlLen = 335;
    int iTmpLen = 0;

    const uint64 roles_version = table_roles.version();

    const int64 roles_roleid = table_roles.roleid();

    const int64 roles_userid = table_roles.userid();

    const int64 roles_worldid = table_roles.worldid();

    const int32 roles_dbid = table_roles.dbid();

    const string &roles_name = table_roles.name();
    char *sz_roles_name = "";
    int len_roles_name = 0;
    GORM_MemPoolData *buffer_roles_name = nullptr;
    if(roles_name.size()>0)
    {
        buffer_roles_name = GORM_MemPool::Instance()->GetData(roles_name.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_roles_name->m_uszData, roles_name.c_str(), roles_name.size());
        buffer_roles_name->m_uszData[iTmpLen] = '\0';
        buffer_roles_name->m_sUsedSize = iTmpLen;
        sz_roles_name = buffer_roles_name->m_uszData;
        len_roles_name = iTmpLen;
    }

    const int32 roles_charid = table_roles.charid();

    const string &roles_face = table_roles.face();
    char *sz_roles_face = "";
    int len_roles_face = 0;
    GORM_MemPoolData *buffer_roles_face = nullptr;
    if(roles_face.size()>0)
    {
        buffer_roles_face = GORM_MemPool::Instance()->GetData(roles_face.size()<<1);
        iTmpLen = mysql_real_escape_string(mysql, buffer_roles_face->m_uszData, roles_face.c_str(), roles_face.size());
        buffer_roles_face->m_uszData[iTmpLen] = '\0';
        buffer_roles_face->m_sUsedSize = iTmpLen;
        sz_roles_face = buffer_roles_face->m_uszData;
        len_roles_face = iTmpLen;
    }

    const int64 roles_createtime = table_roles.createtime();

    int iLen = iSqlLen + 128 + 8 + 8 + 8 + 8 + 8 + len_roles_name + 8 + len_roles_face + 8;
    pReqData = GORM_MemPool::Instance()->GetData(iLen<<1);
    szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, ROLESREPLACESQL, iTableIndex, roles_version, roles_roleid, roles_userid, roles_worldid, roles_dbid, sz_roles_name, roles_charid, sz_roles_face, roles_createtime,roles_worldid,roles_dbid, sz_roles_name,roles_charid, sz_roles_face,roles_createtime);
    pReqData->m_sUsedSize = iLen;

    if (buffer_roles_name != nullptr)
        buffer_roles_name->Release();
    if (buffer_roles_face != nullptr)
        buffer_roles_face->Release();

    return GORM_OK;
}
int GORM_PackReplaceSQLROLES(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_roles())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_roles &table_roles = table.roles();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "roles", table.custom_columns());
#endif
        return GORM_PackReplaceSQLROLES_One(mysql, iTableIndex, table_roles, pReqData);
    }
    return GORM_OK;
}
int GORM_PackReplaceSQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackReplaceSQLCURRENCY(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackReplaceSQLCYCLEEVENT(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_EQUIP:
        return GORM_PackReplaceSQLEQUIP(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_FOOD:
        return GORM_PackReplaceSQLFOOD(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_HERO:
        return GORM_PackReplaceSQLHERO(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MAIL:
        return GORM_PackReplaceSQLMAIL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MATERIAL:
        return GORM_PackReplaceSQLMATERIAL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_NPC:
        return GORM_PackReplaceSQLNPC(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackReplaceSQLROLE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SCENE:
        return GORM_PackReplaceSQLSCENE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SKILL:
        return GORM_PackReplaceSQLSKILL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_INTERACTION:
        return GORM_PackReplaceSQLINTERACTION(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_USER:
        return GORM_PackReplaceSQLUSER(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLES:
        return GORM_PackReplaceSQLROLES(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    }
    return GORM_INVALID_TABLE;
}

int GORM_PackGetSQLTable(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_TABLE& table, GORM_MemPoolData *&pReqData)
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
        return GORM_PackGetSQLCURRENCY_ONE(mysql, uiHashValue, table.currency(), pReqData);
    }
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
    {
        if (!table.has_cycleevent())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "cycleevent", table.custom_columns());
#endif
        return GORM_PackGetSQLCYCLEEVENT_ONE(mysql, uiHashValue, table.cycleevent(), pReqData);
    }
    case GORM_PB_TABLE_IDX_EQUIP:
    {
        if (!table.has_equip())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "equip", table.custom_columns());
#endif
        return GORM_PackGetSQLEQUIP_ONE(mysql, uiHashValue, table.equip(), pReqData);
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
        if (!table.has_food())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "food", table.custom_columns());
#endif
        return GORM_PackGetSQLFOOD_ONE(mysql, uiHashValue, table.food(), pReqData);
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
        if (!table.has_hero())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "hero", table.custom_columns());
#endif
        return GORM_PackGetSQLHERO_ONE(mysql, uiHashValue, table.hero(), pReqData);
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
        if (!table.has_mail())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "mail", table.custom_columns());
#endif
        return GORM_PackGetSQLMAIL_ONE(mysql, uiHashValue, table.mail(), pReqData);
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
        if (!table.has_material())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "material", table.custom_columns());
#endif
        return GORM_PackGetSQLMATERIAL_ONE(mysql, uiHashValue, table.material(), pReqData);
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
        if (!table.has_npc())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "npc", table.custom_columns());
#endif
        return GORM_PackGetSQLNPC_ONE(mysql, uiHashValue, table.npc(), pReqData);
    }
    case GORM_PB_TABLE_IDX_ROLE:
    {
        if (!table.has_role())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "role", table.custom_columns());
#endif
        return GORM_PackGetSQLROLE_ONE(mysql, uiHashValue, table.role(), pReqData);
    }
    case GORM_PB_TABLE_IDX_SCENE:
    {
        if (!table.has_scene())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "scene", table.custom_columns());
#endif
        return GORM_PackGetSQLSCENE_ONE(mysql, uiHashValue, table.scene(), pReqData);
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
        if (!table.has_skill())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "skill", table.custom_columns());
#endif
        return GORM_PackGetSQLSKILL_ONE(mysql, uiHashValue, table.skill(), pReqData);
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
        if (!table.has_interaction())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "interaction", table.custom_columns());
#endif
        return GORM_PackGetSQLINTERACTION_ONE(mysql, uiHashValue, table.interaction(), pReqData);
    }
    case GORM_PB_TABLE_IDX_USER:
    {
        if (!table.has_user())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "user", table.custom_columns());
#endif
        return GORM_PackGetSQLUSER_ONE(mysql, uiHashValue, table.user(), pReqData);
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
        if (!table.has_roles())
            return GORM_REQ_NO_RECORDS;
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "roles", table.custom_columns());
#endif
        return GORM_PackGetSQLROLES_ONE(mysql, uiHashValue, table.roles(), pReqData);
    }
    }
    return GORM_INVALID_TABLE;
}
#define GetByNonPrimaySQL_CURRENCY "select `version`,`roleid`,`snakeid`,`currency1`,`currency2`,`currency3`,`currency4` from currency_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLCURRENCY_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_currency &table_currency, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_CURRENCY);
    int iTotalLen = 64*vFields.size() + iLen + table_currency.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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
int GORM_PackGet_By_Non_Primary_KeySQLCURRENCY_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_currency &table_currency, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_CURRENCY_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_currency.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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
int GORM_PackGet_By_Non_Primary_KeySQLCURRENCY(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
        return GORM_PackGet_By_Non_Primary_KeySQLCURRENCY_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_currency, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLCURRENCY_One(mysql, iTableIndex, table_currency, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_CYCLEEVENT "select `version`,`roleid`,`events` from cycleevent_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_cycleevent &table_cycleevent, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_CYCLEEVENT);
    int iTotalLen = 64*vFields.size() + iLen + table_cycleevent.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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
int GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_cycleevent &table_cycleevent, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_CYCLEEVENT_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_cycleevent.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
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

				pDataBuffer = GORM_MemPool::Instance()->GetData(strData.size()<<1);
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
int GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
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
        return GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_cycleevent, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT_One(mysql, iTableIndex, table_cycleevent, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_EQUIP "select `version`,`roleid`,`snakeid`,`equip1`,`equip2`,`equip3`,`equip4` from equip_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLEQUIP_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_equip &table_equip, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_EQUIP);
    int iTotalLen = 64*vFields.size() + iLen + table_equip.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_EQUIP, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_equip.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_equip.version());
            break;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_equip.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_equip.roleid());
            break;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_equip.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_equip.snakeid());
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP1:
        {
            char *szData = "";
            const string &strData = table_equip.equip1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`equip1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `equip1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP2:
        {
            char *szData = "";
            const string &strData = table_equip.equip2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`equip2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `equip2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP3:
        {
            char *szData = "";
            const string &strData = table_equip.equip3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`equip3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `equip3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP4:
        {
            char *szData = "";
            const string &strData = table_equip.equip4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`equip4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `equip4`=`%s`", szData);
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
#define GetByNonPrimaySQL_EQUIP_DEBUG "select `version`,`roleid`,`snakeid`,`equip1`,`equip2`,`equip3`,`equip4`"
int GORM_PackGet_By_Non_Primary_KeySQLEQUIP_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_equip &table_equip, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_EQUIP_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_equip.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_EQUIP_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["equip"];
    for (int i=7; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from equip where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_EQUIP_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_equip.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_equip.version());
            break;
        }
        case GORM_PB_FIELD_EQUIP_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_equip.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_equip.roleid());
            break;
        }
        case GORM_PB_FIELD_EQUIP_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_equip.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_equip.snakeid());
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP1:
        {
            char *szData = "";
            const string &strData = table_equip.equip1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`equip1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `equip1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP2:
        {
            char *szData = "";
            const string &strData = table_equip.equip2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`equip2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `equip2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP3:
        {
            char *szData = "";
            const string &strData = table_equip.equip3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`equip3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `equip3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_EQUIP_EQUIP4:
        {
            char *szData = "";
            const string &strData = table_equip.equip4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`equip4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `equip4`=`%s`", szData);
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
int GORM_PackGet_By_Non_Primary_KeySQLEQUIP(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_equip())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_equip &table_equip = table.equip();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "equip", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLEQUIP_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_equip, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLEQUIP_One(mysql, iTableIndex, table_equip, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_FOOD "select `version`,`roleid`,`snakeid`,`food1`,`food2`,`food3`,`food4` from food_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLFOOD_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_food &table_food, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_FOOD);
    int iTotalLen = 64*vFields.size() + iLen + table_food.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_FOOD, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_food.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_food.version());
            break;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_food.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_food.roleid());
            break;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_food.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_food.snakeid());
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD1:
        {
            char *szData = "";
            const string &strData = table_food.food1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`food1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `food1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD2:
        {
            char *szData = "";
            const string &strData = table_food.food2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`food2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `food2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD3:
        {
            char *szData = "";
            const string &strData = table_food.food3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`food3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `food3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD4:
        {
            char *szData = "";
            const string &strData = table_food.food4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`food4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `food4`=`%s`", szData);
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
#define GetByNonPrimaySQL_FOOD_DEBUG "select `version`,`roleid`,`snakeid`,`food1`,`food2`,`food3`,`food4`"
int GORM_PackGet_By_Non_Primary_KeySQLFOOD_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_food &table_food, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_FOOD_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_food.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_FOOD_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["food"];
    for (int i=7; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from food where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_FOOD_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_food.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_food.version());
            break;
        }
        case GORM_PB_FIELD_FOOD_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_food.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_food.roleid());
            break;
        }
        case GORM_PB_FIELD_FOOD_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_food.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_food.snakeid());
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD1:
        {
            char *szData = "";
            const string &strData = table_food.food1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`food1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `food1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD2:
        {
            char *szData = "";
            const string &strData = table_food.food2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`food2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `food2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD3:
        {
            char *szData = "";
            const string &strData = table_food.food3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`food3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `food3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_FOOD_FOOD4:
        {
            char *szData = "";
            const string &strData = table_food.food4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`food4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `food4`=`%s`", szData);
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
int GORM_PackGet_By_Non_Primary_KeySQLFOOD(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_food())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_food &table_food = table.food();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "food", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLFOOD_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_food, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLFOOD_One(mysql, iTableIndex, table_food, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_HERO "select `version`,`roleid`,`snakeid`,`heros` from hero_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLHERO_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_hero &table_hero, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_HERO);
    int iTotalLen = 64*vFields.size() + iLen + table_hero.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_HERO, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_hero.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_hero.version());
            break;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_hero.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_hero.roleid());
            break;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_hero.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_hero.snakeid());
            break;
        }
        case GORM_PB_FIELD_HERO_HEROS:
        {
            char *szData = "";
            const string &strData = table_hero.heros();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`heros`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `heros`=`%s`", szData);
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
#define GetByNonPrimaySQL_HERO_DEBUG "select `version`,`roleid`,`snakeid`,`heros`"
int GORM_PackGet_By_Non_Primary_KeySQLHERO_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_hero &table_hero, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_HERO_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_hero.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_HERO_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["hero"];
    for (int i=4; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from hero where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_HERO_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_hero.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_hero.version());
            break;
        }
        case GORM_PB_FIELD_HERO_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_hero.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_hero.roleid());
            break;
        }
        case GORM_PB_FIELD_HERO_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_hero.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_hero.snakeid());
            break;
        }
        case GORM_PB_FIELD_HERO_HEROS:
        {
            char *szData = "";
            const string &strData = table_hero.heros();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`heros`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `heros`=`%s`", szData);
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
int GORM_PackGet_By_Non_Primary_KeySQLHERO(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_hero())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_hero &table_hero = table.hero();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "hero", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLHERO_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_hero, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLHERO_One(mysql, iTableIndex, table_hero, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_MAIL "select `version`,`roleid`,`mail1`,`mail2`,`mail3`,`mail4`,`mail5`,`lastmailid`,`snakeid` from mail_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLMAIL_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_mail &table_mail, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_MAIL);
    int iTotalLen = 64*vFields.size() + iLen + table_mail.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_MAIL, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_mail.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_mail.version());
            break;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_mail.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_mail.roleid());
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL1:
        {
            char *szData = "";
            const string &strData = table_mail.mail1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL2:
        {
            char *szData = "";
            const string &strData = table_mail.mail2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL3:
        {
            char *szData = "";
            const string &strData = table_mail.mail3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL4:
        {
            char *szData = "";
            const string &strData = table_mail.mail4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail4`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL5:
        {
            char *szData = "";
            const string &strData = table_mail.mail5();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail5`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail5`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`lastmailid`=%d", table_mail.lastmailid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `lastmailid`=%d", table_mail.lastmailid());
            break;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_mail.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_mail.snakeid());
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#ifdef GORM_DEBUG
#define GetByNonPrimaySQL_MAIL_DEBUG "select `version`,`roleid`,`mail1`,`mail2`,`mail3`,`mail4`,`mail5`,`lastmailid`,`snakeid`"
int GORM_PackGet_By_Non_Primary_KeySQLMAIL_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_mail &table_mail, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_MAIL_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_mail.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_MAIL_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["mail"];
    for (int i=9; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from mail where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_MAIL_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_mail.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_mail.version());
            break;
        }
        case GORM_PB_FIELD_MAIL_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_mail.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_mail.roleid());
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL1:
        {
            char *szData = "";
            const string &strData = table_mail.mail1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL2:
        {
            char *szData = "";
            const string &strData = table_mail.mail2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL3:
        {
            char *szData = "";
            const string &strData = table_mail.mail3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL4:
        {
            char *szData = "";
            const string &strData = table_mail.mail4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail4`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_MAIL5:
        {
            char *szData = "";
            const string &strData = table_mail.mail5();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`mail5`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `mail5`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MAIL_LASTMAILID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`lastmailid`=%d", table_mail.lastmailid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `lastmailid`=%d", table_mail.lastmailid());
            break;
        }
        case GORM_PB_FIELD_MAIL_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_mail.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_mail.snakeid());
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#endif
int GORM_PackGet_By_Non_Primary_KeySQLMAIL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_mail())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_mail &table_mail = table.mail();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "mail", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLMAIL_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_mail, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLMAIL_One(mysql, iTableIndex, table_mail, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_MATERIAL "select `version`,`roleid`,`snakeid`,`material1`,`material2`,`material3`,`material4` from material_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLMATERIAL_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_material &table_material, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_MATERIAL);
    int iTotalLen = 64*vFields.size() + iLen + table_material.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_MATERIAL, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_material.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_material.version());
            break;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_material.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_material.roleid());
            break;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_material.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_material.snakeid());
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL1:
        {
            char *szData = "";
            const string &strData = table_material.material1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`material1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `material1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL2:
        {
            char *szData = "";
            const string &strData = table_material.material2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`material2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `material2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL3:
        {
            char *szData = "";
            const string &strData = table_material.material3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`material3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `material3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL4:
        {
            char *szData = "";
            const string &strData = table_material.material4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`material4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `material4`=`%s`", szData);
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
#define GetByNonPrimaySQL_MATERIAL_DEBUG "select `version`,`roleid`,`snakeid`,`material1`,`material2`,`material3`,`material4`"
int GORM_PackGet_By_Non_Primary_KeySQLMATERIAL_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_material &table_material, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_MATERIAL_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_material.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_MATERIAL_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["material"];
    for (int i=7; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from material where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_MATERIAL_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_material.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_material.version());
            break;
        }
        case GORM_PB_FIELD_MATERIAL_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_material.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_material.roleid());
            break;
        }
        case GORM_PB_FIELD_MATERIAL_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_material.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_material.snakeid());
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL1:
        {
            char *szData = "";
            const string &strData = table_material.material1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`material1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `material1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL2:
        {
            char *szData = "";
            const string &strData = table_material.material2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`material2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `material2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL3:
        {
            char *szData = "";
            const string &strData = table_material.material3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`material3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `material3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_MATERIAL_MATERIAL4:
        {
            char *szData = "";
            const string &strData = table_material.material4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`material4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `material4`=`%s`", szData);
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
int GORM_PackGet_By_Non_Primary_KeySQLMATERIAL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_material())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_material &table_material = table.material();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "material", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLMATERIAL_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_material, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLMATERIAL_One(mysql, iTableIndex, table_material, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_NPC "select `version`,`roleid`,`snakeid`,`npcs` from npc_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLNPC_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_npc &table_npc, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_NPC);
    int iTotalLen = 64*vFields.size() + iLen + table_npc.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_NPC, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_npc.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_npc.version());
            break;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_npc.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_npc.roleid());
            break;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_npc.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_npc.snakeid());
            break;
        }
        case GORM_PB_FIELD_NPC_NPCS:
        {
            char *szData = "";
            const string &strData = table_npc.npcs();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`npcs`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `npcs`=`%s`", szData);
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
#define GetByNonPrimaySQL_NPC_DEBUG "select `version`,`roleid`,`snakeid`,`npcs`"
int GORM_PackGet_By_Non_Primary_KeySQLNPC_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_npc &table_npc, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_NPC_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_npc.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_NPC_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["npc"];
    for (int i=4; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from npc where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_NPC_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_npc.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_npc.version());
            break;
        }
        case GORM_PB_FIELD_NPC_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_npc.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_npc.roleid());
            break;
        }
        case GORM_PB_FIELD_NPC_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_npc.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_npc.snakeid());
            break;
        }
        case GORM_PB_FIELD_NPC_NPCS:
        {
            char *szData = "";
            const string &strData = table_npc.npcs();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`npcs`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `npcs`=`%s`", szData);
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
int GORM_PackGet_By_Non_Primary_KeySQLNPC(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_npc())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_npc &table_npc = table.npc();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "npc", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLNPC_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_npc, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLNPC_One(mysql, iTableIndex, table_npc, pMsg->header(), pReqData);
    }
    return GORM_OK;
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
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_ROLE, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_role.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_role.version());
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_role.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_role.roleid());
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`rolename`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `rolename`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`level`=%d", table_role.level());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `level`=%d", table_role.level());
            break;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`exp`=%lld", table_role.exp());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `exp`=%lld", table_role.exp());
            break;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`characterid`=%d", table_role.characterid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `characterid`=%d", table_role.characterid());
            break;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`gold`=%d", table_role.gold());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `gold`=%d", table_role.gold());
            break;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`offlinetime`=%lld", table_role.offlinetime());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `offlinetime`=%lld", table_role.offlinetime());
            break;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`inited`=%d", table_role.inited());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `inited`=%d", table_role.inited());
            break;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`createtime`=%lld", table_role.createtime());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `createtime`=%lld", table_role.createtime());
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`face`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `face`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`online`=%lld", table_role.online());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `online`=%lld", table_role.online());
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
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from role where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_ROLE_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_role.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_role.version());
            break;
        }
        case GORM_PB_FIELD_ROLE_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_role.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_role.roleid());
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`rolename`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `rolename`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLE_LEVEL:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`level`=%d", table_role.level());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `level`=%d", table_role.level());
            break;
        }
        case GORM_PB_FIELD_ROLE_EXP:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`exp`=%lld", table_role.exp());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `exp`=%lld", table_role.exp());
            break;
        }
        case GORM_PB_FIELD_ROLE_CHARACTERID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`characterid`=%d", table_role.characterid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `characterid`=%d", table_role.characterid());
            break;
        }
        case GORM_PB_FIELD_ROLE_GOLD:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`gold`=%d", table_role.gold());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `gold`=%d", table_role.gold());
            break;
        }
        case GORM_PB_FIELD_ROLE_OFFLINETIME:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`offlinetime`=%lld", table_role.offlinetime());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `offlinetime`=%lld", table_role.offlinetime());
            break;
        }
        case GORM_PB_FIELD_ROLE_INITED:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`inited`=%d", table_role.inited());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `inited`=%d", table_role.inited());
            break;
        }
        case GORM_PB_FIELD_ROLE_CREATETIME:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`createtime`=%lld", table_role.createtime());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `createtime`=%lld", table_role.createtime());
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`face`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `face`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLE_ONLINE:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`online`=%lld", table_role.online());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `online`=%lld", table_role.online());
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
#define GetByNonPrimaySQL_SCENE "select `version`,`roleid`,`sceneid`,`collects` from scene_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLSCENE_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_scene &table_scene, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_SCENE);
    int iTotalLen = 64*vFields.size() + iLen + table_scene.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_SCENE, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_scene.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_scene.version());
            break;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_scene.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_scene.roleid());
            break;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`sceneid`=%d", table_scene.sceneid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `sceneid`=%d", table_scene.sceneid());
            break;
        }
        case GORM_PB_FIELD_SCENE_COLLECTS:
        {
            char *szData = "";
            const string &strData = table_scene.collects();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`collects`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `collects`=`%s`", szData);
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
#define GetByNonPrimaySQL_SCENE_DEBUG "select `version`,`roleid`,`sceneid`,`collects`"
int GORM_PackGet_By_Non_Primary_KeySQLSCENE_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_scene &table_scene, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_SCENE_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_scene.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_SCENE_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["scene"];
    for (int i=4; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from scene where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_SCENE_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_scene.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_scene.version());
            break;
        }
        case GORM_PB_FIELD_SCENE_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_scene.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_scene.roleid());
            break;
        }
        case GORM_PB_FIELD_SCENE_SCENEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`sceneid`=%d", table_scene.sceneid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `sceneid`=%d", table_scene.sceneid());
            break;
        }
        case GORM_PB_FIELD_SCENE_COLLECTS:
        {
            char *szData = "";
            const string &strData = table_scene.collects();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`collects`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `collects`=`%s`", szData);
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
int GORM_PackGet_By_Non_Primary_KeySQLSCENE(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_scene())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_scene &table_scene = table.scene();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "scene", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLSCENE_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_scene, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLSCENE_One(mysql, iTableIndex, table_scene, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_SKILL "select `version`,`roleid`,`snakeid`,`skill1`,`skill2`,`skill3`,`skill4` from skill_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLSKILL_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_skill &table_skill, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_SKILL);
    int iTotalLen = 64*vFields.size() + iLen + table_skill.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_SKILL, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_skill.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_skill.version());
            break;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_skill.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_skill.roleid());
            break;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_skill.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_skill.snakeid());
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL1:
        {
            char *szData = "";
            const string &strData = table_skill.skill1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`skill1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `skill1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL2:
        {
            char *szData = "";
            const string &strData = table_skill.skill2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`skill2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `skill2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL3:
        {
            char *szData = "";
            const string &strData = table_skill.skill3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`skill3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `skill3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL4:
        {
            char *szData = "";
            const string &strData = table_skill.skill4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`skill4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `skill4`=`%s`", szData);
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
#define GetByNonPrimaySQL_SKILL_DEBUG "select `version`,`roleid`,`snakeid`,`skill1`,`skill2`,`skill3`,`skill4`"
int GORM_PackGet_By_Non_Primary_KeySQLSKILL_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_skill &table_skill, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_SKILL_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_skill.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_SKILL_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["skill"];
    for (int i=7; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from skill where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_SKILL_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_skill.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_skill.version());
            break;
        }
        case GORM_PB_FIELD_SKILL_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_skill.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_skill.roleid());
            break;
        }
        case GORM_PB_FIELD_SKILL_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_skill.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_skill.snakeid());
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL1:
        {
            char *szData = "";
            const string &strData = table_skill.skill1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`skill1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `skill1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL2:
        {
            char *szData = "";
            const string &strData = table_skill.skill2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`skill2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `skill2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL3:
        {
            char *szData = "";
            const string &strData = table_skill.skill3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`skill3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `skill3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_SKILL_SKILL4:
        {
            char *szData = "";
            const string &strData = table_skill.skill4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`skill4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `skill4`=`%s`", szData);
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
int GORM_PackGet_By_Non_Primary_KeySQLSKILL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_skill())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_skill &table_skill = table.skill();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "skill", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLSKILL_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_skill, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLSKILL_One(mysql, iTableIndex, table_skill, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_INTERACTION "select `version`,`roleid`,`snakeid`,`interaction1`,`interaction2`,`interaction3`,`interaction4` from interaction_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLINTERACTION_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_interaction &table_interaction, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_INTERACTION);
    int iTotalLen = 64*vFields.size() + iLen + table_interaction.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_INTERACTION, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_interaction.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_interaction.version());
            break;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_interaction.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_interaction.roleid());
            break;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_interaction.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_interaction.snakeid());
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION1:
        {
            char *szData = "";
            const string &strData = table_interaction.interaction1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`interaction1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `interaction1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION2:
        {
            char *szData = "";
            const string &strData = table_interaction.interaction2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`interaction2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `interaction2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION3:
        {
            char *szData = "";
            const string &strData = table_interaction.interaction3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`interaction3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `interaction3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION4:
        {
            char *szData = "";
            const string &strData = table_interaction.interaction4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`interaction4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `interaction4`=`%s`", szData);
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
#define GetByNonPrimaySQL_INTERACTION_DEBUG "select `version`,`roleid`,`snakeid`,`interaction1`,`interaction2`,`interaction3`,`interaction4`"
int GORM_PackGet_By_Non_Primary_KeySQLINTERACTION_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_interaction &table_interaction, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_INTERACTION_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_interaction.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_INTERACTION_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["interaction"];
    for (int i=7; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from interaction where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_INTERACTION_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_interaction.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_interaction.version());
            break;
        }
        case GORM_PB_FIELD_INTERACTION_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_interaction.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_interaction.roleid());
            break;
        }
        case GORM_PB_FIELD_INTERACTION_SNAKEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`snakeid`=%d", table_interaction.snakeid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `snakeid`=%d", table_interaction.snakeid());
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION1:
        {
            char *szData = "";
            const string &strData = table_interaction.interaction1();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`interaction1`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `interaction1`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION2:
        {
            char *szData = "";
            const string &strData = table_interaction.interaction2();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`interaction2`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `interaction2`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION3:
        {
            char *szData = "";
            const string &strData = table_interaction.interaction3();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`interaction3`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `interaction3`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_INTERACTION_INTERACTION4:
        {
            char *szData = "";
            const string &strData = table_interaction.interaction4();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`interaction4`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `interaction4`=`%s`", szData);
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
int GORM_PackGet_By_Non_Primary_KeySQLINTERACTION(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_interaction())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_interaction &table_interaction = table.interaction();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "interaction", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLINTERACTION_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_interaction, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLINTERACTION_One(mysql, iTableIndex, table_interaction, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_USER "select `version`,`userid`,`ptid`,`pttype`,`createtime` from user_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLUSER_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_user &table_user, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_USER);
    int iTotalLen = 64*vFields.size() + iLen + table_user.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_USER, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_user.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_user.version());
            break;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`userid`=%lld", table_user.userid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `userid`=%lld", table_user.userid());
            break;
        }
        case GORM_PB_FIELD_USER_PTID:
        {
            char *szData = "";
            const string &strData = table_user.ptid();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`ptid`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `ptid`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`pttype`=%d", table_user.pttype());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `pttype`=%d", table_user.pttype());
            break;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`createtime`=%lld", table_user.createtime());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `createtime`=%lld", table_user.createtime());
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#ifdef GORM_DEBUG
#define GetByNonPrimaySQL_USER_DEBUG "select `version`,`userid`,`ptid`,`pttype`,`createtime`"
int GORM_PackGet_By_Non_Primary_KeySQLUSER_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_user &table_user, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_USER_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_user.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_USER_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["user"];
    for (int i=5; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from user where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_USER_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_user.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_user.version());
            break;
        }
        case GORM_PB_FIELD_USER_USERID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`userid`=%lld", table_user.userid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `userid`=%lld", table_user.userid());
            break;
        }
        case GORM_PB_FIELD_USER_PTID:
        {
            char *szData = "";
            const string &strData = table_user.ptid();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`ptid`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `ptid`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_USER_PTTYPE:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`pttype`=%d", table_user.pttype());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `pttype`=%d", table_user.pttype());
            break;
        }
        case GORM_PB_FIELD_USER_CREATETIME:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`createtime`=%lld", table_user.createtime());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `createtime`=%lld", table_user.createtime());
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#endif
int GORM_PackGet_By_Non_Primary_KeySQLUSER(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_user())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_user &table_user = table.user();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "user", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLUSER_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_user, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLUSER_One(mysql, iTableIndex, table_user, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
#define GetByNonPrimaySQL_ROLES "select `version`,`roleid`,`userid`,`worldid`,`dbid`,`name`,`charid`,`face`,`createtime` from roles_%d where "
int GORM_PackGet_By_Non_Primary_KeySQLROLES_One(MYSQL* mysql, int iTableIndex, const GORM_PB_Table_roles &table_roles, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_ROLES);
    int iTotalLen = 64*vFields.size() + iLen + table_roles.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    iLen = GORM_SafeSnprintf(szSQLBegin, iLen, GetByNonPrimaySQL_ROLES, iTableIndex);
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_roles.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_roles.version());
            break;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_roles.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_roles.roleid());
            break;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`userid`=%lld", table_roles.userid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `userid`=%lld", table_roles.userid());
            break;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`worldid`=%lld", table_roles.worldid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `worldid`=%lld", table_roles.worldid());
            break;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`dbid`=%d", table_roles.dbid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `dbid`=%d", table_roles.dbid());
            break;
        }
        case GORM_PB_FIELD_ROLES_NAME:
        {
            char *szData = "";
            const string &strData = table_roles.name();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`name`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `name`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`charid`=%d", table_roles.charid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `charid`=%d", table_roles.charid());
            break;
        }
        case GORM_PB_FIELD_ROLES_FACE:
        {
            char *szData = "";
            const string &strData = table_roles.face();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`face`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `face`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`createtime`=%lld", table_roles.createtime());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `createtime`=%lld", table_roles.createtime());
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#ifdef GORM_DEBUG
#define GetByNonPrimaySQL_ROLES_DEBUG "select `version`,`roleid`,`userid`,`worldid`,`dbid`,`name`,`charid`,`face`,`createtime`"
int GORM_PackGet_By_Non_Primary_KeySQLROLES_One_DEBUG(GORM_MySQLEvent *pMySQLEvent, int iTableIndex, const GORM_PB_CUSTEM_COLUMNS &pbColumns, const GORM_PB_Table_roles &table_roles, const GORM_PB_REQ_HEADER &header, GORM_MemPoolData *&pReqData)
{

	MYSQL* mysql = pMySQLEvent->m_pMySQL;
	string fieldMode = header.fieldmode();
    if (fieldMode == "")
        return GORM_REQ_NO_RECORDS;
    vector<int> vFields = GORM_FieldsOpt::GetFields(fieldMode.c_str(), fieldMode.size());
    int iLen = strlen(GetByNonPrimaySQL_ROLES_DEBUG);
    int iTotalLen = 64*vFields.size() + pbColumns.ByteSizeLong() + iLen + table_roles.ByteSizeLong();
    pReqData = GORM_MemPool::Instance()->GetData(iTotalLen);
    char *szSQLBegin = pReqData->m_uszData;
    strncpy(szSQLBegin, GetByNonPrimaySQL_ROLES_DEBUG, iLen);
    vector<string> &vColumns = pMySQLEvent->m_mapTablesColumnOrder["roles"];
    for (int i=9; i<vColumns.size(); i++)
    {
        iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, ", `%s`", vColumns[i].c_str());
    }
    iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " from roles where ");
    for(int i=0; i<vFields.size(); i++)
    {
        switch (vFields[i])
        {
        case GORM_PB_FIELD_ROLES_VERSION:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`version`=%llu", table_roles.version());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `version`=%llu", table_roles.version());
            break;
        }
        case GORM_PB_FIELD_ROLES_ROLEID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`roleid`=%lld", table_roles.roleid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `roleid`=%lld", table_roles.roleid());
            break;
        }
        case GORM_PB_FIELD_ROLES_USERID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`userid`=%lld", table_roles.userid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `userid`=%lld", table_roles.userid());
            break;
        }
        case GORM_PB_FIELD_ROLES_WORLDID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`worldid`=%lld", table_roles.worldid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `worldid`=%lld", table_roles.worldid());
            break;
        }
        case GORM_PB_FIELD_ROLES_DBID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`dbid`=%d", table_roles.dbid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `dbid`=%d", table_roles.dbid());
            break;
        }
        case GORM_PB_FIELD_ROLES_NAME:
        {
            char *szData = "";
            const string &strData = table_roles.name();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`name`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `name`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLES_CHARID:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`charid`=%d", table_roles.charid());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `charid`=%d", table_roles.charid());
            break;
        }
        case GORM_PB_FIELD_ROLES_FACE:
        {
            char *szData = "";
            const string &strData = table_roles.face();
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
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`face`=`%s`", szData);
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, " and `face`=`%s`", szData);
            if (pDataBuffer != nullptr)
                pDataBuffer->Release();
            break;
        }
        case GORM_PB_FIELD_ROLES_CREATETIME:
        {
            if (i==0)
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "`createtime`=%lld", table_roles.createtime());
            else
                iLen += GORM_SafeSnprintf(szSQLBegin+iLen, iTotalLen-iLen, "and `createtime`=%lld", table_roles.createtime());
            break;
        }
        }
    }
    pReqData->m_sUsedSize = iLen;
    return GORM_OK;
}
#endif
int GORM_PackGet_By_Non_Primary_KeySQLROLES(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableIndex, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{

	if (!pMsg->has_header())
        return GORM_REQ_MSG_NO_HEADER;
    int iTableNum = pMsg->tables_size();
    if (iTableNum == 0)
        return GORM_REQ_NO_RECORDS;
    for (int i=0; i<iTableNum; i++)
    {
        const GORM_PB_TABLE &table = pMsg->tables(i);
        if (!table.has_roles())
            return GORM_REQ_NO_RECORDS;
        const GORM_PB_Table_roles &table_roles = table.roles();
#ifdef GORM_DEBUG
        GORM_MySQLUpdateTableSchema(pMySQLEvent, "roles", table.custom_columns());
        return GORM_PackGet_By_Non_Primary_KeySQLROLES_One_DEBUG(pMySQLEvent, iTableIndex, table.custom_columns(), table_roles, pMsg->header(), pReqData);
#endif
        return GORM_PackGet_By_Non_Primary_KeySQLROLES_One(mysql, iTableIndex, table_roles, pMsg->header(), pReqData);
    }
    return GORM_OK;
}
int GORM_PackGet_By_Non_Primary_KeySQL(GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_CURRENCY:
        return GORM_PackGet_By_Non_Primary_KeySQLCURRENCY(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_CYCLEEVENT:
        return GORM_PackGet_By_Non_Primary_KeySQLCYCLEEVENT(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_EQUIP:
        return GORM_PackGet_By_Non_Primary_KeySQLEQUIP(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_FOOD:
        return GORM_PackGet_By_Non_Primary_KeySQLFOOD(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_HERO:
        return GORM_PackGet_By_Non_Primary_KeySQLHERO(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MAIL:
        return GORM_PackGet_By_Non_Primary_KeySQLMAIL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_MATERIAL:
        return GORM_PackGet_By_Non_Primary_KeySQLMATERIAL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_NPC:
        return GORM_PackGet_By_Non_Primary_KeySQLNPC(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLE:
        return GORM_PackGet_By_Non_Primary_KeySQLROLE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SCENE:
        return GORM_PackGet_By_Non_Primary_KeySQLSCENE(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_SKILL:
        return GORM_PackGet_By_Non_Primary_KeySQLSKILL(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_INTERACTION:
        return GORM_PackGet_By_Non_Primary_KeySQLINTERACTION(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_USER:
        return GORM_PackGet_By_Non_Primary_KeySQLUSER(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
    case GORM_PB_TABLE_IDX_ROLES:
        return GORM_PackGet_By_Non_Primary_KeySQLROLES(pMySQLEvent, mysql, uiHashValue, pMsg, pReqData);
    
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
int GORM_MySQLResult2PbMSG_EQUIP(GORM_PB_Table_equip *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_equip1(row[3], lengths[3]);
    else
        pPbTable->set_equip1("");

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_equip2(row[4], lengths[4]);
    else
        pPbTable->set_equip2("");

    if (nullptr != row[5] && lengths[5] > 0)
        pPbTable->set_equip3(row[5], lengths[5]);
    else
        pPbTable->set_equip3("");

    if (nullptr != row[6] && lengths[6] > 0)
        pPbTable->set_equip4(row[6], lengths[6]);
    else
        pPbTable->set_equip4("");

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_FOOD(GORM_PB_Table_food *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_food1(row[3], lengths[3]);
    else
        pPbTable->set_food1("");

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_food2(row[4], lengths[4]);
    else
        pPbTable->set_food2("");

    if (nullptr != row[5] && lengths[5] > 0)
        pPbTable->set_food3(row[5], lengths[5]);
    else
        pPbTable->set_food3("");

    if (nullptr != row[6] && lengths[6] > 0)
        pPbTable->set_food4(row[6], lengths[6]);
    else
        pPbTable->set_food4("");

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_HERO(GORM_PB_Table_hero *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_heros(row[3], lengths[3]);
    else
        pPbTable->set_heros("");

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_MAIL(GORM_PB_Table_mail *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_mail1(row[2], lengths[2]);
    else
        pPbTable->set_mail1("");

    if (nullptr != row[3] && lengths[3] > 0)
        pPbTable->set_mail2(row[3], lengths[3]);
    else
        pPbTable->set_mail2("");

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_mail3(row[4], lengths[4]);
    else
        pPbTable->set_mail3("");

    if (nullptr != row[5] && lengths[5] > 0)
        pPbTable->set_mail4(row[5], lengths[5]);
    else
        pPbTable->set_mail4("");

    if (nullptr != row[6] && lengths[6] > 0)
        pPbTable->set_mail5(row[6], lengths[6]);
    else
        pPbTable->set_mail5("");

    if (nullptr != row[7] && lengths[7] > 0)
        pPbTable->set_lastmailid(strtol(row[7], (char **)NULL,10));
    else
        pPbTable->set_lastmailid(0);

    if (nullptr != row[8] && lengths[8] > 0)
        pPbTable->set_snakeid(strtol(row[8], (char **)NULL,10));
    else
        pPbTable->set_snakeid(0);

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_MATERIAL(GORM_PB_Table_material *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_material1(row[3], lengths[3]);
    else
        pPbTable->set_material1("");

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_material2(row[4], lengths[4]);
    else
        pPbTable->set_material2("");

    if (nullptr != row[5] && lengths[5] > 0)
        pPbTable->set_material3(row[5], lengths[5]);
    else
        pPbTable->set_material3("");

    if (nullptr != row[6] && lengths[6] > 0)
        pPbTable->set_material4(row[6], lengths[6]);
    else
        pPbTable->set_material4("");

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_NPC(GORM_PB_Table_npc *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_npcs(row[3], lengths[3]);
    else
        pPbTable->set_npcs("");

    return GORM_OK;
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
int GORM_MySQLResult2PbMSG_SCENE(GORM_PB_Table_scene *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_sceneid(strtol(row[2], (char **)NULL,10));
    else
        pPbTable->set_sceneid(0);

    if (nullptr != row[3] && lengths[3] > 0)
        pPbTable->set_collects(row[3], lengths[3]);
    else
        pPbTable->set_collects("");

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_SKILL(GORM_PB_Table_skill *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_skill1(row[3], lengths[3]);
    else
        pPbTable->set_skill1("");

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_skill2(row[4], lengths[4]);
    else
        pPbTable->set_skill2("");

    if (nullptr != row[5] && lengths[5] > 0)
        pPbTable->set_skill3(row[5], lengths[5]);
    else
        pPbTable->set_skill3("");

    if (nullptr != row[6] && lengths[6] > 0)
        pPbTable->set_skill4(row[6], lengths[6]);
    else
        pPbTable->set_skill4("");

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_INTERACTION(GORM_PB_Table_interaction *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_interaction1(row[3], lengths[3]);
    else
        pPbTable->set_interaction1("");

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_interaction2(row[4], lengths[4]);
    else
        pPbTable->set_interaction2("");

    if (nullptr != row[5] && lengths[5] > 0)
        pPbTable->set_interaction3(row[5], lengths[5]);
    else
        pPbTable->set_interaction3("");

    if (nullptr != row[6] && lengths[6] > 0)
        pPbTable->set_interaction4(row[6], lengths[6]);
    else
        pPbTable->set_interaction4("");

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_USER(GORM_PB_Table_user *pPbTable, MYSQL_ROW row, unsigned long *lengths)
{
    if (nullptr != row[0] && lengths[0] > 0)
        pPbTable->set_version(strtoull(row[0], (char **)NULL,10));
    else
        pPbTable->set_version(0);

    if (nullptr != row[1] && lengths[1] > 0)
        pPbTable->set_userid(strtoll(row[1], (char **)NULL,10));
    else
        pPbTable->set_userid(0);

    if (nullptr != row[2] && lengths[2] > 0)
        pPbTable->set_ptid(row[2], lengths[2]);
    else
        pPbTable->set_ptid("");

    if (nullptr != row[3] && lengths[3] > 0)
        pPbTable->set_pttype(strtol(row[3], (char **)NULL,10));
    else
        pPbTable->set_pttype(0);

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_createtime(strtoll(row[4], (char **)NULL,10));
    else
        pPbTable->set_createtime(0);

    return GORM_OK;
}
int GORM_MySQLResult2PbMSG_ROLES(GORM_PB_Table_roles *pPbTable, MYSQL_ROW row, unsigned long *lengths)
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
        pPbTable->set_userid(strtoll(row[2], (char **)NULL,10));
    else
        pPbTable->set_userid(0);

    if (nullptr != row[3] && lengths[3] > 0)
        pPbTable->set_worldid(strtoll(row[3], (char **)NULL,10));
    else
        pPbTable->set_worldid(0);

    if (nullptr != row[4] && lengths[4] > 0)
        pPbTable->set_dbid(strtol(row[4], (char **)NULL,10));
    else
        pPbTable->set_dbid(0);

    if (nullptr != row[5] && lengths[5] > 0)
        pPbTable->set_name(row[5], lengths[5]);
    else
        pPbTable->set_name("");

    if (nullptr != row[6] && lengths[6] > 0)
        pPbTable->set_charid(strtol(row[6], (char **)NULL,10));
    else
        pPbTable->set_charid(0);

    if (nullptr != row[7] && lengths[7] > 0)
        pPbTable->set_face(row[7], lengths[7]);
    else
        pPbTable->set_face("");

    if (nullptr != row[8] && lengths[8] > 0)
        pPbTable->set_createtime(strtoll(row[8], (char **)NULL,10));
    else
        pPbTable->set_createtime(0);

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
#ifdef GORM_DEBUG
int GORM_MySQLResult2PbMSG_EQUIP_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_equip *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_EQUIP(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["equip"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["equip"];
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
int GORM_MySQLResult2PbMSG_FOOD_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_food *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_FOOD(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["food"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["food"];
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
int GORM_MySQLResult2PbMSG_HERO_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_hero *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_HERO(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["hero"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["hero"];
    for (int i=4; i<vTablesColumnOrder.size(); i++)
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
int GORM_MySQLResult2PbMSG_MAIL_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_mail *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_MAIL(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["mail"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["mail"];
    for (int i=9; i<vTablesColumnOrder.size(); i++)
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
int GORM_MySQLResult2PbMSG_MATERIAL_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_material *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_MATERIAL(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["material"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["material"];
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
int GORM_MySQLResult2PbMSG_NPC_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_npc *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_NPC(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["npc"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["npc"];
    for (int i=4; i<vTablesColumnOrder.size(); i++)
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
#ifdef GORM_DEBUG
int GORM_MySQLResult2PbMSG_SCENE_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_scene *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_SCENE(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["scene"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["scene"];
    for (int i=4; i<vTablesColumnOrder.size(); i++)
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
int GORM_MySQLResult2PbMSG_SKILL_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_skill *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_SKILL(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["skill"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["skill"];
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
int GORM_MySQLResult2PbMSG_INTERACTION_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_interaction *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_INTERACTION(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["interaction"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["interaction"];
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
int GORM_MySQLResult2PbMSG_USER_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_user *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_USER(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["user"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["user"];
    for (int i=5; i<vTablesColumnOrder.size(); i++)
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
int GORM_MySQLResult2PbMSG_ROLES_DEBUG(GORM_MySQLEvent *pMySQLEvent, GORM_PB_Table_roles *pPbTable, GORM_PB_CUSTEM_COLUMNS *pColumns, MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != GORM_MySQLResult2PbMSG_ROLES(pPbTable, row, lengths))
        return GORM_ERROR;
    return GORM_OK;
    vector<string> &vTablesColumnOrder = pMySQLEvent->m_mapTablesColumnOrder["roles"];
    unordered_map<string, GORM_PB_COLUMN_TYPE> &mapTablesColumnType = pMySQLEvent->m_mapTablesColumnInfo["roles"];
    for (int i=9; i<vTablesColumnOrder.size(); i++)
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
    case GORM_PB_TABLE_IDX_EQUIP:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_equip *pSrcTable = pPbTable->mutable_equip();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_EQUIP_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_equip *pSrcTable = pPbTable->mutable_equip();
        return GORM_MySQLResult2PbMSG_EQUIP(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_FOOD:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_food *pSrcTable = pPbTable->mutable_food();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_FOOD_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_food *pSrcTable = pPbTable->mutable_food();
        return GORM_MySQLResult2PbMSG_FOOD(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_HERO:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_hero *pSrcTable = pPbTable->mutable_hero();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_HERO_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_hero *pSrcTable = pPbTable->mutable_hero();
        return GORM_MySQLResult2PbMSG_HERO(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_MAIL:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_mail *pSrcTable = pPbTable->mutable_mail();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_MAIL_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_mail *pSrcTable = pPbTable->mutable_mail();
        return GORM_MySQLResult2PbMSG_MAIL(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_MATERIAL:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_material *pSrcTable = pPbTable->mutable_material();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_MATERIAL_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_material *pSrcTable = pPbTable->mutable_material();
        return GORM_MySQLResult2PbMSG_MATERIAL(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_NPC:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_npc *pSrcTable = pPbTable->mutable_npc();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_NPC_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_npc *pSrcTable = pPbTable->mutable_npc();
        return GORM_MySQLResult2PbMSG_NPC(pSrcTable, row, lengths);
    #endif
    }
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
    case GORM_PB_TABLE_IDX_SCENE:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_scene *pSrcTable = pPbTable->mutable_scene();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_SCENE_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_scene *pSrcTable = pPbTable->mutable_scene();
        return GORM_MySQLResult2PbMSG_SCENE(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_SKILL:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_skill *pSrcTable = pPbTable->mutable_skill();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_SKILL_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_skill *pSrcTable = pPbTable->mutable_skill();
        return GORM_MySQLResult2PbMSG_SKILL(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_INTERACTION:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_interaction *pSrcTable = pPbTable->mutable_interaction();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_INTERACTION_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_interaction *pSrcTable = pPbTable->mutable_interaction();
        return GORM_MySQLResult2PbMSG_INTERACTION(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_USER:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_user *pSrcTable = pPbTable->mutable_user();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_USER_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_user *pSrcTable = pPbTable->mutable_user();
        return GORM_MySQLResult2PbMSG_USER(pSrcTable, row, lengths);
    #endif
    }
    case GORM_PB_TABLE_IDX_ROLES:
    {
    #ifdef GORM_DEBUG
        GORM_PB_Table_roles *pSrcTable = pPbTable->mutable_roles();
        GORM_PB_CUSTEM_COLUMNS *pColumns = pPbTable->mutable_custom_columns();
        return GORM_MySQLResult2PbMSG_ROLES_DEBUG(pMySQLEvent, pSrcTable, pColumns, row, lengths);
    #else
        GORM_PB_Table_roles *pSrcTable = pPbTable->mutable_roles();
        return GORM_MySQLResult2PbMSG_ROLES(pSrcTable, row, lengths);
    #endif
    }
    default:
        return GORM_INVALID_TABLE;
    }

    return GORM_OK;
}
