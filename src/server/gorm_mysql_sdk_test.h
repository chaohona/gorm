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

using namespace std;


MYSQL *Connect2MySQL(GORM_DBInfo *pDbCfg)
{
    MYSQL *pMySQL;
    pMySQL = mysql_init(NULL);
    if (pMySQL == nullptr)
    {
        cout << "mysql_init failed" << endl;
        return nullptr;
    }

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

class GORM_MySQLAsyncEventTest: public GORM_Event
{
public:
    GORM_MySQLAsyncEventTest(MYSQL *pMySQL, int iFD, shared_ptr<GORM_Epoll> pEpoll):
        GORM_Event(iFD, pEpoll), m_pMySQL(pMySQL)
    {
    }
    virtual int Write()
    {
        m_iStatus = mysql_real_query_nonblocking(this->m_pMySQL, m_sql,
                                    (unsigned long)strlen(m_sql));
        if (m_iStatus == NET_ASYNC_NOT_READY)
        {
            return 0;
        }
        else if (m_iStatus == NET_ASYNC_ERROR)
        {
            cout << "send message 2 mysql failed:" << mysql_error(m_pMySQL) << endl;
            this->DelWrite();
            return GORM_ERROR;
        }
        else if (m_iStatus == NET_ASYNC_COMPLETE)
        {
            this->ReadyRead();
        }
        return 0;
    }
    virtual int Read()
    {
        m_iStatus = mysql_store_result_nonblocking(this->m_pMySQL, &m_pReadingMySQLResult);
        if (m_iStatus == NET_ASYNC_NOT_READY)
        {
            return 0;
        }
        else if (m_iStatus == NET_ASYNC_ERROR)
        {
            cout << "get message from mysql failed:" << mysql_error(m_pMySQL) << endl;
            this->DelWrite();
            return GORM_ERROR;
        }
        else if (m_iStatus == NET_ASYNC_COMPLETE)
        {
            *this->iFinishNum += 1;
            this->DelRead();
            this->ReadyWrite();
        }
        return 0;
    }
public:
    MYSQL *m_pMySQL = nullptr;
    char *m_sql = "select * from user_2;";
    int *iFinishNum;
    MYSQL_RES *m_pReadingMySQLResult;
    net_async_status m_iStatus;
};


int GORM_MySQLSDKTest(int argc, char** argv)
{
    shared_ptr<GORM_Epoll> pEpool = make_shared<GORM_Epoll>();
    if (!pEpool->Init(1024))
    {
        cout << "init epool failed." << endl;
        return -1;
    }


    char *dbHost = "127.0.0.1";
    char *dbPwd = "ztgame@123";
    char *dbUser = "root";
    char *dbDatabase = "daobatu";
    int dbPort = 3306; 
    #define MYSQL_CONN_NUM 20
    GORM_DBInfo dbInfo;
    strncpy(dbInfo.szHost, dbHost, strlen(dbHost));
    dbInfo.szHost[strlen(dbHost)] = '\0';
    strncpy(dbInfo.szUser, dbUser, strlen(dbUser));
    dbInfo.szUser[strlen(dbUser)] = '\0';
    strncpy(dbInfo.szPW, dbPwd, strlen(dbPwd));
    dbInfo.szPW[strlen(dbPwd)] = '\0';
    strncpy(dbInfo.szDB, dbDatabase, strlen(dbDatabase));
    dbInfo.szDB[strlen(dbDatabase)] = '\0';
    dbInfo.uiPort = dbPort;

    int iFinishNum = 0;
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
        pEvent->iFinishNum = &iFinishNum;
        pEvent->ReadyWrite();
    }

    int iLastNum = 0;
    for(;;)
    {
        pEpool->EventLoopProcess(5);
        pEpool->ProcAllEvents();
        if (iFinishNum - iLastNum > 1000)
        {
            iLastNum = iFinishNum;
            cout << iFinishNum << "    , time:" << GORM_GetNowMS() << endl;
        }
    }
    
    return 0;
}

#endif
