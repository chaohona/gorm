#ifndef _GORM_TRANSFER_H__
#define _GORM_TRANSFER_H__

// 用于处理工作线程与前端接入线程之间的通信

#include "gorm_inc.h"
#include "gorm_event.h"

class GORM_FrontEndThread;
class GORM_SignalEvent : public GORM_Event
{
public:
    GORM_SignalEvent(shared_ptr<GORM_Epoll> pEpoll, GORM_Thread *pThread);
    virtual ~GORM_SignalEvent();

    // 创建读写句柄
    int Init();

    virtual int Write();
    virtual int Read();
    virtual int Error();
    virtual int Close();

    // 向管道发送一个消息
    void Single(bool bForce=false);
public:
    GORM_Thread *m_pThread = nullptr;
    GORM_FD m_iReadFD = 0;
    GORM_FD m_iWriteFD = 0;
    atomic<int> m_iDataFlag;    // 管道中是否有数据标记，由于是做信号使用，已经有数据则不重复写
};

#endif

