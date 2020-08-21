#ifndef _GORM_CLIENT_RESPONSE_H__
#define _GORM_CLIENT_RESPONSE_H__

#include "gorm_record.h"
#include "gorm_log.h"
#include "gorm_mempool.h"

namespace gorm{

class GORM_ClientEvent;
class GORM_ClientRequest;
class GORM_ClientResponse : public GORM_Noncopyable
{
public:
    GORM_ClientResponse(GORM_Log *pLogger = nullptr);
    ~GORM_ClientResponse();
    // 释放响应请求
    /*
    @func   Release
    @brief  Release释放响应结果
    */
    void Release();
    /*
    @func   GetTableName
    @brief  获取表明
    @retval 表名字符串
    @node   只有在请求数据来自同一张表的时候才有效
    */
    int GetTableName(char *&pTableName);
    // 返回操作的错误码
    /*
    @func   GetResult
    @brief  获取响应的错误码
    @parma  pRetCode 保存错误码,包括mysql产生的错误码与错误信息
    @retval 0  请求成功，不需要解析pRetCode
    @retval 非0     请求没有成功,通过参数获取具体错误信息
    @node   
    */
    int GetResultCode(GROM_ResponseCode *&pRetCode);
    // 获取回调id
    /*
    @func   GetCBID
    @brief  获取请求的回调id，和请求返回的id一一对应
    @retval 回调id
    */
    uint32 GetCBID();
    /*
    @func   GetCmd
    @brief  获取对应请求的cmd
    @retval 请求类型
    */
    GORM_CMD GetCmd();
    // 请求中设置的各种flag标记
    // @node 只有GetResult中响应解包成功了，才有效
    GORM_ResultFlag GetResultFlag() const;
    GORM_IncreaseFlag GetAddableIncreaseFlag() const;
    // 获取下一条记录
    /*
    @func   GetRecord
    @brief  获取结果中的一条记录
    @param  pMsg 获取到的记录
    @iIdx   获取的记录的下标
    @retval 0 成功获取到一条记录
    @retval 非0 获取记录失败
    @node   可以使用danamic_cast<>将结果转成相应的结构体使用
            此结构体外部不能释放
    */
    int GetRecord(OUT GORM_Record *&pPbMsg);
    int GetRecord(IN int iIdx, OUT GORM_Record *&pPbMsg);
    /*
    @func   GetRecord
    @brief  一次性获取多条返回记录
    @param  pPbMsg 外部传入的保存结果的buffer的首地址
    @param  iInLen 保存结果的buffer的长度
    @param  iOutLen 返回的实际的数据个数
    @retval 0 成功获取到一条记录
    @retval 非0 获取记录失败
    @node   可以使用danamic_cast<>将结果转成响应的结构体使用
    */
    int GetRecord(OUT GORM_Record *&pPbMsg, OUT int &iRecordNum);
    int GetNextRecord(OUT GORM_Record *&pPbMsg);
    /*
    @func   GetKey
    @brief  返回响应中带的字段，如果请求中设置只请求部分字段，则生效
    @retval 0   成功
            <0  失败
    */
    int GetReturnFields(vector<int> &returnFields);
    int GetReturnFields(vector<char*> &returnFields);
    
    // last_insert_id结果
    /*
    @func   GetInsertID
    @brief  last_insert_id对应的值
    @retval last_insert_id结果
    */
    uint64 GetInsertID();
    // 结果中的记录条数
    /*
    @func   GetRecordCount
    @brief  结果中记录的条数
    @retval 结果中记录的条数
    */
    int32 GetRecordCount();
    // 受影响的记录的条数
    /*
    @brief  delete,update受影响的行数
    */
    int32 GetAffectedRecordNum();
    int32 GetRecordMatchCount();
    int GetSrcPbMsg(PB_MSG_PTR &pbMsg);
friend class GORM_ClientEvent;
private:
    // 读写线程自动解包
    int UnPack(char *szMsg, int iLen);
    int UnPackInsert();
    int UnPackReplace();
    int UnPackIncrease();
    int UnPackGet();
    int UnPackDelete();
    int UnPackBatchGet();
    int UnPackGetByPartKey();
    int UnPackUpdate();
    int UnPackGetByNonPrimaryKey();
    
private:
    PB_MSG_PTR  pResponsePbMsg = nullptr;  // 响应的pb消息
    PB_MSG_PTR  pCustomColumns;     // 存储配置中没有的列
    char        cPreErrCode = 0;      // 只有头中错误标记为0的时候才需要解码
    int         iReadIdx;               // 已经读取的数据的下标
    int         iTableId = 0;
    int         iTableNum = 0;
    GORM_CMD    iReqCmd = GORM_CMD_INVALID;
    uint32      ulCBID;
    char        *szRspBegin = nullptr;
    int         iRspLen = 0;

    uint8 cPreFlag = 0;
    GROM_ResponseCode   rspCode;
    GORM_Log            *pLogger = nullptr;
    GORM_ResultFlag     cResultFlag = GORM_ResultFlag_RETURN_CODE;
    GORM_IncreaseFlag   increaseFlag = GORM_IncreaseFlag_AutoCreate;
    uint64              ulInsertId = 0;
    int32               iAffectedNum = 0;  
    int32               iReturnRecordNum = 0;
    GORM_Record         *pRecords = nullptr;
    int                 iResultGotIdx = 0;  // 当有多个结果的时候，已经取走的结果的下标
    int64               iReqTime = 0;   // 请求时间
    GORM_ClientRequest  *pRequest;   // 响应对应的请求
};

}
#endif

