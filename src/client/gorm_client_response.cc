#include "gorm_client_response.h"
#include "gorm_table_field_map.h"
#include "gorm_client_request.h"
#include "gorm_table_field_map_define.h"


namespace gorm{

GORM_ClientResponse::GORM_ClientResponse(GORM_Log *pLogger):pLogger(pLogger)
{
}

GORM_ClientResponse::~GORM_ClientResponse()
{
}

void GORM_ClientResponse::Release()
{
    if (this->pRequest != nullptr)
    {
        this->pRequest->Release();
        this->pRequest = nullptr;
    }
    if (this->pRecords != nullptr)
    {
        delete []this->pRecords;
        this->pRecords = nullptr;
    }
    if (this->pResponsePbMsg != nullptr)
    {
        DelPbRspMsg(this->iReqCmd, this->pResponsePbMsg);
    }
        
    delete this;
}

int GORM_ClientResponse::GetTableName(char *&pTableName)
{
    if (iTableNum > 1)
    {
        return GORM_MULTI_TABLES;
    }

    return GORM_GetTableName(iTableId, pTableName);
}

int GORM_ClientResponse::GetResultCode(GROM_ResponseCode *&pRetCode)
{
    pRetCode = &this->rspCode;
    return GORM_OK;
}

uint32 GORM_ClientResponse::GetCBID()
{
    return this->ulCBID;
}

GORM_CMD GORM_ClientResponse::GetCmd()
{
    return this->iReqCmd;
}

GORM_ResultFlag GORM_ClientResponse::GetResultFlag() const
{
    return this->cResultFlag;
}

GORM_IncreaseFlag GORM_ClientResponse::GetAddableIncreaseFlag() const
{
    return this->increaseFlag;
}

int GORM_ClientResponse::GetRecord(OUT GORM_Record *&pPbMsg)
{
    if (this->iReturnRecordNum == 0)
        return GORM_NO_MORE_RECORD;
    pPbMsg = nullptr;
    pPbMsg = &(this->pRecords[0]);
    return GORM_OK;
}

int GORM_ClientResponse::GetRecord(IN int iIdx, OUT GORM_Record *&pPbMsg)
{
    if (this->iReturnRecordNum == 0)
        return GORM_NO_MORE_RECORD;
    pPbMsg = &(this->pRecords[0]);
    return GORM_OK;
}

int GORM_ClientResponse::GetRecord(OUT GORM_Record *&pPbMsg, OUT int &iRecordNum)
{
    pPbMsg = this->pRecords;
    iRecordNum = this->iReturnRecordNum;
    return GORM_OK;
}

int GORM_ClientResponse::GetNextRecord(OUT GORM_Record *&pPbMsg)
{
    if (iReadIdx >= this->iReturnRecordNum)
        return GORM_NO_MORE_RECORD;
    pPbMsg = &(this->pRecords[iReadIdx]);
    ++iReadIdx;
    return GORM_OK;
}

int GORM_ClientResponse::GetReturnFields(vector<int> &returnFields)
{
    if (this->pRequest == nullptr )
    {
        return GORM_ERROR;
    }

    const GORM_FieldsOpt &pFieldMode = this->pRequest->FieldMode();
    returnFields = GORM_FieldsOpt::GetFields(pFieldMode.szFieldCollections, pFieldMode.iUsedIdx);
    return GORM_OK;
}

int GORM_ClientResponse::GetReturnFields(vector<char*> &returnFields)
{
    if (this->pRequest == nullptr )
    {
        return GORM_ERROR;
    }

    const GORM_FieldsOpt &pFieldMode = this->pRequest->FieldMode();
    vector<int> vFieldList = GORM_FieldsOpt::GetFields(pFieldMode.szFieldCollections, pFieldMode.iUsedIdx);
    char *szFieldName = nullptr;
    for (auto iFieldId : vFieldList)
    {
        if (GORM_OK != GORM_GetFieldName(iTableId, iFieldId, szFieldName))
        {
            return GORM_ERROR;
        }
        returnFields.push_back(szFieldName);
    }
    return GORM_OK;
}

uint64 GORM_ClientResponse::GetInsertID()
{
    return this->ulInsertId;
}

int32 GORM_ClientResponse::GetRecordCount()
{
    return iReturnRecordNum;
}

int32 GORM_ClientResponse::GetAffectedRecordNum()
{
    return this->iAffectedNum;
}

int GORM_ClientResponse::UnPack(char *szMsg, int iLen)
{
    this->szRspBegin = szMsg;
    this->iRspLen = iLen;
    // TODO 对rsp解包
    GORM_GetRspHeader(szMsg+GORM_MSG_LEN_BYTE, this->iReqCmd, ulCBID, cPreErrCode, cPreFlag);
    if (cPreErrCode != GORM_OK)
    {
        this->rspCode.code = cPreErrCode;
        return GORM_OK;
    }
    if (iLen <= GORM_RSP_MSG_HEADER_LEN)
    {
        if (iReqCmd == GORM_CMD_HEART)
        {
            // TODO 处理心跳
        }
        return GORM_OK;
    }
    iTableId = pRequest->GetTableId();
    iReqCmd = pRequest->GetCmd();
    if (GORM_OK != GetPbRspMsg(iReqCmd, this->pResponsePbMsg))
    {
        this->cPreErrCode = GORM_RSP_UNPACK_FAILED;
        return GORM_OK;
    }
    switch (iReqCmd)
    {
    case GORM_CMD_HEART:
    {
        break;
    }
    case GORM_CMD_INSERT:
    {
        if (GORM_OK != this->UnPackInsert())
        {
            cPreErrCode = GORM_RSP_UNPACK_FAILED;
        }
        break;
    }
    case GORM_CMD_REPLACE:
    {
        if (GORM_OK != this->UnPackReplace())
        {
            cPreErrCode = GORM_RSP_UNPACK_FAILED;
        }
        break;
    }
    case GORM_CMD_INCREASE:
    {
        if (GORM_OK != this->UnPackIncrease())
        {
            cPreErrCode = GORM_RSP_UNPACK_FAILED;
        }
        break;
    }
    case GORM_CMD_GET:
    {
        if (GORM_OK != this->UnPackGet())
        {
            cPreErrCode = GORM_RSP_UNPACK_FAILED;
        }
        break;
    }
    case GORM_CMD_DELETE:
    {
        if (GORM_OK != this->UnPackDelete())
        {
            cPreErrCode = GORM_RSP_UNPACK_FAILED;
        }
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        if (GORM_OK != this->UnPackBatchGet())
        {
            cPreErrCode = GORM_RSP_UNPACK_FAILED;
        }
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        if (GORM_OK != this->UnPackGetByPartKey())
        {
            cPreErrCode = GORM_RSP_UNPACK_FAILED;
        }
        break;
    }
    case GORM_CMD_UPDATE:
    {
        if (GORM_OK != this->UnPackUpdate())
        {
            cPreErrCode = GORM_RSP_UNPACK_FAILED;
        }
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        if (GORM_OK != this->UnPackGetByNonPrimaryKey())
        {
            cPreErrCode = GORM_RSP_UNPACK_FAILED;
        }
        break;
    }
    }

    return GORM_OK;
}

/*
#define GORM_CLIENT_UNPACK_RSP_MSG()\
if (!pRspPbMsg->ParseFromArray(this->szRspBegin+GORM_RSP_MSG_HEADER_LEN, iRspLen-GORM_RSP_MSG_HEADER_LEN))              \
{                                                                                                                       \
    GORM_CUSTOM_LOGE(pLogger, "unpack response from gorm server failed, reqcmd:%d, reqid:%d", iReqCmd, ulCBID);         \
    this->cPreErrCode = GORM_RSP_UNPACK_FAILED;                                                                         \
    return GORM_RSP_UNPACK_FAILED;                                                                                      \
}                                                                                                                       \
const GORM_PB_Ret_Code pRetCode = pRspPbMsg->retcode();                                                                 \
this->SetRspCode(&pRetCode);                            
*/

int GORM_ClientResponse::UnPackInsert()
{
    return GORM_UnPackInsertRsp(pLogger, pResponsePbMsg, szRspBegin, iRspLen, iReqCmd, ulCBID, cPreErrCode, ulInsertId,
            iReturnRecordNum, pRecords, iTableId, rspCode, iAffectedNum);
    /*GORM_PB_INSERT_RSP* pRspPbMsg = dynamic_cast<GORM_PB_INSERT_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    this->ulInsertId = pRspPbMsg->lastinsertid();

    int iTableNum = pRspPbMsg->tables_size();
    if (iTableNum == 0)
    {
        return GORM_OK;
    }
    iTableNum = 1;
    this->iReturnRecordNum = iTableNum;
    this->pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &this->pRecords[0];
        pRecord->iTableId = this->iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    }
    
    return GORM_OK;*/
}

int GORM_ClientResponse::UnPackReplace()
{
    return GORM_UnPackReplaceRsp(pLogger, pResponsePbMsg, szRspBegin, iRspLen, iReqCmd, ulCBID, cPreErrCode, ulInsertId,
            iReturnRecordNum, pRecords, iTableId, rspCode, iAffectedNum);
    /*GORM_PB_REPLACE_RSP* pRspPbMsg = dynamic_cast<GORM_PB_REPLACE_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    this->iAffectedNum = pRspPbMsg->affectednum();

    int iTableNum = pRspPbMsg->tables_size();
    if (iTableNum == 0)
    {
        return GORM_OK;
    }
    iTableNum = 1;
    this->iReturnRecordNum = iTableNum;
    this->pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &this->pRecords[0];
        pRecord->iTableId = this->iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    }
    
    return GORM_OK;*/
}
int GORM_ClientResponse::UnPackIncrease()
{
    return GORM_UnPackIncreaseRsp(pLogger, pResponsePbMsg, szRspBegin, iRspLen, iReqCmd, ulCBID, cPreErrCode, ulInsertId,
            iReturnRecordNum, pRecords, iTableId, rspCode, iAffectedNum);
    /*GORM_PB_INCREASE_RSP* pRspPbMsg = dynamic_cast<GORM_PB_INCREASE_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    this->iAffectedNum = pRspPbMsg->affectednum();

    int iTableNum = pRspPbMsg->tables_size();
    if (iTableNum == 0)
    {
        return GORM_OK;
    }
    iTableNum = 1;
    this->iReturnRecordNum = iTableNum;
    this->pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &this->pRecords[0];
        pRecord->iTableId = this->iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    }
    
    return GORM_OK;*/
}
int GORM_ClientResponse::UnPackGet()
{
    return GORM_UnPackGetRsp(pLogger, pResponsePbMsg, szRspBegin, iRspLen, iReqCmd, ulCBID, cPreErrCode, ulInsertId,
            iReturnRecordNum, pRecords, iTableId, rspCode, iAffectedNum);
    /*GORM_PB_GET_RSP* pRspPbMsg = dynamic_cast<GORM_PB_GET_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    if (!pRspPbMsg->has_table())
            return GORM_OK;
    GORM_PB_TABLE *pTable = pRspPbMsg->mutable_table();
    if (!GORM_TableHasData(pTable, iTableId))
        return GORM_OK;
    this->iReturnRecordNum = 1;
    this->pRecords = new GORM_Record[this->iReturnRecordNum];
    GORM_Record *pRecord = &this->pRecords[0];
    pRecord->iTableId = this->iTableId;
    int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
    if (iRet != GORM_OK)
    {
        return iRet;
    }
    
    return GORM_OK;*/
}
int GORM_ClientResponse::UnPackDelete()
{
    return GORM_UnPackDeleteRsp(pLogger, pResponsePbMsg, szRspBegin, iRspLen, iReqCmd, ulCBID, cPreErrCode, ulInsertId,
            iReturnRecordNum, pRecords, iTableId, rspCode, iAffectedNum);
    /*GORM_PB_DELETE_RSP* pRspPbMsg = dynamic_cast<GORM_PB_DELETE_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    this->iAffectedNum = pRspPbMsg->affectednum();
    return GORM_OK;*/
}
int GORM_ClientResponse::UnPackBatchGet()
{
    return GORM_UnPackBatchGetRsp(pLogger, pResponsePbMsg, szRspBegin, iRspLen, iReqCmd, ulCBID, cPreErrCode, ulInsertId,
            iReturnRecordNum, pRecords, iTableId, rspCode, iAffectedNum);
    /*GORM_PB_BATCH_GET_RSP* pRspPbMsg = dynamic_cast<GORM_PB_BATCH_GET_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    int iTableNum = pRspPbMsg->tables_size();
    this->iReturnRecordNum = iTableNum;
    this->pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &this->pRecords[i];
        pRecord->iTableId = this->iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    }
    
    return GORM_OK;*/
}

int GORM_ClientResponse::UnPackGetByPartKey()
{
    return GORM_UnPackGetByPartKeyRsp(pLogger, pResponsePbMsg, szRspBegin, iRspLen, iReqCmd, ulCBID, cPreErrCode, ulInsertId,
            iReturnRecordNum, pRecords, iTableId, rspCode, iAffectedNum);
    /*GORM_PB_GET_BY_PARTKEY_RSP* pRspPbMsg = dynamic_cast<GORM_PB_GET_BY_PARTKEY_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    int iTableNum = pRspPbMsg->tables_size();
    this->iReturnRecordNum = iTableNum;
    this->pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &this->pRecords[i];
        pRecord->iTableId = this->iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    }
    
    
    return GORM_OK;*/
}

int GORM_ClientResponse::UnPackUpdate()
{
    return GORM_UnPackUpdateRsp(pLogger, pResponsePbMsg, szRspBegin, iRspLen, iReqCmd, ulCBID, cPreErrCode, ulInsertId,
            iReturnRecordNum, pRecords, iTableId, rspCode, iAffectedNum);
    /*
    GORM_PB_UPDATE_RSP* pRspPbMsg = dynamic_cast<GORM_PB_UPDATE_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    this->iAffectedNum = pRspPbMsg->affectednum();

    int iTableNum = pRspPbMsg->tables_size();
    if (iTableNum == 0)
    {
        return GORM_OK;
    }
    iTableNum = 1;
    this->iReturnRecordNum = iTableNum;
    this->pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &this->pRecords[0];
        pRecord->iTableId = this->iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    }
    
    return GORM_OK;
    */
}

int GORM_ClientResponse::UnPackGetByNonPrimaryKey()
{
    return GORM_UnPackGetByNonPrimaryKey(pLogger, pResponsePbMsg, szRspBegin, iRspLen, iReqCmd, ulCBID, cPreErrCode, ulInsertId,
            iReturnRecordNum, pRecords, iTableId, rspCode, iAffectedNum);
}

int GORM_ClientResponse::GetSrcPbMsg(PB_MSG_PTR &pbMsg)
{
    pbMsg = pResponsePbMsg;
    return GORM_OK;
}

}
