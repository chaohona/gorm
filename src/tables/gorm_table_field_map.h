#ifndef _GORM_TABLE_FIELD_MAP_H__
#define _GORM_TABLE_FIELD_MAP_H__
#include "gorm_define.h"
#include "gorm_inc.h"
#include "gorm_log.h"
#include "gorm_pb_proto.pb.h"
#include "gorm_msg_helper.h"

namespace gorm
{

GORM_DLL_DECL bool InvalidTableCheck(int iTableId);


// 所有的表的字段的宏宇字段的名字保存在gorm_fields_map_define中

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
class GORM_DLL_DECL GORM_TableFieldMapInstance
{
public:
	static GORM_TableFieldMapInstance *Instance();
    int Init(GORM_Log *pLogger);
public:
    static FieldId2Name *mapId2Name;
    static FieldName2Id *mapName2Id;
    static TableName2Id *mapTableName2Id;
    static TableId2Name *mapTableId2Name;
    static TableVersionMap *mapTableVersion;
    static GORM_PB_HAND_SHAKE_REQ *pTableInfo;
private:
	static GORM_TableFieldMapInstance* pInstance;
};

}

#endif
