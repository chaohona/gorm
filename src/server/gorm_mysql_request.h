#ifndef _GORM_MYSQL_REQUEST_H__
#define _GORM_MYSQL_REQUEST_H__
#include "gorm_ringbuffer.h"
#include "gorm_mempool.h"
#include "gorm_db_request.h"
#include "mysql.h"
#include "gorm_table_field_map.h"
// 请求和响应的上层封装函数，这个类会再调用一层执行层
// 再封装一层主要是为了自动生成代码，这个类不会改变，
// 这个类调用的执行函数GORM_MySQLPackage[Update|Delete]是根据实际的表结构生成的
// GORM_MySQLPackage[Update|Delete]主要是起到一个路由的作用，根据不同的表结构调用不同的表的处理函数

#define GORM_SQL_REQ(request)\
(request->pReqSQLData->m_uszData)

#define GORM_SQL_REQ_LEN(request)\
(request->pReqSQLData->m_sUsedSize)

class GORM_MySQLEvent;
class GORM_MySQLRequest : public GORM_DBRequest
{
public:
    GORM_MySQLRequest(shared_ptr<GORM_MemPool> &pMemPool);
    virtual ~GORM_MySQLRequest();

    // 获取到了一个结果，此函数负责从mysql到内存数据的转换
    int GetOneRow(MYSQL_ROW row, unsigned long *lengths);
    void InsertResult(int iRet, uint64 ulInsertID);
    void UpdateResult(int iRet, uint32 uiAffectRows);
    void DeleteResult(int iRet, uint32 uiAffectRows);
    void IncreaseResult(int iRet, uint32 uiAffectRows);
    void ReplaceResult(int iRet, uint32 uiAffectRows);

    // 将响应pb消息，打包成二进制数据
    int PackResult();

    // 组装SQL语句
    int PackSQL();

    virtual int InsertReq();
    virtual int ReplaceReq();
    virtual int IncreaseReq();
    virtual int GetReq();
    virtual int DeleteReq();
    virtual int BatchGetReq();
    virtual int GetByPartKeyReq();
    virtual int UpdateReq();
    virtual int GetByNonPrimaryKey();

    virtual int BatchGetNext();

    virtual int PackBatchGetResult();
    virtual int PackGetByPartkeyResult();
public:
    int PackInsertResult();
    int PackReplaceResult();
    int PackIncreaseResult();
    int PackGetResult();
    int PackDeleteResult();
    int PackUpdateResult();
    int PackGetByNonPrimaryKeyResult();
    int PackHeartBeatResult();
    int PackHandShakeResult(int iRet, uint64 ulClientId = 0);
    int PackGetToInsertResult();

    void Release();
};

#endif

