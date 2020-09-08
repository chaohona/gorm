#include "gorm_signal_event.h"
#include "gorm_frontend_thread.h"
#include "gorm_log.h"
#include <unistd.h>

GORM_SignalEvent::GORM_SignalEvent(shared_ptr<GORM_Epoll>       pEpoll, GORM_FrontEndThread *pThread):
    GORM_Event(0, pEpoll), m_pFrontThread(pThread)
{
    m_iDataFlag = 0;
}

GORM_SignalEvent::~GORM_SignalEvent()
{
    if (this->m_iReadFD != 0)
        close(this->m_iReadFD);

    if (this->m_iWriteFD != 0)
        close(this->m_iWriteFD);
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

    if (0 != this->m_pEpoll->AddEventRead(this));
    return GORM_OK;
}

int GORM_SignalEvent::Write()
{
    return GORM_OK;
}

int GORM_SignalEvent::Read()
{
    this->m_iDataFlag = 0;
    #define SIGNAL_READ_BUFF_LEN 64
    char readBuffer[SIGNAL_READ_BUFF_LEN];
    int iNum;
    do{
        iNum = read(this->m_iReadFD, readBuffer, SIGNAL_READ_BUFF_LEN);
    }while(iNum == SIGNAL_READ_BUFF_LEN);

    this->m_pFrontThread->ResponseProc();
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

void GORM_SignalEvent::Single(bool bForce)
{
    // 已经有数据了，则不再往里面写数据了
    if (!bForce)
    {
        if (this->m_iDataFlag.load() == 1)
            return;
    }

    char cSend = 0;
    // 往管道中写数据
    int iSendNum = 0;
    do
    {
        iSendNum = write(this->m_iWriteFD, (char*)&cSend, 1);
    }
    while (iSendNum < 1);
    
    this->m_iDataFlag = 1;
}

