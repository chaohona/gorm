#include "gorm_event.h"
#include "gorm_log.h"
#include "gorm_define.h"
#include "gorm_error.h"


uint64 GORM_Event::global_event_id = 0;


GORM_Event::GORM_Event(GORM_FD iFD, shared_ptr<GORM_Epoll> pEpoll) : m_pEpoll(pEpoll)
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

int GORM_Event::ReadyWrite()
{
    return this->m_pEpoll->AddEventWrite(this);
}
int GORM_Event::DelWrite()
{
    return this->m_pEpoll->DelEventWrite(this);    
}
int GORM_Event::ReadyRead()
{
    return this->m_pEpoll->AddEventRead(this);
}
int GORM_Event::DelRead()
{
    return this->m_pEpoll->DelEventRead(this);
}
int GORM_Event::ReadyRW()
{
    return this->m_pEpoll->AddEventRW(this);
}
int GORM_Event::DelRW()
{
    return this->m_pEpoll->DelEventRW(this);
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
    bzero(m_vEvents, MAX_EVENT_POOLS*sizeof(GORM_Event*));
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

