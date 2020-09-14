// copy from zDBConnPool.h

#ifndef _GORM_DB_CONN_POOL_H__
#define _GORM_DB_CONN_POOL_H__

#include "gorm_sys_inc.h"
#include "gorm_singleton.h"
#include "gorm_noncopyable.h"
#include "gorm_inc.h"
#include "gorm_db_config.h"
#include "gorm_define.h"
#include "gorm_event.h"
#include "gorm_db_request.h"

class GORM_DBInfo;
class GORM_DBConnPool
{
public:
    GORM_DBConnPool(int iMaxPoolSize);
    virtual ~GORM_DBConnPool();

    // 传入数据库，连接地址列表
    virtual bool Init(GORM_DBInfo *pDbCfg, const mutex *m) = 0;
    virtual bool GeneralUrl(GORM_DBInfo *pDbCfg) = 0;
    virtual void Loop() = 0;
    virtual int SendRequest2DB(GORM_DBRequest *pRequest) = 0;
public:
    int     m_iMaxPoolSize = 1; // 每个库最大的连接数
    char    m_szUrl[MAX_URL_LEN];
    string  m_strName;
    GORM_DBInfo *pDbInfo;   // 此链接对应的db信息
};

struct UrlInfo
{
public:
	const unsigned int hashcode;
	const std::string url;
	const bool supportTransactions;

	char host[NET_IP_STR_LEN];
	char user[GORM_DB_USER_MAX_LEN];
	char passwd[GORM_DB_PW_MAX_LEN];
	unsigned int port;
	char dbName[GORM_DB_MAX_LEN];

    UrlInfo(char *host, char *user, char *pw, int port, char *dbName, bool supportTransactions= false);
	UrlInfo(const unsigned int hashcode,const std::string &url, bool supportTransactions=false);
	UrlInfo(const UrlInfo &ui);

private:
	void parseMySQLURLString();
};


#endif
