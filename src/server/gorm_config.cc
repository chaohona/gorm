#include <yaml-cpp/yaml.h>

#include "gorm_config.h"
#include "gorm_sys_inc.h"
#include "gorm_utils.h"


GORM_Config::~GORM_Config()
{
}

bool GORM_Config::Init(char *szCfgFile)
{
    string content;
    try
    {
        YAML::Node node = YAML::LoadFile(szCfgFile);
        for(auto c=node.begin(); c!=node.end(); c++)
        {
            content = c->first.as<string>();
            if (content == "daemonize")
            {
                content = c->second.as<string>();
                if (content == "no")
                {
                    this->m_bDaemonize = false;
                }
            }
            else if (content == "work-threads")
            {
                this->m_iWorkThreadNum = c->second.as<int>();
                if (this->m_iWorkThreadNum < 1 || this->m_iWorkThreadNum > GORM_MAX_WORK_THREAD_NUM)
                {
                    cout << "invalid work-threads configure:" << this->m_iWorkThreadNum << endl;
                    return false;
                }
            }
            else if (content == "connect-num")
            {
                this->m_iConnectNumPerPool = c->second.as<int>();
                if (this->m_iConnectNumPerPool < 1 || this->m_iConnectNumPerPool > GOMR_MAX_CONNECT_NUM_PER_THREAD)
                {
                    cout << "invalid connect-num configure:" << this->m_iConnectNumPerPool << endl;
                    return false;
                }
            }
            else if (content == "listen-address")
            {
                this->m_strListenAddr = c->second.as<string>();
                if (!this->ParseListen())
                {
                    cout << "parse listen address faild:" << this->m_strListenAddr << endl;
                    return false;
                }
            }
            else if (content == "database-config")
            {
                this->m_strDbCfg = c->second.as<string>();
            }
            else if (content == "loglevel")
            {
                string logLevel = c->second.as<string>();
                if (logLevel == "debug")
                {
                    this->m_iLogLevel = GORM_LOG_LEVEL_DEBUG;
                }
                else if (logLevel == "info")
                {
                    this->m_iLogLevel = GORM_LOG_LEVEL_INFO;
                }
                else if (logLevel == "warning")
                {
                    this->m_iLogLevel = GORM_LOG_LEVEL_WARNING;
                }
                else if (logLevel == "error")
                {
                    this->m_iLogLevel = GORM_LOG_LEVEL_ERROR;
                }
                else if (logLevel == "none")
                {
                    this->m_iLogLevel = GORM_LOG_LEVEL_NONE;
                }
                else
                {
                    cout << "wrong loglevel configure." << logLevel << endl;
                }
            }
            else if (content == "cache-type")
            {
                string strCacheType = c->second.as<string>();
                if (strCacheType == GORM_CACHE_REDIS)
                {
                    this->m_iCacheType = GORM_CacheType_Redis;
                    cout << "cache type is redis" << endl;
                }
            }
            else if (content == "redis-info")
            {
                if (!this->ParseRedisInfo(c->second))
                {
                    cout << "parse redis info failed" << endl;
                    return false;
                }
            }
        }
    }
    catch(exception &e)
    {
        cout << "parse config file:" << szCfgFile <<", got exception:" << e.what() << ", " << content << endl;
        return false;
    }
    
    return true;
}

bool GORM_Config::ParseListen()
{
    auto results = split(this->m_strListenAddr, ":");
    if (results.size() != 2)
    {
        return false;
    }
    this->m_strListenIP = results[0];
    this->m_usListenPort = stoi(results[1], 0, 10);

    return true;
}

bool GORM_Config::ParseRedisInfo(YAML::Node &node)
{
    if (!node["redis-server"])
    {
        cout << "redis-info.redis-sever was not configed" << endl;
        return false;
    }
    this->m_strRedisServer = node["redis-server"].as<string>();
    return true;
}

