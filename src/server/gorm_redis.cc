#include "gorm_redis.h"
#include "gorm_log.h"
#include "gorm_utils.h"
#include "gorm_inc.h"
#include "gorm_redis_define.h"

using namespace gorm;

GORM_Redis::GORM_Redis()
{
}

GORM_Redis::~GORM_Redis()
{
}

int GORM_Redis::Init(GORM_Config *pConfig)
{
 /*   this->m_strRedisServer = pConfig->m_strRedisServer;

    auto results = split(this->m_strRedisServer, "/");
    if (results.size() < 1)
    {
        GORM_LOGE("invalid redis address:%s", m_strRedisServer.c_str());
        return GORM_ERROR;
    }

    GORM_Address address;
    for (auto inAddr : results)
    {
        if (GORM_Socket::ParseAddress(inAddr, address) != GORM_OK)
        {
            GORM_LOGE("invalid redis address:%s", this->m_strRedisServer.c_str());
            return GORM_ERROR;
        }
        this->m_vAddress.push_back(address);
    }

    // 和redis建立连接
    if (GORM_OK != this->ConnectRedis())
    {
        GORM_LOGE("connect to redis failed.");
        return GORM_ERROR;
    }
    */
    return GORM_OK;
}

#define REDIS_LOGE()\
    GORM_LOGE("operate redis got error, reqcmd:%d, tableid:%d, reqid:%d", pRequest->iReqCmd, pRequest->iReqTableId, pRequest->uiReqID);

// 插入操作需要直接操作mysql，然后更新到redis中
int GORM_Redis::GetResultFromCache(GORM_DBRequest *pRequest, bool &bGot)
{/*
    bGot = false;
    // 插入操作直接返回
    if (pRequest->iReqCmd == GORM_CMD_INSERT)
    {
        return GORM_OK;
    }

    switch (pRequest->iReqCmd)
    {
    // 插入操作首先操作mysql，这里不做处理
    case GORM_CMD_INSERT:
    {
        break;
    }
    case GORM_CMD_REPLACE:
    {
        
        break;
    }
    case GORM_CMD_INCREASE:
    {
        break;
    }
    case GORM_CMD_GET:
    {
        // hmget获取到请求则bGot=true
        int iRet = GORM_REDIS_HMGET(pRequest->iReqTableId, this->m_pRedisConn, pRequest->pNowReqProcTable, pRequest->pNowRspProcTable, bGot);
        if (iRet != GORM_OK)
        {
            REDIS_LOGE();
            return iRet;
        }
        if (bGot)
            pRequest->pNowReqProcTable = nullptr;
        break;
    }
    case GORM_CMD_DELETE:
    {
        break;
    }
    case GORM_CMD_BATCH_GET:
    {
        break;
    }
    case GORM_CMD_GET_BY_PARTKEY:
    {
        break;
    }
    case GORM_CMD_UPDATE:
    {
        break;
    }
    case GORM_CMD_GET_BY_NON_PRIMARY_KEY:
    {
        break;
    }
    }
    */
    return GORM_OK;
}

int GORM_Redis::UpdateCache(GORM_DBRequest *pRequst)
{/*
    switch (pRequst->iReqCmd)
    {
    case GORM_CMD_INSERT:
    {
        return GORM_REDIS_INSERT(pRequst->iReqTableId, this->m_pRedisConn, pRequst->pNowReqProcTable);
    }
    case GORM_CMD_DELETE:
    {
        return GORM_REDIS_DELETE(pRequst->iReqTableId, this->m_pRedisConn, pRequst->pNowReqProcTable);
    }
    }*/

    return GORM_OK;
}

int GORM_Redis::ConnectRedis()
{/*
    if (m_iAddrIdx >= this->m_vAddress.size())
    {
        m_iAddrIdx = 0;
    }
    GORM_Address addr = m_vAddress[m_iAddrIdx];
    m_iAddrIdx += 1;
    if (m_pRedisConn != nullptr)
    {
        redisFree(m_pRedisConn);
        m_pRedisConn = nullptr;
    }

    struct timeval tv;
    tv.tv_sec = m_iConnectTTS / 1000;
    tv.tv_usec = (m_iConnectTTS % 1000) * 1000;

    m_pRedisConn = redisConnectWithTimeout(addr.strIP.c_str(), addr.uiPort, tv);
    if (m_pRedisConn == nullptr || m_pRedisConn->err)
    {
        if (m_pRedisConn)
        {
            GORM_LOGE("connecto to redis got err, ip:%s, port:%d, err:%s", addr.strIP.c_str(), addr.uiPort, m_pRedisConn->errstr);
            redisFree(m_pRedisConn);
            m_pRedisConn = nullptr;
        }
        else
        {
            GORM_LOGE("connecto to redis can't allocate redis context, ip:%s, port:%d", addr.strIP.c_str(), addr.uiPort);
        }
        return GORM_ERROR;
    }*/
    return GORM_OK;
}

