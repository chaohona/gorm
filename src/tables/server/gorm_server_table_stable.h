#ifndef _GORM_SERVER_TABLE_STABLE_H__
#define _GORM_SERVER_TABLE_STABLE_H__
#include "mysql.h"
#include "gorm_inc.h"
#include "gorm_pb_tables_inc.pb.h"

using namespace gorm;
class GORM_MySQLEvent;
// debug环境动态更新表结构
int GORM_MySQLUpdateTableSchema(GORM_MySQLEvent* pMySQLEvent, const char *szTable, const GORM_PB_CUSTEM_COLUMNS &pbColumns);

#endif

