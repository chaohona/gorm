#ifndef _GORM_EVENT_H__
#define _GORM_EVENT_H__

#include "gorm_socket.h"
#include "gorm_inc.h"
#include "gorm_sys_inc.h"
#include "gorm_log.h"

#ifndef _WIN32
#include <sys/epoll.h>
#endif

enum GORM_CONNECT_STATUS{
    GORM_CONNECT_INIT,
    GORM_CONNECT_CONNECTING,
    GORM_CONNECT_CONNECTED,
    GORM_CONNECT_CLOSED,
    GORM_CONNECT_FORCE_CLOSED,
};

enum GORM_EVENT_TYPE{
  GORM_LISTEN_EVENT,
  GORM_CLIENT_EVENT,
  GORM_TIMER_EVENT,
};

#define MAX_EVENT_POOLS 2048


#define GORM_EVENT_NONE     0       /* No events registered. */
#define GORM_EVENT_READABLE 1   /* Fire when descriptor is readable. */
#define GORM_EVENT_WRITABLE 2   /* Fire when descriptor is writable. */
#define GORM_EVENT_RW       GORM_EVENT_READABLE | GORM_EVENT_WRITABLE
#define GORM_EVENT_ERROR    4


#define GORM_EVENT_CONNECT_OK(event)\
(event->m_Status == GORM_CONNECT_CONNECTING || event->m_Status == GORM_CONNECT_CONNECTED)

class GORM_Epoll;
class GORM_Event
{
public:
    GORM_Event(GORM_FD iFD, shared_ptr<GORM_Epoll>    pEpoll=nullptr);
    virtual ~GORM_Event();

public:
    virtual int AddToTimer();
    virtual int Write();
    virtual int Read();
    virtual int Error();
    virtual int Close();
    int ReadyWrite();
    int DelWrite();
    int ReadyRead();
    int DelRead();
    int ReadyRW();
    int DelRW();
#ifndef _WIN32
    int DoSendv(iovec *iov, int iovcnt);
#endif
    inline int ConnectCheck();
    bool ConnectOK();
    bool IsClosed();
    void SetRemoveAddr();
    void SetFD(GORM_FD iFD);
public:
    uint16                  m_uiPort = 0;           // 端口号
    char                    m_szIP[NET_IP_STR_LEN]; // ip地址
    char                    m_szPerrAddr[MAX_URL_LEN];               // ip:port，主要用于日志输出方便
    static uint64           global_event_id;
    uint32                  m_uiEventId = 0;        // 本事件id
    GORM_FD                 m_iFD = 0;              // 事件句柄
    GORM_CONNECT_STATUS     m_Status = GORM_CONNECT_INIT;
    int                     m_iMask = GORM_EVENT_NONE;            // 被触发的事件类型
    shared_ptr<GORM_Epoll>  m_pEpoll = nullptr;
};

class GORM_Epoll : public GORM_Noncopyable
{
public:
    GORM_Epoll();
    ~GORM_Epoll();
    
    bool Init(int iEventNum);
    inline int AddEventRead(GORM_Event *pEvent) 
    {
        pEvent->m_Status = GORM_CONNECT_CONNECTED;
        return this->AddEvent(pEvent, GORM_EVENT_READABLE);
    }
    inline int AddEventWrite(GORM_Event *pEvent)
    {
        return this->AddEvent(pEvent, GORM_EVENT_WRITABLE);
    }
    inline int DelEventRead(GORM_Event *pEvent)
    {
        return this->DelEvent(pEvent, GORM_EVENT_READABLE);
    }
    inline int DelEventWrite(GORM_Event *pEvent)
    {
        return this->DelEvent(pEvent, GORM_EVENT_WRITABLE);
    }
    inline int AddEventRW(GORM_Event *pEvent)
    {
        return this->AddEvent(pEvent, GORM_EVENT_RW);
    }
    inline int DelEventRW(GORM_Event *pEvent)
    {
        return this->DelEvent(pEvent, GORM_EVENT_READABLE|GORM_EVENT_WRITABLE);
    }
    inline int EventLoopProcess(uint64 ulMS)
    {
        int retval = 0;
#ifdef _WIN32
        memcpy(&this->_rfds,&this->rfds,sizeof(fd_set));
        memcpy(&this->_wfds,&this->wfds,sizeof(fd_set));

        retval = select(MAX_EVENT_POOLS+1,
                    &this->_rfds,&this->_wfds,nullptr,nullptr);
    	return 0;
#else
        this->m_iNumEventsActive = 0;
        if (ulMS < 20)
        {
            ulMS = 20;
        }
        retval = epoll_wait(this->m_iEpFd,this->m_aEpollEvents,this->m_iEventNum,ulMS);
        if (retval > 0) {
            this->m_iNumEventsActive = retval;
        }
        else if (retval < 0)
        {
            if (errno == EINTR || errno == EAGAIN)
            {
                return GORM_OK;
            }
            GORM_LOGE("epoll_wait failed:%d,%s", errno, strerror(errno));
            return GORM_ERROR;
        }
        return GORM_OK;
#endif
    }
    inline int ProcAllEvents()
    {
#ifdef _WIN32
        GORM_Event *pEvent = nullptr;
        for (int i=0; i<MAX_EVENT_POOLS; i++)
        {
            pEvent = m_vEvents[i];
            if (pEvent == nullptr || pEvent->m_iFD <= 0)
                continue;
            if (pEvent->m_iMask & GORM_EVENT_READABLE && FD_ISSET(pEvent->m_iFD, &this->_rfds))
            {
                pEvent->Read();
            }
            if (pEvent->m_iMask & GORM_EVENT_WRITABLE && FD_ISSET(pEvent->m_iFD, &this->_wfds))
            {
                pEvent->Write();
            }
        }
    	return GORM_OK;
#else
        int j;
        int iRet = 0;
        GORM_Event *pEvent = nullptr;
        epoll_event *e;
        for (j = 0; j < this->m_iNumEventsActive; j++) 
        {
            e = this->m_aEpollEvents+j;
            pEvent = (GORM_Event*)e->data.ptr;        
            if ((e->events&EPOLLOUT) && GORM_EVENT_CONNECT_OK(pEvent))
            {
                pEvent->Write();
            }
            if ((e->events&EPOLLIN) && GORM_EVENT_CONNECT_OK(pEvent))
            {
                pEvent->Read();
            }
            if ((e->events & EPOLLERR) && GORM_EVENT_CONNECT_OK(pEvent))
            {
                pEvent->Error();
            }
        }

        return GORM_OK;
#endif
    }
    inline int DelEvent(int iFD)
    {
#ifdef _WIN32
        FD_CLR(iFD,&this->rfds);
        FD_CLR(iFD,&this->wfds);
        return 0;
#else
        struct epoll_event ee = {0};
        epoll_ctl(this->m_iEpFd,EPOLL_CTL_DEL,iFD,&ee);
        //m_mapNetEvents.erase(iFD);
        return GORM_OK;
#endif
    }

private:
    // 根据iMask增加触发
    inline int AddEvent(GORM_Event *pEvent, int iMask)
    {
#ifdef _WIN32
        pEvent->m_iMask |= iMask;
        // 水平触发
        if (pEvent->m_iMask & GORM_EVENT_READABLE) {
            FD_SET(pEvent->m_iFD,&this->rfds);
        }
        if (pEvent->m_iMask & GORM_EVENT_WRITABLE) {
            FD_SET(pEvent->m_iFD,&this->wfds);
        }
    	return 0;
#else
        if (pEvent->m_iFD<=0)
        {
            return GORM_OK;
        }

        epoll_event ee = {0};

        /*auto existEvent = this->GetExistEvent(pEvent->m_iFD);
        if (existEvent == nullptr)
        {
            existEvent = this->SetEvent(pEvent);
        }*/
        int op = pEvent->m_iMask == GORM_EVENT_NONE ? EPOLL_CTL_ADD : EPOLL_CTL_MOD;

        pEvent->m_iMask |= iMask;
        // 水平触发
        if (pEvent->m_iMask & GORM_EVENT_READABLE) {
            ee.events |= (uint32_t)(EPOLLIN);
        }
        if (pEvent->m_iMask & GORM_EVENT_WRITABLE) {
            ee.events |= (uint32_t)(EPOLLIN | EPOLLOUT);
        }
        //ee.data.fd = pEvent->m_iFD;
        ee.data.ptr = pEvent;
        return epoll_ctl(this->m_iEpFd, op, pEvent->m_iFD, &ee);
#endif
    }
    // 根据iMask删除触发
    inline int DelEvent(GORM_Event *pEvent, int iMask)
    {
#ifdef _WIN32
        pEvent->m_iMask = pEvent->m_iMask & (~iMask);
        // 水平触发
        if (iMask & GORM_EVENT_READABLE) {
            FD_CLR(pEvent->m_iFD,&this->rfds);
        }
        if (iMask & GORM_EVENT_WRITABLE) {
            FD_CLR(pEvent->m_iFD,&this->wfds);
        }

    	return 0;
#else
        if (pEvent->m_iFD<=0)
        {
            return GORM_OK;
        }
        //auto existEvent = this->GetExistEvent(pEvent->m_iFD);
        struct epoll_event ee = {0}; /* avoid valgrind warning */
        pEvent->m_iMask = pEvent->m_iMask & (~iMask);

        ee.events = 0;
        if (pEvent->m_iMask & GORM_EVENT_READABLE) ee.events |= EPOLLIN;
        if (pEvent->m_iMask & GORM_EVENT_WRITABLE) ee.events |= EPOLLOUT;
        //ee.data.fd = pEvent->m_iFD;
        ee.data.ptr = pEvent;
        if (pEvent->m_iMask != GORM_EVENT_NONE) {
            epoll_ctl(this->m_iEpFd,EPOLL_CTL_MOD,pEvent->m_iFD,&ee);
        } else {
            /* Note, Kernel < 2.6.9 requires a non null event pointer even for
             * EPOLL_CTL_DEL. */
            epoll_ctl(this->m_iEpFd,EPOLL_CTL_DEL,pEvent->m_iFD,&ee);
        }
        return GORM_OK;
#endif
    }

public:
    int         m_iEpFd = 0;            // epoll句柄
    #ifndef _WIN32
    epoll_event *m_aEpollEvents;        // 接收系统的事件数据
    #endif
    int         m_iEventNum = 0;        // epoll被触发事件缓存数组大小m_aEpollEvents数组大小
    int         m_iNumEventsActive;     // 实际被触发的事件的个数

    #ifdef _WIN32   // select 模型
    GORM_Event *m_vEvents[MAX_EVENT_POOLS];
    fd_set rfds, wfds;
    /* We need to have a copy of the fd sets as it's not safe to reuse
     * FD sets after select(). */
    fd_set _rfds, _wfds;
    #endif
};


#endif

