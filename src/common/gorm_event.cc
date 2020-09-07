#include "gorm_event.h"
#include "gorm_log.h"
#include "gorm_define.h"
#include "gorm_error.h"


uint64 GORM_Event::global_event_id = 0;


GORM_Event::GORM_Event(GORM_FD iFD, shared_ptr<GORM_Epoll>    pEpoll) : m_pEpoll(pEpoll)
{
    this->m_szIP[0] = 0;
    this->m_iFD = iFD;
    this->m_uiEventId = GORM_Event::global_event_id++;
}

GORM_Event::~GORM_Event()
{
}

int GORM_Event::AddToTimer()
{
    return GORM_OK;
}

int GORM_Event::Write()
{
    return 0;
}

int GORM_Event::Read()
{
    return 0;
}

int GORM_Event::Error()
{
    return 0;
}

int GORM_Event::ReadyWrite()
{
    return this->m_pEpoll->AddEventWrite(this);
}

int GORM_Event::DelWrite()
{
    return this->m_pEpoll->DelEventWrite(this);    
}

int GORM_Event::Close()
{
    try
    {
        this->m_Status = GORM_CONNECT_CLOSED;
        if (this->m_iFD > 0)
        {
            if (this->m_pEpoll != nullptr)
            {
                this->m_pEpoll->DelEventRW(this);
            }
#ifdef _WIN32
			closesocket(this->m_iFD);
#else
            close(this->m_iFD);
#endif
            GORM_LOGD("event close %d %s:%d", this->m_iFD, this->m_szIP, this->m_uiPort);
            this->m_iFD = 0;
        }
        this->m_pEpoll = nullptr;
    }
    catch(exception &e)
    {
        GORM_LOGE("close event %d %s:%d got exception:%s", this->m_iFD, this->m_szIP, this->m_uiPort, e.what());
        return GORM_ERROR;
    }
    return GORM_OK;
}

#ifndef _WIN32
int GORM_Event::DoSendv(iovec *iov, int nsend)
{
    if (nsend >512)
    {
        nsend = 512;
    }
    int n;
    for (int i=0; i<2; i++) {
        n = writev(this->m_iFD, iov, nsend);
        if (n > 0) {
            return n;
        }

        if (n == 0) {
            GORM_LOGD("sendv on sd %d returned zero %s:%d", this->m_iFD, this->m_szIP, this->m_uiPort);
            return 0;
        }

        if (errno == EINTR) {
            GORM_LOGD("sendv on sd %d not ready - eintr %s:%d", this->m_iFD, this->m_szIP, this->m_uiPort);
            n = 0;
            continue;
        } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
            GORM_LOGD("sendv on sd %d not ready - eagain %s:%d", this->m_iFD, this->m_szIP, this->m_uiPort);
            return GORM_EAGAIN;
        } else {
            GORM_LOGE("sendv on sd %d failed, num %d, address %s:%d, errmsg %s", this->m_iFD, nsend, this->m_szIP, this->m_uiPort, strerror(errno));
            return GORM_ERROR;
        }
    }

    return GORM_ERROR;
}
#endif

int GORM_Event::ConnectCheck()
{
    if (this->m_Status != GORM_CONNECT_CONNECTING && this->m_Status != GORM_CONNECT_CONNECTED)
    {
        return this->m_Status;
    }
#ifdef _WIN32
    int optval, optlen = sizeof(int);
    getsockopt(this->m_iFD, SOL_SOCKET, SO_ERROR, (char*)&optval, (int*)&optlen);  
#else
    int optval;
    socklen_t optlen = sizeof(int);
    getsockopt(this->m_iFD, SOL_SOCKET, SO_ERROR, &optval, &optlen);  
#endif
    if (optval == 0)
    {
        return GORM_CONNECT_CONNECTED;
    }
    return GORM_CONNECT_CLOSED;
}

bool GORM_Event::ConnectOK()
{
    return this->m_Status == GORM_CONNECT_CONNECTING || this->m_Status == GORM_CONNECT_CONNECTED;
}

bool GORM_Event::IsClosed()
{
    return this->m_Status == GORM_CONNECT_CLOSED || this->m_Status == GORM_CONNECT_FORCE_CLOSED;
}

void GORM_Event::SetFD(GORM_FD iFD)
{
    this->m_iFD = iFD;
}

void GORM_Event::SetRemoveAddr()
{
#ifdef _WIN32
	return;
#else
    struct sockaddr_in      remoteAddr;

    bzero(&remoteAddr, sizeof(struct sockaddr_in));
    socklen_t len = sizeof(struct sockaddr);

    
    getpeername(this->m_iFD, (struct sockaddr *)&remoteAddr, &len);
    int iLen = snprintf(m_szPerrAddr, MAX_URL_LEN, "%s:%d", inet_ntoa(remoteAddr.sin_addr), remoteAddr.sin_port);
    m_szPerrAddr[iLen] = '\0';
#endif
}

GORM_Epoll::GORM_Epoll()
{
    this->m_iEpFd = 0;
}

GORM_Epoll::~GORM_Epoll()
{
#ifdef _WIN32
	WSACleanup();
#else
    try
    {
        if (this->m_aEpollEvents != nullptr)
        {
            delete []this->m_aEpollEvents;
            this->m_aEpollEvents = nullptr;
        }

        close(this->m_iEpFd);
    }
    catch(exception &e)
    {
        GORM_LOGE("destroy epoll got exception:%s", e.what());
    }
#endif
}

bool GORM_Epoll::Init(int iEventNum)
{
#ifdef _WIN32
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
		return false;
    memset(m_vEvents, 0, MAX_EVENT_POOLS*sizeof(GORM_Event*));
    return true;
#else
    try
    {
        this->m_iEventNum = iEventNum;
        if (this->m_iEpFd == 0)
        {
            this->m_iEpFd = epoll_create(this->m_iEventNum);
            if (this->m_iEpFd < 0)
            {
                cout << "create epoll base failed" << strerror(errno) << endl;
                return false;
            }
            this->m_aEpollEvents = new epoll_event[this->m_iEventNum];
        }
        else
        {
            close(this->m_iEpFd);
            this->m_iEpFd = epoll_create(this->m_iEventNum);
            if (this->m_iEpFd < 0)
            {
                cout << "create epoll base failed" << strerror(errno) << endl;
                return false;
            }
        }
    }
    catch(exception &e)
    {
        cout << "init epoll got exception:" << e.what() << endl;
        return false;
    }
    return true;
#endif
}

int GORM_Epoll::AddEventRead(GORM_Event *pEvent)
{
    pEvent->m_Status = GORM_CONNECT_CONNECTED;
    return this->AddEvent(pEvent, GORM_EVENT_READABLE);
}

int GORM_Epoll::AddEventWrite(GORM_Event *pEvent)
{
    return this->AddEvent(pEvent, GORM_EVENT_WRITABLE);
}

int GORM_Epoll::DelEventRead(GORM_Event *pEvent)
{
    return this->DelEvent(pEvent, GORM_EVENT_READABLE);
}

int GORM_Epoll::DelEventWrite(GORM_Event *pEvent)
{
    return this->DelEvent(pEvent, GORM_EVENT_WRITABLE);
}
int GORM_Epoll::AddEventRW(GORM_Event *pEvent)
{
    return this->AddEvent(pEvent, GORM_EVENT_RW);
}

int GORM_Epoll::DelEventRW(GORM_Event *pEvent)
{
    return this->DelEvent(pEvent, GORM_EVENT_READABLE|GORM_EVENT_WRITABLE);
}

// TODO 已经加入事件触发器了，就不要再加入了
int GORM_Epoll::AddEvent(GORM_Event *pEvent, int iMask)
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

int GORM_Epoll::DelEvent(GORM_Event * pEvent, int iMask)
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

int GORM_Epoll::DelEvent(int iFD)
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

int GORM_Epoll::EventLoopProcess(uint64 ulMS)
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

int GORM_Epoll::ProcAllEvents()
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


