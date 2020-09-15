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
        if (this->m_iStep == 1)
        {
            return this->Read();
        }
        m_iStatus = mysql_real_query_nonblocking(this->m_pMySQL, m_sql,
                                    (unsigned long)strlen(m_sql));
        if (m_iStatus == NET_ASYNC_NOT_READY)
        {
            return 0;
        }
        else if (m_iStatus == NET_ASYNC_ERROR)
        {
            cout << "send message 2 mysql failed:" << mysql_error(m_pMySQL) << endl;
            return GORM_ERROR;
        }
        else if (m_iStatus == NET_ASYNC_COMPLETE)
        {
            this->m_iStep = 1;
        }
        return 0;
    }
    virtual int Read()
    {
        if (this->m_iStep == 0)
        {
            return this->Write();
        }
        m_iStatus = mysql_store_result_nonblocking(this->m_pMySQL, &m_pReadingMySQLResult);
        if (m_iStatus == NET_ASYNC_NOT_READY)
        {
            return 0;
        }
        else if (m_iStatus == NET_ASYNC_ERROR)
        {
            cout << "get message from mysql failed:" << mysql_error(m_pMySQL) << endl;
            return GORM_ERROR;
        }
        else if (m_iStatus == NET_ASYNC_COMPLETE)
        {
            *this->iFinishNum += 1;
            //cout << *this->iFinishNum << "    , now:" << GORM_GetNowMS() <<endl;
            this->m_iStep = 1;
            mysql_store_result(m_pMySQL);
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
    MYSQL *m_pMySQL = nullptr;
    char *m_sql = "select ptid from user_2;";
    atomic<int> *iFinishNum;
    MYSQL_RES *m_pReadingMySQLResult;
    net_async_status m_iStatus;
    int m_iStep = 0;    // 0为写，1为读
};

int GORM_MySQLSDKTestThread(atomic<int> *iFinishNum, mutex *m)
{
    mysql_thread_init();
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



int GORM_MySQLSDKTest()
{
    atomic<int> finishNum = 0;
    mutex m;
    for (int i=0; i<2; i++)
    {
        thread d(GORM_MySQLSDKTestThread, &finishNum, &m);
        d.detach();
    }

    for (int i=0; i<1000*60*60; i++)
    {
        ThreadSleepMilliSeconds(10);
        cout << finishNum << "    , now:" << GORM_GetNowMS() << endl;
    }
    
    return 0;
}

int GORM_ProtobuffTeset()
{
    for(int i=0; i<1000000; i++)
    {
        GORM_PB_GET_REQ *pReq = new GORM_PB_GET_REQ();
        GORM_PB_REQ_HEADER *pHeader = pReq->mutable_header();
        GORM_PB_SPLIT_INFO *pTableInfo = pHeader->mutable_splittableinfo();
        GORM_PB_TABLE *pTable = pReq->mutable_table();
        GORM_PB_Table_currency *pCurrency = pTable->mutable_currency();
        if (i%1000 == 0)
            cout << i << "    , now:" << GORM_GetNowMS() << endl;
    }
}

#endif
