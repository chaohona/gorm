#ifndef _GORM_FRONTEND_THREAD_H__
#define _GORM_FRONTEND_THREAD_H__
#include "gorm_thread_pool.h"
#include "gorm_singleton.h"
#include "gorm_config.h"
#include "gorm_event.h"
#include "gorm_frontend_event.h"
#include "gorm_list.h"
#include "gorm_mempool.h"

class GORM_FrontEndThread;
class GORM_ListenEvent : public GORM_Event
{
public:
    GORM_ListenEvent(GORM_FD iFD, shared_ptr<GORM_Epoll>      pEpoll);
    virtual ~GORM_ListenEvent();

public:
    virtual int Write();
    virtual int Read();
    virtual int Error();
    virtual int Close();

private:
    int Accept();
    void AcceptClient(GORM_FD iFD);

public:
    GORM_FrontEndThread *pFrontThread;
};

class GORM_FrontEndThread : public GORM_Thread
{
public:
    GORM_FrontEndThread(shared_ptr<GORM_ThreadPool> pPool, string &strThreadName);
    virtual ~GORM_FrontEndThread();

    virtual void Work(mutex *m);

    int AcceptClient(GORM_FD iFD);
private:
    void EventCheck();
    void ResponseProc();
public:
    GORM_FD                         m_iListenFD = 0;    // 监听端口句柄
    shared_ptr<GORM_ListenEvent>    m_pListenEvent;
    shared_ptr<GORM_Epoll>          m_pEpoll;

    unordered_map<uint64, GORM_Event*>  m_mapFrontEndEvents;    // 客户端的连接

    // 响应统一交给前端线程之后，由前端线程自己处理，避免多线程锁问题
    GORM_SyncList<GORM_DBRequest*> m_ResponseList;
};

class GORM_FrontEndThreadPool : public GORM_ThreadPool, 
            public GORM_Singleton<GORM_FrontEndThreadPool>
{
public:
    GORM_FrontEndThreadPool();
    virtual ~GORM_FrontEndThreadPool();
public:
    virtual int CreateThread(int iNum);
};


#endif
