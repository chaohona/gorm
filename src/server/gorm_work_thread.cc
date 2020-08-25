#include "gorm_work_thread.h"
#include "gorm_sys_inc.h"
#include "gorm_log.h"
#include "gorm_db_conn_mgr.h"
#include "gorm_frontend_event.h"
#include "gorm_mempool.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_config.h"

using namespace gorm;
GORM_WorkThread::GORM_WorkThread(shared_ptr<GORM_ThreadPool> pPool, string &strThreadName, uint64 ulThreadID) : GORM_Thread(pPool, strThreadName),
    m_lClientNum(0), m_ulThreadID(ulThreadID), m_bWaitReq(false), m_listNeedAccess(1024)
{
}

GORM_WorkThread::~GORM_WorkThread()
{
    this->m_pMemPool = nullptr;
    this->Exist();
}

void GORM_WorkThread::Exist()
{
    GORM_LOGI("work thread exist, id:%d", this->m_threadId);
    try
    {
        dynamic_pointer_cast<GORM_WorkThreadPool>(this->m_pPool)->RecycleWorkThread(this);
        this->m_mapFrontEndEvents.clear();
    }
    catch(exception &e)
    {
        GORM_LOGE("work thread:%d exist got exception:%s", this->m_threadId, e.what());
    }
}

// 1、建立和后端数据库的连接
// 2、获取前端过来的连接
// 3、循环工作
void GORM_WorkThread::Work(mutex *m)
{
    try
    {
        //
        this->m_pMemPool= make_shared<GORM_MemPool>();
        if (GORM_OK != this->Init(m, GORM_Config::Instance()))
        {
            GORM_LOGE("database work thread init failed.");
            exit(-1);
            return;
        }
        // 循环处理
        for(;;)
        {
            // 从DB接收消息，回复客户端
            // 接收客户端消息
            // 接收收到的客户端
            if (this->m_dbMgr.RequestNum() == 0) // 休眠
            {
                std::unique_lock<std::mutex> locker(this->m_mutexRequestCondition);
                if (this->m_dbMgr.RequestNum() == 0)
                {
                    m_bWaitReq = true;
                    GORM_LOGD("work thread wait for request");
                    this->m_conditionRequest.wait(this->m_mutexRequestCondition);
                    m_bWaitReq = false;
                }
                GORM_LOGD("work thread got request, begin to process");
            }
            this->RequestPreProc();
            //if (this->m_dbMgr.RequestNum() > 0)
                this->m_dbMgr.Loop();
        }
    }
    catch(exception &e)
    {
        this->Exist();
        GORM_LOGE("work thread got exception:%s", e.what());
    }
}

// 预处理请求，如从缓存获取缓存数据
// 此处的请求是不需要顺序的,先获取到缓存的则直接返回
int GORM_WorkThread::RequestPreProc()
{
    list<GORM_DBRequest*> listRequest;
    this->m_RequestList.Take(listRequest);
    bool bGotResult = false;
    int iRet = GORM_OK;
    for(GORM_DBRequest *pReq : listRequest)
    {
        //pReq->pCacheOpt = this->m_pCacheOpt;
        // 判断是否在缓存中操作成功，如果需要则继续操作数据库
        bGotResult = false;
        /*iRet = pReq->AddTableToRsp(); // TODO 在需要的时候再做
        if (GORM_OK != iRet)
        {
            pReq->GetResult(iRet);
            continue;
        }*/
        iRet = pReq->SetNowReqProcTable();
        if (GORM_OK != iRet)
        {
            pReq->GetResult(iRet);
            continue;
        }
        /*if (this->m_pCacheOpt != nullptr)
        {
            iRet = this->m_pCacheOpt->GetResultFromCache(pReq, bGotResult);
            if (GORM_OK != iRet)
            {
                pReq->GetResult(iRet);
                continue;
            }
            if (bGotResult)
            {
                pReq->GetResult();
                continue;
            }
        }*/

        // 根据路由，获取到响应的mysql句柄，传给mysql
        int iRet = this->m_dbMgr.GetDBPool(pReq->iReqTableId, pReq->uiHashValue, pReq->pDbPool);
        if (iRet != GORM_OK)
        {
            pReq->GetResult(iRet);
            GORM_LOGE("get db pool failed.");
            continue;
        }
        iRet = pReq->pDbPool->SendRequest2DB(pReq);
        if (iRet != GORM_OK)
        {
            pReq->GetResult(iRet);
            GORM_LOGE("send request to db opt failed.");
            continue;
        }
    }
    
    return GORM_OK;
}

bool GORM_WorkThread::DBInit(mutex *m)
{
    if (GORM_OK != this->m_dbMgr.Init(this, m))
        return false;
    return true;
}

void GORM_WorkThread::NotifyNewRequest()
{
    if (m_bWaitReq)
        this->m_conditionRequest.notify_one();
}

int GORM_WorkThread::AccepNewRequest(GORM_DBRequest *pRequest)
{
    this->m_RequestList.Put(pRequest);
    // 向工作线程发送通知
    this->NotifyNewRequest();
    return GORM_OK;
}

// 清除已经关闭的客户端连接
// 将新的连接加入epoll触发器
void GORM_WorkThread::EventCheck()
{
    try
    {
        GORM_Event *pEvent;
        for(auto itr : this->m_mapFrontEndEvents)
        {
            pEvent = itr.second;
            if (pEvent->IsClosed())
            {
                this->m_mapFrontEndEvents.erase(pEvent->m_uiEventId);
                delete pEvent;
            }
        }

    }
    catch(exception &e)
    {
        GORM_LOGE("event check got exception:%s", e.what());
    }
}

void GORM_WorkThread::Finish()
{
    
}

int GORM_WorkThread::Init(mutex *m, GORM_Config *pConfig)
{
    // 建立和数据库的连接
    if (!this->DBInit(m))
    {
        GORM_LOGE("database init failed, exit gorm server.");
        return GORM_ERROR;
    }

    if (GORM_OK != CacheInit(pConfig))
    {
        GORM_LOGE("init cache failed.");
        return GORM_ERROR;
    }
    return GORM_OK;
}

// 暂不支持缓存
int GORM_WorkThread::CacheInit(GORM_Config *pConfig)
{
    return GORM_OK;
    if (0 == GORM_CACHE_SWITCH)
    {
        return GORM_OK;
    }
    if (pConfig->m_iCacheType == GORM_CacheType_None)
    {
        return GORM_OK;
    }
    if (pConfig->m_iCacheType == GORM_CacheType_Redis)
    {
        //this->m_pCacheOpt = new GORM_Redis();
        GORM_LOGI("cache type is redis.");
    }
    else
    {
        GORM_LOGE("invalid catche type:%d", pConfig->m_iCacheType);
        return GORM_ERROR;
    }
    /*if (GORM_OK != this->m_pCacheOpt->Init(pConfig))
    {
        GORM_LOGE("cache init failed.");
        return GORM_ERROR;
    }*/
    GORM_LOGI("work thread cache init success.");

    return GORM_OK;
}

GORM_WorkThreadPool::GORM_WorkThreadPool() : GORM_ThreadPool(string("work-thread")),
    m_iThreadIDSeed(0)
{
}

GORM_WorkThreadPool::~GORM_WorkThreadPool()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    this->m_mapThreadGroup.clear();
}

// 回收工作线程
int GORM_WorkThreadPool::RecycleWorkThread(GORM_WorkThread *pThread)
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    this->m_mapThreadGroup.erase(pThread->m_threadId);
    return GORM_OK;
}

void GORM_WorkThreadPool::WorkThreadUpdateLoad(GORM_WorkThread *pThread, uint64 ulLoad)
{
}

int GORM_WorkThreadPool::PublishRequestToDB(int iTableId, uint32 uiHashValue, GORM_WorkThread *&pWorkThread)
{
    if (this->m_iWorkThreadNum == 0)
        return GORM_NO_DB;

    int iIdx = uiHashValue % this->m_iWorkThreadNum;
    shared_ptr<GORM_WorkThread> pThread = this->m_vThreads[iIdx];
    pWorkThread = pThread.get();
        
    return GORM_OK;
}

int GORM_WorkThreadPool::CreateThread(int iNum)
{
    try
    {
        for (int i=0; i<iNum; i++)
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            ++this->m_iThreadIDSeed;
            shared_ptr<GORM_WorkThread> pThread = make_shared<GORM_WorkThread>(GORM_WorkThreadPool::SharedPtr(), this->m_strThreadType, this->m_iThreadIDSeed);
            this->StartWork(pThread);
            m_vThreads[i] = pThread;
        }
        this->m_iWorkThreadNum = iNum;
    }
    catch(exception &e)
    {
        GORM_LOGE("create frontend thread got exception:%s", e.what());
        return GORM_ERROR;
    }
    
    return GORM_OK;
}

