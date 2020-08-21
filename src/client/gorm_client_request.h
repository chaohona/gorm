#ifndef _GORM_CLIENT_REQUEST_H__
#define _GORM_CLIENT_REQUEST_H__

#include "gorm_sys_inc.h"
#include "gorm_record.h"
#include "gorm_define.h"
#include "gorm_msg_helper.h"
#include "gorm_mempool.h"
#include "gorm_client_server_mgr.h"
#include "gorm_log.h"

namespace gorm{

// 客户端请求封装类
// 用于打包请求消息
// 重点封装KV操作
using CS = const string;
using CC = const uint8*;
/*
以下为请求协议
4字节长度 | 1字节操作类型 | 3字节请求编号 | 1字节flag | 请求内容
*/
//
class GORM_Server;

class GORM_ClientRequest
{
public:
    GORM_ClientRequest();
    ~GORM_ClientRequest();
public:
    /**
    @brief 重置请求数据，以便用于下一次请求准备
    @param [IN]    iTableId     表的类型,默认0不指定表类型
    @param [IN]    cmd            请求操作类型，具体参见 \link GORM_CMD \endlink
    @param [IN]    seq            请求消息序列号，目前gorm不会处理此字段，gorm会将此值不变地通过请求对应的响应消息带回来
    @retval 0    成功
    @retval <0   失败，返回对应的错误码。
    */
    int Init(GORM_CMD iCmd, int iTableId = 0, GORM_Log *pLogger = nullptr);
    int Init(GORM_CMD iCmd, GORM_Log *pLogger);
    // 设置版本号校验规则
    /**
    @func   SetCheckDataVersionPolicy
    @brief  设置版本号校验规则
    @param  ver. 版本号校验规则
    @retval 0     设置成功
    @retval <0    失败，返回对应的错误码。
    @node   目前提供三种版本号校验规则
    */
    int SetCheckDataVersionPolicy(GORM_CheckDataVerType ver);
    /*
    @brief  设置串行化id，不同的businessid请求可以并行处理，默认所有请求都串行处理
    @param  iBusinessId 串行化id
    @node   多协程的业务，此值在大部分情况下可以是协程id
            玩家之间的数据如果没有管理，也可以是玩家id

            预留此接口，目前服务器还不支持此功能
    */
    void SetBusinessId(int32 iBusinessId    );
    /**
    @brief  设置响应标志。主要用于Generic表的insert、increase、replace、update、delete操作和list表的单个delete操作。
    @param  result_flag  请求标志。
                GORM_ResultFlag_RETURN_CODE         // 结果返回成功与否就可以
                GORM_ResultFlag_RETURN_NEW_VALUE    // 将变更的字段带回来
                GORM_ResultFlag_RETURN_ALL_VALUE    // 将所有的字段带回来
    @retval 0    设置成功
    @retval <0   失败，返回对应的错误码
    */
    int SetResultFlag(GORM_ResultFlag flag);
    /**
    @brief  获取响应标志
    @return 返回响应标志
    */
    GORM_ResultFlag GetResultFlag();
    /**
    @brief  设置空记录自增允许标志。用于Generic表的increase操作。
    @param  [IN] increase_flag  空记录自增允许标志。
            GORM_IncreaseFlag_AutoCreate    空值也允许自增自减，这种情况下将按字段默认值创建新记录再自增，若无默认值则返回错误。
            GORM_IncreaseFlag_NoAutoCreate  表示空值不允许自增自减
    @retval 0    设置成功
    @retval <0   失败，返回对应的错误码。通常因为未初始化。
    @node   目前此标记没有实现
    */
    int SetAddableIncreaseFlag(IN GORM_IncreaseFlag increase_flag);

    /**
    @brief  获取空记录自增允许标志
    @return 返回空记录自增允许标志
    */
    GORM_IncreaseFlag GetAddableIncreaseFlag();

    /**
    @brief 设置需要查询或更新的字段名称列表，即部分字段查询和更新，
    		可用于partkeyget操作。
    @param [IN] field_name    需要查询或更新的字段名称列表，每个字段名称不超过32字节，名称以'\0'结尾
    @param [IN] field_count   字段名称个数
    @retval 0                 设置成功
    @retval <0                设置失败，具体错误参见 \link ErrorCode \endlink
    @note 该函数不仅仅用于部分字段查询，当在更新操作中(replace, update, listreplace操作)
    	使用SetData()函数设置数据时，如果只需要更新部分字段，可以使用该
    	函数设定需要更新的字段，但是，注意，在进行部分字段更新时，一
    	定要先调用SetData()函数，然后再调用SetFieldNames()函数，这样才能达到部分
    	部分字段更新的功能。
    	
    @note 多次调用会覆盖之前的结果，如果增量调用请使用函数AddField

    */
    int AddField(IN const char* field_name[], IN const unsigned field_count);
    int AddField(int *vFiledId, uint32 uiCnt);
    int AddField(IN const char* field_name);
    int AddField(int iFiledId);
    int AddField(IN vector<char*> &vFields);
    int AddField(IN vector<int> &vFields);

    /**
    @brief  设置是否需要对该请求做压缩的开关和是否需要对该请求的响应做压缩的开关。
                     目前仅支持用于Generic表的get, batchget操作(命令字)。对于不支持的操作(命令字)
                     该函数的执行是无害空操作虽然其会返回错误提示ServiceApi用户。对于不支
                     持的操作(命令字)ServiceApi一定是不会压缩解压消息的。
               注意: 该函数的作用域仅仅在于当前1条request消息及其对应的response消息，
                     当要处理新的request消息 时需要再次调用该函数.在处理1条request消息时如果
                     没有调用该函数则相当于req_compress_switch是SWITCH_OFF的并且resp_compress_switch是SWITCH_OFF的.
    @param  [IN] req_compress_switch, 可取值SWITCH_OFF或SWITCH_ON。
                        SWITCH_OFF表示不需要对该请求做压缩; SWITCH_ON表示需要对该请求做压缩. 
                 [IN] resp_compress_switch, 可取值SWITCH_OFF或SWITCH_ON。
                        SWITCH_OFF表示不需要对该请求的响应做压缩; SWITCH_ON表示需要对该请求的响应做压缩. 
    @retval 0    设置成功
    @retval != 0   设置失败，返回对应的错误码。
   */
    int32_t SetCompressSwitch(IN GORM_SWITCH req_compress_switch, IN GORM_SWITCH resp_compress_switch);

     /**
     @brief 获取是否需要对该请求做压缩的开关值以及是否需要对该请求的响应做压缩
                      的开关值。
               目前仅支持用于Generic表的get, batchget操作(命令字)。对于不支持的操作(命令字)
                     该函数会返回错误当然输出参数的值也是无意义的。对于不支持的
                     操作(命令字)ServiceApi一定是不会压缩解压消息的。
     @param  [OUT] req_compress_switch, 值可能为SWITCH_OFF或SWITCH_ON。
                           SWITCH_OFF表示不需要对该请求做压缩; SWITCH_ON表示需要对该请求做压缩. 
                  [OUT] resp_compress_switch, 值可能为SWITCH_OFF或SWITCH_ON。
                           SWITCH_OFF表示不需要对该请求的响应做压缩; SWITCH_ON表示需要对该请求的响应做压缩. 
     @retval 0    获取成功
     @retval != 0   获取失败，返回对应的错误码。
    */
     int GetCompressSwitch(OUT GORM_SWITCH& req_compress_switch, OUT GORM_SWITCH& resp_compress_switch);
     /**
     @brief  设置记录的过期时间
     @param  [IN]  expire_time. 过期时间，单位为毫秒
     @retval 0     设置成功
     @retval <0    失败，返回对应的错误码。通常因为某些操作类型(cmd)不支持这种访问方式
     @node   TODO 未实现
     */
     int SetExpireTime(int64 expire_time);

    // 非kv操作需要先获取一条Record，然后设置参数,但是分表信息还是通过SetSplitInfo设置
    /**
    @brief  添加一条记录，如果是同事操作多张表，则此处iTableId不能省略
    @param  pRecord 外带的申请到的记录数据
    @param  iTableId 记录所在的表<如果获取Request的时候已经指定表类型了，则此处默认为Request中指定的表类型>
    @retval 0 成功
    @retval <0  申请失败，大部分是因为表类型不对，或者申请Request的时候没有指定表类型
    */
    int AddRecord(OUT GORM_Record *&pRecord,    int iTableId = 0);
    /**
    @brief  添加一条记录，如果是同事操作多张表，则此处iTableId不能省略,
    @param  pRecord 外带的申请到的记录数据
    @param  iTableId 记录所在的表<如果获取Request的时候已经指定表类型了，则此处默认为Request中指定的表类型>
    @param  pPbMsg  记录对应的表数据
    @retval 0 成功
    @retval <0  申请失败，大部分是因为表类型不对，或者申请Request的时候没有指定表类型
    @node   如果已经设置好PB数据，可以一并设置,否则此函数会自动创建一个pb记录
    */
    int AddRecord(OUT GORM_Record *&pRecord, PB_MSG_PTR pPbMsg, int iTableId = 0);

    /**
    @brief  获取请求操作类型
    @retval TCAPLUS_API_INVALID_REQ  未初始化时，返回此无效命令号。
    @retval \link TCaplusApiCmds \endlink
    */
    GORM_CMD GetCmd();
    
    const char *GetTableName();
    int GetTableId();

    /*
    @func   Release
    @brief  释放请求资源
    @node   如果发送请求的时候指明不需要自动释放，则需要手动调用此函数
    */
    void Release();
    int SetOffSet();
    int SetLimited();

    const GORM_FieldsOpt& FieldMode();
    
friend class GORM_Server;
friend class GORM_ClientEvent;

private:
    // 打包请求成二进制数据
    int PackRequest();
    int PackInsert();
    int PackReplace();
    int PackIncrease();
    int PackGet();
    int PackDelete();
    int PackBatchGet();
    int PackGetByPartKey();
    int PackUpdate();
    int PackGetByNonPrimaryKey();

    int AddRecordCheck();
private:
    GORM_Record *vRecords[GORM_MAX_RECORD_ONE_REQ];     // 请求的记录，每次最多可以带64个记录
    int iNowRecordNum = 0;
    PB_MSG_PTR pPbMsg = nullptr;              // pb消息
    int iTableId = 0;               // 操作的表类型
    uint32 ulSeqId = 0;             // 请求的序列号，在调用发送接口的时候生成
    GORM_CMD iReqCmd = GORM_CMD_INVALID;                // 请求类型
    int iBusinessId = 0;
    uint8 reqPreFlag = 0;                  // 请求头中的flag，是否压缩等信息
    uint32 uiReqFlag = 0;                  // 请求PB协议中的"4字节flag"，包含值的返回方式等信息
    GORM_ResultFlag cResultFlag = GORM_ResultFlag_RETURN_CODE;
    GORM_IncreaseFlag increaseFlag = GORM_IncreaseFlag_AutoCreate;
    GORM_CheckDataVerType   iVerPolicy = NOCHECKDATAVERSION_AUTOINCREASE;
    bool bAutoRecycle   = true;     // 是否自动回收request
    GORM_MemPoolData    *pMsgBuffer = nullptr;// 请求协议生成的二进制数据
    char *szSendPos = nullptr;  // 已经发送到的位置
    GORM_FieldsOpt fieldMode;
    GORM_Log *pLogger = nullptr;
};

}
#endif
