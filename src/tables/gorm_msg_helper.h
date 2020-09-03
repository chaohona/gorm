#ifndef _GROM_MSG_HELPER_H__
#define _GROM_MSG_HELPER_H__

#include "gorm_sys_inc.h"
#include "gorm_define.h"
#include "gorm_error.h"
#include "gorm_inc.h"
#include "gorm_mempool.h"
#include "gorm_log.h"
#include <google/protobuf/message.h>
#include "gorm_pb_proto.pb.h"

namespace gorm{

using PB_MSG_PTR = google::protobuf::Message *;

#define GORM_MAX_DB_ERR_INFO 1024
struct GROM_ResponseCode
{
public:
    int code;               // 请求成功还是失败
    int dbError;            // 如果由于db原因导致的失败，则db测的错误码
    char dbErrorInfo[GORM_MAX_DB_ERR_INFO]; // db测错误的详细信息
};


//4字节长度 | 1字节操作类型 | 3字节请求编号 | 1字节flag | 请求内容
#define GORM_REQ_MSG_HEADER_LEN (4+1+3+1)
//4字节长度 | 3字节请求编号 | 1字节错误码 | 1字节flag | 响应内容
#define GORM_RSP_MSG_HEADER_LEN (4+3+1+1+1)

#define GORM_MAX_REQUEST_LEN (8*1024*1024)    // 请求的长度不能超过8M
#define GORM_MSG_LEN_BYTE   4               // 请求协议中代表长度的字节数


// 长度包括4个字节的长度本身
GORM_DLL_DECL uint32 GORM_GetMsgLen(char *szMsg);
GORM_DLL_DECL void GORM_SetMsgLen(char *szMsg, uint32 uiLen);
GORM_DLL_DECL uint32 GORM_GetReqType(char *szMsg);
GORM_DLL_DECL uint32 GORM_GetReqID(char *szMsg);
// 返回跳过消息头的消息体地址
GORM_DLL_DECL char* GORM_GetReqHeader(IN char *szMsg, OUT GORM_CMD &iReqCmd, OUT uint32 &iReqID, OUT uint8 &flag);
GORM_DLL_DECL void GORM_SetReqHeaderSeqId(char *szMsg, uint32 uiSeqId);
GORM_DLL_DECL void GORM_SetReqHeader(IN char *szMsg, uint32 uiLen,GORM_CMD iReqCmd, uint32 iReqId, uint8 flag);
#define GORM_SET_REQ_PRE_HEADER(MSG,LEN,REQCMD,REQID,FLAG)\
GORM_SetReqHeader(MSG,LEN,REQCMD,REQID,FLAG)

GORM_DLL_DECL void GORM_SetRspHeader(char *szMsg, uint32 uiLen, uint8 reqCmd, uint32 iReqId, char cErrCode, uint8 flag);
GORM_DLL_DECL char *GORM_GetRspHeader(char *szMsg, OUT GORM_CMD &reqCmd, OUT uint32 &iReqId, OUT char &cErrCode, OUT uint8 &flag);

// 生成请求消息,会自动生成header字段
// TODO 池化
GORM_DLL_DECL int GetPbReqMsg(GORM_CMD cmd, OUT PB_MSG_PTR &pMsgPtr);
GORM_DLL_DECL int GetPbRspMsg(GORM_CMD cmd, OUT PB_MSG_PTR &pMsgPtr);

GORM_DLL_DECL void DelPbReqMsg(GORM_CMD cmd, PB_MSG_PTR &pMsgPtr);
GORM_DLL_DECL void DelPbRspMsg(GORM_CMD cmd, PB_MSG_PTR &pMsgPtr);
GORM_DLL_DECL void DelPbTableMsg(int iTableId, PB_MSG_PTR &pMsgPtr);


GORM_DLL_DECL int GORM_PackRequestBuff(GORM_Log *pLogger, shared_ptr<GORM_MemPool> pMemPool, PB_MSG_PTR pPbMsg, GORM_MemPoolData *&pMsgBuffer, 
    GORM_CMD iReqCmd, uint32 ulSeqId, uint8 reqPreFlag);

class GORM_Record;
GORM_DLL_DECL int GORM_PackInsertReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords);
GORM_DLL_DECL int GORM_PackReplaceReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords);
GORM_DLL_DECL int GORM_PackIncreaseReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords);
GORM_DLL_DECL int GORM_PackGetReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords);
GORM_DLL_DECL int GORM_PackDeleteReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords);
GORM_DLL_DECL int GORM_PackBatchGetReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords);
GORM_DLL_DECL int GORM_PackGetByPartKeyReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords);
GORM_DLL_DECL int GORM_PackUpdateReq(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords);
GORM_DLL_DECL int GORM_PackGetByNonPrimaryKey(PB_MSG_PTR pPbMsg, uint32 uiReqFlag, GORM_FieldsOpt &fieldMode, int iTableId, GORM_CheckDataVerType iVerPolicy,
                    int iNowRecordNum, GORM_Record **vRecords);


GORM_DLL_DECL int GORM_UnPackInsertRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum);
GORM_DLL_DECL int GORM_UnPackReplaceRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum);
GORM_DLL_DECL int GORM_UnPackIncreaseRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum);
GORM_DLL_DECL int GORM_UnPackGetRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum);
GORM_DLL_DECL int GORM_UnPackDeleteRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum);
GORM_DLL_DECL int GORM_UnPackBatchGetRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum);
GORM_DLL_DECL int GORM_UnPackGetByPartKeyRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum);
GORM_DLL_DECL int GORM_UnPackUpdateRsp(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum);
GORM_DLL_DECL int GORM_UnPackGetByNonPrimaryKey(GORM_Log *pLogger, PB_MSG_PTR        pResponsePbMsg, char *szRspBegin, int iRspLen, GORM_CMD iReqCmd, uint32 ulCBID,
        char &cPreErrCode, uint64 &ulInsertId, int32 &iReturnRecordNum, GORM_Record *&pRecords, int iTableId, GROM_ResponseCode   &rspCode, 
        int32 &iAffectedNum);


}
#endif

