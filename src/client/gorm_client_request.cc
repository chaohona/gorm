#include "gorm_client_request.h"
#include "gorm_inc.h"
#include "gorm_define.h"
#include "gorm_table_field_map.h"
#include "gorm_table_field_map_define.h"


namespace gorm{

GORM_ClientRequest::GORM_ClientRequest()
{
}

GORM_ClientRequest::~GORM_ClientRequest()
{
}

int GORM_ClientRequest::Init(GORM_CMD iCmd, int iTableId, GORM_Log *pLogger)
{
    // 创建请求信息
    if (GORM_OK != GetPbReqMsg(iCmd, this->pPbMsg))
    {
        return GORM_ERROR;
    }
    this->iReqCmd = iCmd;
    this->iTableId = iTableId;
    this->pLogger = pLogger;
    if (this->pLogger == nullptr)
    {
        this->pLogger = GORM_DefaultLog::Instance();
    }
    return GORM_OK;
}

int GORM_ClientRequest::Init(GORM_CMD iCmd, GORM_Log *pLogger)
{
    return this->Init(iCmd, 0, pLogger);
}

int GORM_ClientRequest::SetCheckDataVersionPolicy(enum GORM_CheckDataVerType ver)
{
    iVerPolicy = ver;

    return GORM_OK;
}

void GORM_ClientRequest::SetBusinessId(int32 iBusinessId)
{
    this->iBusinessId = iBusinessId;
}

int GORM_ClientRequest::SetResultFlag(GORM_ResultFlag flag)
{
    // 校验，不是所有请求都需要带响应的
    if (this->iReqCmd == GORM_CMD_GET || this->iReqCmd == GORM_CMD_DELETE || this->iReqCmd == GORM_CMD_BATCH_GET ||
        this->iReqCmd == GORM_CMD_GET_BY_PARTKEY || this->iReqCmd == GORM_CMD_GET_BY_NON_PRIMARY_KEY)
        flag = GORM_ResultFlag_RETURN_CODE;
    this->cResultFlag = flag;
    return GORM_OK;
}

GORM_ResultFlag GORM_ClientRequest::GetResultFlag()
{
    return this->cResultFlag;
}

int GORM_ClientRequest::SetAddableIncreaseFlag(IN GORM_IncreaseFlag increase_flag)
{
    this->increaseFlag = increase_flag;
    return GORM_OK;
}

GORM_IncreaseFlag GORM_ClientRequest::GetAddableIncreaseFlag()
{
    return increaseFlag;
}

int GORM_ClientRequest::AddField(int *vFiledId, uint32 uiCnt)
{
    int iFieldId = 0;
    for (int i=0; i<uiCnt; i++)
    {
        iFieldId = vFiledId[i];
        if (GORM_OK != this->AddField(iFieldId))
        {
            return GORM_INVALID_FIELD;
        }
    }

    return GORM_OK;
}


int GORM_ClientRequest::AddField(IN const char* field_name[], IN const unsigned field_count)
{
    const char *fName = nullptr;
    int iFieldId = 0;
    for (int i=0; i<field_count; i++)
    {
        fName = field_name[i];
        if (GORM_OK != this->AddField(fName))
        {
            return GORM_INVALID_FIELD;
        }
    }

    return GORM_OK;
}

int GORM_ClientRequest::AddField(IN const char* field_name)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(this->iTableId, field_name, iFieldId))
    {
        return GORM_INVALID_FIELD;
    }

    if (!this->fieldMode.AddField(iFieldId))
    {
        return GORM_ERROR;
    }

    return GORM_OK;
}

int GORM_ClientRequest::AddField(int iField)
{
    if (!this->fieldMode.AddField(iField))
    {
        return GORM_ERROR;
    }

    return GORM_OK;
}

int GORM_ClientRequest::AddField(IN vector<char*> &vFields)
{
    for (auto szField : vFields)
    {
        if (GORM_OK != this->AddField(szField))
            return GORM_ERROR;
    }

    return GORM_OK;
}

int GORM_ClientRequest::AddField(IN vector<int> &vFields)
{
    for (auto szField : vFields)
    {
        if (GORM_OK != this->AddField(szField))
            return GORM_ERROR;
    }

    return GORM_OK;
}


int32_t GORM_ClientRequest::SetCompressSwitch(IN enum GORM_SWITCH req_compress_switch, 
                          IN enum GORM_SWITCH resp_compress_switch)
{
    if (req_compress_switch == GORM_SWITCH_ON)
    {
        this->reqPreFlag |= GORM_FLAG_REQ_COMPRESS;
    }
    if (resp_compress_switch == GORM_SWITCH_ON)
    {
        this->reqPreFlag |= GORM_FLAG_RSP_COMPRESS;
    }
    return GORM_OK;
}

int GORM_ClientRequest::GetCompressSwitch(OUT enum GORM_SWITCH& req_compress_switch, 
                    OUT enum GORM_SWITCH& resp_compress_switch)
{
    req_compress_switch = GORM_SWITCH_OFF;
    if (this->reqPreFlag & GORM_FLAG_REQ_COMPRESS > 0)
    {
        req_compress_switch = GORM_SWITCH_ON;
    }
    resp_compress_switch = GORM_SWITCH_OFF;
    if (this->reqPreFlag & GORM_FLAG_RSP_COMPRESS > 0)
    {
        resp_compress_switch = GORM_SWITCH_ON;
    }

  return GORM_OK;
}

int GORM_ClientRequest::SetExpireTime(int64 expire_time)
{
    return GORM_OK;
}

int GORM_ClientRequest::AddRecord(GORM_Record *&pRecord, int iTableId)
{
    int iRet = this->AddRecordCheck();
    if (iRet != GORM_OK )
    {
        return iRet;
    }

    if (iTableId == 0)
    {
        iTableId = this->iTableId;
    }
    if (!InvalidTableCheck(iTableId))
    {
        return GORM_INVALID_TABLE;
    }
    // TODO 内存池
    pRecord = new GORM_Record();
    if (GORM_OK != pRecord->Init(iTableId, pLogger))
    {
        return GORM_INIT_RECORD;
    }
    this->vRecords[iNowRecordNum++] = pRecord;

    return GORM_OK;
}

GORM_CMD GORM_ClientRequest::GetCmd()
{
    return iReqCmd;
}

const char *GORM_ClientRequest::GetTableName()
{
    char *szTableName = nullptr;
    GORM_GetTableName(iTableId, szTableName);
    return szTableName;
}

int GORM_ClientRequest::GetTableId()
{
    return this->iTableId;
}

void GORM_ClientRequest::Release()
{
    try
    {
        if (this->pMsgBuffer != nullptr)
        {
            this->pMsgBuffer->Release();
            this->pMsgBuffer = nullptr;
        }
        if (this->pPbMsg != nullptr)
        {
            DelPbReqMsg(this->iReqCmd, this->pPbMsg);
            this->pPbMsg = nullptr;
        }
        for (int i=0; i<iNowRecordNum; i++)
        {
            GORM_Record *pRecord = this->vRecords[i];
            if (pRecord != nullptr)
                delete pRecord;
        }

        delete this;
    }
    catch(exception &e)
    {
        GORM_CUSTOM_LOGD(pLogger, "release client request got exception:%s", e.what());
    }
    this->pLogger = nullptr;
}

int GORM_ClientRequest::SetOffSet()
{
    return GORM_OK;
}

int GORM_ClientRequest::SetLimited()
{
    return GORM_OK;
}

int GORM_ClientRequest::PackRequest()
{
    // 1、设置各种flag
    // 设置resultflag
    switch (this->cResultFlag)
    {
    case GORM_ResultFlag_RETURN_CODE:
    {
        uiReqFlag |= GORM_REQ_FLAG_RETURN_CODE;
        break;
    }
    case GORM_ResultFlag_RETURN_NEW_VALUE:
    {
        uiReqFlag |= GORM_REQ_FLAG_RETURN_NEW_VALUE;
        break;
    }
    case GORM_ResultFlag_RETURN_ALL_VALUE:
    {
        uiReqFlag |= GORM_REQ_FLAG_RETURN_ALL_VALUE;
        break;
    }
    default:
    {
        uiReqFlag |= GORM_REQ_FLAG_RETURN_CODE;
        break;
    } 
    }

    // 设置IncreaseFlag
    if (this->increaseFlag == GORM_IncreaseFlag_AutoCreate)
    {
        uiReqFlag |= GORM_REQ_FLAG_EMPTY_INCREASE;
    }
    else
    {
        uiReqFlag &= (GORM_REQ_FLAG_MODE ^ GORM_REQ_FLAG_EMPTY_INCREASE);
    }

    if (this->iVerPolicy != NOCHECKDATAVERSION_AUTOINCREASE)
    {
        for (int i=0; i<this->iNowRecordNum; i++)
        {
            GORM_Record *pRecord = vRecords[i];
            if (pRecord == nullptr || pRecord->ulVersion == 0xFFFFFFFFFFFFFFFF)
                return GORM_VERSION_NOT_SET;
        }
    }

    // 2、填充reqmsg
    switch (iReqCmd)
    {
    case GORM_CMD_INSERT:
    {
        if (GORM_OK != this->PackInsert())
        {
            return GORM_PACK_REQ_ERROR;
        }
        break;
    }
    case GORM_CMD_REPLACE:
    {
        if (GORM_OK != this->PackReplace())
        {
            return GORM_PACK_REQ_ERROR;
        }
        break;
    }
    case GORM_CMD_INCREASE:
    {
        if (GORM_OK != this->PackIncrease())
        {
            return GORM_PACK_REQ_ERROR;
        }
        break;
    }
    case GORM_CMD_GET:
    {
        if (GORM_OK != this->PackGet())
        {
            return GORM_PACK_REQ_ERROR;
        }
        break;
    }
    case GORM_CMD_DELETE:
    {
        if (GORM_OK != this->PackDelete())
        {
            return GORM_PACK_REQ_ERROR;
        }
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        if (GORM_OK != this->PackBatchGet())
        {
            return GORM_PACK_REQ_ERROR;
        }
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        if (GORM_OK != this->PackGetByPartKey())
        {
            return GORM_PACK_REQ_ERROR;
        }
        break;
    }
    case GORM_CMD_UPDATE:
    {
        if (GORM_OK != this->PackUpdate())
        {
            return GORM_PACK_REQ_ERROR;
        }
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        if (GORM_OK != this->PackGetByNonPrimaryKey())
        {
            return GORM_PACK_REQ_ERROR;
        }
        break;
    }
    }

    if (GORM_OK != GORM_PackRequestBuff(pLogger, this->pMemPool, this->pPbMsg, this->pMsgBuffer, this->iReqCmd, this->ulSeqId, reqPreFlag))
    {
        GORM_CUSTOM_LOGE(pLogger, "pack request message failed.");
        return GORM_ERROR;
    }
    return GORM_OK;
}

int GORM_ClientRequest::PackInsert()
{
    return GORM_PackInsertReq(pPbMsg, uiReqFlag, fieldMode, iTableId, iVerPolicy, iNowRecordNum, vRecords);
}

int GORM_ClientRequest::PackReplace()
{
    return GORM_PackReplaceReq(pPbMsg, uiReqFlag, fieldMode, iTableId, iVerPolicy, iNowRecordNum, vRecords);
}

int GORM_ClientRequest::PackIncrease()
{
    return GORM_PackIncreaseReq(pPbMsg, uiReqFlag, fieldMode, iTableId, iVerPolicy, iNowRecordNum, vRecords);
}

int GORM_ClientRequest::PackGet()
{
    return GORM_PackGetReq(pPbMsg, uiReqFlag, fieldMode, iTableId, iVerPolicy, iNowRecordNum, vRecords);
}
int GORM_ClientRequest::PackDelete()
{
    return GORM_PackDeleteReq(pPbMsg, uiReqFlag, fieldMode, iTableId, iVerPolicy, iNowRecordNum, vRecords);
}

int GORM_ClientRequest::PackBatchGet()
{
    return GORM_PackBatchGetReq(pPbMsg, uiReqFlag, fieldMode, iTableId, iVerPolicy, iNowRecordNum, vRecords);
}

int GORM_ClientRequest::PackGetByPartKey()
{
    return GORM_PackGetByPartKeyReq(pPbMsg, uiReqFlag, fieldMode, iTableId, iVerPolicy, iNowRecordNum, vRecords);
}


int GORM_ClientRequest::PackUpdate()
{
    return GORM_PackUpdateReq(pPbMsg, uiReqFlag, fieldMode, iTableId, iVerPolicy, iNowRecordNum, vRecords);
}

int GORM_ClientRequest::PackGetByNonPrimaryKey()
{
    return GORM_PackGetByNonPrimaryKey(pPbMsg, uiReqFlag, fieldMode, iTableId, iVerPolicy, iNowRecordNum, vRecords);
}

int GORM_ClientRequest::AddRecordCheck()
{
    if (iNowRecordNum >= GORM_MAX_RECORD_ONE_REQ)
    {
        GORM_CUSTOM_LOGD(pLogger, "too many records add to request:%d", this->iTableId);
        return GORM_TOO_MUCH_RECORD;
    }
    
    switch (iReqCmd)
    {
    case GORM_CMD_GET:
    {
        if (iNowRecordNum != 0)
        {
            return GORM_GET_CMD_SETED;
        }
    }
    }

    return GORM_OK;
}

const GORM_FieldsOpt& GORM_ClientRequest::FieldMode()
{
    return this->fieldMode;
}


}

