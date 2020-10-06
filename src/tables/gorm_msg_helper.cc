#include "gorm_msg_helper.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_table_field_map_define.h"
#include "gorm_record.h"

namespace gorm{

uint32 GORM_GetMsgLen(char *szMsg)
{
    return (uint32(szMsg[0])<<24 & 0xFF000000) | (uint32(szMsg[1])<<16 & 0xFF0000) | (uint32(szMsg[2])<<8 & 0xFF00) | (szMsg[3]&0xFF);
}

void GORM_SetMsgLen(char *szMsg, uint32 uiLen)
{
    szMsg[0] = uiLen>>24;
    szMsg[1] = uiLen>>16;
    szMsg[2] = uiLen>>8;
    szMsg[3] = uiLen;
}

uint32 GORM_GetReqType(char *szMsg)
{
    return uint32(szMsg[0])&0xFF;
}

uint32 GORM_GetReqID(char *szMsg)
{
    return (uint32(szMsg[0])<<16 & 0xFF0000) | (uint32(szMsg[1])<<8 & 0xFF00) | (uint32(szMsg[2])&0xFF);
}

char* GORM_GetReqHeader(IN char *szMsg, OUT GORM_CMD &iReqCmd, OUT uint32 &iReqID, OUT uint8 &flag)
{
    iReqCmd = GORM_CMD(szMsg[0]);
    iReqID = (uint32(szMsg[1])<<16 & 0xFF0000) | (uint32(szMsg[2])<<8 & 0xFF00) | (uint32(szMsg[3])&0xFF);
    flag = uint8(szMsg[4]);

    return szMsg+5;
}

void GORM_SetReqHeaderSeqId(char *szMsg, uint32 uiSeqId)
{
    szMsg[5] = uiSeqId>>16;
    szMsg[6] = uiSeqId>>8;
    szMsg[7] = uiSeqId;
}

void GORM_SetReqHeader(IN char *szMsg, uint32 uiLen,GORM_CMD iReqCmd, uint32 iReqId, uint8 flag)
{
    szMsg[0] = char(uiLen>>24);
    szMsg[1] = char(uiLen>>16);
    szMsg[2] = char(uiLen>>8);
    szMsg[3] = char(uiLen);

    szMsg[4] = iReqCmd;

    szMsg[5] = iReqId>>16;
    szMsg[6] = iReqId>>8;
    szMsg[7] = iReqId;

    szMsg[8] = flag;
}

void GORM_SetRspHeader(char *szMsg, uint32 uiLen, uint8 reqCmd, uint32 iReqId, char cErrCode, uint8 flag)
{
    szMsg[0] = char(uiLen>>24);
    szMsg[1] = char(uiLen>>16);
    szMsg[2] = char(uiLen>>8);
    szMsg[3] = char(uiLen);

    szMsg[4] = reqCmd;

    szMsg[5] = iReqId>>16;
    szMsg[6] = iReqId>>8;
    szMsg[7] = iReqId;

    szMsg[8] = cErrCode;

    szMsg[9] = flag;
}

char *GORM_GetRspHeader(char *szMsg, OUT GORM_CMD &reqCmd, OUT uint32 &iReqId, OUT char &cErrCode, OUT uint8 &flag)
{
    reqCmd = GORM_CMD(szMsg[0]);
    iReqId = (uint32(szMsg[1])<<16 & 0xFF0000) | (uint32(szMsg[2])<<8 & 0xFF00) | szMsg[3];
    cErrCode = szMsg[4];
    flag = szMsg[5];
    return szMsg+6;
}

int GetPbReqMsg(GORM_CMD cmd, OUT PB_MSG_PTR &pMsgPtr)
{
    switch (cmd)
    {
    case GORM_CMD_HEART:
    {
       auto ptr = new GORM_PB_HEART_REQ();
       pMsgPtr = ptr;
       ptr->mutable_header();
       break; 
    } 
    case GORM_CMD_HAND_SHAKE:
    {
       auto ptr = new GORM_PB_HAND_SHAKE_REQ();
       pMsgPtr = ptr;
       ptr->mutable_header();
       break; 
    } 
    case GORM_CMD_INSERT:
    {
       auto ptr = new GORM_PB_INSERT_REQ();
       pMsgPtr = ptr;
       ptr->mutable_header();
       break; 
    } 
    case GORM_CMD_REPLACE:
    {
       auto ptr = new GORM_PB_REPLACE_REQ();
       pMsgPtr = ptr;
       ptr->mutable_header();
       break; 
    } 
    case GORM_CMD_INCREASE:
    {
       auto ptr = new GORM_PB_INCREASE_REQ();
       pMsgPtr = ptr;
       ptr->mutable_header();
       break; 
    } 
    case GORM_CMD_GET:
    {
       auto ptr = new GORM_PB_GET_REQ();
       pMsgPtr = ptr;
       ptr->mutable_header();
       break; 
    }
    case GORM_CMD_DELETE:
    {
        auto ptr = new GORM_PB_DELETE_REQ();
        pMsgPtr = ptr;
        ptr->mutable_header();
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        auto ptr = new GORM_PB_BATCH_GET_REQ();
        pMsgPtr = ptr;
        ptr->mutable_header();
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        auto ptr = new GORM_PB_GET_BY_PARTKEY_REQ();
        pMsgPtr = ptr;
        ptr->mutable_header();
        break;
    }
    case GORM_CMD_UPDATE:
    {
        auto ptr = new GORM_PB_UPDATE_REQ();
        pMsgPtr = ptr;
        ptr->mutable_header();
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        auto ptr = new GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ();
        pMsgPtr = ptr;
        ptr->mutable_header();
        break;
    }
    default:
        return GORM_ERROR;
    }
    
    return GORM_OK;
}

int GetPbRspMsg(GORM_CMD cmd, OUT PB_MSG_PTR &pMsgPtr)
{
    switch (cmd)
    {
    case GORM_CMD_HEART:
    {
       auto ptr = new GORM_PB_HEART_RSP();
       pMsgPtr = ptr;
       ptr->mutable_retcode();
       break; 
    } 
    case GORM_CMD_HAND_SHAKE:
    {
       auto ptr = new GORM_PB_HAND_SHAKE_RSP();
       pMsgPtr = ptr;
       ptr->mutable_retcode();
       break; 
    } 
    case GORM_CMD_INSERT:
    {
       auto ptr = new GORM_PB_INSERT_RSP();
       pMsgPtr = ptr;
       ptr->mutable_retcode();
       break; 
    } 
    case GORM_CMD_REPLACE:
    {
       auto ptr = new GORM_PB_REPLACE_RSP();
       pMsgPtr = ptr;
       ptr->mutable_retcode();
       break; 
    } 
    case GORM_CMD_INCREASE:
    {
       auto ptr = new GORM_PB_INCREASE_RSP();
       pMsgPtr = ptr;
       ptr->mutable_retcode();
       break; 
    } 
    case GORM_CMD_GET:
    {
       auto ptr = new GORM_PB_GET_RSP();
       pMsgPtr = ptr;
       ptr->mutable_retcode();
       break; 
    }
    case GORM_CMD_DELETE:
    {
        auto ptr = new GORM_PB_DELETE_RSP();
        pMsgPtr = ptr;
        ptr->mutable_retcode();
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        auto ptr = new GORM_PB_BATCH_GET_RSP();
        pMsgPtr = ptr;
        ptr->mutable_retcode();
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        auto ptr = new GORM_PB_GET_BY_PARTKEY_RSP();
        pMsgPtr = ptr;
        ptr->mutable_retcode();
        break;
    }
    case GORM_CMD_UPDATE:
    {
        auto ptr = new GORM_PB_UPDATE_RSP();
        pMsgPtr = ptr;
        ptr->mutable_retcode();
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        auto ptr = new GORM_PB_GET_BY_NON_PRIMARY_KEY_RSP();
        pMsgPtr = ptr;
        ptr->mutable_retcode();
        break;
    }
    default:
        return GORM_ERROR;
    }
    return GORM_OK;
}

void DelPbReqMsg(GORM_CMD cmd, PB_MSG_PTR &pMsgPtr)
{
    if (pMsgPtr == nullptr)
        return;
    ASSERT(pMsgPtr != nullptr);
    delete pMsgPtr;
    pMsgPtr = nullptr;
}
void DelPbRspMsg(GORM_CMD cmd, PB_MSG_PTR &pMsgPtr)
{
    if (pMsgPtr == nullptr)
        return;
    ASSERT(pMsgPtr != nullptr);
    delete pMsgPtr;
    pMsgPtr = nullptr;
}
void DelPbTableMsg(int iTableId, PB_MSG_PTR &pMsgPtr)
{
    if (pMsgPtr == nullptr)
        return;
    ASSERT(pMsgPtr != nullptr);
    delete pMsgPtr;
    pMsgPtr = nullptr;
}

int GORM_PackRequestBuff(GORM_Log *pLogger, GORM_MemPool *pMemPool, PB_MSG_PTR pPbMsg, GORM_MemPoolData *&pMsgBuffer, 
    GORM_CMD iReqCmd, uint32 ulSeqId, uint8 reqPreFlag)
{
    // 3、打包数据到buffer
    size_t sPbSize = pPbMsg->ByteSizeLong() + GORM_REQ_MSG_HEADER_LEN;
    pMsgBuffer = pMemPool->GetData(sPbSize);
    if (pMsgBuffer == nullptr)
    {
        GORM_CUSTOM_LOGE(pLogger, "pack request, get buffer failed, buffer size:%d", sPbSize);
        return GORM_ERROR;
    }

    // 设置发送消息头
    //#define GORM_SET_REQ_HEADER(MSG,LEN,REQCMD,REQID,FLAG)
    GORM_SET_REQ_PRE_HEADER(pMsgBuffer->m_uszData, sPbSize, iReqCmd, ulSeqId, reqPreFlag);
    // 压缩pb数据到内存
    if (!pPbMsg->SerializeToArray(pMsgBuffer->m_uszData + GORM_REQ_MSG_HEADER_LEN, sPbSize-GORM_REQ_MSG_HEADER_LEN))
    {
        GORM_CUSTOM_LOGD(pLogger, "serialize msg to buffer failed.");
        return GORM_ERROR;
    }
    pMsgBuffer->m_sUsedSize = sPbSize;

    return GORM_OK;
}

    
#define GORM_CLIENTREQUEST_SETHEADER()                                              \
GORM_PB_REQ_HEADER *header = pPbReq->mutable_header();                              \
header->set_reqflag(uiReqFlag);                                                     \
header->set_fieldmode(fieldMode.szFieldCollections, fieldMode.iUsedIdx);\
header->set_tableid(iTableId);                                                      \
header->set_verpolice(iVerPolicy);


int GORM_PackInsertReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords)
{
    // TODO 打包头
    GORM_PB_INSERT_REQ  *pPbReq = dynamic_cast<GORM_PB_INSERT_REQ*>(pPbMsg);
    GORM_CLIENTREQUEST_SETHEADER();
    
    // 打包包体
    if (iNowRecordNum == 0)
    {
        return GORM_REQ_NO_RECORDS;
    }
    int iRet = 0;
    GORM_Record *pRecord = nullptr;
    for (int i=0; i<iNowRecordNum; i++)
    {
        pRecord = vRecords[i];
        if (pRecord == nullptr)
        {
            break;
        }
        GORM_PB_TABLE *pTable = pPbReq->add_tables();
        iRet = GORM_AddRecordToReqPbMsgDefine(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        if (pRecord->pCustomColumns != nullptr)
        {
            GORM_PB_CUSTEM_COLUMNS *pColumns = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pRecord->pCustomColumns);
            pTable->set_allocated_custom_columns(pColumns);
        }
    #endif
        break;
    }
    return GORM_OK;
}

int GORM_PackReplaceReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords)
{
    GORM_PB_REPLACE_REQ  *pPbReq = dynamic_cast<GORM_PB_REPLACE_REQ*>(pPbMsg);
    GORM_CLIENTREQUEST_SETHEADER();

    // 打包包体
    if (iNowRecordNum == 0)
    {
        return GORM_REQ_NO_RECORDS;
    }
    int iRet = 0;
    GORM_Record *pRecord = nullptr;
    for (int i=0; i<iNowRecordNum; i++)
    {
        pRecord = vRecords[i];
        if (pRecord == nullptr)
        {
            break;
        }
        GORM_PB_TABLE *pTable = pPbReq->add_tables();
        iRet = GORM_AddRecordToReqPbMsgDefine(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        if (pRecord->pCustomColumns != nullptr)
        {
            GORM_PB_CUSTEM_COLUMNS *pColumns = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pRecord->pCustomColumns);
            pTable->set_allocated_custom_columns(pColumns);
        }
    #endif
        // TODO 确认重复设置会不会造成内存泄露
        header->set_fieldmode(pRecord->requestField.szFieldCollections);
        break;
    }

    return GORM_OK;
}

int GORM_PackIncreaseReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords)
{
    GORM_PB_INCREASE_REQ  *pPbReq = dynamic_cast<GORM_PB_INCREASE_REQ*>(pPbMsg);
    GORM_CLIENTREQUEST_SETHEADER();

    // 打包包体
    if (iNowRecordNum == 0)
    {
        return GORM_REQ_NO_RECORDS;
    }
    int iRet = 0;
    GORM_Record *pRecord = nullptr;
    for (int i=0; i<iNowRecordNum; i++)
    {
        pRecord = vRecords[i];
        if (pRecord == nullptr)
        {
            break;
        }
        GORM_PB_TABLE *pTable = pPbReq->add_tables();
        iRet = GORM_AddRecordToReqPbMsgDefine(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        if (pRecord->pCustomColumns != nullptr)
        {
            GORM_PB_CUSTEM_COLUMNS *pColumns = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pRecord->pCustomColumns);
            pTable->set_allocated_custom_columns(pColumns);
        }
    #endif
        // TODO 确认重复设置会不会造成内存泄露
        header->set_fieldmode(pRecord->requestField.szFieldCollections);
        pPbReq->set_minuscolumns(pRecord->minusField.szFieldCollections, pRecord->minusField.iUsedIdx);
        break;
    }
}

int GORM_PackGetReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
               int iNowRecordNum, GORM_Record **vRecords)
{
    GORM_PB_GET_REQ  *pPbReq = dynamic_cast<GORM_PB_GET_REQ*>(pPbMsg);
    GORM_CLIENTREQUEST_SETHEADER();

    // 打包包体
    if (iNowRecordNum == 0)
    {
        return GORM_REQ_NO_RECORDS;
    }
    int iRet = 0;
    GORM_Record *pRecord = nullptr;
    for (int i=0; i<iNowRecordNum; i++)
    {
        pRecord = vRecords[i];
        if (pRecord == nullptr)
        {
            break;
        }
        GORM_PB_TABLE *pTable = pPbReq->mutable_table();
        iRet = GORM_AddRecordToReqPbMsgDefine(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        if (pRecord->pCustomColumns != nullptr)
        {
            GORM_PB_CUSTEM_COLUMNS *pColumns = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pRecord->pCustomColumns);
            pTable->set_allocated_custom_columns(pColumns);
        }
    #endif
        // TODO 确认重复设置会不会造成内存泄露
        header->set_fieldmode(pRecord->requestField.szFieldCollections);
        break;
    }
    return GORM_OK;
}

int GORM_PackDeleteReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords)
{
    GORM_PB_DELETE_REQ  *pPbReq = dynamic_cast<GORM_PB_DELETE_REQ*>(pPbMsg);
    GORM_CLIENTREQUEST_SETHEADER();

    // 打包包体
    if (iNowRecordNum < 1)
    {
        return GORM_REQ_NO_RECORDS;
    }
    if (iNowRecordNum > 1)
        return GORM_TOO_MUCH_RECORD;
    int iRet = 0;
    GORM_Record *pRecord = nullptr;
    for (int i=0; i<iNowRecordNum; i++)
    {
        pRecord = vRecords[i];
        if (pRecord == nullptr)
        {
            break;
        }
        GORM_PB_TABLE *pTable = pPbReq->mutable_table();
        iRet = GORM_AddRecordToReqPbMsgDefine(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        if (pRecord->pCustomColumns != nullptr)
        {
            GORM_PB_CUSTEM_COLUMNS *pColumns = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pRecord->pCustomColumns);
            pTable->set_allocated_custom_columns(pColumns);
        }
    #endif
        // TODO 确认重复设置会不会造成内存泄露
        header->set_fieldmode(pRecord->requestField.szFieldCollections);
        break;
    }
    return GORM_OK;
}

int GORM_PackBatchGetReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords)
{
    // 打包头
    GORM_PB_BATCH_GET_REQ  *pPbReq = dynamic_cast<GORM_PB_BATCH_GET_REQ*>(pPbMsg);
    GORM_CLIENTREQUEST_SETHEADER();
    
    // 打包包体
    if (iNowRecordNum == 0)
    {
        return GORM_REQ_NO_RECORDS;
    }
    int iRet = 0;
    GORM_Record *pRecord = nullptr;
    for (int i=0; i<iNowRecordNum; i++)
    {
        pRecord = vRecords[i];
        if (pRecord == nullptr)
        {
            break;
        }
        GORM_PB_TABLE *pTable = pPbReq->add_tables();
        iRet = GORM_AddRecordToReqPbMsgDefine(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        if (pRecord->pCustomColumns != nullptr)
        {
            GORM_PB_CUSTEM_COLUMNS *pColumns = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pRecord->pCustomColumns);
            pTable->set_allocated_custom_columns(pColumns);
        }
    #endif
    }
    return GORM_OK;
}

int GORM_PackGetByPartKeyReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                            int iNowRecordNum, GORM_Record **vRecords)
{
    // 打包头
    GORM_PB_GET_BY_PARTKEY_REQ  *pPbReq = dynamic_cast<GORM_PB_GET_BY_PARTKEY_REQ*>(pPbMsg);
    GORM_CLIENTREQUEST_SETHEADER();
    
    // 打包包体
    if (iNowRecordNum == 0)
    {
        return GORM_REQ_NO_RECORDS;
    }
    int iRet = 0;
    GORM_Record *pRecord = nullptr;
    for (int i=0; i<iNowRecordNum; i++)
    {
        pRecord = vRecords[i];
        if (pRecord == nullptr)
        {
            break;
        }
        GORM_PB_TABLE *pTable = pPbReq->add_tables();
        iRet = GORM_AddRecordToReqPbMsgDefine(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        if (pRecord->pCustomColumns != nullptr)
        {
            GORM_PB_CUSTEM_COLUMNS *pColumns = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pRecord->pCustomColumns);
            pTable->set_allocated_custom_columns(pColumns);
        }
    #endif
    }
    return GORM_OK;
}

int GORM_PackUpdateReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords)
{
    // TODO 打包头
    GORM_PB_UPDATE_REQ  *pPbReq = dynamic_cast<GORM_PB_UPDATE_REQ*>(pPbMsg);
    GORM_CLIENTREQUEST_SETHEADER();
    
    // 打包包体
    if (iNowRecordNum == 0)
    {
        return GORM_REQ_NO_RECORDS;
    }
    int iRet = 0;
    GORM_Record *pRecord = nullptr;
    for (int i=0; i<iNowRecordNum; i++)
    {
        pRecord = vRecords[i];
        if (pRecord == nullptr)
        {
            break;
        }
        GORM_PB_TABLE *pTable = pPbReq->add_tables();
        iRet = GORM_AddRecordToReqPbMsgDefine(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        if (pRecord->pCustomColumns != nullptr)
        {
            GORM_PB_CUSTEM_COLUMNS *pColumns = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pRecord->pCustomColumns);
            pTable->set_allocated_custom_columns(pColumns);
        }
    #endif
        // TODO 确认重复设置会不会造成内存泄露
        header->set_fieldmode(pRecord->requestField.szFieldCollections);
        break;
    }
    return GORM_OK;
}

int GORM_PackGetByNonPrimaryKey(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords)
{
    // TODO 打包头
    GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ  *pPbReq = dynamic_cast<GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ*>(pPbMsg);
    GORM_CLIENTREQUEST_SETHEADER();
    
    // 打包包体
    if (iNowRecordNum == 0)
    {
        return GORM_REQ_NO_RECORDS;
    }
    int iRet = 0;
    GORM_Record *pRecord = nullptr;
    for (int i=0; i<iNowRecordNum; i++)
    {
        pRecord = vRecords[i];
        if (pRecord == nullptr)
        {
            break;
        }
        GORM_PB_TABLE *pTable = pPbReq->add_tables();
        iRet = GORM_AddRecordToReqPbMsgDefine(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        if (pRecord->pCustomColumns != nullptr)
        {
            GORM_PB_CUSTEM_COLUMNS *pColumns = dynamic_cast<GORM_PB_CUSTEM_COLUMNS*>(pRecord->pCustomColumns);
            pTable->set_allocated_custom_columns(pColumns);
        }
    #endif
        // TODO 确认重复设置会不会造成内存泄露
        header->set_fieldmode(pRecord->requestField.szFieldCollections);
        break;
    }
    return GORM_OK;
}


#define GORM_CLIENT_UNPACK_RSP_MSG()\
if (!pRspPbMsg->ParseFromArray(szRspBegin+GORM_RSP_MSG_HEADER_LEN, iRspLen-GORM_RSP_MSG_HEADER_LEN))                    \
{                                                                                                                       \
    GORM_CUSTOM_LOGE(pLogger, "unpack response from gorm server failed, reqcmd:%d, reqid:%d", iReqCmd, ulCBID);         \
    cPreErrCode = GORM_RSP_UNPACK_FAILED;                                                                               \
    return GORM_RSP_UNPACK_FAILED;                                                                                      \
}                                                                                                                       \
const GORM_PB_Ret_Code pRetCode = pRspPbMsg->retcode();                                                                 \
rspCode.code = pRetCode.code();                                                                                         \
rspCode.dbError = pRetCode.dbcode();                                                                                    \
if (rspCode.dbError > 0)                                                                                                \
    strncpy(rspCode.dbErrorInfo, (char*)pRetCode.dberrinfo().c_str(), GORM_MAX_DB_ERR_INFO);

int GORM_UnPackCustomRsp(GORM_PB_TABLE *pTable, GORM_Record *pRecord)
{
    if (!pTable->has_custom_columns())
        return GORM_OK;

    const GORM_PB_CUSTEM_COLUMNS &pbColumns = pTable->custom_columns();
    if (pbColumns.columns_size() == 0)
        return GORM_OK;

    pRecord->pCustomColumns = pTable->mutable_custom_columns();
    return GORM_OK;
}
                    

int GORM_UnPackInsertRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum)
{
    GORM_PB_INSERT_RSP* pRspPbMsg = dynamic_cast<GORM_PB_INSERT_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    ulInsertId = pRspPbMsg->lastinsertid();

    int iTableNum = pRspPbMsg->tables_size();
    if (iTableNum == 0)
    {
        return GORM_OK;
    }
    iTableNum = 1;
    iReturnRecordNum = iTableNum;
    pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &pRecords[0];
        pRecord->iTableId = iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        iRet = GORM_UnPackCustomRsp(pTable, pRecord);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #endif
    }
    
    return GORM_OK;
}

int GORM_UnPackReplaceRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode,
        int32 &iAffectedNum)
{
    GORM_PB_REPLACE_RSP* pRspPbMsg = dynamic_cast<GORM_PB_REPLACE_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    iAffectedNum = pRspPbMsg->affectednum();

    int iTableNum = pRspPbMsg->tables_size();
    if (iTableNum == 0)
    {
        return GORM_OK;
    }
    iTableNum = 1;
    iReturnRecordNum = iTableNum;
    pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &pRecords[0];
        pRecord->iTableId = iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        iRet = GORM_UnPackCustomRsp(pTable, pRecord);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #endif
    }
    
    return GORM_OK;
}

int GORM_UnPackIncreaseRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode,
        int32 &iAffectedNum)
{
    GORM_PB_INCREASE_RSP* pRspPbMsg = dynamic_cast<GORM_PB_INCREASE_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    iAffectedNum = pRspPbMsg->affectednum();

    int iTableNum = pRspPbMsg->tables_size();
    if (iTableNum == 0)
    {
        return GORM_OK;
    }
    iTableNum = 1;
    iReturnRecordNum = iTableNum;
    pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &pRecords[0];
        pRecord->iTableId = iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        iRet = GORM_UnPackCustomRsp(pTable, pRecord);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #endif
    }
    
    return GORM_OK;
}

int GORM_UnPackGetRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode,
        int32 &iAffectedNum)
{
    GORM_PB_GET_RSP* pRspPbMsg = dynamic_cast<GORM_PB_GET_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    if (!pRspPbMsg->has_table())
            return GORM_OK;
    GORM_PB_TABLE *pTable = pRspPbMsg->mutable_table();
    if (!GORM_TableHasData(pTable, iTableId))
        return GORM_OK;
    iReturnRecordNum = 1;
    pRecords = new GORM_Record[iReturnRecordNum];
    GORM_Record *pRecord = &pRecords[0];
    pRecord->iTableId = iTableId;
    int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
    if (iRet != GORM_OK)
    {
        return iRet;
    }
    #ifdef GORM_DEBUG
    iRet = GORM_UnPackCustomRsp(pTable, pRecord);
    if (iRet != GORM_OK)
    {
        return iRet;
    }
    #endif
    
    return GORM_OK;
}

int GORM_UnPackDeleteRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode,
        int32 &iAffectedNum)
{
    GORM_PB_DELETE_RSP* pRspPbMsg = dynamic_cast<GORM_PB_DELETE_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    iAffectedNum = pRspPbMsg->affectednum();
    return GORM_OK;
}

int GORM_UnPackBatchGetRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode,
        int32 &iAffectedNum)
{
    GORM_PB_BATCH_GET_RSP* pRspPbMsg = dynamic_cast<GORM_PB_BATCH_GET_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    int iTableNum = pRspPbMsg->tables_size();
    iReturnRecordNum = iTableNum;
    pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &pRecords[i];
        pRecord->iTableId = iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        iRet = GORM_UnPackCustomRsp(pTable, pRecord);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #endif
    }
    
    return GORM_OK;
}

int GORM_UnPackGetByNonPrimaryKey(GORM_Log *pLogger, PB_MSG_PTR          pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum)
{
    GORM_PB_GET_BY_NON_PRIMARY_KEY_RSP* pRspPbMsg = dynamic_cast<GORM_PB_GET_BY_NON_PRIMARY_KEY_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    int iTableNum = pRspPbMsg->tables_size();
    iReturnRecordNum = iTableNum;
    pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &pRecords[i];
        pRecord->iTableId = iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        iRet = GORM_UnPackCustomRsp(pTable, pRecord);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #endif
    }
    
    return GORM_OK;
}


int GORM_UnPackGetByPartKeyRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode,
        int32 &iAffectedNum)
{
    GORM_PB_GET_BY_PARTKEY_RSP* pRspPbMsg = dynamic_cast<GORM_PB_GET_BY_PARTKEY_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    int iTableNum = pRspPbMsg->tables_size();
    iReturnRecordNum = iTableNum;
    pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &pRecords[i];
        pRecord->iTableId = iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        iRet = GORM_UnPackCustomRsp(pTable, pRecord);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #endif
    }
    
    
    return GORM_OK;
}

int GORM_UnPackUpdateRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode,
        int32 &iAffectedNum)
{
    GORM_PB_UPDATE_RSP* pRspPbMsg = dynamic_cast<GORM_PB_UPDATE_RSP*>(pResponsePbMsg);
    GORM_CLIENT_UNPACK_RSP_MSG();

    iAffectedNum = pRspPbMsg->affectednum();

    int iTableNum = pRspPbMsg->tables_size();
    if (iTableNum == 0)
    {
        return GORM_OK;
    }
    iTableNum = 1;
    iReturnRecordNum = iTableNum;
    pRecords = new GORM_Record[iTableNum];
    for (int i=0; i<iTableNum; i++)
    {
        GORM_PB_TABLE *pTable = (GORM_PB_TABLE*)&pRspPbMsg->tables(i);
        if (!GORM_TableHasData(pTable, iTableId))
            continue;
        
        GORM_Record *pRecord = &pRecords[0];
        pRecord->iTableId = iTableId;
        int iRet = GORM_GetTableSrcPbMsg(iTableId, pTable, pRecord->pPbMsg);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #ifdef GORM_DEBUG
        iRet = GORM_UnPackCustomRsp(pTable, pRecord);
        if (iRet != GORM_OK)
        {
            return iRet;
        }
    #endif
    }
    
    return GORM_OK;
}


}

