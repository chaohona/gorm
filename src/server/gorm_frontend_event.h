#ifndef _GORM_FRONTEND_EVENT_H__
#define _GORM_FRONTEND_EVENT_H__
#include "gorm_event.h"
#include "gorm_sys_inc.h"
#include "gorm_inc.h"
#include "gorm_ringbuffer.h"
#include "gorm_mempool.h"
#include "gorm_db_request.h"

using namespace gorm;
enum GORM_FrontEndStatus
{
    GORM_FS_CONNECTED,
    GORM_FS_VERIFIED,
};

class GORM_WorkThread;
class GORM_FrontEndThread;
class GORM_FrontEndEvent : public GORM_Event
{
public:
    GORM_FrontEndEvent(GORM_FD iFD, shared_ptr<GORM_Epoll>       pEpoll, GORM_FrontEndThread *pThread);
    virtual ~GORM_FrontEndEvent();

    void SetMemPool(shared_ptr<GORM_MemPool> &pMemPool);

    virtual int Write();
    virtual int Read();
    virtual int Error();
    virtual int Close();

    GORM_Ret SendMsgToWorkThread(GORM_DBRequest  *pCurrentRequest);
private:
    GORM_Ret ParseMsg(int iRead);
    GORM_Ret ProcMsg(char *szMsg, int iMsgLen);
    GORM_Ret Verify();
    void FillErrReplyBuffer(GORM_DBRequest *pRequest);
    GORM_Ret HeartBeat();
    GORM_Ret HandShake(char *szMsg, int iMsgLen, uint32 iReqID);
    GORM_Ret GetNextSending(bool &bContinue);
    inline void MoveMsg2Start()
    {
        int iCurrentLen = m_pCurrentReadPtr - this->m_pStartPtr;
        memmove(this->m_pReadCache->m_uszData, this->m_pStartPtr, iCurrentLen);
        this->m_pStartPtr = this->m_pReadCache->m_uszData;
        this->m_pCurrentReadPtr = this->m_pStartPtr + iCurrentLen;
    }
public:
    //
    iovec               *m_vCiov = nullptr;
    // 请求的缓冲池子,主要此池子中数据个数大于1就说明有pending消息
    shared_ptr<GORM_RingBuffer<GORM_DBRequest>> m_pRequestRing = nullptr;
    /////////////////////////////////接收客户端相关
    // 当前的正在处理的请求
    GORM_DBRequest                              *m_pCurrentRequest = nullptr;   // 正在解析的从客户端过来的请求
    // sendv使用的数据结构
    iovec                                       *m_vCiov = nullptr;
    GORM_MemPoolData    *m_pReadCache;      // 读取缓冲池
    char                *m_pCurrentReadPtr = nullptr;   // 当前读取开始地址
    char                *m_pStartPtr = nullptr;         // 消息起始地址
    uint32              m_uiMsgLen = 0;                 // 消息长度
    ////////////////////////////////////////////////////////////////////


    ///////////////////////////////////往客户端发送相关////////////////////////////////////
    GORM_DBRequest      *m_pSendingRequest = nullptr;   // 正在往客户端发的结果
    char                *m_pCurrentWrite = nullptr;            // 当前数据写入开始地址
    int32               m_iNeedWrite = 0;
    // 当消息编码失败后，用这个组装消息头发送给客户端
    char                m_szErrorReplyHeader[GORM_RSP_MSG_HEADER_LEN];  
    ////////////////////////////////////////////////////////////////////////////////////////
    GORM_FrontEndStatus m_iFS = GORM_FS_CONNECTED;
    
    // 事件所在的线程
    GORM_FrontEndThread *m_pFrontThread;
    uint64              ulHeadBeatTime = 0;
    shared_ptr<GORM_MemPool> pMemPool;
private:
    uint64  m_ulClientId = 0;
};


#endif
