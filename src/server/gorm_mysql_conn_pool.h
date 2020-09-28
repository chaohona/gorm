#ifndef _GORM_MYSQL_CONN_POOL_H__
#define _GORM_MYSQL_CONN_POOL_H__

#include "gorm_db_conn_pool.h"
#include "gorm_db_config.h"
#include "gorm_sys_inc.h"
#include "gorm_event.h"
#include "gorm_ringbuffer.h"
#include "gorm_db_request.h"
#include "gorm_mysql_request.h"
#include "gorm_tables.h"


#define GORM_GET_MYSQL_FD(MYSQL, FD)\
FD=MYSQL->net.vio->mysql_socket.fd

enum MySQLOptStep
{
    MYSQL_OPT_CONNECTING,       // 正在和后端建立连接
    MYSQL_OPT_WAITING_REQ,      // 等待下一个请求
    MYSQL_SENDING_REQ,          // 正在向后端发送数据
    MYSQL_STORE_RESULT,         // 执行mysql的store_result操作
    MYSQL_FETCH_ROW,            // 执行fetch_row操作
    MYSQL_READ_FINISH,          // 读取数据结束--接下来应该将数据发送给客户端
};
class GORM_MySQLConnPool;
// 和mysql的操作不会同时有读和写
#define MYSQL_REQUEST_POOL_SIZE 1024*8
class GORM_MySQLEvent : public GORM_Event
{
public:
    GORM_MySQLEvent(shared_ptr<GORM_Epoll> &pEpoll, MYSQL *pMySQL, int iFD, GORM_DBInfo *pDbCfg,  GORM_MySQLConnPool *pPool);
    ~GORM_MySQLEvent();

    int Loop();
    virtual int Write();
    virtual int Read();
    int ConnectSuccessCB();
    // 将新的请求放到发送队列中等待发送给MYSQL
    int SendRequest2DB(GORM_MySQLRequest *pRequest)
    {
        if (!this->m_pSendingToMySQLRing->AddData(pRequest))
        {
            if (this->m_pSendingToMySQLRing->Full())
                return GORM_RING_FULL;
            GORM_LOGE("add request to sending list failed.");
            return GORM_ERROR;
        }

        return this->AddToEpoll();
    }
    inline int AddToEpoll()
    {
        if (this->m_iMask != GORM_EVENT_NONE)
            return GORM_OK;
        return this->ReadyRW();
    }

    int MySQLSyncQuery(char *szSQL, int iLen);
    int MySQLSyncStoreResult();
    int MySQLSyncFetchRow(MYSQL_ROW &row);
    int MySQLTableInfoUpdate(MYSQL_ROW row, unsigned long *lengths);
private:
    int SendMsg2MySQL();
    int ReadFromMySQL();
    GORM_Ret StoreResult();
    GORM_Ret FetchRows();   // 只负责取结果，取结果过程中有错误，交给调用函数处理
    char *DBError();
    int DBErrNo();
    void GotResults(int iErrCode = GORM_OK, int iDBErrNo = 0, char *szErrInfo = nullptr);
    void FinishReading();
    void FinishWriting();
    void WriteError(int iErrCode = GORM_OK, int iDBErrNo = 0, char *szErrInfo = nullptr);
    int GetMySQLTableInfo();
    int Connecting();
    
public:
    friend class GORM_MySQLRequest;
    net_async_status    m_iMySQLNetStatus = NET_ASYNC_ERROR;    // 网络状态
    MySQLOptStep        m_iOptStep;                            // 当前event状态机状态
    MYSQL_RES           *m_pReadingMySQLResult = nullptr;        // 从mysql获取的结果
    MYSQL               *m_pMySQL = nullptr;
    int                 m_iMySQLFD = 0;
    GORM_DBInfo         *m_pDbCfg = nullptr;
    GORM_MySQLConnPool  *m_pMySQLConnPool;

    // 需要被发送的SQL消息池子
    shared_ptr<GORM_RingBuffer<GORM_MySQLRequest, MYSQL_REQUEST_POOL_SIZE>> m_pSendingToMySQLRing;
    GORM_MySQLRequest  *m_pSendingRequest = nullptr;   // 出去发送状态的请求
    GORM_MySQLRequest  *m_pReadingRequest = nullptr;   // 处于接收状态的请求
    int                 m_iReadingRows = 0;     // 一共有几行数据需要被接收
    int                 m_iReadedRows = 0;      // 接受过几行数据了
    string              m_strDBName;    // 数据库名字

    unordered_map<string, vector<string>> m_mapTablesColumnOrder; // 对应的库的表的信息
    unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> m_mapTablesColumnInfo; // 对应的库的表的信息
};

// 管理和一个mysql的通信
class GORM_MySQLConnPool : public GORM_DBConnPool
{
public:
    GORM_MySQLConnPool(int iMaxPoolSize);
    virtual ~GORM_MySQLConnPool();

    // mysql初始化函数不是线程安全的,mutex必须为全局锁
    virtual bool Init(shared_ptr<GORM_Epoll> &pEpoll, GORM_DBInfo *pDbCfg, const mutex *m);
    virtual bool GeneralUrl(GORM_DBInfo *pDbCfg);
    virtual void Loop();
    virtual int SendRequest2DB(GORM_DBRequest *pRequest)
    {
        GORM_MySQLEvent *pEvent = this->m_EventList[pRequest->uiHashValue%this->m_iMaxPoolSize];
        pRequest->pDbEvent = pEvent;
        return pEvent->SendRequest2DB(dynamic_cast<GORM_MySQLRequest*>(pRequest));
        //return this->m_pEvent->SendRequest2DB(dynamic_cast<GORM_MySQLRequest*>(pRequest));
    }

private:
    bool GetMYSQL(GORM_DBInfo *pDbCfg, const    mutex *m, MYSQL *&pMySQL, net_async_status &iConnectStatus);
    bool ConnectToMySQL(shared_ptr<GORM_Epoll> &pEpoll, GORM_MySQLEvent *&pEvent, GORM_DBInfo *pDbCfg, const mutex *m);
public:
    GORM_MySQLEvent *m_pEvent = nullptr; // TODO 改成连接池
    GORM_MySQLEvent *m_EventList[GOMR_MAX_CONNECT_NUM_PER_THREAD];
    
};

#endif
