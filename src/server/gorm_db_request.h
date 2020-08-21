#ifndef _GORM_DB_REQUEST_H__
#define _GORM_DB_REQUEST_H__

#include "gorm_sys_inc.h"
#include "gorm_event.h"
#include "gorm_define.h"
#include "gorm_msg_helper.h"
#include "gorm_pb_proto.pb.h"

// TODO 做成模板，按请求的类型
using namespace gorm;
class GORM_MemPoolData;
class GORM_DBConnMgr;
class GORM_DBConnPool;
class GORM_FrontEndThread;
class GORM_WorkThread;
class GORM_CacheOpt;
class GORM_DBRequest
{
public:
    GORM_DBRequest();
    virtual ~GORM_DBRequest();

    int SendToWorkThread();
    int ParseReqMsg(char *szMsg = nullptr, int iMsgLen = 0);
    int AddTableToRsp();
    int SetNowReqProcTable();

    virtual int InsertReq() = 0; 
    virtual int ReplaceReq() = 0;
    virtual int IncreaseReq() = 0;
    virtual int GetReq() = 0;
    virtual int DeleteReq() = 0;
    virtual int BatchGetReq() = 0;
    virtual int GetByPartKeyReq() = 0;
    virtual int UpdateReq() = 0;
    virtual int GetByNonPrimaryKey() = 0;

    virtual int PackBatchGetResult() = 0;
    virtual int PackGetByPartkeyResult() = 0;

    virtual int BatchGetNext() = 0;

    virtual int PackResult() = 0;
    int GetResult(int iErrCode = GORM_OK, int iDBErrNo = 0, char *szErrInfo = nullptr);
    void GetAllResult(int iErrCode = GORM_OK, int iDBErrNo = 0, char *szErrInfo = nullptr);

    void Release();

    // 设置pb消息中的头
    void PackPbRetCode(GORM_PB_Ret_Code *pRetCode);
private:
    void SetDbErrInfo(int iErrCode = GORM_OK, int iDBErrNo = 0, char *szErrInfo = nullptr);
public:
    GORM_Event  *pFrontendEvent = nullptr;
    GORM_DBConnPool *pDbPool = nullptr;
    //GORM_CacheOpt   *pCacheOpt = nullptr;
    
    GORM_DBConnMgr *pDBMgr = nullptr;
    uint8           iSentToWorkThread = 0;  // 是否已经发送给工作线程
    uint8           iPreGood = 0;         // 前面一个消息已经有响应了 0：没有 1：收到响应
    uint8           iWaitRsp = 0;         // 自己是否收到响应 0：没收到，1：收到响应
    uint8           iWaitDone = 0;        // 已经得到响应了
    uint8           iRspDone = 0;         // 响应是否发送完成

    int32 iGotRspNum = 0;   // 获取到的响应的条数
    int32 iReqNum = 1;      // 发出的请求的数量

    uint32              uiReqFlag = 0;
    GORM_MemPoolData    *pReqData = nullptr;    // 组装的请求SQL语句
    int                 iReqTableId = GORM_PB_TABLE_IDX_MIN__;          // 请求的表编号
    uint32              uiReqID = 0;
    int                 iErrCode = 0;
    char                cReplyFlag = GORM_ResultFlag_RETURN_CODE;   // 如果需要获取到最终的结果，会在结果返回之后再执行一遍get请求操作
    bool                bGotReturn = false;                         // 已经获取到需要返回的结果了
    GORM_GET_FLAG       iGetFlag   = GORM_GET_FLAG_NON_RETURN;
    int                 iDBErrCode = 0;
    GORM_MemPoolData    *pDbErrorInfo = nullptr;
    GORM_CMD            iReqCmd = GORM_CMD_INVALID;
    GORM_CMD            iRedirectCmd = GORM_CMD_INVALID;
    PB_MSG_PTR          pReqPbMsg = nullptr;              // 收到的前端的pb请求消息
    PB_MSG_PTR          pRspPbMsg = nullptr;
    GORM_MemPoolData    *pRspData = nullptr;

    GORM_IncreaseFlag increaseFlag = GORM_IncreaseFlag_NoAutoCreate;

    GORM_FrontEndThread *pFrontThread = nullptr;
    GORM_WorkThread     *pWorkThread = nullptr;

    gorm::GORM_PB_REQ_HEADER    *pHeader = nullptr;
    gorm::GORM_PB_TABLE         *pNowReqProcTable = nullptr;          // 当前请求所对应的表信息

    gorm::GORM_PB_TABLE         *pNowRspProcTable = nullptr;            // 当前响应需要填充的table

    uint32 uiHashValue = 0;
    int staticRequest = 0;      // 此标记为1，则不会被回收
};

#endif
