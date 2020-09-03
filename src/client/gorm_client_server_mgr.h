#ifndef _GORM_CLIENT_SERVER_MGR_H__
#define _GORM_CLIENT_SERVER_MGR_H__
#include "gorm_client_event.h"
#include "gorm_log.h"
#include "gorm_client_request.h"
#include "gorm_sys_inc.h"
#include "gorm_client_response.h"
#include "gorm_mempool.h"
namespace gorm{

// 管理客户端和服务器的连接
class GORM_Server;
class GORM_ClientSvrMgr
{
public:
    GORM_ClientSvrMgr(GORM_MemPool *pMemPool, GORM_Log *pLogger = nullptr);
    ~GORM_ClientSvrMgr();
public:
    int Start();
    int Stop();
    int SetServerUrl(const char* szUrl);
    ///////////////业务线程函数hegin//////////////////////////
    // 将请求打包，并发送到发送队列
    // 此函数涉及到和发送线程的交互
    int SendRequest(const GORM_ClientRequest *pRequest, uint32 &ulCBID);
    int RecvResponse(GORM_ClientResponse *&response);
    // 获取一组响应
    int RecvResponse(list<GORM_ClientResponse*> &list);
    //////////////业务线程函数end////////////////////////////
friend class GORM_Server;
private:
    // 和GORMServer建立连接
    shared_ptr<GORM_Epoll> ConnectToServer(int &iRet);
    // 检查和服务器的连接，并对断线的连接做重连处理
    void EventStatusCheck();
private:
    GORM_ClientEvent    *svrEvent;                   // 目前只支持一个请求，后期改为集群
    char                szServerUrl[MAX_URL_LEN];       // GORMSvr的地址 127.0.0.1:8880/127.0.0.1:8881
    char                szServerIP[NET_IP_STR_LEN];     // GORMSvr的ip
    uint16              uiServerPort = 0;               // GORMSvr的port
    GORM_Log            *pLogger = nullptr;
    bool                bStopFlag = false;
    atomic<bool>        bNewRequest;
    // 防止epoll被释放
    shared_ptr<GORM_Epoll>  pEpoll;
    GORM_MemPool        *pMemPool = nullptr;
};

}
#endif

