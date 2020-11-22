#include "gorm_client_event.h"
#include "gorm_msg_helper.h"
#include "gorm_client_request.h"
#include "gorm_sys_inc.h"
#include "gorm_define.h"

namespace gorm{

GORM_ClientEvent::GORM_ClientEvent(GORM_Log *pLogger, shared_ptr<GORM_Epoll> pEpoll):GORM_Event(0, pEpoll)
{
    this->pLogger = pLogger;
    this->m_pReadingBuffer = this->m_pMemPool->GetData(1024*1024);
    this->m_szBeginPos = this->m_pReadingBuffer->m_uszData;
}

GORM_ClientEvent::~GORM_ClientEvent()
{
}

void GORM_ClientEvent::SetLogger(GORM_Log *pLogger)
{
    this->pLogger = pLogger;
}

void GORM_ClientEvent::SetMemPool(GORM_MemPool *pMemPool)
{
    this->m_pMemPool = pMemPool;
}

int GORM_ClientEvent::Read()
{
    // TODO 判断是否可读，是否是断线
    // 1、判断是否可读，如果不可读则返回GORM_EAGAIN
    // 2、如果可读判断是否读取了一整个消息
    int iNeedRead = 0;
    int iNowLen = 0;
    bool bCouldContinue = true;
    if (this->m_pReadingResponse == nullptr)
    {
        this->m_pReadingResponse = new GORM_ClientResponse();
    }
    do
    {
#ifdef _WIN32
		iNowLen = recv(m_iFD, m_szBeginPos + m_iReadedLen, m_pReadingBuffer->m_uszEnd - m_szBeginPos - m_iReadedLen, 0);
#else
        iNowLen = read(m_iFD, m_szBeginPos+m_iReadedLen, m_pReadingBuffer->m_uszEnd-m_szBeginPos-m_iReadedLen);
#endif
        if (iNowLen == 0)
        {
            GORM_CUSTOM_LOGE(pLogger, "read from server failed");
            return GORM_ERROR;
        }
        if (iNowLen < 0)
        {
            if (errno == EINTR)
            {
                GORM_CUSTOM_LOGD(pLogger, "recv from redis not ready - eintr");
                continue;
            }
            else if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                GORM_CUSTOM_LOGD(pLogger, "recv from redis not ready - eagain");
                return GORM_EAGAIN;
            }
            GORM_CUSTOM_LOGE(pLogger, "redis read failed:%d, errmsg:%s", errno, strerror(errno));
            this->Close();
            return GORM_ERROR;
        }
        if (iNowLen < (m_pReadingBuffer->m_uszEnd-m_szBeginPos-m_iReadedLen))
        {
            bCouldContinue = false;
        }
        m_iReadedLen += iNowLen;
        do{
            if (m_iNeedLen == 0 )
            {
                if (GORM_OK != this->BeginReadNextMsg())
                {
                    this->Close();
                    return GORM_ERROR;
                }
            }
            if (m_iNeedLen != 0 && m_iNeedLen <= m_iReadedLen) // 读完一条消息
            {
                // TODO 解包
                GotReply();
                m_szBeginPos = m_szBeginPos += m_iNeedLen;
                m_iReadedLen -= m_iNeedLen;
                m_iNeedLen = 0;
                if (GORM_OK != this->BeginReadNextMsg())
                {
                    this->Close();
                    return GORM_ERROR;
                }
            }
            else
            {
                break;
            }
        }while(true);
        
        if (!bCouldContinue)
            break;
    }while(true);
    return GORM_OK;
}

int GORM_ClientEvent::BeginReadNextMsg()
{
    if (m_iNeedLen == 0 && m_iReadedLen > 4)
    {
        m_iNeedLen = GORM_GetMsgLen(m_pReadingBuffer->m_uszData);
        if (m_iNeedLen > GORM_MAX_REQUEST_LEN)
        {
            GORM_CUSTOM_LOGD(pLogger, "response is too large.");
            this->m_pReadingResponse->cPreErrCode = GORM_PACK_RSP_ERROR;
            return GORM_ERROR;
        }
        // 需要的长度比当前长度大
        if (m_iNeedLen > (m_pReadingBuffer->m_uszEnd-m_szBeginPos))
        {
            // 消息长度比缓冲区大则，重新申请缓冲区
            if (m_iNeedLen > m_pReadingBuffer->m_sCapacity)
            {
                GORM_MemPoolData *pOldData = m_pReadingBuffer;
                m_pReadingBuffer = this->m_pMemPool->GetData(m_szBeginPos, m_iReadedLen, m_iNeedLen);
                pOldData->Release();
            }
            else // 将消息拷贝到开始的地方
            {
                memmove(m_pReadingBuffer->m_uszData, m_szBeginPos, m_iReadedLen);
            }
            m_szBeginPos = m_pReadingBuffer->m_uszData;
        }
    }

    return GORM_OK;
}

// TODO 改成writev的形式
int GORM_ClientEvent::Write()
{
    // 从内存队列中取出数据，发送完为止
    if (m_pSendingData == nullptr)
    {
        this->m_listSend.Take(this->m_pSendingData);
        if (this->m_pSendingData == nullptr)
        {
            m_pEpoll->DelEventWrite(this);
            return GORM_OK;
        }
        this->m_pSendingData->szSendPos = this->m_pSendingData->pMsgBuffer->m_uszData;
    }
    GORM_ClientRequest *pRequest = nullptr;
    GORM_MemPoolData *pData = nullptr;
    int iReadLen = 0;
    int iNeedSend = 0;
    for (; m_pSendingData != nullptr;)
    {
        pRequest = this->m_pSendingData;
        pData = pRequest->pMsgBuffer;
        iNeedSend = pData->m_sUsedSize-(m_pSendingData->szSendPos-pData->m_uszData);
#ifdef _WIN32
		iReadLen = send(this->m_iFD, pRequest->szSendPos, iNeedSend, 0);
#else
        iReadLen = write(this->m_iFD, pRequest->szSendPos, iNeedSend);
#endif
		if (iReadLen == 0)
        {
            return GORM_ERROR;
        }
        if (iReadLen > 0)
        {
            pRequest->szSendPos += iReadLen;
            iNeedSend -= iReadLen;
            // 发送完一条数据了
            if (iNeedSend == 0)
            {
                // 获取下一条需要发送的数据
                m_pSendingData = nullptr;
                this->m_listSend.Take(this->m_pSendingData);
                // 没有需要发送的数据
                if (m_pSendingData == nullptr)
                {
                    m_pEpoll->DelEventWrite(this);
                    break;
                }
                else
                {
                    this->m_pSendingData->szSendPos = this->m_pSendingData->pMsgBuffer->m_uszData;
                }
                break;
            }
            continue;
        }
        if (errno == EINTR) {
            GORM_CUSTOM_LOGD(pLogger, "write on sd %d not ready", this->m_iFD);
            break;
        } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
            GORM_CUSTOM_LOGD(pLogger, "sendv on sd %d not ready - eagain", this->m_iFD);
            break;
        } else {
            GORM_CUSTOM_LOGE(pLogger, "sendv on sd %d failed, errmsg %s", this->m_iFD, strerror(errno));
            return GORM_ERROR;
        }
    }
    return GORM_OK;
}

int GORM_ClientEvent::ConnectToServer(const char *szIP, uint16 uiPort)
{
    int iFD = socket(AF_INET, SOCK_STREAM, 0);
    if (iFD < 0)
    {
        GORM_CUSTOM_LOGE(pLogger, "create socket failed:%s,%d, errno:%d,errmsg:%s", szIP, uiPort, errno, strerror(errno));
        return GORM_ERROR;
    }
    this->m_iFD = iFD;
    this->m_uiPort = uiPort;
    strncpy(m_szIP, szIP, NET_IP_STR_LEN);
    sockaddr_in server_address;
#ifdef _WIN32
	memset(&server_address, 0, sizeof(server_address));
#else
	bzero(&server_address, sizeof(server_address));
#endif
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, szIP, &server_address.sin_addr);
    server_address.sin_port = htons(uiPort);

    this->m_Status = GORM_CONNECT_CONNECTING;
    do
    {
        int iRet = connect(iFD, (sockaddr*)&server_address, sizeof(server_address));
        if (iRet != 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            GORM_CUSTOM_LOGE(pLogger, "connecto to server failed, server address %s:%d, errno:%d, errmsg:%s", 
                    szIP, uiPort, errno, strerror(errno));
                    
            return GORM_CONN_FAILED;
        }
        break;
    }while(true);
    this->m_Status = GORM_CONNECT_CONNECTED;

    int iRet = GORM_Socket::SetNonBlocking(iFD);
    if (iRet != GORM_OK)
    {
        GORM_CUSTOM_LOGE(pLogger, "set socket nonblock failed:%s,%d, errno:%d, errmsg:%s", szIP, uiPort, errno, strerror(errno));
        return iRet;
    }
    iRet = GORM_Socket::SetTcpNoDelay(iFD);
    if (iRet != GORM_OK)
    {
        GORM_CUSTOM_LOGE(pLogger, "set socket tcpnodelay failed:%s,%d, errno:%d, errmsg:%s", szIP, uiPort, errno, strerror(errno));
        return iRet;
    }
    /*iRet = GORM_Socket::SetSndTimeO(iFD, 100);
    if (iRet != GORM_OK)
    {
        GORM_CUSTOM_LOGE(pLogger, "set socket send time out failed:%s,%d, errno:%d, errmsg:%s", szIP, uiPort, errno, strerror(errno));
        return iRet;
    }
    iRet = GORM_Socket::SetRcvTimeO(iFD, 100);
    if (iRet != GORM_OK)
    {
        GORM_CUSTOM_LOGE(pLogger, "set socket recv time out failed:%s,%d, errno:%d, errmsg:%s", szIP, uiPort, errno, strerror(errno));
        return iRet;
    }
    iRet = GORM_Socket::SetSynCnt(iFD, 2);
    if (iRet != GORM_OK)
    {
        GORM_CUSTOM_LOGE(pLogger, "set socket syn count failed:%s,%d, errno:%d, errmsg:%s", szIP, uiPort, errno, strerror(errno));
        return iRet;
    }
    // 和redis的buffer设置大一点,测试下来一次最多只能接收127K
    iRet = GORM_Socket::SetRevBuf(iFD, 512*1024);
    if (iRet != GORM_OK)
    {
        GORM_CUSTOM_LOGE(pLogger, "set socket tcpnodelay failed:%s,%d, errno:%d, errmsg:%s", szIP, uiPort, errno, strerror(errno));
        return iRet;
    }*/
    iRet = GORM_Socket::SetTcpKeepAlive(iFD);
    if (iRet != GORM_OK)
    {
        GORM_CUSTOM_LOGE(pLogger, "set socket SetTcpKeepAlive failed:%s,%d, errno:%d, errmsg:%s", szIP, uiPort, errno, strerror(errno));
        return iRet;
    }
    
    return GORM_OK;
}

int GORM_ClientEvent::Reconnect()
{
    if (m_bFinish)
    {
        return GORM_OK;
    }
    return GORM_OK;
}


int GORM_ClientEvent::NewRequest(const GORM_ClientRequest *pRequest, uint32 &ulCBID)
{
    ulCBID = (uint32)this->m_listSend.Put((GORM_ClientRequest*)pRequest);
    if (ulCBID == 0)
    {
        return GORM_ERROR;
    }
    ((GORM_ClientRequest*)pRequest)->ulSeqId = ulCBID;
    GORM_SetReqHeaderSeqId(((GORM_ClientRequest*)pRequest)->pMsgBuffer->m_uszData, ulCBID);
    this->m_listWaitingRsp.Put((GORM_ClientRequest*)pRequest);
    return GORM_OK;
}

GORM_ClientRequest* GORM_ClientEvent::GetRequest()
{
    GORM_ClientRequest *pResult = nullptr;

    m_listWaitingRsp.Take(pResult);
    return pResult;
}

void GORM_ClientEvent::GotReply()
{
    GORM_ClientRequest *pRequest = this->GetRequest();
    if (pRequest == nullptr) // 通常为响应已经超时了，
    {
        return;
    }
    this->m_pReadingResponse->pRequest = pRequest;
    int iRet = this->m_pReadingResponse->UnPack(m_szBeginPos, m_iNeedLen);
    if (GORM_OK != iRet)
    {
        this->m_pReadingResponse->rspCode.code = iRet;
    }
    ASSERT(pRequest->ulSeqId == this->m_pReadingResponse->ulCBID);
    this->m_listRead.Put(this->m_pReadingResponse);
    this->m_bNewResponse = true;
}


}

