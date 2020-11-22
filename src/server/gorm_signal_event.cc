#include "gorm_signal_event.h"
#include "gorm_frontend_thread.h"
#include "gorm_log.h"
#include <unistd.h>

GORM_SignalEvent::GORM_SignalEvent(shared_ptr<GORM_Epoll> pEpoll, GORM_Thread *pThread):
    GORM_Event(0, pEpoll), m_pThread(pThread)
{
    m_iDataFlag = 0;
}

GORM_SignalEvent::~GORM_SignalEvent()
{

}

int GORM_SignalEvent::Init()
{
    int fds[2];
    if (0 != pipe(fds))
    {
        GORM_LOGE("create pipe failed.");
        return GORM_ERROR;
    }
    this->m_iReadFD = fds[0];
    this->m_iWriteFD = fds[1];
    this->m_iFD = m_iReadFD;
    GORM_Socket::SetNonBlocking(this->m_iReadFD);
    GORM_Socket::SetNonBlocking(this->m_iWriteFD);
    
    this->m_Status = GORM_CONNECT_CONNECTED;

    if (0 != this->m_pEpoll->AddEventRead(this))
    {
        return GORM_ERROR;
    }
    return GORM_OK;
}

int GORM_SignalEvent::Write()
{
    return GORM_OK;
}

int GORM_SignalEvent::Read()
{
    #define SIGNAL_READ_BUFF_LEN 64
    char readBuffer[SIGNAL_READ_BUFF_LEN];
    int iNum;
    do{
        iNum = read(this->m_iReadFD, readBuffer, SIGNAL_READ_BUFF_LEN);
    }while(iNum == SIGNAL_READ_BUFF_LEN);

    this->m_iDataFlag = 0;
    this->m_pThread->SignalCB();
    
    return GORM_OK;
}

int GORM_SignalEvent::Error()
{
    return GORM_OK;
}

int GORM_SignalEvent::Close()
{
    return GORM_OK;
}

