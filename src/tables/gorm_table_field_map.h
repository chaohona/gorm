#ifndef _GORM_TABLE_FIELD_MAP_H__
#define _GORM_TABLE_FIELD_MAP_H__
#include "gorm_define.h"
#include "gorm_inc.h"
#include "gorm_log.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_msg_helper.h"

namespace gorm
{

GORM_DLL_DECL bool GORM_InvalidTableCheck(int iTableId);


// 通过表中字段的名字，获取字段的宏
GORM_DLL_DECL int GORM_GetFieldID(int iTableId, const char* szFiledName, OUT int &iFieldId);
GORM_DLL_DECL int GORM_GetFieldID(const char* szTable, const char* szFiledName, OUT int &iFieldId);

// 通过表中字段的宏，获取字段的名字
GORM_DLL_DECL int GORM_GetFieldName(int iTableId, int iFieldId, OUT char *&szFieldName);
GORM_DLL_DECL int GORM_GetFieldName(const char* szTable, int iFieldId, OUT char *&szFieldName);

GORM_DLL_DECL int GORM_GetTableVersion(int iTableId, OUT uint64 &ulVersion);
GORM_DLL_DECL int GORM_GetTableVersion(const char *szTable, OUT uint64 &ulVersion);

GORM_DLL_DECL int GORM_GetTableId(const char *szTableName, OUT int &iTableId);
GORM_DLL_DECL int GORM_GetTableName(int iTableId, OUT char *&szTableName);

// 将Record加入通信消息
GORM_DLL_DECL int GORM_AddRecordToReqPbMsg(int iTableId, GORM_PB_TABLE *pPbTable, PB_MSG_PTR pPbMsg); 


GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char* szField, const char * pValue, const size_t sSize);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char* szField, const char * pValue);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, int8 i8Value);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, int16 i16Value);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, int32 iValue);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, int64 lValue);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, double flValue);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, uint8 i8Value);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, uint16 i16Value);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, uint32 iValue);
GORM_DLL_DECL int GORM_SetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, uint64 lValue);

GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT string &strValue);
GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char* szField, OUT uint8 *&pValue, OUT size_t &sSize);
GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char *szField, OUT int8 &i8Value);
GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT int16 &i16Value);
GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT int32 &iValue);
GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT int64 &lValue);
GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT uint8 &i8Value);
GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT uint16 &i16Value);
GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT uint32 &iValue);
GORM_DLL_DECL int GORM_GetCustomColumnValue(PB_MSG_PTR pPbMsg, const char * szField, OUT uint64 &lValue);

using FieldId2Name = unordered_map<int,string>;
using FieldName2Id = unordered_map<string,int>;
using TableName2Id = unordered_map<string,int>;
using TableId2Name = unordered_map<int,string>;
using TableVersionMap = unordered_map<int,uint64>;
// 表相关的映射关系
class GORM_DLL_DECL GORM_TableFieldMapInstance
{
public:
	static GORM_TableFieldMapInstance *Instance();
    int Init(GORM_Log *pLogger);
public:
    // 各个表的列id与列名映射关系
    static FieldId2Name *mapId2Name;
    static FieldName2Id *mapName2Id;
    // 表名与id映射关系
    static TableName2Id *mapTableName2Id;
    static TableId2Name *mapTableId2Name;
    // 表的元数据版本信息
    static TableVersionMap *mapTableVersion;
    // 表信息的proto结构，用于版本校验
    static PB_MSG_PTR pTableInfo;
private:
	static GORM_TableFieldMapInstance* pInstance;
};

}

#endif
