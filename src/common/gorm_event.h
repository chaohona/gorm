#ifndef _GORM_EVENT_H__
#define _GORM_EVENT_H__

#include "gorm_socket.h"
#include "gorm_inc.h"
#include "gorm_sys_inc.h"

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
#ifndef _WIN32
    int DoSendv(iovec *iov, int iovcnt);
#endif
    int ConnectCheck();
    bool ConnectOK();
    bool IsClosed();
    void SetRemoveAddr();
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
    int AddEventRead(GORM_Event *pEvent);         // 增加事件读触发
    int AddEventWrite(GORM_Event *pEvent);        // 增加事件写触发
    int DelEventRead(GORM_Event *pEvent);         //  删除事件读触发
    int DelEventWrite(GORM_Event *pEvent);        // 删除事件写触发
    int AddEventRW(GORM_Event *pEvent);           // 增加读写
    int DelEventRW(GORM_Event *pEvent);           // 删除读写

    int EventLoopProcess(uint64 ulMS);
    int ProcAllEvents();
    int DelEvent(int iFD);

private:
    int AddEvent(GORM_Event *pEvent, int iMask);// 根据iMask增加触发
    int DelEvent(GORM_Event *pEvent, int iMask);// 根据iMask删除触发
    GORM_Event* SetEvent(GORM_Event *pEvent);

public:
    int         m_iEpFd = 0;            // epoll句柄
    #ifndef _WIN32
    epoll_event *m_aEpollEvents;        // 接收系统的事件数据
    #endif
    int         m_iEventNum = 0;        // epoll被触发事件缓存数组大小m_aEpollEvents数组大小
    int         m_iNumEventsActive;     // 实际被触发的事件的个数

    #ifdef _WIN32
    GORM_Event *m_vEvents[MAX_EVENT_POOLS];
    fd_set rfds, wfds;
    /* We need to have a copy of the fd sets as it's not safe to reuse
     * FD sets after select(). */
    fd_set _rfds, _wfds;
    #endif
};


#endif

