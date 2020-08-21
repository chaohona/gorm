#ifndef _GORM_REDIS_H__
#define _GORM_REDIS_H__

//#include "hiredis/async.h"
#include "gorm_sys_inc.h"
#include "gorm_inc.h"
#include "gorm_socket.h"
#include "gorm_config.h"
#include "gorm_cache_opt.h"

using namespace gorm;
class GORM_Redis : public GORM_CacheOpt
{
public:
    GORM_Redis();
    ~GORM_Redis();

    int Init(GORM_Config *pConfig);

    virtual int GetResultFromCache(GORM_DBRequest *pRequst, bool &bGot);
    virtual int UpdateCache(GORM_DBRequest *pRequst);
private:
    int ConnectRedis();
private:
    /*string m_strRedisServer;

    int m_iAddrIdx = 0;
    vector<GORM_Address> m_vAddress;

    redisContext *m_pRedisConn = nullptr;

    int m_iConnectTTS = 200;*/
};

#endif
