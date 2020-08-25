#ifndef _GORM_DATABASE_CONFIG_H__
#define _GORM_DATABASE_CONFIG_H__
#include <yaml-cpp/yaml.h>

#include "gorm_sys_inc.h"
#include "gorm_define.h"
#include "gorm_error.h"

enum DBType
{
    DBType_NONE = 0,
    DBType_MGO = 1,
    DBType_MySQL = 2,
};

struct GORM_DBInfo
{
public:
    DBType GetDBType(); 
public:
    char    szDBSymbol[GORM_DB_IDENTY_MAX_LEN]; // name
    char    szHost[NET_IP_STR_LEN];
    uint32  uiPort;
    char    szUser[GORM_DB_USER_MAX_LEN];
    uint32  iPWLen;
    char    szPW[GORM_DB_PW_MAX_LEN];
    char    szType[GORM_DB_TYPE_MAX_LEN];
    char    szDB[GORM_DB_MAX_LEN];  // database
};

struct GORM_DBList
{
public:
    uint32      iDBNum;
    GORM_DBInfo vDBLists[GORM_DB_MAX_DB_LIST];
};

struct GORM_RouteDB
{
public:
    char    szDBSymbol[GORM_DB_IDENTY_MAX_LEN];   // 对应GORM_DBInfo.szName
    uint32  iSplitNum;
};

struct GORM_RouteTable
{
public:
    char            szTable[GORM_DB_TABLE_MAX_LEN]; // table
    uint32          iDBNum;
    GORM_RouteDB    vRouteDB[GORM_DB_MAX_DB_LIST];
    int             iTableId = 0;
    int             iSplitMode = 0;
};

struct GORM_Routes
{
public:
    int             iTableNum;
    GORM_RouteTable vRouteTables[GORM_DB_MAX_TABLE_NUM];
};

struct GORM_RouteInfo
{
public:
    int Init(const char *szCfg);
private:
    int ParseDB(YAML::Node &node);
    int ParseRoute(YAML::Node &node);
    int ParseRouteList(GORM_RouteTable *pTable, YAML::Node &node);
public:
    uint64      ulVersion;
    GORM_DBList dblist;
    GORM_Routes routes;
};

GORM_Ret ReloadRoute(const char *szCfg);
GORM_RouteInfo *GetDatabaseRoute();

#endif

