#include "gorm_db_conn_mgr.h"
#include "gorm_db_config.h"
#include "gorm_log.h"
#include "gorm_mysql_conn_pool.h"

GORM_DBConnMgr::GORM_DBConnMgr()
{
}

// 进程已经结束了，内存就不管了
GORM_DBConnMgr::~GORM_DBConnMgr()
{
    /*if (this->m_pDBPool != nullptr)
    {
        delete []m_pDBPool;
    }*/
}

GORM_Ret GORM_DBConnMgr::Init(GORM_WorkThread *pWorkThread, mutex *m)
{
    m_pWorkThread = pWorkThread;
    this->m_pDBPool = new GORM_DBConnPool*[GORM_DB_MAX_DB_LIST];
    bzero(this->m_pDBPool, sizeof(GORM_DBConnPool*)*GORM_DB_MAX_DB_LIST);

    GORM_RouteInfo *pRoute = GetDatabaseRoute();
    if (pRoute == nullptr)
    {
        GORM_LOGE("get database route failed.");
        return GORM_ERROR;
    }

    this->m_iPoolNum = pRoute->dblist.iDBNum;
    for (int i=0; i<pRoute->dblist.iDBNum; i++)
    {
        if (GORM_OK != CreatePool(&(pRoute->dblist.vDBLists[i]), i, m))
        {
            GORM_LOGE("create db connection failed.");
            return GORM_ERROR;
        }
    }
    
    return GORM_OK;
}

int GORM_DBConnMgr::RequestNum()
{
    for (int i=0; i<m_iPoolNum; i++)
    {
        GORM_MySQLConnPool *pPool = dynamic_cast<GORM_MySQLConnPool*>(m_pDBPool[i]);
        if (pPool == nullptr || pPool->m_pEvent == nullptr || pPool->m_pEvent->m_pSendingToMySQLRing == nullptr)
            continue;
        if (pPool->m_pEvent->m_pReadingRequest != nullptr || pPool->m_pEvent->m_pSendingToMySQLRing->GetNum() > 0)
            return 1;
    }
    return 0;
}

GORM_Ret GORM_DBConnMgr::CreatePool(GORM_DBInfo *pDbInfo, int iIndex, mutex *m)
{
    GORM_DBConnPool *pPool = nullptr;
    if (this->m_iDBType == DBType_NONE)
    {
        this->m_iDBType = pDbInfo->GetDBType();
        if (this->m_iDBType != DBType_MySQL && this->m_iDBType != DBType_MGO)
        {
            GORM_LOGE("dbtype should be mysql of mongo, now is:%s", pDbInfo->szType);
            return GORM_ERROR;
        }
    }
    try
    {
        if (this->m_iDBType == DBType_MySQL)
        {
            pPool = new GORM_MySQLConnPool(8);
        }
        //else if (this->m_iDBType == DBType_MGO)
        //{
        //}
        else
        {
            GORM_LOGE("invalid db type, %s, %s", pDbInfo->szDBSymbol, pDbInfo->szType);
            GORM_ERROR;
        }
        if (!pPool->Init(pDbInfo, m))
        {
            GORM_LOGE("init db connection failed:%s", pDbInfo->szDBSymbol);
            return GORM_ERROR;
        }
        this->m_pDBPool[iIndex] = pPool;
    }
    catch(exception &e)
    {
        GORM_LOGE("create connection pool got exception, db:%s, err:%s", pDbInfo->szDBSymbol, e.what());
        if (pPool != nullptr)
        {
            delete pPool;
        }
        return GORM_ERROR;
    }

    return GORM_OK;
}

int GORM_DBConnMgr::GetDBPool(int iTableId, uint32 uiHashValue, GORM_DBConnPool *&pDbPool)
{
    if (this->m_iPoolNum == 0)
    {
        return GORM_NO_DB;
    }
    pDbPool = m_pDBPool[0];
    return GORM_OK;
}

void GORM_DBConnMgr::Loop()
{
    GORM_DBConnPool *pPool = nullptr;
    for (int i=0; i<this->m_iPoolNum; i++)
    {
        pPool = this->m_pDBPool[i];
        if (pPool == nullptr)
        {
            continue;
        }
        pPool->Loop();
    }
}


