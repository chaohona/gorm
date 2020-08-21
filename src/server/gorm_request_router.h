#ifndef _GORM_REQUEST_ROUTER_H__
#define _GORM_REQUEST_ROUTER_H__
#include "gorm_inc.h"
#include "gorm_sys_inc.h"
#include "gorm_singleton.h"

// 管理请求的路由，直接路由到work进程中的GORM_MySQLEvent中
class GORM_RequestRouter : public GORM_Singleton<GORM_RequestRouter>
{
public:
atomic<uint8>   m_iWorkExpandFlag;  // 工作线程是否在扩容，在扩容期间，则需要加锁
};

#endif
