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
class GORM_MySQLEvent
{
public:
    GORM_MySQLEvent(MYSQL *pMySQL, GORM_DBInfo *pDbCfg, GORM_MySQLConnPool *pPool);
    ~GORM_MySQLEvent();

    int Write();
    int Read();
    int Loop();
    int ConnectSuccessCB();
    // 将新的请求放到发送队列中等待发送给MYSQL
    int SendRequest2DB(GORM_MySQLRequest *pRequest);

    int MySQLSyncQuery(char *szSQL, int iLen);
    int MySQLSyncStoreResult();
    int MySQLSyncFetchRow(MYSQL_ROW &row);
    int MySQLTableInfoUpdate(MYSQL_ROW row, unsigned long *lengths);
private:
    void TryNextRequest();
    GORM_Ret StoreResult();
    GORM_Ret FetchRows();
    char *DBError();
    int DBErrNo();
    void GotResults(int iErrCode = GORM_OK, int iDBErrNo = 0, char *szErrInfo = nullptr);
    void FinishReading();
    void FinishWriting();
    void WriteError(int iErrCode = GORM_OK, int iDBErrNo = 0, char *szErrInfo = nullptr);
    int GetMySQLTableInfo();
    
public:
    friend class GORM_MySQLRequest;
    net_async_status m_iMySQLNetStatus = NET_ASYNC_ERROR;    // 网络状态
    MySQLOptStep     m_iOptStep;                            // 当前event状态机状态
    MYSQL_RES       *m_pReadingMySQLResult = nullptr;        // 从mysql获取的结果
    MYSQL           *m_pMySQL = nullptr;
    GORM_DBInfo     *m_pDbCfg = nullptr;
    GORM_MySQLConnPool  *m_pMySQLConnPool;

    // 需要被发送的SQL消息池子
    shared_ptr<GORM_RingBuffer<GORM_MySQLRequest>> m_pSendingToMySQLRing;
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
    virtual bool Init(GORM_DBInfo *pDbCfg, const mutex *m);
    virtual bool GeneralUrl(GORM_DBInfo *pDbCfg);
    virtual void Loop();
    virtual int SendRequest2DB(GORM_DBRequest *pRequest);

private:
    bool GetMYSQL(GORM_DBInfo *pDbCfg, const    mutex *m, MYSQL *&pMySQL, net_async_status &iConnectStatus);
public:
    GORM_MySQLEvent* m_pEvent = nullptr; // TODO 改成连接池
};

#endif
