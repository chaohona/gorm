#ifndef _GORM_REDIS_DEFINE_H__
#define _GORM_REDIS_DEFINE_H__
/*
#include "hiredis/async.h"
#include "gorm_sys_inc.h"
#include "gorm_inc.h"
#include "gorm_mempool.h"
#include "gorm_pb_proto.pb.h"

using namespace gorm;

#define GORM_REDIS_REPLY_DOUBLE(reply, toValue)             \
toValue = 0;                                                \
if (reply->type == REDIS_REPLY_DOUBLE)                      \
    toValue = reply->dval;                                  \
else if (reply->type == REDIS_REPLY_STRING && reply->len>0) \
{                                                           \
    toValue = stod(reply->str);                             \
}
    

#define GORM_REDIS_REPLY_LONG(reply, toValue)   \
switch (reply->type)                            \
{                                               \
case REDIS_REPLY_INTEGER:                       \
{                                               \
    toValue = reply->integer;                   \
    break;                                      \
}                                               \
case REDIS_REPLY_NIL:                           \
{                                               \
    toValue = 0;                                \
    break;                                      \
}                                               \
case REDIS_REPLY_DOUBLE:                        \
{                                               \
    toValue = reply->dval;                      \
    break;                                      \
}                                               \
case REDIS_REPLY_STRING:                        \
{                                               \
    if (reply->len>0)                           \
    {                                           \
        toValue = stoll(reply->str);            \
    }                                           \
    break;                                      \
}                                               \
default:                                        \
    return GORM_DB_ERROR;                       \
}

#define GORM_REDIS_REPLY_ULONG(reply, toValue)  \
switch (reply->type)                            \
{                                               \
case REDIS_REPLY_INTEGER:                       \
{                                               \
    toValue = reply->integer;                   \
    break;                                      \
}                                               \
case REDIS_REPLY_NIL:                           \
{                                               \
    toValue = 0;                                \
    break;                                      \
}                                               \
case REDIS_REPLY_DOUBLE:                        \
{                                               \
    toValue = reply->dval;                      \
    break;                                      \
}                                               \
case REDIS_REPLY_STRING:                        \
{                                               \
    toValue = stoull(reply->str);               \
    break;                                      \
}                                               \
default:                                        \
    return GORM_DB_ERROR;                       \
}

int GORM_REDIS_HMGET(int iTableId, redisContext *pRedisConn, GORM_PB_TABLE *pPbTable, GORM_PB_TABLE *pOutPbTable, bool &bGotResult);
int GORM_REDIS_INSERT(int iTableId, redisContext *pRedisConn, GORM_PB_TABLE *pPbTable);
int GORM_REDIS_DELETE(int iTableId, redisContext *pRedisConn, GORM_PB_TABLE *pPbTable);

*/
#endif


