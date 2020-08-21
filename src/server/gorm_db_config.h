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


/*

<databases>
    <db name="mysql1" host="192.168.12.42" port="3306" user="mark" password="123456" type="mysql" database="test1"/>
    <db name="mysql2" host="192.168.12.42" port="3306" user="mark" password="123456" type="mysql" database="test2"/>
</databases>
<routes>
    <table name="account" splittablekey="id">
        <db name="mysql1" splittablenum="128"/>
        <db name="mysql2" splittablenum="128"/>
    </table>
</routes>

*/

struct GORM_DBInfo
{
public:
    DBType GetDBType(); 
public:
    char  szDBSymbol[GORM_DB_IDENTY_MAX_LEN]; // name
    char  szHost[NET_IP_STR_LEN];
    uint32  uiPort;
    char  szUser[GORM_DB_USER_MAX_LEN];
    uint32     iPWLen;
    char   szPW[GORM_DB_PW_MAX_LEN];
    char    szType[GORM_DB_TYPE_MAX_LEN];
    char    szDB[GORM_DB_MAX_LEN];  // database
};

struct GORM_DBList
{
public:
    uint32 iDBNum;
    GORM_DBInfo vDBLists[GORM_DB_MAX_DB_LIST];
};

struct GORM_RouteDB
{
public:
    char  szDBName[GORM_DB_IDENTY_MAX_LEN];   // 对应GORM_DBInfo.szName
    uint32  iSplitNum;
};

struct GORM_RouteTable
{
public:
    char szTable[GORM_DB_TABLE_MAX_LEN]; // table
    char szSplitColumn[GORM_DB_FIELD_MAX_LEN];// 列名
    uint32  iDBNum;
    GORM_RouteDB    vRouteDB[GORM_DB_MAX_DB_LIST];
};

struct GORM_Routes
{
public:
    int iTableNum;
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

