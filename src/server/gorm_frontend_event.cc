#include "gorm_frontend_event.h"
#include "gorm_msg_helper.h"
#include "gorm_work_thread.h"
#include "gorm_msg_helper.h"
#include "gorm_frontend_thread.h"
#include "gorm_table_field_map.h"

using namespace gorm;
GORM_FrontEndEvent::GORM_FrontEndEvent(GORM_FD iFD, shared_ptr<GORM_Epoll>       pEpoll, GORM_FrontEndThread *pThread) : 
    GORM_Event(iFD, pEpoll), m_pFrontThread(pThread)
{
    if (GORM_Config::Instance()->m_workMode == GORM_WORK_MODE_SERIAL)
        this->m_pRequestRing = make_shared<GORM_RingBuffer<GORM_DBRequest, 1024*8>>();
    this->m_pReadCache = m_pFrontThread->m_pMemPool->GetData(1024*1024);
    m_pCurrentReadPtr = this->m_pReadCache->m_uszData;
    m_pStartPtr = this->m_pCurrentReadPtr;
    this->SetRemoveAddr();
    this->ulHeadBeatTime = GORM_GetNowMS();
    this->m_Status = GORM_CONNECT_CONNECTED;
}

// TODO 将所有请求的对应的frontevent置为空
GORM_FrontEndEvent::~GORM_FrontEndEvent()
{
    try
    {
        if (this->m_pReadCache != nullptr)
            m_pFrontThread->m_pMemPool->Release(this->m_pReadCache);
        GORM_DBRequest *pRequest = nullptr;
        do{
            pRequest = this->m_pRequestRing->PopFront();
            if (pRequest == nullptr)
            {
                break;
            }
            pRequest->pFrontendEvent = nullptr;
        }while(pRequest != nullptr);
        m_pRequestRing = nullptr;

        auto it = this->m_requestMap.begin();
        while(it != this->m_requestMap.end())
        {
            it->second->pFrontendEvent = nullptr;
            it = this->m_requestMap.erase(it);
        }
        auto it = this->m_waitForResponseMap.begin();
        while(it != this->m_waitForResponseMap.end())
        {
            it->second->pFrontendEvent = nullptr;
            it = this->m_waitForResponseMap.erase(it);
        }
    }
    catch(exception &e)
    {   
        
    }
}

void GORM_FrontEndEvent::SetMemPool(shared_ptr<GORM_MemPool> &pMemPool)
{
    this->pMemPool = pMemPool;
}

GORM_Ret GORM_FrontEndEvent::GetNextSending(bool &bContinue)
{
    bContinue = false;
    GORM_DBRequest *pRequest = nullptr;
    //if (GORM_Config::Instance()->m_workMode == GORM_WORK_MODE_SERIAL)
    //{
        pRequest = this->m_pRequestRing->GetFront();                    
        if (pRequest == nullptr)                                                        
        {                                                                               
            this->DelWrite();                                                           
            return GORM_OK;                                                             
        }                                                                               
        if (pRequest->iWaitDone != 1)                                                   
        {                                                                               
            this->DelWrite();                                                           
            if (pRequest->iSentToWorkThread == 0)                                       
            {                                                                           
                this->SendMsgToWorkThread(pRequest);                                     
                return GORM_OK;                                                         
            }                                                                           
        }                                                                               
        this->m_pSendingRequest = this->m_pRequestRing->PopFront();                     
        if (this->m_pSendingRequest == nullptr)                                         
        {                                                                               
            this->DelWrite();                                                           
            return GORM_OK;                                                             
        }  
    /*}
    else
    {
        if (this->m_requestMap.size() == 0)
        {
            this->DelWrite();
            return GORM_OK;
        }
        auto it = this->m_requestMap.begin();
        if (it == this->m_requestMap.end())
        {
            this->DelWrite();                                                           
            return GORM_OK;
        }
        this->m_pSendingRequest = it->second;
        this->m_requestMap.erase(it);
    }*/
    if (this->m_pSendingRequest->iReqCmd == GORM_CMD_BATCH_GET)                     
        this->m_pSendingRequest->PackBatchGetResult();                              
    else if( this->m_pSendingRequest->iReqCmd == GORM_CMD_GET_BY_PARTKEY)           
        this->m_pSendingRequest->PackGetByPartkeyResult();                          
    auto sendingRequest = this->m_pSendingRequest;                                  
    if (sendingRequest != nullptr)                                                  
    {                                                                               
        if (sendingRequest->pRspData != nullptr)                                    
        {                                                                           
            this->m_pCurrentWrite = sendingRequest->pRspData->m_uszData;            
            this->m_iNeedWrite = sendingRequest->pRspData->m_sUsedSize;             
        }                                                                           
        else                                                                        
        {                                                                           
            GORM_SetRspHeader(m_szErrorReplyHeader, GORM_RSP_MSG_HEADER_LEN, sendingRequest->iReqCmd ,sendingRequest->uiReqID, sendingRequest->iErrCode, sendingRequest->cReplyFlag);
            this->m_pCurrentWrite = m_szErrorReplyHeader;                           
            this->m_iNeedWrite = GORM_RSP_MSG_HEADER_LEN;                           
        }                                                                           
    }

    bContinue = true;
    return GORM_OK;
}

// 将响应消息发送给客户端
int GORM_FrontEndEvent::Write()
{
    if (this->m_pSendingRequest == nullptr)
    {
        bool bContinue;
        int iRet = GetNextSending(bContinue);
        if (iRet != GORM_OK || !bContinue)
            return iRet;
    }

    for(;;)
    {
        if (this->m_pSendingRequest == nullptr)
        {
            this->DelWrite();
            return GORM_OK;
        }
        int iWriteLen = write(this->m_iFD, this->m_pCurrentWrite, this->m_iNeedWrite);
        if (iWriteLen == 0)
        {
            return GORM_ERROR;
        }
        if (iWriteLen < 0)
        {
            if (errno == EINTR) {
                GORM_LOGD("write on sd %d not ready", this->m_iFD);
                continue;
            } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
                GORM_LOGD("sendv on sd %d not ready - eagain", this->m_iFD);
                break;
            } else {
                GORM_LOGE("sendv on sd %d failed, errmsg %s", this->m_iFD, strerror(errno));
                return GORM_ERROR;
            }
            return GORM_ERROR;
        }
        this->m_iNeedWrite -= iWriteLen;
        this->m_pCurrentWrite += iWriteLen;
        ASSERT(this->m_iNeedWrite>=0);
        if (this->m_iNeedWrite == 0)
        {
            this->m_pSendingRequest->Release();
            this->m_pSendingRequest = nullptr;

            // 获取请求判断是否已经接收完响应了，接收完响应才会发送
            bool bContinue;
            int iRet = GetNextSending(bContinue);
            if (iRet != GORM_OK || !bContinue)
                return iRet;
        }
        else
        {
            break;
        }
    }
    
    // 发送
    return GORM_OK;
}

GORM_Ret GORM_FrontEndEvent::PreRead()
{
    // 同步请求，同时只处理一个
    if (this->m_workMode == GORM_WORK_MODE_SERIAL)
    {
        int iPendingNum = this->m_pRequestRing->GetNum();
        // 有没有获取到响应的请求
        if ( iPendingNum > 0)
        {
            GORM_DBRequest *reqMsg = this->m_pRequestRing->GetFront();
            if (reqMsg != nullptr)
            {
                reqMsg->ulRspTimeMS = GORM_GetNowMS();
                if (reqMsg->ulRspTimeMS - reqMsg->ulReqTimeMS > 1000)
                {
                    reqMsg->pFrontendEvent = nullptr;
                    GORM_LOGE("request is time out, seqid:%d", reqMsg->uiReqID);
                    reqMsg->GetResult(GORM_REQUEST_TT);
                    this->AddWrite();
                }
                return GORM_EAGAIN;
            }
        }
        if (GORM_RB_POOLFULL(this->m_pRequestRing))
        {
            GORM_LOGE("wait for response pool is full, fd %d, addr %s:%d", this-m_iFD, this->m_szIP, this->m_uiPort);
            ASSERT(false);
            return GORM_ERROR;
        }
    }

    return GORM_OK;
}

int GORM_FrontEndEvent::Read()
{
    // 已经关闭了
    if (this->m_iFD <= 0 )
    {
        return GORM_ERROR;
    }
    GORM_Ret iRet;
    iRet = PreRead();
    if (iRet == GORM_EAGAIN)
        return GORM_OK;
    else if (iRet != GORM_ERROR)
    {
        GORM_LOGE("close gorm client.");
        this->Close();
        return GORM_ERROR;
    }

    int iLeft = 0;
    int iRead = 0;

    for(;;)
    {
        iLeft = m_pReadCache->m_uszEnd - m_pCurrentReadPtr;
        iRead = read(this->m_iFD, m_pCurrentReadPtr, iLeft);
        if (iRead < 0)
        {
            if (errno == EINTR)
            {
                GORM_LOGE("recv from client not ready - eintr, %s:%d", this->m_szIP, this->m_uiPort);
                continue;
            }
            else if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                GORM_LOGE("recv from client not ready - eagain, %s:%d", this->m_szIP, this->m_uiPort);
                return GORM_EAGAIN;
            }
            GORM_LOGE("read got error, close the connection %s:%d, error:%d, errmsg:%s", this->m_szIP, this->m_uiPort, errno, strerror(errno));
            this->Close();
            
            return GORM_ERROR;
        }
        else if (iRead == 0)
        {
            GORM_LOGE("read got 0, client close the connection %s:%d", this->m_szIP, this->m_uiPort);
            this->Close();
            return GORM_ERROR;
        }

        iRet = this->ParseMsg(iRead);
        if (GORM_OK != iRet)
        {
            GORM_LOGE("parse request failed, close the connection %s:%d", this->m_szIP, this->m_uiPort);
            break;
        }
        // 数据已经读完了
        if (iRead < iLeft)
        {
            break;
        }
    }
    return GORM_OK;
}

GORM_Ret GORM_FrontEndEvent::ParseMsg(int iRead)
{
    m_pCurrentReadPtr += iRead;
    for (;;)
    {
        if (this->m_workMode == GORM_WORK_MODE_SERIAL)
        {
            if (GORM_RB_POOLFULL(this->m_pRequestRing))
            {
                GORM_LOGE("wait for response pool is full, fd %d, addr %s:%d", this-m_iFD, this->m_szIP, this->m_uiPort);
                ASSERT(false);
                return GORM_ERROR;
            }
        }

        // 1、检查是否获取到消息头
        if (this->m_uiMsgLen == 0)
        {
            if (this->m_pReadCache->m_uszEnd - m_pStartPtr < GORM_REQ_MSG_HEADER_LEN)
            {
                MoveMsg2Start();
                return GORM_EAGAIN;
            }
            if (m_pCurrentReadPtr - this->m_pStartPtr < GORM_REQ_MSG_HEADER_LEN)
            {
                return GORM_OK;
            }
            this->m_uiMsgLen = gorm::GORM_GetMsgLen(m_pStartPtr);
            if (this->m_uiMsgLen > GORM_MAX_REQUEST_LEN)
            {
                GORM_LOGE("client rquest is too long:%d", this->m_uiMsgLen);
                return GORM_ERROR;
            }
            // 分配一个大小至少为消息体大小的buffer
            if (this->m_pReadCache->m_sCapacity < this->m_uiMsgLen)
            {
                char *szOldStart = this->m_pStartPtr;
                this->m_pReadCache = this->pMemPool->GetData(this->m_uiMsgLen);
                memcpy(this->m_pReadCache->m_uszData, this->m_pStartPtr, m_pCurrentReadPtr - this->m_pStartPtr);
                m_pCurrentReadPtr += this->m_pReadCache->m_uszData - szOldStart;
                m_pStartPtr += this->m_pReadCache->m_uszData - szOldStart;
            }
        }
        
        // 2、如果空间比消息长度小则将消息移动到开头
        if (this->m_pReadCache->m_uszEnd - m_pStartPtr < this->m_uiMsgLen)
        {
            MoveMsg2Start();
            return GORM_EAGAIN;
        }
        // 3、检查是否接收到一整条消息了
        if (m_pCurrentReadPtr - this->m_pStartPtr < this->m_uiMsgLen)
        {
            return GORM_EAGAIN;
        }
        // 4、获取到一条消息了
        if (GORM_OK != this->ProcMsg(this->m_pStartPtr, this->m_uiMsgLen))
        {
            GORM_LOGE("parse request failed %s:%d", this->m_szIP, this->m_uiPort);
            return GORM_ERROR;
        }
        // 处理完一条消息，初始化数据
        this->m_pStartPtr += this->m_uiMsgLen;
        this->m_uiMsgLen = 0;
    }

    return GORM_OK;
}


GORM_Ret GORM_FrontEndEvent::ProcMsg(char *szMsg, int iMsgLen)
{
    // 获取消息头
    uint32 iReqID;
    uint8 flag;
    GORM_CMD iReqCmd;
    szMsg = GORM_GetReqHeader(szMsg+GORM_MSG_LEN_BYTE, iReqCmd, iReqID, flag);
    // TODO 解压缩
    if (flag & GORM_FLAG_REQ_COMPRESS > 0)
    {
        
    }
    GORM_LOGD("got request from client, cmd:%d, seqid:%u, flag:%d", iReqCmd, iReqID, flag);

    // TODO 返回心跳，连接5秒没消息则主动断开
    if (iReqCmd == GORM_CMD_HEART)
    {
        return this->HeartBeat();
    } 
    else if (iReqCmd == GORM_CMD_HAND_SHAKE)
    {
        if (this->m_ulClientId  != 0)
        {
            GORM_LOGW("has make hand shake, %s:%d", this->m_szIP, this->m_uiPort);
        }
        return this->HandShake(szMsg, iMsgLen, iReqID);
    } 
    else if (iReqCmd > GORM_CMD_MAX || iReqCmd <= GORM_CMD_INVALID)
    {
        GORM_LOGE("got invalid request command, cmd id:%d", iReqCmd);
        return GORM_ERROR;
    }
    GORM_DBRequest  *pCurrentRequest = new GORM_MySQLRequest(this->pMemPool);
    // 读取到一个请求之后传给解析器解析,如果当前的请求和前一个请求的事务id一样，则需要等前一个请求返回之后再接收下一个请求
    if (pCurrentRequest == nullptr)
    {
        // TODO 返回错误
        GORM_LOGE("malloc request got failed, %s:%d", this->m_szIP, this->m_uiPort);
        return GORM_ERROR;
    }
    GORM_SetRequestSourceInfo(pCurrentRequest, iReqID, iReqCmd, this, this->m_pFrontThread);
    if (this->m_workMode == GORM_WORK_MODE_SERIAL)
    {
        if (!this->m_pRequestRing->AddData(pCurrentRequest))
        {
            ASSERT(false);
            GORM_LOGE("add request to request ring failed.");
            return GORM_ERROR;
        }
    }
    else
    {
        this->m_requestMap.insert(std::make_pair<uint32, GORM_DBRequest*>(pCurrentRequest->uiReqID, pCurrentRequest));
    }

    if (this->m_ulClientId == 0)
    {
        GORM_LOGE("client send request before make hand shake.");
        pCurrentRequest->GetResult(GORM_NEED_HAND_SHAKE, 0, nullptr);
        this->ReadyWrite();
        return GORM_OK;
    }

    // 获取请求的路由
    int iRet = pCurrentRequest->ParseReqMsg(szMsg, iMsgLen);
    if (iRet != GORM_OK)
    {
        pCurrentRequest->GetResult(iRet, 0, nullptr);
        this->ReadyWrite();
        GORM_LOGE("parse request from client failed, tableid:%d, cmd:%d, seqid:%u, flag:%d", pCurrentRequest->iReqTableId, iReqCmd, iReqID, flag);
        return iRet;
    }

    if (this->m_workMode == GORM_WORK_MODE_SERIAL)
    {
        int iPendingNum = this->m_pRequestRing->GetNum();
        // 有没有获取到响应的请求
        if ( iPendingNum > 1)
        {
            return GORM_OK;
        }
    }

    unique_lock<mutex> locker(pCurrentRequest->m_Mutex);
    return this->SendMsgToWorkThread(pCurrentRequest);
}

GORM_Ret GORM_FrontEndEvent::SendMsgToWorkThread(GORM_DBRequest       *pCurrentRequest)
{
    // 将request根据路由发送到后端工作进程
    int iRet = pCurrentRequest->SendToWorkThread();
    if (iRet != GORM_OK) // 消息本身处理出错，将错误返回给客户端就行了
    {
        // TODO 如果后端处理不过来则等待发送
        if (iRet == GORM_RING_FULL)
        {
        }
        pCurrentRequest->GetResult(iRet, 0, nullptr);
        this->ReadyWrite();
        return iRet;
    }

    return GORM_OK;
}

GORM_Ret GORM_FrontEndEvent::Verify()
{
    return GORM_OK;
}

int GORM_FrontEndEvent::Error()
{
    return GORM_OK;
}

int GORM_FrontEndEvent::Close()
{
    this->m_pEpoll->DelEventRW(this);
    GORM_Event::Close();
    return GORM_OK;
}

void GORM_FrontEndEvent::FillErrReplyBuffer(GORM_DBRequest *pRequest)
{
    GORM_SetRspHeader(this->m_szErrorReplyHeader, GORM_RSP_MSG_HEADER_LEN, pRequest->iReqCmd, pRequest->uiReqID, pRequest->iErrCode, pRequest->cReplyFlag);
}

GORM_Ret GORM_FrontEndEvent::HeartBeat()
{
    static GORM_MySQLRequest *pHeartBeat = nullptr;
    if (pHeartBeat == nullptr)
    {
        pHeartBeat = new GORM_MySQLRequest(this->pMemPool);
        if (pHeartBeat == nullptr)
        {
            // TODO 退出
        }
        pHeartBeat->staticRequest = 1;
        if (GORM_OK != pHeartBeat->PackHeartBeatResult())
        {
            // TODO 退出
        }
        pHeartBeat->iWaitDone = 1;
        pHeartBeat->iPreGood = 1;
    }
    this->ulHeadBeatTime = GORM_GetNowMS();
    if (this->m_workMode == GORM_WORK_MODE_SERIAL)
    {
        if (!this->m_pRequestRing->AddData(pHeartBeat))
        {
            GORM_LOGE("add request to request ring failed.");
            return GORM_OK;
        }
    }
    else
    {
        this->m_requestMap.insert(std::make_pair<uint32, GORM_DBRequest*>(pCurrentRequest->uiReqID, pCurrentRequest));
    }
    this->ReadyWrite();

    return GORM_OK;
}

GORM_Ret GORM_FrontEndEvent::HandShakeResult(GORM_MySQLRequest* pHandShake, int code, uint64 clientId)
{
    if (GORM_OK != pHandShake->PackHandShakeResult(code, clientId))   
    {                                                               
    }                                                               
    pHandShake->iWaitDone = 1;                                      
    pHandShake->iPreGood = 1;                                       
    if (this->m_workMode == GORM_WORK_MODE_SERIAL)
    {
        if (!this->m_pRequestRing->AddData(pHeartBeat))
        {
            GORM_LOGE("add request to request ring failed.");
            return GORM_OK;
        }
    }
    else
    {
        this->m_requestMap.insert(std::make_pair<uint32, GORM_DBRequest*>(pCurrentRequest->uiReqID, pCurrentRequest));
    }                                                         
    this->ReadyWrite();

    return GORM_OK;
}

GORM_Ret GORM_FrontEndEvent::HandShake(char *szMsg, int iMsgLen, uint32 iReqID)
{
    GORM_MySQLRequest* pHandShake = new GORM_MySQLRequest(this->pMemPool);
    shared_ptr<GORM_PB_HAND_SHAKE_REQ> pHandShakeReq = make_shared<GORM_PB_HAND_SHAKE_REQ>();
    if (pHandShakeReq == nullptr)
    {
        GORM_LOGE("malloc hand shake message failed.");
        delete pHandShake;
        return GORM_ERROR;
    }
    GORM_SetRequestSourceInfo(pHandShake, iReqID, GORM_CMD_HAND_SHAKE, this, this->m_pFrontThread);

    if (!pHandShakeReq->ParseFromArray(szMsg, iMsgLen-GORM_REQ_MSG_HEADER_LEN))
    {                                                                   
        GORM_LOGE("parse input buffer failed.");
        delete pHandShake;
        return GORM_UNPACK_REQ;                                         
    } 

    // 比对请求版本与服务器版本差异
    GORM_PB_HAND_SHAKE_REQ *pSvrHandShake = dynamic_cast<GORM_PB_HAND_SHAKE_REQ*>(GORM_TableFieldMapInstance::pTableInfo);
    if (pHandShakeReq->md5() != pSvrHandShake->md5())
    {
        GORM_LOGE("hand shake md5 check failed.");
        //GORM_HAND_SHAKE_RESULT(GORM_VERSION_NOT_MATCH, 0);
        HandShakeResult(pHandShake, GORM_VERSION_NOT_MATCH, 0)
        return GORM_OK;
    }
    if (pHandShakeReq->schemas_size() != pSvrHandShake->schemas_size())
    {
        GORM_LOGE("hand shake schema size check failed, req size:%d, server size:%d", pHandShakeReq->schemas_size(), pSvrHandShake->schemas_size());
        //GORM_HAND_SHAKE_RESULT(GORM_VERSION_NOT_MATCH, 0);
        HandShakeResult(pHandShake, GORM_VERSION_NOT_MATCH, 0)
        return GORM_OK;
    }
    for(int i=0; i<pHandShakeReq->schemas_size(); i++)
    {
        const GORM_PB_TABLE_SCHEMA_INFO &reqInfo = pHandShakeReq->schemas(i);
        const GORM_PB_TABLE_SCHEMA_INFO &svrInfo = pSvrHandShake->schemas(i);
        if (reqInfo.columns_size() != svrInfo.columns_size())
        {
            GORM_LOGE("hand shake column size check failed, table:%s", reqInfo.tablename().c_str());
            //GORM_HAND_SHAKE_RESULT(GORM_VERSION_NOT_MATCH, 0);
            HandShakeResult(pHandShake, GORM_VERSION_NOT_MATCH, 0)
            return GORM_OK;
        }
        for (int j=0; j<reqInfo.columns_size(); j++)
        {
            const GORM_PB_TABLE_SCHEMA_INFO_COLUMN &reqColumn = reqInfo.columns(j);
            const GORM_PB_TABLE_SCHEMA_INFO_COLUMN &svrColumn = svrInfo.columns(j);
            if (reqColumn.type() != svrColumn.type())
            {
                GORM_LOGE("hand shake column type check failed, table:%s, column:%s", reqInfo.tablename().c_str(), reqColumn.name().c_str());
                //GORM_HAND_SHAKE_RESULT(GORM_VERSION_NOT_MATCH, 0);
                HandShakeResult(pHandShake, GORM_VERSION_NOT_MATCH, 0)
                return GORM_OK;
            }
        }
    }

    this->m_ulClientId = 1;
    HandShakeResult(pHandShake, GORM_OK, this->m_ulClientId);
    //GORM_HAND_SHAKE_RESULT(GORM_OK, this->m_ulClientId);
    return GORM_OK;
}

