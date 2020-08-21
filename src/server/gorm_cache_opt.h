#ifndef _GORM_CACHE_OPT_H__
#define _GORM_CACHE_OPT_H__

#include "gorm_sys_inc.h"
#include "gorm_inc.h"
#include "gorm_socket.h"
#include "gorm_config.h"
#include "gorm_db_request.h"

using namespace gorm;
class GORM_CacheOpt
{
public:
    virtual ~GORM_CacheOpt();
    virtual int Init(GORM_Config *pConfig) = 0;

    virtual int GetResultFromCache(GORM_DBRequest *pRequst, bool &bGot) = 0;
    virtual int UpdateCache(GORM_DBRequest *pRequst) = 0;
public:
};

#endif
