#ifndef _GORM_ERROR_H__
#define _GORM_ERROR_H__

// 小于0为错误码，大于0为Code
using GORM_Ret=int;

#define     GORM_RING_FULL              2
#define     GORM_GET_ALL_DATA           1
#define     GORM_OK                     0

#define     GORM_ERROR                  -1
#define     GORM_EAGAIN                 -2
#define     GORM_INVALID_CLIENT         -3
#define     GORM_PART_FAILED            -4  // 请求部分失败
#define     GORM_INVALID_TABLE          -5  // 无效的表
#define     GORM_RESET                  -6  // 重复设置
#define     GORM_TOO_MUCH_RECORD        -7  // 太多record
#define     GORM_INIT_RECORD            -8
#define     GORM_INVALID_FIELD          -9  // 无效的field
#define     GORM_PACK_REQ_ERROR         -10 // 打包请求失败
#define     GORM_REQ_NO_RECORDS         -11 // 没有往请求中放入record
#define     GORM_MULTI_TABLES           -12 // 有多张表
#define     GORM_RSP_UNPACK_FAILED      -13 // 响应解包失败
#define     GORM_CONN_CLOSED            -14 // 连接已经关闭了
#define     GORM_CONN_FAILED            -15 // 连接GORM服务器失败
#define     GORM_DB_ERROR               -16 // 数据库发生错误,此时需要根据db信息获取进一步错误信息
#define     GORM_NO_DB                  -17 // 没有找到db
#define     GORM_REQ_MSG_ERROR          -18 // 请求信息错误
#define     GORM_NOT_SUPPORT_CMD        -19 // 不支持的命令
#define     GORM_UNPACK_REQ             -20 // 解压缩请求信息出错
#define     GORM_PACK_RSP_ERROR         -21 // 压缩响应消息出错
#define     GORM_REQ_MSG_NO_HEADER      -22 // 请求没有设置消息头
#define     GORM_REQ_NEED_SPLIT         -23 // split信息没有带全
#define     GORM_REQ_TOO_LARGE          -24 // 请求数据太大
#define     GORM_DB_2_STRUCT_ERROR      -25 // db结果转换到struct出错，一般都是版本对不上导致
#define     GORM_NO_MORE_RECORD         -26 // 没有更多record
#define     GORM_VERSION_NOT_SET        -27 // 没有设置版本号
#define     GORM_CACHE_ERROR            -28 // 操作缓存错误
#define     GORM_NO_VALUE               -29 // 没有对应的值
#define     GORM_INVALID_VALUE_TYPE     -30 // 无效的类型



#define     GORM_GET_CMD_SETED          -1001 // get命令重复增加record，get命令只能获取一条信息

struct RetStringTable
{
    GORM_Ret   iCode;
    const char *pString;
};

const char *GORM_ErrStr(int iRet);

#ifdef _WIN32

#define strerror(no) ""

#endif


#endif

