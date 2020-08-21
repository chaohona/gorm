#ifndef _GORM_SERVER_H__
#define _GORM_SERVER_H__

#include "gorm_sys_inc.h"
#include "gorm_inc.h"
#include "gorm_log.h"
#include "gorm_client_server_mgr.h"
#include "gorm_record.h"
#include "gorm_client_request.h"
#include "gorm_client_response.h"
#include "gorm_event.h"

namespace gorm{

// 负责客户端和服务器之间的操作的管理
// 对客户端来说这个类就代表服务器
// 由于是通过加载配置好的数据，所以版本号自动加载的
class GORM_Server : public GORM_Noncopyable
{
public:
    GORM_Server();
    virtual ~GORM_Server();

    // 初始化函数
    /**
    @func   Init
    @brief  设置日志指针
    @param  pLogger自定义的日志指针
    @param  ulCfgVersion配置的版本号，默认为0，不指定
    @param  szUrl.GORMSvr的地址，默认可以不传，可以通过SetServerUrl设置服务器地址
    @retval 0     设置成功
    @retval <0    失败，返回对应的错误码。
    */
    int Init(GORM_Log *pLogger, const char* szCfgVersion=nullptr, const char *szUrl=nullptr);
    /**
    @func   Init
    @brief  设置服务器地址
    @param  szUrl 服务器地址
    @retval 0     设置成功
    @retval <0    失败，返回对应的错误码。
    */
    int SetServerUrl(const char *szUrl);
    /**
    @brief  设置签名信息，仅用于TCAPLUS_API_APP_SIGNUP_REQ命令号
    @param [IN] type          鉴权类型，目前只支持0，表示静态密码
    @param [IN] signature     签名信息字符串，长度不能超过TCAPDIR_SIGNATURE_LEN。
    @retval 0 设置成功
    @retval <0 失败，返回对应的错误码
    @node   只有在握手的时候会调用
    */
    int SetSignature(int type, const char* signature);

    // 资源释放函数
    /**
    @func   Fini
    @brief  程序结束释放资源函数
    */
    void Fini();

    // 开始启动服务器线程，启动成功就可以工作了
    // 启动函数主要是连接GORM_Svr
    /**
    @func   Start
    @brief  此处会经历启动线程，和服务器建立连接成功整个过程
    */
    bool Start();

    // 重新加载配置,暂时是空接口
    bool ReloadTable(const char *szTablePath);

    // 获取一个打包类
    /**
    @func   GetRequest
    @brief  获取一个请求句柄，请求的参数在Requet里面设置
    @param  cmd 操作的类型,具体值参考GORM_CMD
    @param  iTableId表的类型，每次只能操作一个表
    @retval 0     设置成功
    @retval <0    失败，返回对应的错误码。
    @node   目前，每个请求只能操作一个指定的表
            如果没有指定表，则GORM_ClientRequest中必须指定表信息
    */
    //GORM_ClientRequest *GetRequest(int iTableId);
    //GORM_ClientRequest *GetRequest(const char *szTableName);
    // 批量操作中，使用到不同的表用此接口
    //GORM_ClientRequest *GetRequest();
    GORM_ClientRequest *GetRequest(GORM_CMD cmd, int iTableId = 0);

    /**
    @func   GetRequestFor....
    @brief  为特定操作获取一个请求句柄，请求的参数在Requet里面设置
    @param  iTableId 表的类型，每次只能操作一个表
    @retval 0     设置成功
    @retval <0    失败，返回对应的错误码。
    @node   目前，每个请求只能操作一个指定的表
    */
    GORM_ClientRequest *GetRequestForInsert(int iTableId = 0);
    GORM_ClientRequest *GetRequestForReplace(int iTableId = 0);
    GORM_ClientRequest *GetRequestForIncrease(int iTableId = 0);
    GORM_ClientRequest *GetRequestForGet(int iTableId = 0);
    GORM_ClientRequest *GetRequestForDelete(int iTableId = 0);
    GORM_ClientRequest *GetRequestForBatchGet(int iTableId = 0);
    GORM_ClientRequest *GetRequestForGetByPartKey(int iTableId = 0);
    GORM_ClientRequest *GetRequestForUpdate(int iTableId = 0);
    // 批量取同一个路由下面的数据，不做分页，最多可以取1024条数据.以字段a为路由select a,b,c from table where a=1 and b=2 limit 1024;
    // 使用场景举例:获取同一个用户下面的多个账号信息
    GORM_ClientRequest *GetRequestForGetByNonPrimaryKey(int iTableId = 0);
    
    GORM_ClientRequest *GetRequestForInsert(const char *szTableName);
    GORM_ClientRequest *GetRequestForReplace(const char *szTableName);
    GORM_ClientRequest *GetRequestForIncrease(const char *szTableName);
    GORM_ClientRequest *GetRequestForGet(const char *szTableName);
    GORM_ClientRequest *GetRequestForDelete(const char *szTableName);
    GORM_ClientRequest *GetRequestForBatchGet(const char *szTableName);
    GORM_ClientRequest *GetRequestForGetByPartKey(const char *szTableName);
    GORM_ClientRequest *GetRequestForUpdate(const char *szTableName);
    GORM_ClientRequest *GetRequestForGetByNonPrimaryKey(const char *szTableName);

    // 将打包好的请求发送给服务器
    /**
    @func   SendRequest....
    @param  pRequest 打包之后的请求
    @param  ulCBID 发送请求的回调ID
    @param  bAutoRecycle 是否自动回收请求请求资源，默认自动回收
    @retval 0     设置成功
    @retval <0    失败，返回对应的错误码。
    @node   ulCBID 是请求的回调，在底层是rpc请求对应的id
            此处需要和发送线程交互
            ulCBID为3字节循环使用，长时间下有可能会重复，业务层不可长期保存
    */
    int SendRequest(GORM_ClientRequest *pRequest,     uint32 &ulCBID, bool bAutoRecycle=true);


    // 获取一个响应
    /**
    @func   RecvResponse
    @brief  获取一个响应结果
    @param  response 结果的指针
    @retval 0     获取结果成功
    @retval <0    获取结果失败
    @node   需要和持久化线程交互
    */
    int RecvResponse(GORM_ClientResponse *&response);
    // 获取一组响应
    int RecvResponse(list<GORM_ClientResponse*> &list);

    /**
	@brief 获取service api 的版本号，该版本号即为service api所在的发布包的版本号
	@retval 返回指向版本号的指针，例如版本号为"2.1.13.52612.x86_64_release_20131010"
	**/
    const char* GetApiVersion();
private:
    // 启动工作线程,和业务线程已经不是一个线程了
    void StartWork();
private:
    char                szCfgVersion[MAX_VERSION_LEN];  // 配置版本号
    GORM_Log            *pLogger = nullptr;             // 日志指针
    char                szServerUrl[MAX_URL_LEN];       // GORMSvr的地址 127.0.0.1:8880/127.0.0.1:8881
    std::once_flag      onceCallFlag;
    GORM_ClientSvrMgr   *pSvrMgr = nullptr;             // 和GORMSvr连接的管理器
    char                szSignature[GORM_DB_PW_MAX_LEN];
};

}
#endif

