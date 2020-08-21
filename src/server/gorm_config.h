#ifndef _GORM_CONFIG_H__
#define _GORM_CONFIG_H__

#include <yaml-cpp/yaml.h>

#include "gorm_singleton.h"
#include "gorm_sys_inc.h"
#include "gorm_type.h"
#include "gorm_define.h"

using namespace gorm;
class GORM_Config: public GORM_Singleton<GORM_Config>
{
public:
    ~GORM_Config();

    bool Init(char *szCfgFile);

private:
    bool ParseListen();
    bool ParseRedisInfo(YAML::Node &node);

public:
    bool               m_bDaemonize = true;                           // 是否以后台进程运行
    int                m_iWorkThreadNum = 1;
    string             m_strListenAddr;                                // 监听地址
    GORM_LOG_LEVEL     m_iLogLevel = GORM_LOG_LEVEL_DEBUG;

    string      m_strListenIP = string("0.0.0.0");
    uint16      m_usListenPort = 8806;

    string      m_strDbCfg;
    string      m_strRedisServer = string("127.0.0.1:6379");

    GORM_CacheType  m_iCacheType = GORM_CacheType_Redis;
};

#endif
