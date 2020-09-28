#ifndef _GORM_DEFINE_H__
#define _GORM_DEFINE_H__

#include "gorm_type.h"
namespace gorm{
/** \brief 输入参数类型 */
#ifndef IN
#define IN   
#endif


/** \brief 输出参数类型 */
#ifndef OUT 
#define OUT    
#endif

/** \brief 输入输出参数类型 */
#ifndef INOUT 
#define INOUT    
#endif

#define MAX_VERSION_LEN 128
#define NET_IP_STR_LEN  46


#define MAX_HOSTSIZE	128
#define MAX_URL_LEN     1024

#define GORM_DEFAULT_RSP_DATA_LEN 1024

#define GORM_DB_FIELD_MAX_LEN   256      // 列名最大长度
#define GORM_DB_TABLE_MAX_LEN   256     // 表名最大长度
#define GORM_DB_IDENTY_MAX_LEN  256     // 数据库标识
#define GORM_DB_USER_MAX_LEN    512     // 用户名最大长度
#define GORM_DB_PW_MAX_LEN      64          // 数据库密码最大长度
#define GORM_DB_TYPE_MAX_LEN    32      // 数据库类型最大长度(目前仅有mysql与mongo)
#define GORM_DB_MAX_LEN         256             // db名字最大长度

#define GORM_DB_MAX_DB_LIST     128
#define GORM_DB_MAX_TABLE_NUM   4096
#define GORM_REQUEST_BUFF_LEN   1024*16

#define GORM_DB_MGO             "mongo"
#define GORM_DB_MYSQL           "mysql"

#define GORM_CACHE_REDIS        "redis"

#define GORM_VERSION_FIELD_STR  "version"

#define GORM_MAX_RECORD_ONE_REQ 128

#define GORM_CACHE_SWITCH 0

// 最多不超过128个工作线程
#define GORM_MAX_WORK_THREAD_NUM 128
#define GOMR_MAX_CONNECT_NUM_PER_THREAD 128

// 前端接入线程最多不能积攒超过1000万个请求
#define GORM_FRONT_REQUEST_QUEUE_LEN 0x7FFFFF
#define GORM_WORK_REQUEST_QUEUE_LEN 0x7FFFF


enum GORM_CacheType
{
    GORM_CacheType_None     = 0,    // 不带缓存
    GORM_CacheType_Redis    = 1,
};

// version版本检查策略
enum GORM_CheckDataVerType
{
    CHECKDATAVERSION_AUTOINCREASE = 1,  /* 检测记录版本号,只有当该版本号与服务器端的版本号相同时，该版本号才会自增 */
    NOCHECKDATAVERSION_OVERWRITE = 2,   /* 不检测记录版本号，强制把客户端的记录版本号写入到服务器中 */
    NOCHECKDATAVERSION_AUTOINCREASE = 3,   /* 不检测记录版本号，将服务器端的版本号自增 */
};

/* SWITCH*/
enum GORM_SWITCH 
{
    GORM_SWITCH_OFF = 0, 
    GORM_SWITCH_ON = 1, 
};

/** \brief 更新操作类型定义 */
enum GORM_Operation
{
    /** \brief 增量加操作 */
    GORM_OP_PLUS     = 1,

    /** \brief 增量减操作 */
    GORM_OP_MINUS    = 2,
};


// GORM客户端与服务器之间通信的协议号
/*enum GORM_CMD : uint8
{
    GORM_CMD_INVALID            = 0,    // 无效协议
    GORM_CMD_HEART              = 1,    // 心跳，内部使用的协议

    GORM_CMD_GET_CLIENT_ID      = 2,    // 握手，获取客户端id过程
*/
    /*
    暂只支持单条记录插入
    多条记录同时插入，不能保证原子性(即全插入成功，或者全插入失败)
    */
/*    GORM_CMD_INSERT             = 3,    // 增加记录

    GORM_CMD_REPLACE            = 4,    // 有则替换，没有则插入

    GORM_CMD_INCREASE           = 5,    // 增量更新请求

    GORM_CMD_GET                = 6,    // 单条查询请求

    GORM_CMD_DELETE             = 7,    // 删除请求

    GORM_CMD_BATCH_GET          = 8,    // 批量查询请求

    GORM_CMD_GET_BY_PARTKEY     = 9,    // 部分key查询请求

    GORM_CMD_UPDATE             = 10,    // 更新请求

    GORM_CMD_GET_BY_NON_PRIMARY_KEY = 11,   // 通过非主键批量获取
        
    // 协议编号不能超过255
    GORM_CMD_MAX                = 255,      
};*/

#define GORM_FLAG_REQ_COMPRESS          0b1     // 请求是被压缩过的
#define GORM_FLAG_RSP_COMPRESS          0b10    // 响应需要被压缩

// 最多可以设置32个标记
enum GORM_ReqFlag
{
    // 0-1 返回数据flag
    GORM_REQ_FLAG_RETURN_NEW_VALUE  = 0b1,      // 将变更的字段带回来
    GORM_REQ_FLAG_RETURN_ALL_VALUE  = 0b10,     // 将所有的字段带回来
    GORM_REQ_FLAG_RETURN_CODE       = 0b00,    // 结果返回成功与否就可以

    // 2 空值是否可以自增
    GORM_REQ_FLAG_EMPTY_INCREASE    = 0b100,    // 空值也可以自增,自减

    GORM_REQ_FLAG_MODE      = 0xFFFFFFFF,
};

enum GORM_ResultFlag
{
    GORM_ResultFlag_RETURN_CODE      = 0,
    GORM_ResultFlag_RETURN_NEW_VALUE = 1,
    GORM_ResultFlag_RETURN_ALL_VALUE = 2,
};

enum GORM_IncreaseFlag
{
    GORM_IncreaseFlag_AutoCreate    = 0,      // 默认值，如果没有记录则用默认值创建一条记录，并进行加减操作
    GORM_IncreaseFlag_NoAutoCreate  = 1,
};

enum GORM_LOG_LEVEL{
    GORM_LOG_LEVEL_NONE,
    GORM_LOG_LEVEL_ERROR,
    GORM_LOG_LEVEL_WARNING,
    GORM_LOG_LEVEL_INFO,
    GORM_LOG_LEVEL_DEBUG,
};

enum GORM_GET_FLAG {
    GORM_GET_FLAG_NON_RETURN = 0,
    GORM_GET_FLAG_NON_INSERT = 1,
};

#ifdef _WIN32

#define strncpy strncpy_s

#endif

#ifdef _WIN32
    #ifdef GORM_DLL_EXPORT
        #define GORM_API
        //#define GORM_API __declspec(dllexport)
    #else
        #define GORM_API
        //#define GORM_API __declspec(dllimport)
    #endif // GAMESH_NET_DLL_EXPORT

#else
    #define GORM_API
#endif

#ifdef __cplusplus
    #define GORM_DLL_DECL GORM_API
    #define GORM_DLL_C_DECL extern "C" GORM_API
#else
    #define GORM_DLL_DECL GORM_API
    #define GORM_DLL_C_DECL GORM_DLL_DECL
#endif //__cplusplus



}


#endif

