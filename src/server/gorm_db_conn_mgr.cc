#include "gorm_db_conn_mgr.h"
#include "gorm_db_config.h"
#include "gorm_config.h"
#include "gorm_log.h"
#include "gorm_mysql_conn_pool.h"
#include "gorm_table_field_map.h"
#include "gorm_work_thread.h"

using namespace gorm;

GORM_DBConnMgr::GORM_DBConnMgr()
{
}

// 进程已经结束了，内存就不管了
GORM_DBConnMgr::~GORM_DBConnMgr()
{
    if (this->m_vTableRouteInfo != nullptr)
        delete this->m_vTableRouteInfo;
}

GORM_Ret GORM_DBConnMgr::Init(GORM_WorkThread *pWorkThread, mutex *m)
{
    m_pWorkThread = pWorkThread;

    if (GORM_OK != this->InitDB(m))
    {
        GORM_LOGE("connect to database failed.");
        return GORM_ERROR;
    }
    
    if (GORM_OK != this->InitRoute(m))
    {
        GORM_LOGE("init route failed.");
        return GORM_ERROR;
    }

    return GORM_OK;
}

int GORM_DBConnMgr::InitRoute(mutex *m)
{
    GORM_RouteInfo *pRoute = GetDatabaseRoute();

    if (pRoute->routes.iTableNum < 1)
    {
        GORM_LOGE("table route was not configed.");
        return GORM_ERROR;
    }
    // 获取最大的表ID
    for (int i=0; i<pRoute->routes.iTableNum; i++)
    {
        GORM_RouteTable &table = pRoute->routes.vRouteTables[i];
        int iNowId = -1;
        GORM_GetTableId(table.szTable, iNowId);
        if (iNowId < 1)
        {
            GORM_LOGE("table was not loaded from xml, table name:%s", table.szTable);
            return GORM_ERROR;
        }
        table.iTableId = iNowId;
        int iSplitMode = 0;
        for (int j=0; j<table.iDBNum; j++)
        {
            iSplitMode += table.vRouteDB[j].iSplitNum;
        }
        if (iSplitMode < 1)
        {
            GORM_LOGE("table route was not configed, table name:%s", table.szTable);
            return GORM_ERROR;
        }
        table.iSplitMode = iSplitMode;
        if (iNowId > this->iMaxTableId)
            this->iMaxTableId = iNowId;
    }
    this->m_vTableRouteInfo = new GORM_TableRouteMgr[this->iMaxTableId+1];
    for (int i=0; i<pRoute->routes.iTableNum; i++)
    {
        GORM_RouteTable &table = pRoute->routes.vRouteTables[i];
        GORM_TableRouteMgr &routeMgr = this->m_vTableRouteInfo[table.iTableId];
        routeMgr.iSpilitMode = table.iSplitMode;
        routeMgr.iTableId = table.iTableId;
        routeMgr.vDbConn = new GORM_DBConnPool*[routeMgr.iSpilitMode];
        int splitIdx = 0;   // 每个表分片的下标对应的db连接
        for (int j=0; j<table.iDBNum; j++)
        {
            GORM_RouteDB &routeDB = table.vRouteDB[j];
            GORM_DBConnPool *pConn = m_mapDB2Conn[routeDB.szDBSymbol];
            if (pConn == nullptr)
            {
                GORM_LOGE("get connect for database failed, db:%s", routeDB.szDBSymbol);
                return GORM_ERROR;
            }
            for (;splitIdx<routeDB.iSplitNum; splitIdx++)
            {
                routeMgr.vDbConn[splitIdx] = pConn;
            }
        }
    }
    return GORM_OK;
}

int GORM_DBConnMgr::InitDB(mutex *m)
{
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
            pPool = new GORM_MySQLConnPool(GORM_Config::Instance()->m_iConnectNumPerPool);
        }
        else
        {
            GORM_LOGE("invalid db type, %s, %s", pDbInfo->szDBSymbol, pDbInfo->szType);
            GORM_ERROR;
        }
        pPool->pDbInfo = pDbInfo;
        if (!pPool->Init(m_pWorkThread->m_pEpoll, pDbInfo, m))
        {
            GORM_LOGE("init db connection failed:%s", pDbInfo->szDBSymbol);
            return GORM_ERROR;
        }
        this->m_pDBPool[iIndex] = pPool;
        this->m_mapDB2Conn[pDbInfo->szDBSymbol] = pPool;
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

int GORM_DBConnMgr::GetDBPool(GORM_DBRequest *pDBReq)
{
    if (this->m_iPoolNum == 0)
    {
        return GORM_NO_DB;
    }
    if (pDBReq->iReqTableId < 1 || pDBReq->iReqTableId > this->iMaxTableId || this->m_vTableRouteInfo+pDBReq->iReqTableId == nullptr)
    {
        GORM_LOGE("table route was not configed or invalid table id:%d", pDBReq->iReqTableId);
        return GORM_INVALID_TABLE;
    }
    GORM_TableRouteMgr &route = this->m_vTableRouteInfo[pDBReq->iReqTableId];
    // 获取表的下标
    if (!pDBReq->clientRefToTableIndex)
        pDBReq->iTableIndex = pDBReq->uiHashValue%route.iSpilitMode;
    else if(pDBReq->iTableIndex >= route.iSpilitMode) // 如果客户端带的下标超表则报错
    {
        GORM_LOGE("client ref to invalid table index, tableid:%d, ref index:%d", pDBReq->iReqTableId, pDBReq->iTableIndex);
        return GORM_NO_DB;
    }
    pDBReq->pDbPool = route.vDbConn[pDBReq->iTableIndex];
    if (pDBReq->pDbPool == nullptr)
    {
        GORM_LOGE("table route was not configed or invalid table id:%d, index:%d", pDBReq->iReqTableId, pDBReq->iTableIndex);
        return GORM_INVALID_TABLE;
    }

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


