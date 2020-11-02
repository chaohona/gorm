#include <yaml-cpp/yaml.h>
#include <mutex>

#include "gorm_db_config.h"
#include "gorm_sys_inc.h"
#include "gorm_log.h"
#include "gorm_define.h"
#include "gorm_utils.h"

static GORM_RouteInfo *g_globel_router_info = nullptr;
static mutex g_global_router_mutex;


DBType GORM_DBInfo::GetDBType()
{
    if (strncmp(this->szType, GORM_DB_MYSQL, GORM_DB_TYPE_MAX_LEN) == 0)
    {
        return DBType_MySQL;
    }
    else if (strncmp(this->szType, GORM_DB_MGO, GORM_DB_TYPE_MAX_LEN) == 0)
    {
        return DBType_MGO;
    }
    return DBType_NONE;
}

GORM_RouteInfo *GetDatabaseRoute()
{
    lock_guard<std::mutex> lock(g_global_router_mutex);
    return g_globel_router_info;
}

GORM_Ret ReloadRoute(const char *szCfg)
{
    string content;
    GORM_RouteInfo *pNewRoute = nullptr;
    try
    {
        pNewRoute = new GORM_RouteInfo();
        if (GORM_OK != pNewRoute->Init(szCfg) )
        {
            cout << "parse route config file failed:" <<  szCfg << endl;
            return GORM_ERROR;
        }
    }
    catch(exception &e)
    {
        cout << "parse config file:" << szCfg <<", got exception:" << e.what() << ", " << content << endl;
        return GORM_ERROR;
    }

    GORM_LOGI("reload database route config file success, file is:%s", szCfg);
    lock_guard<std::mutex> lock(g_global_router_mutex);
    try
    {
        if (g_globel_router_info != nullptr)
        {
            delete g_globel_router_info;
        }
        g_globel_router_info = pNewRoute;
    }
    catch(exception &e)
    {
        GORM_LOGI("reload database route config file failed, got exception:%s", e.what());
        return GORM_ERROR;
    }
    
    return GORM_OK;
}

int GORM_RouteInfo::Init(const char *szCfg)
{
    string content;
    try
    {
        YAML::Node node = YAML::LoadFile(szCfg);
        for(auto c=node.begin(); c!=node.end(); c++)
        {
            content = c->first.as<string>();
            if (content == "version")
            {
                this->ulVersion = c->second.as<uint64>();
            }
            else if (content == "databases")
            {
                if (GORM_OK != this->ParseDB(c->second))
                {
                    GORM_LOGE("parse databases failed.");
                    return GORM_ERROR;
                }
            }
            else if (content == "table_route")
            {
                if (GORM_OK != this->ParseRoute(c->second))
                {
                    GORM_LOGE("parse table_route failed.");
                    return GORM_ERROR;
                }
            }
        }
    }
    catch(exception &e)
    {
        GORM_LOGE("parse route config file got exception:%s", e.what());
        return GORM_ERROR;
    }

    return GORM_OK;
}

int GORM_RouteInfo::ParseDB(YAML::Node &node)
{
    try
    {
        this->dblist.iDBNum = node.size();
        if (this->dblist.iDBNum > GORM_DB_MAX_DB_LIST)
        {
            GORM_LOGE("too many databases:%d", this->dblist.iDBNum);
            return GORM_ERROR;
        }
        GORM_DBInfo *pDbInfo = this->dblist.vDBLists;
        string strTmp;
        for(int i=0; i<node.size(); i++)
        {
            pDbInfo = &this->dblist.vDBLists[i];
            auto db = node[i];
            if (!db["name"])
            {
                GORM_LOGE("invalid config databases.name:%d", i);
                return GORM_ERROR;
            }
            strncpy(pDbInfo->szDBSymbol, db["name"].as<string>().c_str(), GORM_DB_IDENTY_MAX_LEN);

            if (!db["type"])
            {
                GORM_LOGE("invalid config databases.type:%d", i);
                return GORM_ERROR;
            }
            strTmp = db["type"].as<string>();
            strncpy(pDbInfo->szType, strTmp.c_str(), GORM_DB_TYPE_MAX_LEN);
            if (strTmp != GORM_DB_MGO && strTmp != GORM_DB_MYSQL)
            {
                GORM_LOGE("invalid config databases.index:%d, type:%s", i, pDbInfo->szType);
                return GORM_ERROR;
            }

            if (!db["host"])
            {
                GORM_LOGE("invalid config databases.host:%d", i);
                return GORM_ERROR;
            }
            strncpy(pDbInfo->szHost, db["host"].as<string>().c_str(), NET_IP_STR_LEN);

            if (!db["port"])
            {
                GORM_LOGE("invalid config databases.port:%d", i);
                return GORM_ERROR;
            }
            pDbInfo->uiPort = db["port"].as<int>();

            if (!db["user"])
            {
                GORM_LOGE("invalid config databases.user:%d", i);
                return GORM_ERROR;
            }
            strncpy(pDbInfo->szUser, db["user"].as<string>().c_str(), GORM_DB_USER_MAX_LEN);

            if (!db["passwd"])
            {
                GORM_LOGE("invalid config databases.passwd:%d", i);
                return GORM_ERROR;
            }
            strncpy(pDbInfo->szPW, db["passwd"].as<string>().c_str(), GORM_DB_PW_MAX_LEN);

            if (!db["database"])
            {
                GORM_LOGE("invalid config databases.database:%d", i);
                return GORM_ERROR;
            }
            strncpy(pDbInfo->szDB, db["database"].as<string>().c_str(), GORM_DB_MAX_LEN);
        }
    }
    catch(exception &e)
    {
        GORM_LOGE("parse route.databases config file got exception:%s", e.what());
        return GORM_ERROR;
    }
    return GORM_OK;
}

// 解析table_route字段
int GORM_RouteInfo::ParseRoute(YAML::Node &node)
{
    try
    {
        GORM_RouteTable *pTable;
        this->routes.iTableNum = node.size();
        if (this->routes.iTableNum > GORM_DB_MAX_TABLE_NUM)
        {
            GORM_LOGE("too many table_route.table_name:%d", this->routes.iTableNum);
            return GORM_ERROR;
        }
        for (int i=0; i<this->routes.iTableNum; i++)
        {
            pTable = &this->routes.vRouteTables[i];
            auto table = node[i];
            // table_route.table_name
            if (!table["table_name"])
            {
                GORM_LOGE("invalid config table_route.table_name:%d", i);
                return GORM_ERROR;
            }
            strncpy(pTable->szTable, table["table_name"].as<string>().c_str(), GORM_DB_TABLE_MAX_LEN);

            if (!table["router"])
            {
                GORM_LOGE("invalid config table_route.router:%d", i);
                return GORM_ERROR;
            }

            auto router = table["router"];
            pTable->iDBNum = router.size();
            if (pTable->iDBNum > GORM_DB_MAX_DB_LIST)
            {
                GORM_LOGE("invalid config table_route.router, too many config, index:%d, num:", i, pTable->iDBNum);
                return GORM_ERROR;
            }
            // 解析table_route.router
            if (GORM_OK != this->ParseRouteList(pTable, router))
            {
                GORM_LOGE("invalid config table_route.router:%d", i);
                return GORM_ERROR;
            }
        }
    }
    catch(exception &e)
    {
        GORM_LOGE("parse route.table_route config file got exception:%s", e.what());
        return GORM_ERROR;
    }

    return GORM_OK;
}

// 解析table_route.router下面的路由列表
int GORM_RouteInfo::ParseRouteList(GORM_RouteTable *pTable, YAML::Node &node)
{
    GORM_RouteDB *pRoute;
    for (int i=0; i<node.size(); i++)
    {
        pRoute = &pTable->vRouteDB[i];
        auto strRoute = node[i].as<string>();

        auto vDatas = split(strRoute, ":");
        if (vDatas.size() != 2)
        {
            GORM_LOGE("invalid config table_route.router - :%d, routeinfo:%s", i, (char*)strRoute.c_str());
            return GORM_ERROR;
        }
        strncpy(pRoute->szDBSymbol, vDatas[0].c_str(), GORM_DB_IDENTY_MAX_LEN);

        pRoute->iSplitNum = atoi(vDatas[1].c_str());
    }
    return GORM_OK;
}


