#include "gorm_redis_define.h"
/*
using namespace gorm;
#define GORM_ROLE_REDIS_HMGET "hmget %s  version roleid rolename level exp characterid gold offlinetime inited createtime face online"
int GORM_REDIS_HMGET_ROLE(const GORM_PB_Table_role &inTable, redisContext *pRedisConn, GORM_PB_TABLE *pOutPbTable, bool &bGotResult)
{
    char szKey[2048];
    snprintf(szKey, 2048, "role_%lld", inTable.roleid());
    redisReply* r = (redisReply*)redisCommand(pRedisConn, GORM_ROLE_REDIS_HMGET, szKey);
    if (r == nullptr)
        return GORM_CACHE_ERROR;
    if (r->type != REDIS_REPLY_ARRAY || r->elements != 12)
    {
        freeReplyObject(r);
        return GORM_CACHE_ERROR;
    }
    bGotResult = false;
    for (int i=0; i<12; i++)
    {
        if ((*(r->element+i))->type != REDIS_REPLY_NIL)
        {
            bGotResult = true;
            break;
        }
    }
    if (!bGotResult)
    {
        freeReplyObject(r);
        return GORM_OK;
    }
    GORM_PB_Table_role *pROLE = pOutPbTable->mutable_role();
    if (pROLE == nullptr)
    {
        freeReplyObject(r);
        return GORM_CACHE_ERROR;
    }
    redisReply *pElement = nullptr;
    pElement = *(r->element+0);
    uint64 role_version = 0;
    GORM_REDIS_REPLY_ULONG(pElement, role_version);
    pROLE->set_version(role_version);
    pElement = *(r->element+1);
    int64 role_roleid = 0;
    GORM_REDIS_REPLY_LONG(pElement, role_roleid);
    pROLE->set_roleid(role_roleid);
    pElement = *(r->element+2);
    if (pElement->len > 0)
        pROLE->set_rolename(pElement->str, pElement->len);
    pElement = *(r->element+3);
    int32 role_level = 0;
    GORM_REDIS_REPLY_LONG(pElement, role_level);
    pROLE->set_level(role_level);
    pElement = *(r->element+4);
    int64 role_exp = 0;
    GORM_REDIS_REPLY_LONG(pElement, role_exp);
    pROLE->set_exp(role_exp);
    pElement = *(r->element+5);
    int32 role_characterid = 0;
    GORM_REDIS_REPLY_LONG(pElement, role_characterid);
    pROLE->set_characterid(role_characterid);
    pElement = *(r->element+6);
    int32 role_gold = 0;
    GORM_REDIS_REPLY_LONG(pElement, role_gold);
    pROLE->set_gold(role_gold);
    pElement = *(r->element+7);
    int64 role_offlinetime = 0;
    GORM_REDIS_REPLY_LONG(pElement, role_offlinetime);
    pROLE->set_offlinetime(role_offlinetime);
    pElement = *(r->element+8);
    int32 role_inited = 0;
    GORM_REDIS_REPLY_LONG(pElement, role_inited);
    pROLE->set_inited(role_inited);
    pElement = *(r->element+9);
    int64 role_createtime = 0;
    GORM_REDIS_REPLY_LONG(pElement, role_createtime);
    pROLE->set_createtime(role_createtime);
    pElement = *(r->element+10);
    if (pElement->len > 0)
        pROLE->set_face(pElement->str, pElement->len);
    pElement = *(r->element+11);
    int64 role_online = 0;
    GORM_REDIS_REPLY_LONG(pElement, role_online);
    pROLE->set_online(role_online);

    freeReplyObject(r);
    bGotResult = true;
    return GORM_OK;
}

int GORM_REDIS_HMGET(int iTableId, redisContext *pRedisConn, GORM_PB_TABLE *pPbTable, GORM_PB_TABLE *pOutPbTable, bool &bGotResult)
{
    bGotResult = false;
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        if (!pPbTable->has_role())
            return GORM_REQ_NO_RECORDS;
        return GORM_REDIS_HMGET_ROLE(pPbTable->role(), pRedisConn, pOutPbTable, bGotResult);
    }
    default:
        return GORM_OK;
    }
}
#define GORM_REDIS_INSERT_ROLE_LUA " \
if redis.call(\"EXISTS\",KEYS[1]) == 0 then \
    redis.call(\"hmset\", KEYS[1], \"version\", ARGV[1], \"roleid\", ARGV[2], \"rolename\", ARGV[3], \"level\", ARGV[4], \"exp\", ARGV[5], \"characterid\", ARGV[6], \"gold\", ARGV[7], \"offlinetime\", ARGV[8], \"inited\", ARGV[9], \"createtime\", ARGV[10], \"face\", ARGV[11], \"online\", ARGV[12]) \
end \
return 0"
int GORM_REDIS_INSERT_ROLE(const GORM_PB_Table_role &inTable, redisContext *pRedisConn)
{
    char szKey[2048];
    snprintf(szKey, 2048, "role_%lld", inTable.roleid());
    redisReply* r = (redisReply*)redisCommand(pRedisConn, "EVAL %s 1 %s %llu %lld %s %d %lld %d %d %lld %d %lld %s %lld", GORM_REDIS_INSERT_ROLE_LUA, szKey, 
    inTable.version(), inTable.roleid(), inTable.rolename().c_str(), inTable.level(), inTable.exp(), inTable.characterid(), inTable.gold(), inTable.offlinetime(), inTable.inited(), inTable.createtime(), inTable.face().c_str(), inTable.online());
    if (r == nullptr || r->type == REDIS_REPLY_ERROR)
        return GORM_CACHE_ERROR;
    int iResult = -1;
    GORM_REDIS_REPLY_LONG(r,  iResult);
    if (iResult != 0)
        return GORM_CACHE_ERROR;

    return GORM_OK;
}

int GORM_REDIS_INSERT(int iTableId, redisContext *pRedisConn, GORM_PB_TABLE *pPbTable)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        if (!pPbTable->has_role())
            return GORM_REQ_NO_RECORDS;
        return GORM_REDIS_INSERT_ROLE(pPbTable->role(), pRedisConn);
    }
    default:
        return GORM_OK;
    }
}
int GORM_REDIS_DELETE_ROLE(const GORM_PB_Table_role &inTable, redisContext *pRedisConn)
{
    char szKey[2048];
    snprintf(szKey, 2048, "role_%lld", inTable.roleid());
    redisReply* r = (redisReply*)redisCommand(pRedisConn, "del %s", szKey);
    if (r == nullptr || r->type == REDIS_REPLY_ERROR)
        return GORM_CACHE_ERROR;
    int iResult = -1;
    GORM_REDIS_REPLY_LONG(r,  iResult);
    if (iResult == -1)
        return GORM_CACHE_ERROR;
    return GORM_OK;
}

int GORM_REDIS_DELETE(int iTableId, redisContext *pRedisConn, GORM_PB_TABLE *pPbTable)
{
    switch (iTableId)
    {
    case GORM_PB_TABLE_IDX_ROLE:
    {
        if (!pPbTable->has_role())
            return GORM_REQ_NO_RECORDS;
        return GORM_REDIS_DELETE_ROLE(pPbTable->role(), pRedisConn);
    }
    default:
        return GORM_OK;
    }
}*/
