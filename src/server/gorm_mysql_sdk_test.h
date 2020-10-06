#ifndef GORM_MYSQL_TEST
#define GORM_MYSQL_TEST

#include "gorm_sys_inc.h"
#include "gorm_server_instance.h"
#include "gorm_error.h"
#include "gorm_config.h"
#include "gorm_daemonize.h"
#include "gorm_options.h"
#include "gorm_utils.h"
#include "gorm_work_thread.h"
#include "gorm_frontend_thread.h"
#include "gorm_db_config.h"
#include "gorm_table_field_map.h"
#include "gorm_mysql_conn_pool.h"
#include "gorm_type.h"
#include "gorm-db.pb.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_mempool.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace gorm;

MYSQL *Connect2MySQL(GORM_DBInfo *pDbCfg)
{
    MYSQL *pMySQL;
    pMySQL = mysql_init(NULL);
    if (pMySQL == nullptr)
    {
        cout << "mysql_init failed" << endl;
        return nullptr;
    }

    GORM_RouteInfo *pRoute = GetDatabaseRoute();
    if (pRoute == nullptr)
    {
        GORM_LOGE("get database route failed.");
        return nullptr;
    }

    pDbCfg = &(pRoute->dblist.vDBLists[0]);

    net_async_status iConnectStatus = NET_ASYNC_ERROR;
    while ((iConnectStatus = mysql_real_connect_nonblocking(pMySQL, pDbCfg->szHost, pDbCfg->szUser,
                                                  pDbCfg->szPW, pDbCfg->szDB, pDbCfg->uiPort,
                                                  nullptr, 0))
               == NET_ASYNC_NOT_READY);

    if (iConnectStatus == NET_ASYNC_ERROR)
    {
        cout << "connect to mysql failed, errinfo:" << mysql_error(pMySQL) << endl;
        mysql_close(pMySQL);
        return nullptr;
    }
    cout << "connecto to mysql success" << endl;
    return pMySQL;
}

/*int GORM_PackGetSQLCURRENCY_ONE(shared_ptr<GORM_MemPool> &pMemPool, MYSQL* mysql, int iTableIndex, 
        const GORM_PB_Table_currency &table_currency, GORM_MemPoolData *&pReqData);
*/
#define CHARBASE_SQL "SELECT `CHARID`, `ACCID`, `NAME`, `TYPE`, `LEVEL`, `FACE`, `HAIR`, `BODYCOLOR`, `GOODNESS`, `PKADDITION`, `MAPID`, `MAPNAME`, `X`, `Y`, `HP`, `MP`, `SP`, `CREATEIP`, `EXP`, `LUCKY`, `SKILLPOINTS`, `POINTS`, `COUNTRY`, `UNIONID`, `CONSORT`, `SEPTID`, `SCHOOLID`, `SYSSET`, `FORBIDTALK`, `BITMASK`, `ONLINETIME`, `AVAILABLE`, `LASTACTIVEDATE`, `MEN`, `ZHENG_INT`, `DEX`, `STR`, `CON`, `RELIVEWEAKTIME`, `GRACE`, `EXPLOIT`, `TIRETIME`, `OFFLINETIME`, `FIVETYPE`, `FIVELEVEL`, `ALLBINARY`, `ANSWERCOUNT`, `MONEY`, `HONOR`, `GOMAPTYPE`, `MAXHONOR`, `MSGTIME`, `ACCPRIV`, `GOLD`, `TICKET`, `CREATETIME`, `GOLDGIVE`, `PETPACK`, `PETPOINT`, `LEVELSEPT`, `PUNISHTIME`, `TRAINTIME`, `CAPTION`, `ZONE_STATE`, `SOURCE_ID`, `SOURCE_ZONE`, `TARGET_ZONE`, `SALARY`, `LASTIP`, `ROUND`, `NUMPASSWD`, `NUMPASSWDCANCELTIME`, `OPENMONEYBOX`, `OBJ_CMD`, `BIND_MONEY`, `DROPTIME`, `TRAVEL`, `LASTTRAVELTIME`, `BACKDATA`, `IMGERRLOCK`, `PHOTOCHECKSTATE`, `NEWWORLDID`, `PROVINCE`, `CITY`, `SOURCE_COUNTRY`, `NEWWORLDID_ZONE`, `ICQMASK`, `FORBIDTIME`, `FORBIDTALKTYPE`, `VIPEXCHTOTAL`, `BUYFUND`, `GETFUNDGOLD`, `TATOLGOLDNUM`, `BODYID`, `ACTIVITY`, `DEPOSIT`, `MASTERPOINT`, `PROMOTERACCID`, `PROMOTERSTATE`, `GETSEVENTYTIME`, `CONTRIBUTE`, `ALIACCOUNT`, `ACTIVITY3`, `FIGHTPOINT`, `CHANGEZONETYPE`, `MERGE_ZONEID`, `LOSTBACK`, `MONEYCARD`, `MACHINECODE`, `NUMPASSWD2`, `NUMPASSWD3`, `NUMPASSWD4`, `NUMPASSWD5`, `NUMPASSWD6`, `QQ_1`, `QQ_2`, `DEPOSIT_SALARY`, `TOTAL_EXCHANGE_MONEY`, `RESOLUTIIONS`, `AMOY_PRIZE_MONEY`, `MONEY_INCOME`, `MONEY_PAY`, `MAC`, `ISMCPRECREATE`, `PRECREATE_POINT`, `PKLEVEL`, `VALUE_MATERIAL`, `VALUE_SALARY`, `VALUE_WARSOUL`, `VALUE_MANTLE`, `VALUE_POINT`, `VOTETIME`, `LASTWEEKLOGIN`, `CURWEEKLOGIN`, `LEVELDEGREE`, `LEVELDEGREEGLOBAL`, `ZHENQI`, `BLOODDIAMOND`, `DCHARGE_POINT`, `DCHARGE_TYPE`, `MAIN_CAREER`, `MAIN_SUBCAREER`, `SECOND_CAREER`, `SECOND_SUBCAREER`, `BLOOD_DIAMOND_OBJ`, `LEVEL_SECSOUL`, `LEVEL_SKYSOUL`, `SYNHOMEGARDEN`, `FIGHTPOINT_TIME`, `TRAVELING`, `BLOOD_DIAMOND_BINDOBJ`, `TARGET_COUNTRY`, `ZT2_POINT`, `ZT2_POINT_OBJ`, `ZT2_POINT_BINDOBJ`, `ZT2_POINT_YICHANGOBJ`, `ZT2_POINT_YICHANGBINDOBJ`, `TARGET_MAP`, `TRAVELSCORE`, `YYCODE`, `ELAPSE_BLOODOBJ`, `ELAPSE_BLOODBINDOBJ`, `MYCACHE_MD5`, `BATI`, `SUPERPACKBINARY`, `SUITLEVEL`, `SUPERPACKVERSION`, `MUTISKILLPOINTS`, `OFFLINEHOOK`, `YEARENDBONUS`, `PKGRADE`, `LOGINGIFT`, `ISBOT`, `ZT2_POINT_HISTORY`, `YEARENDBONUS_1W`, `IS_CERTIFICATION`, `TRAVEL_BY_FUNCION`, `TARGET_POSX`, `TARGET_POSY`, `TARGET_MAPNAME`, `SILVER_CASH`, `TRANSACTIONS`, `BONUS`, `INSURANCE`, `CHATTIME`, `CURUSEFACE` FROM CHARBASE WHERE  `CHARID`=%d;"
class GORM_MySQLAsyncEventTest: public GORM_Event
{
public:
    GORM_MySQLAsyncEventTest(MYSQL *pMySQL, int iFD, shared_ptr<GORM_Epoll> pEpoll):
        GORM_Event(iFD, pEpoll), m_pMySQL(pMySQL)
    {
        this->m_Status = GORM_CONNECT_CONNECTED;
        this->m_pMemPool = make_shared<GORM_MemPool>();
    }
    virtual int Write()
    {
        if (this->m_iStep == 1)
        {
            return this->Read();
        }
        if (this->m_iStep == 2)
        {
            this->index += 1;
            int nowIdx = this->index % 4000000;
            this->iSQLLen = snprintf(this->szSQL, 128*1024, CHARBASE_SQL, nowIdx);
            this->szSQL[this->iSQLLen] = '\0';
            this->m_iStep = 0;
        }
        m_iOptStatus = mysql_real_query_nonblocking(this->m_pMySQL, this->szSQL, this->iSQLLen);
        if (m_iOptStatus == NET_ASYNC_NOT_READY)
        {
            return 0;
        }
        else if (m_iOptStatus == NET_ASYNC_ERROR)
        {
            cout << "send message 2 mysql failed:" << mysql_error(m_pMySQL) << endl;
            return GORM_ERROR;
        }
        else if (m_iOptStatus == NET_ASYNC_COMPLETE)
        {
            this->m_iStep = 1;
        }
        return 0;
    }
    virtual int Read()
    {
        if (this->m_iStep != 1)
        {
            return this->Write();
        }
        m_iOptStatus = mysql_store_result_nonblocking(this->m_pMySQL, &m_pReadingMySQLResult);
        if (m_iOptStatus == NET_ASYNC_NOT_READY)
        {
            return 0;
        }
        else if (m_iOptStatus == NET_ASYNC_ERROR)
        {
            cout << "get message from mysql failed:" << mysql_error(m_pMySQL) << endl;
            return GORM_ERROR;
        }
        else if (m_iOptStatus == NET_ASYNC_COMPLETE)
        {
            *this->iFinishNum += 1;
            //cout << *this->iFinishNum << "    , now:" << GORM_GetNowMS() <<endl;
            this->m_iStep = 2;
            this->m_pReadingMySQLResult = mysql_store_result(m_pMySQL);
            if (this->m_pReadingMySQLResult == nullptr)
                return 0;
            int iReadingRows =mysql_num_rows(this->m_pReadingMySQLResult);
            MYSQL_ROW stRow;
            for (int i=0; i<iReadingRows; i++)
            {
                stRow = mysql_fetch_row(this->m_pReadingMySQLResult);
            }
            mysql_free_result(m_pReadingMySQLResult);
            this->m_pReadingMySQLResult = nullptr;
        }
        
        return 0;
    }
public:
    MYSQL               *m_pMySQL = nullptr;
    //char                *m_sql = "SELECT `CHARID`, `ACCID`, `NAME`, `TYPE`, `LEVEL`, `FACE`, `HAIR`, `BODYCOLOR`, `GOODNESS`, `PKADDITION`, `MAPID`, `MAPNAME`, `X`, `Y`, `HP`, `MP`, `SP`, `CREATEIP`, `EXP`, `LUCKY`, `SKILLPOINTS`, `POINTS`, `COUNTRY`, `UNIONID`, `CONSORT`, `SEPTID`, `SCHOOLID`, `SYSSET`, `FORBIDTALK`, `BITMASK`, `ONLINETIME`, `AVAILABLE`, `LASTACTIVEDATE`, `MEN`, `ZHENG_INT`, `DEX`, `STR`, `CON`, `RELIVEWEAKTIME`, `GRACE`, `EXPLOIT`, `TIRETIME`, `OFFLINETIME`, `FIVETYPE`, `FIVELEVEL`, `ALLBINARY`, `ANSWERCOUNT`, `MONEY`, `HONOR`, `GOMAPTYPE`, `MAXHONOR`, `MSGTIME`, `ACCPRIV`, `GOLD`, `TICKET`, `CREATETIME`, `GOLDGIVE`, `PETPACK`, `PETPOINT`, `LEVELSEPT`, `PUNISHTIME`, `TRAINTIME`, `CAPTION`, `ZONE_STATE`, `SOURCE_ID`, `SOURCE_ZONE`, `TARGET_ZONE`, `SALARY`, `LASTIP`, `ROUND`, `NUMPASSWD`, `NUMPASSWDCANCELTIME`, `OPENMONEYBOX`, `OBJ_CMD`, `BIND_MONEY`, `DROPTIME`, `TRAVEL`, `LASTTRAVELTIME`, `BACKDATA`, `IMGERRLOCK`, `PHOTOCHECKSTATE`, `NEWWORLDID`, `PROVINCE`, `CITY`, `SOURCE_COUNTRY`, `NEWWORLDID_ZONE`, `ICQMASK`, `FORBIDTIME`, `FORBIDTALKTYPE`, `VIPEXCHTOTAL`, `BUYFUND`, `GETFUNDGOLD`, `TATOLGOLDNUM`, `BODYID`, `ACTIVITY`, `DEPOSIT`, `MASTERPOINT`, `PROMOTERACCID`, `PROMOTERSTATE`, `GETSEVENTYTIME`, `CONTRIBUTE`, `ALIACCOUNT`, `ACTIVITY3`, `FIGHTPOINT`, `CHANGEZONETYPE`, `MERGE_ZONEID`, `LOSTBACK`, `MONEYCARD`, `MACHINECODE`, `NUMPASSWD2`, `NUMPASSWD3`, `NUMPASSWD4`, `NUMPASSWD5`, `NUMPASSWD6`, `QQ_1`, `QQ_2`, `DEPOSIT_SALARY`, `TOTAL_EXCHANGE_MONEY`, `RESOLUTIIONS`, `AMOY_PRIZE_MONEY`, `MONEY_INCOME`, `MONEY_PAY`, `MAC`, `ISMCPRECREATE`, `PRECREATE_POINT`, `PKLEVEL`, `VALUE_MATERIAL`, `VALUE_SALARY`, `VALUE_WARSOUL`, `VALUE_MANTLE`, `VALUE_POINT`, `VOTETIME`, `LASTWEEKLOGIN`, `CURWEEKLOGIN`, `LEVELDEGREE`, `LEVELDEGREEGLOBAL`, `ZHENQI`, `BLOODDIAMOND`, `DCHARGE_POINT`, `DCHARGE_TYPE`, `MAIN_CAREER`, `MAIN_SUBCAREER`, `SECOND_CAREER`, `SECOND_SUBCAREER`, `BLOOD_DIAMOND_OBJ`, `LEVEL_SECSOUL`, `LEVEL_SKYSOUL`, `SYNHOMEGARDEN`, `FIGHTPOINT_TIME`, `TRAVELING`, `BLOOD_DIAMOND_BINDOBJ`, `TARGET_COUNTRY`, `ZT2_POINT`, `ZT2_POINT_OBJ`, `ZT2_POINT_BINDOBJ`, `ZT2_POINT_YICHANGOBJ`, `ZT2_POINT_YICHANGBINDOBJ`, `TARGET_MAP`, `TRAVELSCORE`, `YYCODE`, `ELAPSE_BLOODOBJ`, `ELAPSE_BLOODBINDOBJ`, `MYCACHE_MD5`, `BATI`, `SUPERPACKBINARY`, `SUITLEVEL`, `SUPERPACKVERSION`, `MUTISKILLPOINTS`, `OFFLINEHOOK`, `YEARENDBONUS`, `PKGRADE`, `LOGINGIFT`, `ISBOT`, `ZT2_POINT_HISTORY`, `YEARENDBONUS_1W`, `IS_CERTIFICATION`, `TRAVEL_BY_FUNCION`, `TARGET_POSX`, `TARGET_POSY`, `TARGET_MAPNAME`, `SILVER_CASH`, `TRANSACTIONS`, `BONUS`, `INSURANCE`, `CHATTIME`, `CURUSEFACE` FROM CHARBASE WHERE  `CHARID`=%d;";
    atomic<int>         *iFinishNum;
    MYSQL_RES           *m_pReadingMySQLResult;
    net_async_status    m_iOptStatus;
    int                 m_iStep = 2;    // 0为写，1为读
    GORM_MemPoolData    *m_pReqSQLData = nullptr;    // 组装的请求SQL语句
    shared_ptr<GORM_MemPool>        m_pMemPool = nullptr;
    char                szSQL[128*1024];
    int                 iSQLLen = 0;
    //GORM_PB_Table_currency m_TableCurrency;
    int index = 1;
};

int GORM_MySQLSDKTestThread(atomic<int> *iFinishNum, mutex *m, int dbIdx)
{
    mysql_thread_init();
    shared_ptr<GORM_Epoll> pEpool = make_shared<GORM_Epoll>();
    if (!pEpool->Init(1024))
    {
        cout << "init epool failed." << endl;
        return -1;
    }


    char *dbHost = "127.0.0.1";
    char *dbPwd = "123456";
    char *dbUser = "root";
    char *dbDatabase = "test";
    int dbPort = 3306; 
#define TEST_DB "test%d"
#define MYSQL_CONN_NUM 20
    GORM_DBInfo dbInfo;
    strncpy(dbInfo.szHost, dbHost, strlen(dbHost));
    dbInfo.szHost[strlen(dbHost)] = '\0';
    strncpy(dbInfo.szUser, dbUser, strlen(dbUser));
    dbInfo.szUser[strlen(dbUser)] = '\0';
    strncpy(dbInfo.szPW, dbPwd, strlen(dbPwd));
    dbInfo.szPW[strlen(dbPwd)] = '\0';
    int iLen = snprintf(dbInfo.szDB, GORM_DB_MAX_LEN, TEST_DB, (dbIdx%5)+1);
    dbInfo.szDB[iLen] = '\0';
    dbInfo.uiPort = dbPort;

    m->lock();
    GORM_MySQLAsyncEventTest *mysqlEventList[MYSQL_CONN_NUM];
    MYSQL *pMySQL = nullptr;
    for (int i=0; i<MYSQL_CONN_NUM; i++)
    {
        pMySQL = Connect2MySQL(&dbInfo);
        if (pMySQL == nullptr)
        {
            cout << "connecto to mysql failed." << endl;
            return -1;
        }
        int iMySQLFD = 0;
        GORM_GET_MYSQL_FD(pMySQL, iMySQLFD);
        GORM_MySQLAsyncEventTest *pEvent = new GORM_MySQLAsyncEventTest(pMySQL, iMySQLFD, pEpool);
        mysqlEventList[i] = pEvent;
        pEvent->iFinishNum = iFinishNum;
        pEpool->AddEventRW(pEvent);
    }
    m->unlock();

    for(;;)
    {
        pEpool->EventLoopProcess(5);
        pEpool->ProcAllEvents();
    }
    
    return 0;
}



int GORM_MySQLSDKTest(int argc, char** argv)
{
    if (GORM_OK != GORM_GetOptions(argc, argv))
    {
        cout << "parse args failed." << endl;
        return -1;
    }
    
    srand((int)(time(NULL)));
    atomic<int> finishNum(0);
    mutex m;
    for (int i=0; i<2; i++)
    {
        thread d(GORM_MySQLSDKTestThread, &finishNum, &m, rand());
        d.detach();
    }

    for (int i=0; i<1000*60*60; i++)
    {
        ThreadSleepMilliSeconds(1000);
        cout << finishNum << "    , now:" << GORM_GetNowMS() << endl;
    }
    
    return 0;
}

#endif
