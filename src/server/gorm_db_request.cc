#include "gorm_db_request.h"
#include "gorm_mempool.h"
#include "gorm_db_conn_pool.h"
#include "gorm_log.h"
#include "gorm_msg_helper.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_frontend_thread.h"
#include "gorm_work_thread.h"
#include "gorm_table_field_map_define.h"

using namespace gorm;
GORM_DBRequest::GORM_DBRequest(shared_ptr<GORM_MemPool> &pMemPool):pMemPool(pMemPool)
{
    iGotRspNum = 0;
    iReqNum = 1;
    uiHashValue = 0;
    this->pRspData = pMemPool->GetData(GORM_DEFAULT_RSP_DATA_LEN);
}

GORM_DBRequest::~GORM_DBRequest()
{
    this->pMemPool = nullptr;
}

void GORM_DBRequest::ResetMemPool(shared_ptr<GORM_MemPool> &pMemPool)
{
    this->pMemPool = nullptr;
    this->pMemPool = pMemPool;
    GORM_Reset_MemData_MemPool(this->pReqSQLData, pMemPool);
    GORM_Reset_MemData_MemPool(this->pDbErrorInfo, pMemPool);
    GORM_Reset_MemData_MemPool(this->pRspData, pMemPool);
}

#define GORM_PARSE_REQ_PB_MSG()                                     \
if (nullptr == pReqMsg)                                             \
{                                                                   \
    GORM_LOGE("parse input buffer failed.");                        \
    return GORM_ERROR;                                              \
}                                                                   \
if (!pReqMsg->ParseFromArray(szMsg, iMsgLen-GORM_REQ_MSG_HEADER_LEN))\
{                                                                   \
    GORM_LOGE("parse input buffer failed.");                        \
    return GORM_UNPACK_REQ;                                         \
}                                                                   \
this->pReqPbMsg = pReqMsg;                                          \
const GORM_PB_REQ_HEADER &header = pReqMsg->header();               \
iReqTableId = header.tableid();                                     \
uiReqFlag   = header.reqflag();                                     \
if ((uiReqFlag & GORM_REQ_FLAG_RETURN_NEW_VALUE) > 0)               \
    cReplyFlag = GORM_ResultFlag_RETURN_NEW_VALUE;                  \
else if ((uiReqFlag & GORM_REQ_FLAG_RETURN_ALL_VALUE) > 0)          \
    cReplyFlag = GORM_ResultFlag_RETURN_ALL_VALUE;                  \
if ((uiReqFlag&GORM_REQ_FLAG_EMPTY_INCREASE) > 0)                   \
    increaseFlag = GORM_IncreaseFlag_AutoCreate;

int GORM_DBRequest::SendToWorkThread()
{
#ifdef GORM_DEBUG
    this->ulReqTimeMS = GORM_GetNowMS();
#endif
    if (this->iGotRspNum >= this->iReqNum)
    {
        return GORM_OK;
    }
    // TODO 将请求路由到后端的
    switch (this->iReqCmd)
    {
    case GORM_CMD_INSERT:
    {
        this->iSentToWorkThread = 1;
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_INSERT_REQ *pReqMsg = nullptr;
        pReqMsg = dynamic_cast<gorm::GORM_PB_INSERT_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg != nullptr);

        uiHashValue = GORM_TableHash(iReqTableId, pReqMsg->tables(0));
        
        int iRet = GORM_WorkThreadPool::Instance()->PublishRequestToDB(iReqTableId, uiHashValue, this->pWorkThread);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("process insert message, get db failed, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_REPLACE:
    {
        this->iSentToWorkThread = 1;
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_REPLACE_REQ *pReqMsg = nullptr;
        pReqMsg = dynamic_cast<gorm::GORM_PB_REPLACE_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg != nullptr);

        uiHashValue = GORM_TableHash(iReqTableId, pReqMsg->tables(0));
        
        int iRet = GORM_WorkThreadPool::Instance()->PublishRequestToDB(iReqTableId, uiHashValue, this->pWorkThread);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("process replace message, get db failed, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_INCREASE:
    {
        this->iSentToWorkThread = 1;
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_INCREASE_REQ *pReqMsg = nullptr;
        pReqMsg = dynamic_cast<gorm::GORM_PB_INCREASE_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg != nullptr);

        uiHashValue = GORM_TableHash(iReqTableId, pReqMsg->tables(0));
        
        int iRet = GORM_WorkThreadPool::Instance()->PublishRequestToDB(iReqTableId, uiHashValue, this->pWorkThread);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("process increase message, get db failed, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_GET:
    {
        this->iSentToWorkThread = 1;
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_GET_REQ *pReqMsg = nullptr;
        pReqMsg = dynamic_cast<gorm::GORM_PB_GET_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg != nullptr);

        uiHashValue = GORM_TableHash(iReqTableId, pReqMsg->table());
        
        int iRet = GORM_WorkThreadPool::Instance()->PublishRequestToDB(iReqTableId, uiHashValue, this->pWorkThread);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("process get message, get db failed, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_DELETE:
    {
        this->iSentToWorkThread = 1;
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_DELETE_REQ *pReqMsg = nullptr;
        pReqMsg = dynamic_cast<gorm::GORM_PB_DELETE_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg != nullptr);

        uiHashValue = GORM_TableHash(iReqTableId, pReqMsg->table());
        
        int iRet = GORM_WorkThreadPool::Instance()->PublishRequestToDB(iReqTableId, uiHashValue, this->pWorkThread);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("process delete message, get db failed, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_BATCH_GET_REQ *pReqMsg = nullptr;
        pReqMsg = dynamic_cast<gorm::GORM_PB_BATCH_GET_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg != nullptr);

        const GORM_PB_TABLE &table = pReqMsg->tables(this->iGotRspNum);
        uiHashValue = GORM_TableHash(iReqTableId, table);

        ASSERT(this->iGotRspNum < this->iReqNum);
        int iRet = GORM_WorkThreadPool::Instance()->PublishRequestToDB(iReqTableId, uiHashValue, this->pWorkThread);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("process insert message, get db failed, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_GET_BY_PARTKEY_REQ *pReqMsg = nullptr;
        pReqMsg = dynamic_cast<gorm::GORM_PB_GET_BY_PARTKEY_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg != nullptr);

        const GORM_PB_TABLE &table = pReqMsg->tables(this->iGotRspNum);
        uiHashValue = GORM_TableHash(iReqTableId, table);

        ASSERT(this->iGotRspNum < this->iReqNum);
        int iRet = GORM_WorkThreadPool::Instance()->PublishRequestToDB(iReqTableId, uiHashValue, this->pWorkThread);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("process insert message, get db failed, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_UPDATE:
    {
        this->iSentToWorkThread = 1;
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_UPDATE_REQ *pReqMsg = nullptr;
        pReqMsg = dynamic_cast<gorm::GORM_PB_UPDATE_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg != nullptr);

        uiHashValue = GORM_TableHash(iReqTableId, pReqMsg->tables(0));
        
        int iRet = GORM_WorkThreadPool::Instance()->PublishRequestToDB(iReqTableId, uiHashValue, this->pWorkThread);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("process update message, get db failed, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
            return iRet;
        }
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ *pReqMsg = nullptr;
        pReqMsg = dynamic_cast<gorm::GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg != nullptr);

        const GORM_PB_TABLE &table = pReqMsg->tables(this->iGotRspNum);
        uiHashValue = GORM_TableHash(iReqTableId, table);

        ASSERT(this->iGotRspNum < this->iReqNum);
        int iRet = GORM_WorkThreadPool::Instance()->PublishRequestToDB(iReqTableId, uiHashValue, this->pWorkThread);
        if (iRet != GORM_OK)
        {
            GORM_LOGE("process insert message, get db failed, tableid:%d, reqid:%ud", this->iReqTableId, this->uiReqID);
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


    return this->pWorkThread->AccepNewRequest(this);
}


// 读取请求先查找请求
int GORM_DBRequest::ParseReqMsg(char *szMsg, int iMsgLen)
{
    // TODO 将请求路由到后端的
    switch (this->iReqCmd)
    {
    case GORM_CMD_INSERT:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_INSERT_REQ *pReqMsg = nullptr;
        if (szMsg != nullptr && iMsgLen > 0)
        {
            pReqMsg = new gorm::GORM_PB_INSERT_REQ();
            GORM_PARSE_REQ_PB_MSG();

            this->iReqNum = pReqMsg->tables_size();
            if (this->iReqNum == 0)
            {
                this->GetResult(GORM_REQ_NO_RECORDS);
                return GORM_OK;
            }
        } 
        
        break;
    }
    case GORM_CMD_REPLACE:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_REPLACE_REQ *pReqMsg = nullptr;
        if (szMsg != nullptr && iMsgLen > 0)
        {
            pReqMsg = new gorm::GORM_PB_REPLACE_REQ();
            GORM_PARSE_REQ_PB_MSG();

            this->iReqNum = pReqMsg->tables_size();
            if (this->iReqNum == 0)
            {
                this->GetResult(GORM_REQ_NO_RECORDS);
                return GORM_OK;
            }
        }
        else
        {
            pReqMsg = dynamic_cast<gorm::GORM_PB_REPLACE_REQ*>(pReqPbMsg);
        }
        ASSERT(pReqMsg != nullptr);
        
        break;
    }
    case GORM_CMD_INCREASE:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_INCREASE_REQ *pReqMsg = nullptr;
        if (szMsg != nullptr && iMsgLen > 0)
        {
            pReqMsg = new gorm::GORM_PB_INCREASE_REQ();
            GORM_PARSE_REQ_PB_MSG();

            this->iReqNum = pReqMsg->tables_size();
            if (this->iReqNum == 0)
            {
                this->GetResult(GORM_REQ_NO_RECORDS);
                return GORM_OK;
            }
        }
        else
        {
            pReqMsg = dynamic_cast<gorm::GORM_PB_INCREASE_REQ*>(pReqPbMsg);
        }
        ASSERT(pReqMsg != nullptr);
        
        break;
    }
    case GORM_CMD_GET:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_GET_REQ *pReqMsg = nullptr;
        if (szMsg != nullptr && iMsgLen > 0)
        {
            pReqMsg = new gorm::GORM_PB_GET_REQ();
            GORM_PARSE_REQ_PB_MSG();

            if (!pReqMsg->has_table())
            {
                this->GetResult(GORM_REQ_NO_RECORDS);
                return GORM_OK;
            }
        }
        else
        {
            pReqMsg = dynamic_cast<gorm::GORM_PB_GET_REQ*>(pReqPbMsg);
        }
        ASSERT(pReqMsg != nullptr);
        if (pReqMsg->getflag() == 1)
            this->iGetFlag = GORM_GET_FLAG_NON_INSERT;
        
        break;
    }
    case GORM_CMD_DELETE:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_DELETE_REQ *pReqMsg = nullptr;
        if (szMsg != nullptr && iMsgLen > 0)
        {
            pReqMsg = new gorm::GORM_PB_DELETE_REQ();
            GORM_PARSE_REQ_PB_MSG();

            if (!pReqMsg->has_table())
            {
                this->GetResult(GORM_REQ_NO_RECORDS);
                return GORM_OK;
            }
        }
        else
        {
            pReqMsg = dynamic_cast<gorm::GORM_PB_DELETE_REQ*>(pReqPbMsg);
        }
        ASSERT(pReqMsg != nullptr);
        
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_BATCH_GET_REQ *pReqMsg = nullptr;
        if (szMsg != nullptr && iMsgLen > 0)
        {
            pReqMsg = new gorm::GORM_PB_BATCH_GET_REQ();
            GORM_PARSE_REQ_PB_MSG();
        
            this->iReqNum = pReqMsg->tables_size();
            if (this->iReqNum == 0)
            {
                this->GetResult(GORM_REQ_NO_RECORDS);
                return GORM_OK;
            }
        }
        else
        {
            pReqMsg = dynamic_cast<gorm::GORM_PB_BATCH_GET_REQ*>(pReqPbMsg);
        }
        ASSERT(pReqMsg != nullptr);

        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_GET_BY_PARTKEY_REQ *pReqMsg = nullptr;
        if (szMsg != nullptr && iMsgLen > 0)
        {
            pReqMsg = new gorm::GORM_PB_GET_BY_PARTKEY_REQ();
            GORM_PARSE_REQ_PB_MSG();
        
            this->iReqNum = pReqMsg->tables_size();
            if (this->iReqNum == 0)
            {
                this->GetResult(GORM_REQ_NO_RECORDS);
                return GORM_OK;
            }
        }
        else
        {
            pReqMsg = dynamic_cast<gorm::GORM_PB_GET_BY_PARTKEY_REQ*>(pReqPbMsg);
        }
        ASSERT(pReqMsg != nullptr);

        break;
    }
    case GORM_CMD_UPDATE:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_UPDATE_REQ *pReqMsg = nullptr;
        if (szMsg != nullptr && iMsgLen > 0)
        {
            pReqMsg = new gorm::GORM_PB_UPDATE_REQ();
            GORM_PARSE_REQ_PB_MSG();
            
            this->iReqNum = pReqMsg->tables_size();
            if (this->iReqNum == 0)
            {
                this->GetResult(GORM_REQ_NO_RECORDS);
                return GORM_OK;
            }
        }
        else
        {
            pReqMsg = dynamic_cast<gorm::GORM_PB_UPDATE_REQ*>(pReqPbMsg);
        }
        ASSERT(pReqMsg != nullptr);
        
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        // 1、解码获取结构体, TODO 内存池
        gorm::GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ *pReqMsg = nullptr;
        if (szMsg != nullptr && iMsgLen > 0)
        {
            pReqMsg = new gorm::GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ();
            GORM_PARSE_REQ_PB_MSG();
            
            this->iReqNum = pReqMsg->tables_size();
            if (this->iReqNum == 0)
            {
                this->GetResult(GORM_REQ_NO_RECORDS);
                return GORM_OK;
            }
        }
        else
        {
            pReqMsg = dynamic_cast<gorm::GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ*>(pReqPbMsg);
        }
        ASSERT(pReqMsg != nullptr);
        
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

int GORM_DBRequest::AddTableToRsp()
{
    if (pNowRspProcTable != nullptr)
        return GORM_OK;
    // 根据请求的组装返回的结果
    // 更新请求也可能因为需要回带结果而需要组装结果数据
    switch (iReqCmd)
    {
    case GORM_CMD_INSERT:
    {
        int iRet = GORM_OK;
        if (pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(iReqCmd, this->pRspPbMsg))
        {
            GORM_LOGE("malloc rsp pb message failed, tableid:%d, cmd:%d, seqid:%ud", iReqTableId, iReqCmd, this->uiReqID);
            return GORM_ERROR;
        }
        GORM_PB_INSERT_RSP *pGetPbRsp = dynamic_cast<GORM_PB_INSERT_RSP*>(this->pRspPbMsg);
        if (pNowRspProcTable == nullptr)
            pNowRspProcTable = pGetPbRsp->add_tables();
        break;
    }
    case GORM_CMD_UPDATE:
    {
        int iRet = GORM_OK;
        if (pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(iReqCmd, this->pRspPbMsg))
        {
            GORM_LOGE("malloc rsp pb message failed, tableid:%d, cmd:%d, seqid:%ud", iReqTableId, iReqCmd, this->uiReqID);
            return GORM_ERROR;
        }
        GORM_PB_UPDATE_RSP *pGetPbRsp = dynamic_cast<GORM_PB_UPDATE_RSP*>(this->pRspPbMsg);
        if (pNowRspProcTable == nullptr)
            pNowRspProcTable = pGetPbRsp->add_tables();
        break;
    }
    case GORM_CMD_INCREASE:
    {
        int iRet = GORM_OK;
        if (pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(iReqCmd, this->pRspPbMsg))
        {
            GORM_LOGE("malloc rsp pb message failed, tableid:%d, cmd:%d, seqid:%ud", iReqTableId, iReqCmd, this->uiReqID);
            return GORM_ERROR;
        }
        GORM_PB_INCREASE_RSP *pGetPbRsp = dynamic_cast<GORM_PB_INCREASE_RSP*>(this->pRspPbMsg);
        if (nullptr == pNowRspProcTable)
            pNowRspProcTable = pGetPbRsp->add_tables();
        break;
    }
    case GORM_CMD_REPLACE:
    {
        int iRet = GORM_OK;
        if (pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(iReqCmd, this->pRspPbMsg))
        {
            GORM_LOGE("malloc rsp pb message failed, tableid:%d, cmd:%d, seqid:%ud", iReqTableId, iReqCmd, this->uiReqID);
            return GORM_ERROR;
        }
        GORM_PB_REPLACE_RSP *pGetPbRsp = dynamic_cast<GORM_PB_REPLACE_RSP*>(this->pRspPbMsg);
        if (nullptr == pNowRspProcTable)
            pNowRspProcTable = pGetPbRsp->add_tables();
        break;
    }
    case GORM_CMD_GET:
    {
        int iRet = GORM_OK;
        if (pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(iReqCmd, this->pRspPbMsg))
        {
            GORM_LOGE("malloc rsp pb message failed, tableid:%d, cmd:%d, seqid:%ud", iReqTableId, iReqCmd, this->uiReqID);
            return GORM_ERROR;
        }
        GORM_PB_GET_RSP *pGetPbRsp = dynamic_cast<GORM_PB_GET_RSP*>(this->pRspPbMsg);
        if (pGetPbRsp->has_table())
        {
            GORM_LOGW("get cmd get more than 1 rows, tableid:%d, cmd:%d, seqid:%ud", iReqTableId, iReqCmd, uiReqID);
            return GORM_OK;
        }
        if (nullptr == pNowRspProcTable)
            pNowRspProcTable = pGetPbRsp->mutable_table();
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        int iRet = GORM_OK;
        if (pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(iReqCmd, this->pRspPbMsg))
        {
            GORM_LOGE("malloc rsp pb message failed, tableid:%d, cmd:%d, seqid:%ud", iReqTableId, iReqCmd, this->uiReqID);
            return GORM_ERROR;
        }
        GORM_PB_BATCH_GET_RSP *pGetPbRsp = dynamic_cast<GORM_PB_BATCH_GET_RSP*>(this->pRspPbMsg);
        if (nullptr == pNowRspProcTable)
            pNowRspProcTable = pGetPbRsp->add_tables();
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        int iRet = GORM_OK;
        if (pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(iReqCmd, this->pRspPbMsg))
        {
            GORM_LOGE("malloc rsp pb message failed, tableid:%d, cmd:%d, seqid:%ud", iReqTableId, iReqCmd, this->uiReqID);
            return GORM_ERROR;
        }
        GORM_PB_GET_BY_PARTKEY_RSP *pGetPbRsp = dynamic_cast<GORM_PB_GET_BY_PARTKEY_RSP*>(this->pRspPbMsg);
        if (nullptr == pNowRspProcTable)
            pNowRspProcTable = pGetPbRsp->add_tables();
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        int iRet = GORM_OK;
        if (pRspPbMsg == nullptr && GORM_OK != GetPbRspMsg(iReqCmd, this->pRspPbMsg))
        {
            GORM_LOGE("malloc rsp pb message failed, tableid:%d, cmd:%d, seqid:%ud", iReqTableId, iReqCmd, this->uiReqID);
            return GORM_ERROR;
        }
        GORM_PB_GET_BY_NON_PRIMARY_KEY_RSP *pGetPbRsp = dynamic_cast<GORM_PB_GET_BY_NON_PRIMARY_KEY_RSP*>(this->pRspPbMsg);
        if (nullptr == pNowRspProcTable)
            pNowRspProcTable = pGetPbRsp->add_tables();
        break;
    }
    default:
        GORM_LOGE("mysql result not support:%d", iReqCmd);
    }

    return GORM_OK;
}

int GORM_DBRequest::SetNowReqProcTable()
{
    if (pNowReqProcTable != nullptr)
        return GORM_OK;
    // 根据请求的组装返回的结果
    // 更新请求也可能因为需要回带结果而需要组装结果数据
    if (iGotRspNum >= iReqNum)
        return GORM_NO_MORE_RECORD;
    switch (iReqCmd)
    {
    case GORM_CMD_INSERT:
    {
        const gorm::GORM_PB_INSERT_REQ *pReqMsg = dynamic_cast<GORM_PB_INSERT_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg!=nullptr);
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(0));
        break;
    }
    case GORM_CMD_DELETE:
    {
        const gorm::GORM_PB_DELETE_REQ *pReqMsg = dynamic_cast<GORM_PB_DELETE_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg!=nullptr);
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->table());
        break;
    }
    case GORM_CMD_UPDATE:
    {
        const gorm::GORM_PB_UPDATE_REQ *pReqMsg = dynamic_cast<GORM_PB_UPDATE_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg!=nullptr);
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(0));
        break;
    }
    case GORM_CMD_INCREASE:
    {
        const gorm::GORM_PB_INCREASE_REQ *pReqMsg = dynamic_cast<GORM_PB_INCREASE_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg!=nullptr);
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(0));
        break;
    }
    case GORM_CMD_REPLACE:
    {
        const gorm::GORM_PB_REPLACE_REQ *pReqMsg = dynamic_cast<GORM_PB_REPLACE_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg!=nullptr);
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(0));
        break;
    }
    case GORM_CMD_GET:
    {
        const gorm::GORM_PB_GET_REQ *pReqMsg = dynamic_cast<GORM_PB_GET_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg!=nullptr);
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->table());
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        const gorm::GORM_PB_BATCH_GET_REQ *pReqMsg = dynamic_cast<GORM_PB_BATCH_GET_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg!=nullptr);

        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(iGotRspNum));
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        const gorm::GORM_PB_GET_BY_PARTKEY_REQ *pReqMsg = dynamic_cast<GORM_PB_GET_BY_PARTKEY_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg!=nullptr);
        
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(iGotRspNum));
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        const gorm::GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ *pReqMsg = dynamic_cast<GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ*>(pReqPbMsg);
        ASSERT(pReqMsg!=nullptr);
        
        this->pNowReqProcTable = (gorm::GORM_PB_TABLE*)&(pReqMsg->tables(iGotRspNum));
        break;
    }
    default:
        GORM_LOGE("mysql result not support:%d", iReqCmd);
    }

    return GORM_OK;
}

void GORM_DBRequest::GetAllResult(int iErrCode, int iDBErrNo, char *szErrInfo)
{
    // 打包响应数据
    if (GORM_OK != this->PackResult())
    {
        GORM_LOGE("pack result failed.");
    }

#ifdef GORM_DEBUG
    this->ulRspTimeMS = GORM_GetNowMS();
    GORM_LOGD("duration:%llu", this->ulRspTimeMS-this->ulReqTimeMS);
#endif
    // 将响应交给前端处理线程
    unique_lock<mutex> locker(m_Mutex);
    this->pFrontThread->GotResult(this);
}

// 打包，给前端线程返回响应
int GORM_DBRequest::GetResult(int iErrCode, int iDBErrNo, char *szErrInfo)
{
    // 操作数据库成功，刷新cache，操作完cache，不会再操作db，操作db是异步操作的
    /*if (iErrCode == GORM_OK && pCacheOpt != nullptr)
    {
        int iRet = pCacheOpt->UpdateCache(this);
        if (iRet != GORM_OK)
        {
            iErrCode = GORM_CACHE_ERROR;
            GORM_LOGE("operate db success but update cache failed, reqcmd:%d, tableid:%d, seqid:%d", this->iReqCmd, this->iReqTableId, this->uiReqID);
        }
    }*/
    this->SetDbErrInfo(iErrCode, iDBErrNo, szErrInfo);
    this->iGotRspNum += 1;
    if (this->iGotRspNum >= this->iReqNum)
        this->iWaitDone = 1;
    this->GetAllResult(iErrCode, iDBErrNo, szErrInfo);
    return GORM_GET_ALL_DATA;
}

void GORM_DBRequest::SetDbErrInfo(int iErrCode, int iDBErrNo, char *szErrInfo)
{
    this->iErrCode = iErrCode;
    this->iDBErrCode = iDBErrNo;
    if (iDBErrNo != 0 && szErrInfo != nullptr)
    {
        int iLen = strlen(szErrInfo);
        this->pDbErrorInfo = this->pMemPool->GetData(iLen);
        strncpy(this->pDbErrorInfo->m_uszData, szErrInfo, iLen);
        this->pDbErrorInfo->m_sUsedSize = iLen;
    }
}

void GORM_DBRequest::FinishSending2DB()
{
    if (pReqSQLData != nullptr)
    {
        pReqSQLData->Release();
        pReqSQLData = nullptr;
    }
}

void GORM_DBRequest::Release()
{
    if (this->staticRequest == 1)
        return;
    DelPbReqMsg(this->iReqCmd, this->pReqPbMsg);
    DelPbReqMsg(this->iReqCmd, this->pRspPbMsg);

    if (pReqSQLData != nullptr)
    {
        pReqSQLData->Release();
        pReqSQLData = nullptr;
    }
        
    if (pRspData != nullptr)
    {
        pRspData->Release();
        pRspData = nullptr;
    }
    if (pDbErrorInfo != nullptr)
    {
        pDbErrorInfo->Release();
        pDbErrorInfo = nullptr;
    }
}

void GORM_DBRequest::PackPbRetCode(GORM_PB_Ret_Code *pRetCode)
{
    pRetCode->set_code(this->iErrCode);
    pRetCode->set_dbcode(iDBErrCode);
    if (pDbErrorInfo != nullptr && pDbErrorInfo->m_sUsedSize>0)
        pRetCode->set_dberrinfo(pDbErrorInfo->m_uszData, pDbErrorInfo->m_sUsedSize);
}

