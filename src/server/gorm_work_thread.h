#ifndef _GORM_WORK_THREAD_H__
#define _GORM_WORK_THREAD_H__
#include "gorm_thread_pool.h"
#include "gorm_singleton.h"
#include "gorm_frontend_event.h"
#include "gorm_list.h"
#include "gorm_event.h"
#include "gorm_db_conn_mgr.h"
#include "gorm_object_pool.h"
#include "gorm_mempool.h"
#include "gorm_mysql_request.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_redis.h"
#include "gorm_config.h"
#include "gorm_signal_event.h"

#define GORM_MAX_WORK_THREADS 1024

class GORM_WorkThreadPool;
class GORM_DBConnMgr;
class GORM_SignalEvent;
class GORM_WorkThread : public GORM_Thread
{
public:
    GORM_WorkThread(shared_ptr<GORM_ThreadPool> pPool, string &strThreadName, uint64 ulThreadID, int iInnerIdx);
    virtual ~GORM_WorkThread();

    virtual void Work(mutex *m);
    void Finish();
    // 工作线程接收到前端请求
    int AccepNewRequest(GORM_DBRequest *pRequest);
    virtual void SignalCB();
private:
    // db模块初始化工作，多线程程序，mysql驱动建立连接的时候需要在互斥区里面
    bool DBInit(mutex *m);
    // cache模块初始化
    int CacheInit(GORM_Config *pConfig);
    // 检查
    void Exist();
    int Init(mutex *m, GORM_Config *pConfig);
    // 前端线程通知本线程有新消息
    inline void NotifyNewRequest()
    {
        this->m_pSignalEvent->Single();
    }
    
public:
    // 线程内部使用的变量
    unordered_map<uint64, GORM_Event*>      m_mapFrontEndEvents;    // 客户端的连接
    GORM_DBConnMgr                          m_dbMgr;    // 每个线程单独使用一个数据库连接器
    GORM_ObjectPool<GORM_MySQLRequest, 1024>  m_vRequestParse; // 目前只支持mysql协议,每个线程一个内存池
public:
    // 线程需要和外部交互的变量///////////////////////////////////////////////
    atomic_long             m_lClientNum;       // 线程服务的客户端连接数
    uint64                  m_ulThreadID;       // 本线程id
    ///////////////////////////////////////////////////////////////////////////

    GORM_SSQueue<GORM_DBRequest*, GORM_WORK_REQUEST_QUEUE_LEN> *m_pResponseList;
    int m_iInnerIdx = -1;

    //
    shared_ptr<GORM_Epoll>              m_pEpoll = nullptr;
    shared_ptr<GORM_SignalEvent>    m_pSignalEvent = nullptr;
    int m_iRequestPendingNum = 0;  // 是否有请求的消息没有处理
};

class GORM_WorkThreadPool : public GORM_ThreadPool,
                public GORM_Singleton<GORM_WorkThreadPool>

{
public:
    GORM_WorkThreadPool();
    virtual ~GORM_WorkThreadPool();
    // 回收工作线程
    int RecycleWorkThread(GORM_WorkThread *pThread);
    // 分配请求总入口，将请求分配给后端工作线程
    int PublishRequestToDB(int iTableId, uint32 uiHashValue, GORM_WorkThread *&pWorkThread);
public:
    virtual int CreateThread(int iNum);

    // 所有的工作线程
private:
    shared_ptr<GORM_WorkThread> m_vThreads[1024];
    int                         m_iWorkThreadNum = 0;
    atomic_long                 m_iThreadIDSeed;    // 用于生成线程id
    atomic_int                  m_iTotalThreadNum;
};

#endif
