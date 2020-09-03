#include "gorm_client_server_mgr.h"
#include "gorm_utils.h"

namespace gorm{

GORM_ClientSvrMgr::GORM_ClientSvrMgr(GORM_MemPool *pMemPool, GORM_Log *pLogger = nullptr)
{
    this->pMemPool = pMemPool;
    this->pLogger = pLogger;
    if (this->pLogger == nullptr)
    {
        this->pLogger = GORM_DefaultLog::Instance();
    }
}

GORM_ClientSvrMgr::~GORM_ClientSvrMgr()
{
}

int GORM_ClientSvrMgr::Stop()
{
    this->bStopFlag = true;
    // TODO 确保下面Start退出之后，再退出此函数，防止Start使用已经释放的资源,暂时用sleep代替
    ThreadSleepMilliSeconds(200);

	return 0;
}

int GORM_ClientSvrMgr::Start()
{
    if (strlen(this->szServerIP) == 0)
    {
        GORM_CUSTOM_LOGD(pLogger, "begin to connecto to gorm server, but gorm server address was not set.")
        return GORM_ERROR;
    }
   
    for (;!bStopFlag;)
    {
        // 有新请求，则触发写事件，向服务器发送请求
        if (this->bNewRequest)
        {
            pEpoll->AddEventWrite(this->svrEvent);
            this->bNewRequest = false;
        }
        // 将写事件加入触发器
        pEpoll->EventLoopProcess(100);
        pEpoll->ProcAllEvents();
        EventStatusCheck();
    }
    pEpoll->DelEventRW(this->svrEvent);
    this->svrEvent->m_bFinish = true;
    this->svrEvent->Close();

    GORM_CUSTOM_LOGD(pLogger, "gorm work thread exist, thread id:%d", std::this_thread::get_id())
    return GORM_OK;
}

int GORM_ClientSvrMgr::SetServerUrl(const char* szUrl)
{
    try
    {
        memcpy(this->szServerUrl, szUrl, MAX_URL_LEN);
        // 将127.0.0.1:8880/127.0.0.1:8881 解析为ip,端口号
        auto addrs = split(this->szServerUrl, "/");
        if (addrs.size() < 1)
        {
            GORM_CUSTOM_LOGE(this->pLogger, "invalid server url:%s", szUrl);
            return GORM_ERROR;
        }
        string address = addrs[0];
        // 获取ip与端口号
        auto ipports = split(address, ":");
        if (ipports.size() < 2)
        {
            GORM_CUSTOM_LOGE(this->pLogger, "invalid server url:%s", szUrl);
            return GORM_ERROR;
        }
        memcpy(this->szServerIP, ipports[0].c_str(), NET_IP_STR_LEN);
        this->uiServerPort = atoi(ipports[1].c_str());
        if (this->uiServerPort <= 0)
        {
            GORM_CUSTOM_LOGE(pLogger, "invalid server url:%s", szUrl);
            return GORM_ERROR;
        }
    }
    catch(exception &e)
    {
        GORM_CUSTOM_LOGD(pLogger, "set gorm server url got exception:%s", e.what());
        return GORM_ERROR;
    }

    return GORM_OK;
    
}

int GORM_ClientSvrMgr::SendRequest(const GORM_ClientRequest *pRequest, uint32 &ulCBID)
{
    if (bStopFlag)
    {
        return GORM_CONN_CLOSED;
    }
    // 交给发送线程,涉及到线程交互
    if (GORM_OK != this->svrEvent->NewRequest(pRequest, ulCBID))
    {
        return GORM_ERROR;
    }
    this->bNewRequest = true;

    return GORM_OK;
}

int GORM_ClientSvrMgr::RecvResponse(GORM_ClientResponse *&response)
{
    if (!this->svrEvent->m_bNewResponse)
    {
        return GORM_OK;
    }
    this->svrEvent->m_bNewResponse = false;

    this->svrEvent->m_listRead.Take(response);
    return GORM_OK;
}

// 获取一组响应
int GORM_ClientSvrMgr::RecvResponse(list<GORM_ClientResponse*> &response)
{
    if (!this->svrEvent->m_bNewResponse)
    {
        return GORM_OK;
    }
    this->svrEvent->m_bNewResponse = false;

    this->svrEvent->m_listRead.Take(response);
    return GORM_OK;
}

shared_ptr<GORM_Epoll> GORM_ClientSvrMgr::ConnectToServer(int &iRet)
{
    
    shared_ptr<GORM_Epoll> pEpoll(new GORM_Epoll());
    pEpoll->Init(32);
    this->svrEvent = new GORM_ClientEvent(this->pLogger, pEpoll);
    this->svrEvent->SetLogger(this->pLogger);
    this->svrEvent->SetMemPool(this->pMemPool);
    this->svrEvent->m_pClientMgr = this;
    iRet = this->svrEvent->ConnectToServer(this->szServerIP, this->uiServerPort);
    if (iRet != GORM_OK)
    {
        return nullptr;
    }
    // 将读写事件加入epoll
    if (GORM_OK != pEpoll->AddEventRead(this->svrEvent))
    {
        GORM_CUSTOM_LOGD(pLogger, "add gorm server event to epoll failed, error:%d, errinfo:%s", errno, strerror(errno));
        iRet = GORM_CONN_FAILED;
    }

    return pEpoll;
}

void GORM_ClientSvrMgr::EventStatusCheck()
{
    if (bStopFlag)
    {
        return;
    }
}

}

