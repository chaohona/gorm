#include "gorm_frontend_thread.h"
#include "gorm_sys_inc.h"
#include "gorm_event.h"
#include "gorm_socket.h"
#include "gorm_log.h"
#include "gorm_work_thread.h"
#include "gorm_define.h"
#include "gorm_config.h"

GORM_ListenEvent::GORM_ListenEvent(GORM_FD iFD, shared_ptr<GORM_Epoll>      pEpoll) : GORM_Event(iFD, pEpoll)
{
}

GORM_ListenEvent::~GORM_ListenEvent()
{
}

int GORM_ListenEvent::Write()
{
    return GORM_OK;
}

int GORM_ListenEvent::Read()
{
    int iStatus;
    int iMaxTry = 10; // 每次最多同时接收5个连接
    while(iMaxTry-- > 0)
    {
        iStatus = this->Accept();
        if (iStatus != GORM_OK)
        {
            return iStatus;
        }
    };

    return GORM_OK;
}

int GORM_ListenEvent::Accept()
{
        // 获取到客户端的连接，然后转给后端工作线程
    sockaddr sa;
    socklen_t salen = sizeof(sa);

    int fd = -1;
    for(;;)
    {
        fd = accept(this->m_iFD, &sa, &salen);
        if (fd < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else if ( errno == EAGAIN || errno == EWOULDBLOCK || errno == ECONNABORTED)
            {
                return GORM_EAGAIN;
            }
            else
            {
                GORM_LOGE("accept err:%d, errmsg:%s", errno, strerror(errno));
                return GORM_ERROR;
            }
        }
        this->AcceptClient(fd);
        break;
    }

    return GORM_OK;
}

void GORM_ListenEvent::AcceptClient(GORM_FD iFD)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    char ipAddr[MAX_URL_LEN];//保存点分十进制的地址
    if(getpeername(iFD, (struct sockaddr*)&addr, &addrlen) == -1)
    {
        GORM_LOGE("discovery client information failed, fd=%d, errno=%d, errinfo:%s", iFD, errno, strerror(errno));        
        return;
    }
    GORM_LOGI("got new access from client %s:%d, fd:%d", 
        inet_ntop(AF_INET, &addr.sin_addr, ipAddr, sizeof(ipAddr)), ntohs(addr.sin_port),  iFD);
    if (GORM_OK != GORM_Socket::SetNonBlocking(iFD))
    {
        GORM_LOGE("set nonblock failed:%d", iFD);
        return;
    }
    if (GORM_OK != GORM_Socket::SetTcpNoDelay(iFD))
    {
        GORM_LOGE("set tcpnodelay failed:%d", iFD);
        return;
    }
    if (GORM_OK != GORM_Socket::SetReuseAddr(iFD))
    {
        GORM_LOGE("set reuseraddr failed:%d", iFD);
        return;
    }
    if (GORM_OK != GORM_Socket::SetLinger(iFD, 0))
    {
        GORM_LOGE("set SetLinger failed:%d", iFD);
        return;
    }
    if (GORM_OK != GORM_Socket::SetTcpKeepAlive(iFD))
    {
        GORM_LOGE("set SetLinger failed:%d", iFD);
        return;
    }

    if (GORM_OK != this->pFrontThread->AcceptClient(iFD))
    {
        close(iFD);
        GORM_LOGE("publish client to work thread failed, fd:%d", iFD);
        return;
    }

    return;
}

int GORM_ListenEvent::Error()
{
    return GORM_OK;
}

int GORM_ListenEvent::Close()
{
    return GORM_OK;
}

GORM_FrontEndThread::GORM_FrontEndThread(shared_ptr<GORM_ThreadPool> pPool, string &strThreadName) : GORM_Thread(pPool, strThreadName),
    m_pListenEvent(nullptr), m_pEpoll(nullptr)
{
    m_pResponseList = new GORM_SSQueue<GORM_DBRequest*, GORM_FRONT_REQUEST_QUEUE_LEN>[GORM_MAX_WORK_THREAD_NUM];
    this->m_iWorkThreadNum = GORM_Config::Instance()->m_iWorkThreadNum;
}

GORM_FrontEndThread::~GORM_FrontEndThread()
{
    if (this->m_pResponseList != nullptr)
        delete []this->m_pResponseList;
    this->m_pListenEvent = nullptr;
    this->m_pEpoll = nullptr;
    if (this->m_iListenFD > 0)
    {
        close(this->m_iListenFD);
        this->m_iListenFD = 0;
    }
}

int GORM_FrontEndThread::AcceptClient(GORM_FD iFD)
{
    GORM_LOGD("fornt thread got new client:%d", iFD);
    GORM_FrontEndEvent *pEvent = new GORM_FrontEndEvent(iFD, this->m_pEpoll, this);
    pEvent->SetMemPool(this->m_pMemPool);
    pEvent->m_workMode = GORM_Config::Instance()->m_workMode;
    this->m_pEpoll->AddEventRead(pEvent);
    this->m_mapFrontEndEvents[pEvent->m_uiEventId] = pEvent;
    return GORM_OK;
}

// 客户端检查
void GORM_FrontEndThread::EventCheck()
{
    try
    {
        GORM_Event *pEvent;
        auto itr = this->m_mapFrontEndEvents.begin();
        while(itr != this->m_mapFrontEndEvents.end())
        {
            pEvent = itr->second;
            if (pEvent == nullptr)
            {
                itr = this->m_mapFrontEndEvents.erase(itr);
                continue;
            }
            else if (pEvent->IsClosed())
            {
                this->m_pEpoll->DelEvent(pEvent->m_iFD);
                itr = this->m_mapFrontEndEvents.erase(itr);
                //
                delete pEvent;
                continue;
            }
            else
                itr++;
        }
    }
    catch(exception &e)
    {
        GORM_LOGE("event check got exception:%s", e.what());
    }
}

void GORM_FrontEndThread::SignalCB()
{
    GORM_SSQueue<GORM_DBRequest*, GORM_FRONT_REQUEST_QUEUE_LEN> *pQueue = nullptr;
    for(int i=0; i<this->m_iWorkThreadNum; i++)
    {
        pQueue = &this->m_pResponseList[i];
        if (pQueue->m_nowNum == 0)
            continue;
        int64 leftNum = 0;
        GORM_DBRequest* pReq;
        do
        {
            if (!pQueue->Take(pReq, leftNum))
                break;
            unique_lock<mutex> locker(pReq->m_Mutex);
            pReq->ResetMemPool(this->m_pMemPool);
            // TODO 回收request
            if (pReq->pFrontendEvent == nullptr)
            {
                pReq->Release();
            }
            else 
            {
                GORM_FrontEndEvent *pEvent = dynamic_cast<GORM_FrontEndEvent*>(pReq->pFrontendEvent);
                if (pEvent->m_workMode == GORM_WORK_MODE_SERIAL)
                {
                }
                else
                {
                    pEvent->m_pRequestRing->AddData(pReq);
                    pEvent->m_requestMap.erase(pReq->uiReqID);
                }
                pReq->pFrontendEvent->ReadyWrite();
                
                if (pReq->iWaitDone == 1)
                    pReq->pFrontendEvent->ReadyWrite();
                else    // 针对批量请求，再接着发送下一个请求
                {
                    GORM_FrontEndEvent *pEvent = dynamic_cast<GORM_FrontEndEvent*>(pReq->pFrontendEvent);
                    if (pEvent == nullptr)
                    {
                        pReq->pFrontendEvent->ReadyWrite();
                        continue;
                    }
                    // 此处有req锁
                    pEvent->SendMsgToWorkThread(pReq);
                }
            }
        }while (leftNum > 0);
        
    }
    
    /*if (this->m_ResponseList.Empty())
        return;
    list<GORM_DBRequest*> requestList;
    this->m_ResponseList.Take(requestList);
    for (GORM_DBRequest *pReq : requestList)
    {
        pReq->ResetMemPool(this->m_pMemPool);
        // TODO 回收request
        if (pReq->pFrontendEvent == nullptr)
        {
            pReq->Release();
        }
        else 
        {
            if (pReq->iWaitDone == 1)
                pReq->pFrontendEvent->ReadyWrite();
            else    // 针对批量请求，再接着发送下一个请求
            {
                GORM_FrontEndEvent *pEvent = dynamic_cast<GORM_FrontEndEvent*>(pReq->pFrontendEvent);
                if (pEvent == nullptr)
                {
                    pReq->pFrontendEvent->ReadyWrite();
                    continue;
                }
                pEvent->SendMsgToWorkThread(pReq);
            }
        }
    }*/
}

void GORM_FrontEndThread::Work(mutex *m)
{
    // 1.创建epoll
    this->m_pEpoll = make_shared<GORM_Epoll>();
    if (!this->m_pEpoll->Init(MAX_EVENT_POOLS))
    {
        GORM_LOGE("epoll init failed.");
        return;
    }
    if (GORM_OK != this->InitTransferEvent())
    {
        GORM_LOGE("init transfer event failed.");
        return;
    }

    shared_ptr<GORM_Config> pConfig = GORM_Config::SharedPtr();
    // 2.启动监听服务
    this->m_iListenFD = GORM_Socket::CreateAndListen(pConfig->m_strListenIP.c_str(), pConfig->m_usListenPort);
    if (this->m_iListenFD <= 0)
    {
        GORM_LOGE("create listen socket failed, gorm server will exit, errno:%d, errmsg:%s", errno, strerror(errno));
        exit(0);
        return;
    }
    this->m_pListenEvent = make_shared<GORM_ListenEvent>(this->m_iListenFD, this->m_pEpoll);
    this->m_pListenEvent->pFrontThread = this;
    this->m_pEpoll->AddEventRead(this->m_pListenEvent.get());
    // 3.循环处理客户端连接
    for(;;)
    {
        this->m_pEpoll->EventLoopProcess(5);
        this->m_pEpoll->ProcAllEvents();
        this->EventCheck();
    }
}

int GORM_FrontEndThread::InitTransferEvent()
{
    this->m_pSignalEvent = make_shared<GORM_SignalEvent>(this->m_pEpoll, this);
    if (GORM_OK != this->m_pSignalEvent->Init())
    {
        GORM_LOGE("init transfer event failed.");
        return GORM_ERROR;
    }

    return GORM_OK;
}

void GORM_FrontEndThread::GotResult(GORM_DBRequest *pRequest)
{
    int iIdx = 0;
    if (pRequest->pWorkThread != nullptr)
        iIdx = pRequest->pWorkThread->m_iInnerIdx;
    this->m_pResponseList[iIdx].Put(pRequest);
    this->ResponseSignal();
}

GORM_FrontEndThreadPool::GORM_FrontEndThreadPool() : GORM_ThreadPool(string("frontend-thread"))
{
    
}

GORM_FrontEndThreadPool::~GORM_FrontEndThreadPool()
{
}

int GORM_FrontEndThreadPool::CreateThread(int iNum)
{
    try
    {
        shared_ptr<GORM_FrontEndThread> t = make_shared<GORM_FrontEndThread>(GORM_FrontEndThreadPool::SharedPtr(), this->m_strThreadType);
        this->StartWork(t);
    }
    catch(exception &e)
    {
        GORM_LOGE("create frontend thread got exception:%s", e.what());
        return GORM_ERROR;
    }
    
    return GORM_OK;
}

