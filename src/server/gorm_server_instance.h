#ifndef _GORM_SERVER_INSTANCE_H__
#define _GORM_SERVER_INSTANCE_H__
#include "gorm_inc.h"

// grom server 主线程，用于管理工作
class GORM_ServerInstance: public GORM_Noncopyable, public GORM_Singleton<GORM_ServerInstance>
{
public:
    virtual ~GORM_ServerInstance();

    int Init();
};

#endif