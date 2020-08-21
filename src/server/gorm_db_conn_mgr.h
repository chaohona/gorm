#ifndef _GORM_DB_CONN_MGR_H__
#define _GORM_DB_CONN_MGR_H__

#include "gorm_sys_inc.h"
#include "gorm_db_conn_pool.h"
#include "gorm_db_config.h"
#include "gorm_event.h"
#include "gorm_db_request.h"
#include "gorm_object_pool.h"
#include "gorm_pb_proto.pb.h"

using namespace gorm;
// 先做成一个线程一个连接池，TODO改成所有线程共享一个连接池
class GORM_WorkThread;
class GORM_DBConnMgr 
{
public:
    GORM_DBConnMgr();
    virtual ~GORM_DBConnMgr();

    GORM_Ret Init(GORM_WorkThread *pWorkThread, mutex *m);
    void Loop();
    // 获取请求的路由的数据库
    int GetDBPool(int iTableId, uint32 uiHashValue, GORM_DBConnPool *&pDbPool);
    int RequestNum(); // 返回当前没有处理的请求的个数，如果有请求没有处理，则接着处理，否则休眠等待唤醒
private:
    GORM_Ret CreatePool(GORM_DBInfo *pDbInfo, int iIndex, mutex *m);
private:
    int m_iPoolNum = 0;
    GORM_DBConnPool **m_pDBPool;
    GORM_WorkThread *m_pWorkThread;
    DBType          m_iDBType = DBType_NONE;
    mutex       m_Mutex;
};


#endif
