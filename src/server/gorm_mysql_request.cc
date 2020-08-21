#include "gorm_mysql_request.h"
#include "gorm_db_request.h"
#include "gorm_msg_helper.h"
#include "gorm_table_field_map_define.h"
#include "gorm_mysql_conn_pool.h"
#include "gorm_db_conn_mgr.h"
#include "gorm_work_thread.h"
#include "gorm_server_table_define.h"

using namespace gorm;
GORM_MySQLRequest::GORM_MySQLRequest()
{}

GORM_MySQLRequest::~GORM_MySQLRequest()
{
    this->Release();
}

int GORM_MySQLRequest::GetOneRow(MYSQL_ROW row, unsigned long *lengths)
{
    if (GORM_OK != AddTableToRsp())
    {
        return GORM_ERROR;
    }
    pNowRspProcTable->set_tableid(iReqTableId);
    int iRet = GORM_MySQLResult2PbMSG(this->m_pMySqlEvent, iReqTableId, pNowRspProcTable, row, lengths);
    pNowRspProcTable = nullptr;
    if (iRet != GORM_OK)
    {
        return GORM_DB_2_STRUCT_ERROR;
    }
    
    return GORM_OK;
}

void GORM_MySQLRequest::InsertResult(int iRet, uint64 ulInsertID)
{
    if (this->pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(this->iReqCmd, this->pRspPbMsg))
    {
        this->iErrCode = GORM_ERROR;
        return;
    }

    if (this->iReqCmd == GORM_CMD_INSERT)
    {
        GORM_PB_INSERT_RSP *pInsertRsp = dynamic_cast<GORM_PB_INSERT_RSP*>(this->pRspPbMsg);
        pInsertRsp->set_lastinsertid(ulInsertID);
    }
    else if(this->iReqCmd == GORM_CMD_GET)  // get 转 insert 请求
    {
        GORM_PB_GET_RSP *pInsertRsp = dynamic_cast<GORM_PB_GET_RSP*>(this->pRspPbMsg);
        pInsertRsp->set_lastinsertid(ulInsertID);  
    }
    
    return;
}

void GORM_MySQLRequest::UpdateResult(int iRet, uint32 uiAffectRows)
{
    if (this->pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(this->iReqCmd, this->pRspPbMsg))
    {
        this->iErrCode = GORM_ERROR;
        return;
    }

    GORM_PB_UPDATE_RSP *pInsertRsp = dynamic_cast<GORM_PB_UPDATE_RSP*>(this->pRspPbMsg);
    pInsertRsp->set_affectednum(uiAffectRows);

    return;
}

void GORM_MySQLRequest::IncreaseResult(int iRet, uint32 uiAffectRows)
{
    if (this->pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(this->iReqCmd, this->pRspPbMsg))
    {
        this->iErrCode = GORM_ERROR;
        return;
    }

    GORM_PB_INCREASE_RSP *pInsertRsp = dynamic_cast<GORM_PB_INCREASE_RSP*>(this->pRspPbMsg);
    pInsertRsp->set_affectednum(uiAffectRows);

    return;
}

void GORM_MySQLRequest::ReplaceResult(int iRet, uint32 uiAffectRows)
{
    if (this->pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(this->iReqCmd, this->pRspPbMsg))
    {
        this->iErrCode = GORM_ERROR;
        return;
    }

    GORM_PB_REPLACE_RSP *pInsertRsp = dynamic_cast<GORM_PB_REPLACE_RSP*>(this->pRspPbMsg);
    pInsertRsp->set_affectednum(uiAffectRows);

    return;
}


void GORM_MySQLRequest::DeleteResult(int iRet, uint32 uiAffectRows)
{
    if (this->pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(this->iReqCmd, this->pRspPbMsg))
    {
        this->iErrCode = GORM_ERROR;
        return;
    }

    GORM_PB_DELETE_RSP *pInsertRsp = dynamic_cast<GORM_PB_DELETE_RSP*>(this->pRspPbMsg);
    pInsertRsp->set_affectednum(uiAffectRows);

    return;
}


#define PACK_RESULT_FAILED_LOG()\
GORM_LOGE("pack rsp msg failed, reqcmd:%d, tableid:%d, seqid:%d", iReqCmd, iReqTableId, uiReqID);

int GORM_MySQLRequest::PackResult()
{
    // 客户端连接已经断了，不需要打包了
    // TODO 断线重连获取老的结果
    if (this->pFrontendEvent == nullptr)
    {
        this->Release();
        return GORM_OK;
    }
    if (pRspPbMsg == nullptr)   // 之前流程中出现错误，没有申请响应消息
    {
        GetPbRspMsg(iReqCmd, this->pRspPbMsg);
    }
    switch (iReqCmd)
    {
    case GORM_CMD_INSERT:
    {
        if (GORM_OK != this->PackInsertResult())
        {
            PACK_RESULT_FAILED_LOG();
        }
        break;
    }
    case GORM_CMD_REPLACE:
    {
        if (GORM_OK != this->PackReplaceResult())
        {
            PACK_RESULT_FAILED_LOG();
        }
        break;
    }
    case GORM_CMD_INCREASE:
    {
        if (GORM_OK != this->PackIncreaseResult())
        {
            PACK_RESULT_FAILED_LOG();
        }
        break;
    }
    case GORM_CMD_GET:
    {
        if (GORM_OK != this->PackGetResult())
        {
            PACK_RESULT_FAILED_LOG();
        }
        break;
    }
    case GORM_CMD_DELETE:
    {
        if (GORM_OK != this->PackDeleteResult())
        {
            PACK_RESULT_FAILED_LOG();
        }
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        // 需要重新组装响应，放到前端打包
        /*if (GORM_OK != this->PackBatchGetResult())
        {
            PACK_RESULT_FAILED_LOG();
        }*/
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        // 需要重新组装响应，放到前端打包
        /*if (GORM_OK != this->PackGetByPartkeyResult())
        {
            PACK_RESULT_FAILED_LOG();
        }*/
        break;
    }
    case GORM_CMD_UPDATE:
    {
        if (GORM_OK != this->PackUpdateResult())
        {
            PACK_RESULT_FAILED_LOG();
        }
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        if (GORM_OK != this->PackGetByNonPrimaryKeyResult())
        {
            PACK_RESULT_FAILED_LOG();
        }
        break;
    }
    default:
    {
        PACK_RESULT_FAILED_LOG();
    }
    }
    
    return GORM_OK;
}

int GORM_MySQLRequest::PackInsertResult()
{
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr)
    {
        GORM_PB_INSERT_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_INSERT_RSP*>(pRspPbMsg);
        GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
        this->PackPbRetCode(retCode);
        iLen += pRspPackPbMsg->ByteSizeLong();
        pRspData = GORM_MemPool::Instance()->GetData(iLen);
        if (pRspData == nullptr)
        {
            this->iErrCode = GORM_PACK_RSP_ERROR;
            GORM_LOGE("pack insert result, get data buffer failed.");
            return GORM_ERROR;
        }
        if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
        {
            iRet = GORM_PACK_RSP_ERROR;
            iLen = GORM_RSP_MSG_HEADER_LEN;
            //pRspData->Release();
            //pRspData = nullptr;
            //GORM_LOGE("pack insert result failed.");
            //return GORM_ERROR;
        }
    }
    else
    {
        pRspData = GORM_MemPool::Instance()->GetData(GORM_RSP_MSG_HEADER_LEN);
    }

    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_INSERT, this->uiReqID, iRet, cReplyFlag);

    return GORM_OK;
}

int GORM_MySQLRequest::PackReplaceResult()
{
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr)
    {
        GORM_PB_REPLACE_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_REPLACE_RSP*>(pRspPbMsg);
        GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
        this->PackPbRetCode(retCode);
        iLen += pRspPackPbMsg->ByteSizeLong();
        pRspData = GORM_MemPool::Instance()->GetData(iLen);
        if (pRspData == nullptr)
        {
            this->iErrCode = GORM_PACK_RSP_ERROR;
            return GORM_ERROR;
        }
        if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
        {
            iLen = GORM_RSP_MSG_HEADER_LEN;
            iRet = GORM_PACK_RSP_ERROR;
            //this->iErrCode = GORM_PACK_RSP_ERROR;
            //pRspData->Release();
            //pRspData = nullptr;
            //return GORM_ERROR;
        }
    }
    else
    {
        pRspData = GORM_MemPool::Instance()->GetData(GORM_RSP_MSG_HEADER_LEN);
    }

    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_REPLACE, this->uiReqID, iRet, cReplyFlag);

    return GORM_OK;
}

int GORM_MySQLRequest::PackIncreaseResult()
{
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr)
    {
        GORM_PB_INCREASE_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_INCREASE_RSP*>(pRspPbMsg);
        GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
        this->PackPbRetCode(retCode);
        iLen += pRspPackPbMsg->ByteSizeLong();
        pRspData = GORM_MemPool::Instance()->GetData(iLen);
        if (pRspData == nullptr)
        {
            this->iErrCode = GORM_PACK_RSP_ERROR;
            return GORM_ERROR;
        }
        if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
        {
            iLen = GORM_RSP_MSG_HEADER_LEN;
            iRet = GORM_PACK_RSP_ERROR;
            //this->iErrCode = GORM_PACK_RSP_ERROR;
            //pRspData->Release();
            //pRspData = nullptr;
            //return GORM_ERROR;
        }
    }
    else
    {
        pRspData = GORM_MemPool::Instance()->GetData(GORM_RSP_MSG_HEADER_LEN);
    }

    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_INCREASE, this->uiReqID, iRet, cReplyFlag);

    return GORM_OK;
}

int GORM_MySQLRequest::PackGetToInsertResult()
{
    if (this->iRedirectCmd != GORM_CMD_INSERT || this->iGetFlag != GORM_GET_FLAG_NON_INSERT )
    {
        return GORM_OK;
    }
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr && this->pNowReqProcTable != nullptr)
    {
        GORM_PB_GET_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_GET_RSP*>(pRspPbMsg);
        ASSERT(pRspPackPbMsg != nullptr);
        pRspPackPbMsg->set_newinsert(1);
        GORM_PB_TABLE *pDestTable = pRspPackPbMsg->mutable_table();
        *pDestTable = *this->pNowReqProcTable;
    }

    return GORM_OK;
}


int GORM_MySQLRequest::PackGetResult()
{
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr)
    {
        GORM_PB_GET_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_GET_RSP*>(pRspPbMsg);
        GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
        this->PackPbRetCode(retCode);
        if (this->iRedirectCmd == GORM_CMD_INSERT && retCode->code() == 0)
        {
            PackGetToInsertResult();
        }
        iLen += pRspPackPbMsg->ByteSizeLong();
        pRspData = GORM_MemPool::Instance()->GetData(iLen);
        if (pRspData == nullptr)
        {
            this->iErrCode = GORM_PACK_RSP_ERROR;
            return GORM_ERROR;
        }
        if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
        {
            iLen = GORM_RSP_MSG_HEADER_LEN;
            iRet = GORM_PACK_RSP_ERROR;
        }
    }
    else
    {
        pRspData = GORM_MemPool::Instance()->GetData(GORM_RSP_MSG_HEADER_LEN);
    }

    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_GET, this->uiReqID, iErrCode, cReplyFlag);
    
    return GORM_OK;
}

int GORM_MySQLRequest::PackGetByNonPrimaryKeyResult()
{
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr)
    {
        GORM_PB_GET_BY_NON_PRIMARY_KEY_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_GET_BY_NON_PRIMARY_KEY_RSP*>(pRspPbMsg);
        GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
        this->PackPbRetCode(retCode);
        iLen += pRspPackPbMsg->ByteSizeLong();
        pRspData = GORM_MemPool::Instance()->GetData(iLen);
        if (pRspData == nullptr)
        {
            this->iErrCode = GORM_PACK_RSP_ERROR;
            return GORM_ERROR;
        }
        if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
        {
            iLen = GORM_RSP_MSG_HEADER_LEN;
            iRet = GORM_PACK_RSP_ERROR;
        }
    }
    else
    {
        pRspData = GORM_MemPool::Instance()->GetData(GORM_RSP_MSG_HEADER_LEN);
    }

    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_GET_BY_NON_PRIMARY_KEY, this->uiReqID, iErrCode, cReplyFlag);
    
    return GORM_OK;
}


int GORM_MySQLRequest::PackDeleteResult()
{
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr)
    {
        GORM_PB_DELETE_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_DELETE_RSP*>(pRspPbMsg);
        GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
        this->PackPbRetCode(retCode);
        iLen += pRspPackPbMsg->ByteSizeLong();
        pRspData = GORM_MemPool::Instance()->GetData(iLen);
        if (pRspData == nullptr)
        {
            this->iErrCode = GORM_PACK_RSP_ERROR;
            return GORM_ERROR;
        }
        if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
        {
            iLen = GORM_RSP_MSG_HEADER_LEN;
            iRet = GORM_PACK_RSP_ERROR;
        }
    }
    else
    {
        pRspData = GORM_MemPool::Instance()->GetData(GORM_RSP_MSG_HEADER_LEN);
    }

    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_DELETE, this->uiReqID, iRet, cReplyFlag);
    
    return GORM_OK;
}


// 打包放到前端线程做，前端线程需要重新组装消息
int GORM_MySQLRequest::PackBatchGetResult()
{
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr)
    {
        GORM_PB_BATCH_GET_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_BATCH_GET_RSP*>(pRspPbMsg);
        GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
        this->PackPbRetCode(retCode);
        iLen += pRspPackPbMsg->ByteSizeLong();
        pRspData = GORM_MemPool::Instance()->GetData(iLen);
        if (pRspData == nullptr)
        {
            this->iErrCode = GORM_PACK_RSP_ERROR;
            return GORM_ERROR;
        }

        if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
        {
            iLen = GORM_RSP_MSG_HEADER_LEN;
            iRet = GORM_PACK_RSP_ERROR;
        }
    }
    else
    {
        pRspData = GORM_MemPool::Instance()->GetData(GORM_RSP_MSG_HEADER_LEN);
    }

    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_BATCH_GET, this->uiReqID, iRet, cReplyFlag);
    
    return GORM_OK;
}


int GORM_MySQLRequest::PackGetByPartkeyResult()
{
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr)
    {
        GORM_PB_GET_BY_PARTKEY_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_GET_BY_PARTKEY_RSP*>(pRspPbMsg);
        GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
        this->PackPbRetCode(retCode);
        iLen += pRspPackPbMsg->ByteSizeLong();
        pRspData = GORM_MemPool::Instance()->GetData(iLen);
        if (pRspData == nullptr)
        {
            this->iErrCode = GORM_PACK_RSP_ERROR;
            return GORM_ERROR;
        }
        if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
        {
            iLen = GORM_RSP_MSG_HEADER_LEN;
            iRet = GORM_PACK_RSP_ERROR;
        }
    }
    else
    {
        pRspData = GORM_MemPool::Instance()->GetData(GORM_RSP_MSG_HEADER_LEN);
    }

    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_GET_BY_PARTKEY, this->uiReqID, iRet, cReplyFlag);
    
    return GORM_OK;
}


int GORM_MySQLRequest::PackUpdateResult()
{
    int iLen = GORM_RSP_MSG_HEADER_LEN;
    int iRet = GORM_OK;
    if (pRspPbMsg != nullptr)
    {
        GORM_PB_UPDATE_RSP *pRspPackPbMsg = dynamic_cast<GORM_PB_UPDATE_RSP*>(pRspPbMsg);
        GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
        this->PackPbRetCode(retCode);
        iLen += pRspPackPbMsg->ByteSizeLong();
        pRspData = GORM_MemPool::Instance()->GetData(iLen);
        if (pRspData == nullptr)
        {
            this->iErrCode = GORM_PACK_RSP_ERROR;
            return GORM_ERROR;
        }
        if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
        {
            iLen = GORM_RSP_MSG_HEADER_LEN;
            iRet = GORM_PACK_RSP_ERROR;
        }
    }
    else
    {
        pRspData = GORM_MemPool::Instance()->GetData(GORM_RSP_MSG_HEADER_LEN);
    }

    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_UPDATE, this->uiReqID, iRet, cReplyFlag);
    
    return GORM_OK;
}

int GORM_MySQLRequest::PackHeartBeatResult()
{
    if (pRspData != nullptr)
    {
        return GORM_OK;
    }
    int iLen = GORM_RSP_MSG_HEADER_LEN;

    GORM_PB_UPDATE_RSP *pRspPackPbMsg = new GORM_PB_UPDATE_RSP();
    if (pRspPackPbMsg == nullptr)
        return GORM_ERROR;
    GORM_PB_Ret_Code *retCode = pRspPackPbMsg->mutable_retcode();
    this->PackPbRetCode(retCode);
    iLen += pRspPackPbMsg->ByteSizeLong();
    pRspData = GORM_MemPool::Instance()->GetData(iLen);
    if (!pRspPackPbMsg->SerializeToArray(pRspData->m_uszData+GORM_RSP_MSG_HEADER_LEN, iLen-GORM_RSP_MSG_HEADER_LEN) )
    {
        delete pRspPackPbMsg;
        return GORM_ERROR;
    }
    
    pRspData->m_sUsedSize = iLen;
    GORM_SetRspHeader(pRspData->m_uszData, iLen, GORM_CMD_HEART, 0, GORM_OK, 0);
    
    return GORM_OK;
}

void GORM_MySQLRequest::Release()
{
    if (this->staticRequest == 1)
        return;
    GORM_DBRequest::Release();

    this->m_pMySqlEvent = nullptr;

    // TODO 回收再利用
    delete this;
}

int GORM_MySQLRequest::PackSQL()
{
    int iReqCmd = this->iReqCmd;
    if (this->iRedirectCmd != GORM_CMD_INVALID)
    {
        if (this->iRedirectCmd == GORM_CMD_GET)
        {
            if (this->pNowReqProcTable == nullptr)
            {
                GORM_LOGE("pack sql, has no request table, %d", iReqCmd);
                return GORM_REQ_MSG_ERROR;
            }
            GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);
            uiHashValue = GORM_TableHash(iReqTableId, *pNowReqProcTable);
            if (GORM_OK != GORM_PackGetSQLTable(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, uiHashValue, *pNowReqProcTable, pReqData))
            {
                GORM_LOGE("pack insert sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
                return GORM_ERROR;
            }
        } 
        else if (this->iRedirectCmd == GORM_CMD_INSERT)
        {
            if (this->pNowReqProcTable == nullptr)
            {
                GORM_LOGE("pack sql, has no request table, %d", iReqCmd);
                return GORM_REQ_MSG_ERROR;
            }
            GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);
            uiHashValue = GORM_TableHash(iReqTableId, *pNowReqProcTable);
            if (GORM_OK != GORM_PackInsertSQLTable(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, uiHashValue, *pNowReqProcTable, pReqData))
            {
                GORM_LOGE("pack insert sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
                return GORM_ERROR;
            }
        }
        
        return GORM_OK;
    }

    if (this->pReqData != nullptr)
        this->pReqData->Release();
    switch ((iReqCmd))
    {
    case GORM_CMD_INSERT:
    {
        int iRet = this->InsertReq();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack insert sql failed, , tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_REPLACE:
    {
        int iRet = this->ReplaceReq();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack replace sql failed, , tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_INCREASE:
    {
        int iRet = this->IncreaseReq();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack increase sql failed, , tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_GET:
    {
        int iRet = this->GetReq();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack get sql failed, , tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_DELETE:
    {
        int iRet = this->DeleteReq();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack delete sql failed, , tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        int iRet = this->BatchGetNext();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack batch_get sql failed, , tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        int iRet = this->DeleteReq();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack get_by_partkey sql failed, , tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_UPDATE:
    {
        int iRet = this->UpdateReq();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack update sql failed, , tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        int iRet = this->GetByNonPrimaryKey();
        if (iRet != GORM_OK)
        {
            GORM_LOGE("pack get by non primary key sql failed, , tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    default:
    {
        this->iErrCode = GORM_NOT_SUPPORT_CMD;
        GORM_LOGE("invalid req cmd:%d", iReqCmd);
        return GORM_NOT_SUPPORT_CMD;
    }
    }
    return GORM_OK;
}

int GORM_MySQLRequest::InsertReq()
{
    const gorm::GORM_PB_INSERT_REQ *pReqMsg = dynamic_cast<GORM_PB_INSERT_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);

    GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);

    if (!pReqMsg->has_header())
    {
        GORM_LOGE("insert request has no header.");
        return GORM_REQ_MSG_ERROR;
    }
    this->pHeader = (gorm::GORM_PB_REQ_HEADER*)&(pReqMsg->header());

    if (pReqMsg->tables_size() == 0)
    {
        GORM_LOGE("insert request has no table.");
        return GORM_REQ_NO_RECORDS;
    }
        
    if (nullptr == this->pNowReqProcTable)
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(0));
    
    if (GORM_OK != GORM_PackInsertSQL(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, this->uiHashValue, pReqMsg, pReqData))
    {
        GORM_LOGE("pack insert sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
        return GORM_ERROR;
    }
    GORM_LOGD("insert sql:%s", this->pReqData->m_uszData);
    return GORM_OK;
}

int GORM_MySQLRequest::ReplaceReq()
{
    const gorm::GORM_PB_REPLACE_REQ *pReqMsg = dynamic_cast<GORM_PB_REPLACE_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);

    GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);

    if (!pReqMsg->has_header())
        return GORM_REQ_MSG_ERROR;
    this->pHeader = (gorm::GORM_PB_REQ_HEADER*)&(pReqMsg->header());

    if (pReqMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;
    if (nullptr == this->pNowReqProcTable)
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(0));

    
    if (GORM_OK != GORM_PackReplaceSQL(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, this->uiHashValue, pReqMsg, pReqData))
    {
        GORM_LOGE("pack replace sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
        return GORM_ERROR;
    }
    GORM_LOGD("replace sql:%s", this->pReqData->m_uszData);
    return GORM_OK;
}


int GORM_MySQLRequest::IncreaseReq()
{
    const gorm::GORM_PB_INCREASE_REQ *pReqMsg = dynamic_cast<GORM_PB_INCREASE_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);

    if (!pReqMsg->has_header())
        return GORM_REQ_MSG_ERROR;
    this->pHeader = (gorm::GORM_PB_REQ_HEADER*)&(pReqMsg->header());

    if (pReqMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;
    if (nullptr == this->pNowReqProcTable)
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(0));
    
    GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);
    if (GORM_OK != GORM_PackIncreaseSQL(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, this->uiHashValue, pReqMsg, pReqData))
    {
        GORM_LOGE("pack insert sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
        return GORM_ERROR;
    }
    GORM_LOGD("insert sql:%s", this->pReqData->m_uszData);
    return GORM_OK;
}


int GORM_MySQLRequest::GetReq()
{
    const gorm::GORM_PB_GET_REQ *pReqMsg = dynamic_cast<GORM_PB_GET_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);
    if (!pReqMsg->has_table())
    {
        GORM_LOGE("get request has no request table.");
        return GORM_REQ_NO_RECORDS;
    }
    if (!pReqMsg->has_header())
    {
        GORM_LOGE("get request has no request header.");
        return GORM_REQ_MSG_ERROR;
    }
    this->pHeader = (gorm::GORM_PB_REQ_HEADER*)&(pReqMsg->header());
    if (nullptr == this->pNowReqProcTable)
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->table());
    
    // TODO 放在dbpool中做，也就是放在work线程中做
    GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);
    if (GORM_OK != GORM_PackGetSQL(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, this->uiHashValue, pReqMsg, pReqData))
    {
        GORM_LOGE("pack insert sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
        return GORM_ERROR;
    }
    GORM_LOGD("insert sql:%s", this->pReqData->m_uszData);
    return GORM_OK;
}


int GORM_MySQLRequest::DeleteReq()
{
    const gorm::GORM_PB_DELETE_REQ *pReqMsg = dynamic_cast<GORM_PB_DELETE_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);

    GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);
    if (GORM_OK != GORM_PackDeleteSQL(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, this->uiHashValue, pReqMsg, pReqData))
    {
        GORM_LOGE("pack insert sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
        return GORM_ERROR;
    }
    GORM_LOGD("insert sql:%s", this->pReqData->m_uszData);
    return GORM_OK;
}

// TODO 可能包含多个路由
int GORM_MySQLRequest::BatchGetReq()
{
    const gorm::GORM_PB_BATCH_GET_REQ *pReqMsg = dynamic_cast<GORM_PB_BATCH_GET_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);

    if(!pReqMsg->has_header())
    {
        GORM_LOGE("request message has no header info, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
        return GORM_REQ_MSG_ERROR;
    }
    if (pReqMsg->tables_size() < 1)
    {
        GORM_LOGE("request message has no data, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
        return GORM_REQ_MSG_ERROR;
    }

    const GORM_PB_REQ_HEADER &header = pReqMsg->header();
    iReqTableId = header.tableid();
    this->iReqNum = pReqMsg->tables_size();

    const GORM_PB_TABLE &table = pReqMsg->tables(this->iGotRspNum);
    return GORM_OK;
}

int GORM_MySQLRequest::BatchGetNext()
{
    if (this->iGotRspNum >= this->iReqNum)
    {
        GORM_LOGE("batch get has got all data, tableid:%d, reqid:%u", this->iReqTableId, this->uiReqID);
        return GORM_ERROR;
    }

    const gorm::GORM_PB_BATCH_GET_REQ *pReqMsg = dynamic_cast<GORM_PB_BATCH_GET_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);
    const GORM_PB_TABLE &table = pReqMsg->tables(this->iGotRspNum);
    GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);

    if (!pReqMsg->has_header())
        return GORM_REQ_MSG_ERROR;
    this->pHeader = (gorm::GORM_PB_REQ_HEADER*)&(pReqMsg->header());

    if (pReqMsg->tables_size() == 0)
        return GORM_REQ_NO_RECORDS;
    if (nullptr == this->pNowReqProcTable)
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(this->iGotRspNum));

    if (GORM_OK != GORM_PackGetSQLTable(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, this->uiHashValue, table, pReqData))
    {
        GORM_LOGE("pack insert sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
        return GORM_ERROR;
    }
    GORM_LOGD("batch get sql:%s", this->pReqData->m_uszData);
    return GORM_OK;
}

int GORM_MySQLRequest::GetByPartKeyReq()
{
    const gorm::GORM_PB_GET_BY_PARTKEY_REQ *pReqMsg = dynamic_cast<GORM_PB_GET_BY_PARTKEY_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);

    if(!pReqMsg->has_header())
    {
        GORM_LOGE("request message has no header info, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
        return GORM_REQ_MSG_ERROR;
    }
    if (pReqMsg->tables_size() < 1)
    {
        GORM_LOGE("request message has no data, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
        return GORM_REQ_MSG_ERROR;
    }

    const GORM_PB_REQ_HEADER &header = pReqMsg->header();
    iReqTableId = header.tableid();
    this->iReqNum = pReqMsg->tables_size();
    
    const GORM_PB_TABLE &table = pReqMsg->tables(this->iGotRspNum);
    //return this->BatchGetNext(header, table);
    return GORM_OK;
}

int GORM_MySQLRequest::UpdateReq()
{
    const gorm::GORM_PB_UPDATE_REQ *pReqMsg = dynamic_cast<GORM_PB_UPDATE_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);

    if (!pReqMsg->has_header())
    {
        GORM_LOGE("insert request has no header.");
        return GORM_REQ_MSG_ERROR;
    }
    this->pHeader = (gorm::GORM_PB_REQ_HEADER*)&(pReqMsg->header());

    if (pReqMsg->tables_size() == 0)
    {
        GORM_LOGE("insert request has no table.");
        return GORM_REQ_NO_RECORDS;
    }
    if (nullptr == this->pNowReqProcTable)
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(0));

    GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);
    if (GORM_OK != GORM_PackUpdateSQL(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, this->uiHashValue, pReqMsg, pReqData))
    {
        GORM_LOGE("pack insert sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
        return GORM_ERROR;
    }
    GORM_LOGD("update sql:%s", this->pReqData->m_uszData);
    return GORM_OK;
}

int GORM_MySQLRequest::GetByNonPrimaryKey()
{
    const gorm::GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ *pReqMsg = dynamic_cast<GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ*>(pReqPbMsg);
    ASSERT(pReqMsg!=nullptr);

    if (!pReqMsg->has_header())
    {
        GORM_LOGE("get by non primary key request has no header.");
        return GORM_REQ_MSG_ERROR;
    }
    this->pHeader = (gorm::GORM_PB_REQ_HEADER*)&(pReqMsg->header());

    if (pReqMsg->tables_size() == 0)
    {
        GORM_LOGE("get by non primary key request has no table.");
        return GORM_REQ_NO_RECORDS;
    }
    if (nullptr == this->pNowReqProcTable)
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(0));

    GORM_MySQLConnPool *pMySQLPool = dynamic_cast<GORM_MySQLConnPool*>(this->pDbPool);
    if (GORM_OK != GORM_PackGet_By_Non_Primary_KeySQL(pMySQLPool->m_pEvent, pMySQLPool->m_pEvent->m_pMySQL, iReqTableId, this->uiHashValue, pReqMsg, pReqData))
    {
        GORM_LOGE("pack insert sql failed, tableid:%d, reqid:%ud", iReqTableId, uiReqID);
        return GORM_ERROR;
    }
    GORM_LOGD("get by non primary key sql:%s", this->pReqData->m_uszData);
    return GORM_OK;
}


