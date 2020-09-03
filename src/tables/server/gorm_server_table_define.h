#ifndef _GORM_SERVER_TABLE_DEFILE_H__
#define _GORM_SERVER_TABLE_DEFILE_H__

#include "gorm_sys_inc.h"
#include "gorm_inc.h"
#include "gorm_msg_helper.h"
#include "gorm_table_field_map.h"
#include "gorm_mempool.h"
#include "mysql.h"
#include "gorm_table_field_map_define.h"

using namespace gorm;

class GORM_MySQLEvent;
// 获取sql语句
int GORM_PackInsertSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_INSERT_REQ* pMsg, GORM_MemPoolData *&pReqData);
int GORM_PackGetSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_GET_REQ* pMsg, GORM_MemPoolData *&pReqData);
int GORM_PackDeleteSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_DELETE_REQ* pMsg, GORM_MemPoolData *&pReqData);
int GORM_PackUpdateSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_UPDATE_REQ* pMsg, GORM_MemPoolData *&pReqData);
int GORM_PackIncreaseSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_INCREASE_REQ* pMsg, GORM_MemPoolData *&pReqData);
int GORM_PackReplaceSQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_REPLACE_REQ* pMsg, GORM_MemPoolData *&pReqData);
int GORM_PackGet_By_Non_Primary_KeySQL(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_GET_BY_NON_PRIMARY_KEY_REQ* pMsg, GORM_MemPoolData *&pReqData);

int GORM_PackGetSQLTable(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_TABLE& table, GORM_MemPoolData *&pReqData);
int GORM_PackInsertSQLTable(shared_ptr<GORM_MemPool> &pMemPool, GORM_MySQLEvent *pMySQLEvent, MYSQL* mysql, int iTableId, uint32 uiHashValue, const GORM_PB_TABLE& table, GORM_MemPoolData *&pReqData);


int GORM_MySQLResult2PbMSG(GORM_MySQLEvent *pMySQLEvent, int iTableId, GORM_PB_TABLE *pPbTable, MYSQL_ROW row, unsigned long *lengths);

#endif
