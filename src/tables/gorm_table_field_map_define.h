#ifndef _GORM_FIELDS_MAP_H__
#define _GORM_FIELDS_MAP_H__
#include "gorm_sys_inc.h"
#include "gorm_inc.h"
#include "gorm_msg_helper.h"
#include "gorm_table_field_map.h"
#include "gorm_mempool.h"

// 保存表中字段的名字与宏的相互映射关系
namespace gorm{
GORM_DLL_DECL int GORM_InitTableSchemaInfo(PB_MSG_PTR pMsgPtr);

GORM_DLL_DECL int GORM_SetTableFieldId2Name(int iTableId, OUT FieldId2Name &mapId2Name);
GORM_DLL_DECL int GORM_SetTableFieldName2Id(int iTableId, OUT FieldName2Id &mapName2Id);
GORM_DLL_DECL int GORM_SetTableName2Id(OUT TableName2Id &mapName2Id);
GORM_DLL_DECL int GORM_SetTableId2Name(OUT TableId2Name &mapId2Name);

GORM_DLL_DECL int GORM_SetTableVersion(OUT TableVersionMap& mapTableVersion);

GORM_DLL_DECL int GORM_GetCustomPbMsg(PB_MSG_PTR &pMsgPtr);
GORM_DLL_DECL int GetTablePbMsgDefine(int iTableId, PB_MSG_PTR &pMsgPtr);
GORM_DLL_DECL bool GORM_TableHasData(GORM_PB_TABLE *pTable, int iTableId);
GORM_DLL_DECL int GORM_GetTableSrcPbMsg(int iTableId, GORM_PB_TABLE *pTable, PB_MSG_PTR &pMsgPtr);

GORM_DLL_DECL int GORM_AddRecordToReqPbMsgDefine(int iTableId, GORM_PB_TABLE *pPbTable, PB_MSG_PTR pPbMsg);

GORM_DLL_DECL uint32 GORM_TableHash(int iTableId, const GORM_PB_TABLE &pbTable);

GORM_DLL_DECL int GORM_InitTableColumnInfo(unordered_map<string, vector<string>> &mapTablesColumnOrder, unordered_map<string, unordered_map<string, GORM_PB_COLUMN_TYPE>> &mapTablesColumnInfo);


//string对应
/////////////////////////////向pb协议中设置字段          start  /////////////////////////////////////////////
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, const char * value, const size_t size);
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, const char * value);

// 整数对应
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int8 value);
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int16 value);
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int32 value);
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int64 value);
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, double value);

GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 value);
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint16 value);
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint32 value);
GORM_DLL_DECL void GORM_SetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint64 value);
/////////////////////////////向pb协议中设置字段          end  /////////////////////////////////////////////

/////////////////////////////从pb协议中读取字段 start /////////////////////////////////////////////
GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, string &strValue);
GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 *&value, size_t &size);

GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int8 &value);
GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int16 &value);
GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int32 &value);
GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, int64 &value);
GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, double &value);

GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint8 &value);
GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint16 &value);
GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint32 &value);
GORM_DLL_DECL int GORM_GetTableFieldValue(PB_MSG_PTR pMsg, int iTableId, int iFieldId, uint64 &value);
/////////////////////////////从pb协议中读取字段          end /////////////////////////////////////////////


}
#endif

