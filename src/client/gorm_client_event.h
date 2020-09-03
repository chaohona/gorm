#ifndef _GORM_CLIENT_EVNET_H__
#define _GORM_CLIENT_EVNET_H__

#include "gorm_sys_inc.h"
#include "gorm_event.h"
#include "gorm_list.h"
#include "gorm_mempool.h"
#include "gorm_log.h"
namespace gorm{

class GORM_ClientRequest;
class GORM_ClientResponse;
class GORM_ClientSvrMgr;
// 管理客户端和服务器的连接
class GORM_ClientEvent: public GORM_Event
{
public:
    GORM_ClientEvent(GORM_Log *pLogger = nullptr, shared_ptr<GORM_Epoll> pEpoll = nullptr);
    virtual ~GORM_ClientEvent();

    void SetLogger(GORM_Log *pLogger);
    void SetMemPool(GORM_MemPool *pMemPool);

public:
    virtual int Write();
    virtual int Read();
    int Reconnect();

    // 阻塞调用
    int ConnectToServer(const char *szIP, uint16 uiPort);

    // 接收一个新的需要发送的请求数据
    int NewRequest(const GORM_ClientRequest *pRequest, uint32 &ulCBID);
friend class GORM_ClientSvrMgr;
private:
    int BeginReadNextMsg();
    GORM_ClientRequest* GetRequest();
    void GotReply();
private:
    GORM_ClientSvrMgr   *m_pClientMgr = nullptr;
    /*发送队列不删除,等待服务器响应,目前为发送顺序与响应顺序相同*/
    GORM_SyncList<GORM_ClientRequest*> m_listWaitingRsp;
    GORM_SyncList<GORM_ClientRequest*> m_listSend;      // 待发送给服务器的内存队列
    GORM_SyncList<GORM_ClientResponse*> m_listRead;     // 读取到的列表
    GORM_ClientResponse *m_pReadingResponse = nullptr;
    GORM_ClientRequest  *m_pSendingData = nullptr;
    GORM_MemPoolData    *m_pReadingBuffer = nullptr;    // 读取GORMSERVER响应缓冲区
    char *m_szBeginPos = nullptr;                       // 当前消息开始的地方
    int m_iNeedLen = 0;                                 // 当前消息的总长度
    int m_iReadedLen = 0;                               // 已经读取的长度
    GORM_Log *pLogger = nullptr;
    atomic<bool>    m_bNewResponse;
    bool    m_bFinish = false;      // 进程结束，不需要
    mutex   m_Mutex;
    GORM_MemPool *m_pMemPool = nullptr;
};

}

#endif
