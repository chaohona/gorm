#include "gorm_server.h"
#include "gorm_utils.h"
#include "gorm_table_field_map.h"


namespace gorm{

GORM_Server::GORM_Server()
{
    this->szServerUrl[0] = '\0';
}

GORM_Server::~GORM_Server()
{
    try
    {
        if (this->pSvrMgr != nullptr)
        {
            this->pSvrMgr->Stop();
            delete this->pSvrMgr;
        }
        this->pMemPool = nullptr;
    }
    catch(exception &e)
    {
        cout << "got exception:" << e.what() << endl;
    }
}

int GORM_Server::Init(GORM_Log *pLogger, const char* szCfgVersion, const char *szUrl)
{
    this->pMemPool = make_shared<GORM_MemPool>();
    this->pLogger = pLogger;
    if (pLogger == nullptr)
    {
        this->pLogger = GORM_DefaultLog::Instance();
    }
    if (!this->pLogger->Init())
    {
        cout << "gorm server init failed." << endl;
        return GORM_ERROR;
    }
    this->pSvrMgr = new GORM_ClientSvrMgr(this->pMemPool.get());
    if (szUrl != nullptr)
    {
        if (GORM_OK != this->SetServerUrl(szUrl))
        {
            return GORM_ERROR;
        }
    }

    if (szCfgVersion != nullptr)
    {
        strncpy(this->szCfgVersion, szCfgVersion, MAX_VERSION_LEN);
    }

    if (GORM_OK != GORM_TableFieldMapInstance::Instance()->Init(pLogger))
    {
        return GORM_ERROR;
    }
    
    return GORM_OK;
}

int GORM_Server::SetServerUrl(const char *szUrl)
{
    return this->pSvrMgr->SetServerUrl(szUrl);
}

int GORM_Server::SetSignature(int type, const char* signature)
{
    strncpy(this->szSignature, signature, GORM_DB_PW_MAX_LEN);

    return GORM_OK;
}

void GORM_Server::Fini()
{
    if (this->pSvrMgr != nullptr)
    {
        this->pSvrMgr->Stop();
    }
}

bool GORM_Server::Start()
{
    // 先和服务器建立连接再启动线程，让使用者知道连接是否成功
    int iConnectRet = GORM_OK;
    shared_ptr<GORM_Epoll> pEpoll = this->pSvrMgr->ConnectToServer(iConnectRet);
    if (iConnectRet != GORM_OK)
    {
        return iConnectRet;
    }
    this->pSvrMgr->pEpoll = pEpoll;
    // 启动线程，和gormserver建立连接
    std::thread t([&]() {
			std::call_once(this->onceCallFlag, [&]() {this->StartWork(); });
			});
    t.detach();
    return true;
}

// 工作线程
void GORM_Server::StartWork()
{
    GORM_CUSTOM_LOGD(pLogger, "gorm work thread started, thread id:%d", std::this_thread::get_id());
    this->pSvrMgr->Start();
}

bool GORM_Server::ReloadTable(const char *szTablePath)
{
    return true;
}

GORM_ClientRequest *GORM_Server::GetRequest(GORM_CMD cmd, int iTableId)
{
    GORM_ClientRequest *pRequest = new GORM_ClientRequest();
    if (GORM_OK != pRequest->Init(cmd, iTableId))
    {
        // TODO 内存池
        delete pRequest;
        return nullptr;
    }
    pRequest->pMemPool = this->pMemPool.get();

    return pRequest;
}

GORM_ClientRequest *GORM_Server::GetRequestForInsert(int iTableId)
{
    return this->GetRequest(GORM_CMD_INSERT, iTableId);
}
GORM_ClientRequest *GORM_Server::GetRequestForReplace(int iTableId)
{
    return this->GetRequest(GORM_CMD_REPLACE, iTableId);
}

GORM_ClientRequest *GORM_Server::GetRequestForIncrease(int iTableId)
{
    return this->GetRequest(GORM_CMD_INCREASE, iTableId);
}

GORM_ClientRequest *GORM_Server::GetRequestForGet(int iTableId)
{
    return this->GetRequest(GORM_CMD_GET, iTableId);
}

GORM_ClientRequest *GORM_Server::GetRequestForDelete(int iTableId)
{
    return this->GetRequest(GORM_CMD_DELETE, iTableId);
}

GORM_ClientRequest *GORM_Server::GetRequestForBatchGet(int iTableId)
{
    return this->GetRequest(GORM_CMD_BATCH_GET, iTableId);
}

GORM_ClientRequest *GORM_Server::GetRequestForGetByPartKey(int iTableId)
{
    return this->GetRequest(GORM_CMD_GET_BY_PARTKEY, iTableId);
}

GORM_ClientRequest *GORM_Server::GetRequestForUpdate(int iTableId)
{
    return this->GetRequest(GORM_CMD_UPDATE, iTableId);
}

GORM_ClientRequest *GORM_Server::GetRequestForGetByNonPrimaryKey(int iTableId)
{
    return this->GetRequest(GORM_CMD_GET_BY_NON_PRIMARY_KEY, iTableId);
}


#define GETREQUEST_BYNAME(tablename, cmd)                           \
int iTableId = 0;                                                   \
if (GORM_OK != GORM_GetTableId(tablename, iTableId))                \
{                                                                   \
    GORM_CUSTOM_LOGD(pLogger, "invalid table name:%s", tablename);  \
    return nullptr;                                                 \
}                                                                   \
return this->GetRequest(cmd, iTableId);

GORM_ClientRequest *GORM_Server::GetRequestForInsert(const char *szTableName)
{
    GETREQUEST_BYNAME(szTableName, GORM_CMD_INSERT);
}

GORM_ClientRequest *GORM_Server::GetRequestForReplace(const char *szTableName)
{
    GETREQUEST_BYNAME(szTableName, GORM_CMD_REPLACE);
}

GORM_ClientRequest *GORM_Server::GetRequestForIncrease(const char *szTableName)
{
    GETREQUEST_BYNAME(szTableName, GORM_CMD_INCREASE);
}

GORM_ClientRequest *GORM_Server::GetRequestForGet(const char *szTableName)
{
    GETREQUEST_BYNAME(szTableName, GORM_CMD_GET);
}

GORM_ClientRequest *GORM_Server::GetRequestForDelete(const char *szTableName)
{
    GETREQUEST_BYNAME(szTableName, GORM_CMD_DELETE);
}

GORM_ClientRequest *GORM_Server::GetRequestForBatchGet(const char *szTableName)
{
    GETREQUEST_BYNAME(szTableName, GORM_CMD_BATCH_GET);
}

GORM_ClientRequest *GORM_Server::GetRequestForGetByPartKey(const char *szTableName)
{
    GETREQUEST_BYNAME(szTableName, GORM_CMD_GET_BY_PARTKEY);
}

GORM_ClientRequest *GORM_Server::GetRequestForUpdate(const char *szTableName)
{
    GETREQUEST_BYNAME(szTableName, GORM_CMD_UPDATE);
}

GORM_ClientRequest *GORM_Server::GetRequestForGetByNonPrimaryKey(const char *szTableName)
{
    GETREQUEST_BYNAME(szTableName, GORM_CMD_GET_BY_NON_PRIMARY_KEY);
}


int GORM_Server::SendRequest(GORM_ClientRequest *pRequest,     uint32 &ulCBID, bool bAutoRecycle)
{
    if (GORM_OK != pRequest->PackRequest())
    {
        return GORM_ERROR;
    }
    // 将request发给连接evnet，获取cbid
    pRequest->bAutoRecycle = bAutoRecycle;
    if (GORM_OK != pSvrMgr->SendRequest(pRequest, ulCBID))
    {
        GORM_CUSTOM_LOGD(pLogger, "send request to gorm server failed.");
        return GORM_ERROR;
    }
    return GORM_OK;
}

int GORM_Server::RecvResponse(GORM_ClientResponse *&response)
{
    return this->pSvrMgr->RecvResponse(response);
}

// 获取一组响应
int GORM_Server::RecvResponse(list<GORM_ClientResponse*> &list)
{
    return this->pSvrMgr->RecvResponse(list);
}

const char* GORM_Server::GetApiVersion()
{
    return this->szCfgVersion;
}

}
