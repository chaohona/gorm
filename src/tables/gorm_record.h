#ifndef _GROM_RECORD_H__
#define _GROM_RECORD_H__

#include "gorm_define.h"
#include "gorm_log.h"
#include "gorm_msg_helper.h"
#include "gorm_utils.h"
namespace gorm{
enum GORM_FIELD_TYPE
{
    GORM_FIELD_TYPE_INVALID = 0,
    GORM_FIELD_TYPE_INT8 = 1,
    GORM_FIELD_TYPE_UINT8 = 2,
    GORM_FIELD_TYPE_INT16 = 3,
    GORM_FIELD_TYPE_UINT16 = 4,
    GORM_FIELD_TYPE_INT32 = 5,
    GORM_FIELD_TYPE_UINT32 = 6,
    GORM_FIELD_TYPE_INT64 = 7,
    GORM_FIELD_TYPE_UINT64 = 8,
    GORM_FIELD_TYPE_FLOAT = 9,
    GORM_FIELD_TYPE_DOUBLE = 10,
    GORM_FIELD_TYPE_STRING = 11,
    GORM_FIELD_TYPE_BINARY = 12,
    GORM_FIELD_TYPE_END = 13
};

/*
// SetColumn**函数
// 字符串:对应列名
// 整数对应gorm_client_record_opt中对应的列的宏
*/

class GORM_DLL_DECL GORM_Record
{
public:
    // 设置record对应操作对象
    /*
    @func   SetTableType
    @brief  设置记录对应的表类型，表类型会自动生成
    @parma  iTableId 表的类型的宏，或者名字
    @retval 0  请求成功，不需要解析pRetCode
    @retval 非0     请求没有成功,通过参数获取具体错误信息
    @node   Record会根据类型做自动映射，此函数都是系统调用的
    */
    int Init(int iTableId, GORM_Log *pLogger = nullptr);
    int Init(const char* szTable, GORM_Log *pLogger = nullptr);
    // 结束编码
    //int Finish();
    // 更新此record对应的版本号
    /*
    @func   SetVersion
    @brief  设置记录的版本号
    @parma  ulVer 记录的版本号
    @retval 0  请求成功，不需要解析pRetCode
    @retval 非0     请求没有成功,通过参数获取具体错误信息
    @node   如果使用SetData，并且不想更改版本号，则不需填此字段
    */
    int SetVersion(uint64 ulVer);
    uint64 GetVersion();

    // 设置record中列的数据
    /*
    @func   SetFieldValue
    @brief  设置记录中列的数据
    @parma  szColumn,iFieldId 列的宏，或者列的字符串名字
    @param  value 重载的各种列的具体值
    @retval 0  请求成功，不需要解析
    @retval 非0     请求没有成功,通过参数获取具体错误信息
    */
    int SetFieldValue(const char* szField, const char * pValue, const size_t sSize);
    int SetFieldValue(int iFieldId, const char * pValue, const size_t sSize);
    int SetFieldValue(const char* szField, const char * pValue);
    int SetFieldValue(int iFieldId, const char * pValue);
    
    int SetFieldValue(const char *szField, int8 i8Value);
    int SetFieldValue(int iFieldId, int8 i8Value);
    int SetFieldValue(const char *szField, int16 i16Value);
    int SetFieldValue(int iFieldId, int16 i16Value);
    int SetFieldValue(const char *szField, int32 iValue);
    int SetFieldValue(int iFieldId, int32 iValue);
    int SetFieldValue(const char *szField, int64 lValue);
    int SetFieldValue(int iFieldId, int64 lValue);
    int SetFieldValue(const char *szField, double flValue);
    int SetFieldValue(int iFieldId, double flValue);

    int SetFieldValue(const char *szField, uint8 i8Value);
    int SetFieldValue(int iFieldId, uint8 i8Value);
    int SetFieldValue(const char *szField, uint16 i16Value);
    int SetFieldValue(int iFieldId, uint16 i16Value);
    int SetFieldValue(const char *szField, uint32 iValue);
    int SetFieldValue(int iFieldId, uint32 iValue);
    int SetFieldValue(const char *szField, uint64 lValue);
    int SetFieldValue(int iFieldId, uint64 lValue);

    /*
    @func   GetFieldValue
    @brief  获取记录中列的值
    @parma  szColumn,iColumn 列的宏，或者列的字符串名字
    @param  value 重载的各种的传出值
    @retval 0  请求成功
    @retval 非0     请求没有成功
    */
    int GetFieldValue(const char * szField, OUT string &strValue);
    int GetFieldValue(int iFieldId, OUT string &strValue);
    int GetFieldValue(const char* szField, OUT uint8 *&pValue, OUT size_t &sSize);
    int GetFieldValue(int iFieldId, OUT uint8 *&pValue, OUT size_t &sSize);
    
    int GetFieldValue(const char *szField, OUT int8 &i8Value);
    int GetFieldValue(int iFieldId, OUT int8 &i8Value);
    int GetFieldValue(const char *szField, OUT int16 &i16Value);
    int GetFieldValue(int iFieldId, OUT int16 &i16Value);
    int GetFieldValue(const char *szField, OUT int32 &iValue);
    int GetFieldValue(int iFieldId, OUT int32 &iValue);
    int GetFieldValue(const char *szField, OUT int64 &lValue);
    int GetFieldValue(int iFieldId, OUT int64 &lValue);

    int GetFieldValue(const char *szField, OUT uint8 &i8Value);
    int GetFieldValue(int iFieldId, OUT uint8 &i8Value);
    int GetFieldValue(const char *szField, OUT uint16 &i16Value);
    int GetFieldValue(int iFieldId, OUT uint16 &i16Value);
    int GetFieldValue(const char *szField, OUT uint32 &iValue);
    int GetFieldValue(int iFieldId, OUT uint32 &iValue);
    int GetFieldValue(const char *szField, OUT uint64 &lValue);
    int GetFieldValue(int iFieldId, OUT uint64 &lValue);

    /**
    @brief 加入要操作的字段名称及操作类型，若对应字段名之前已存在，则覆盖之。只能用于增量更新请求
    @param [IN] field_name          字段名称，最大长度32字节，以'\0'结尾
    @param [IN] operation          操作类型，具体参见 \link GORM_Operation \endlink
                                    GORM_OP_PLUS 增量加操作
                                    GORM_OP_MINUS 增量减操作
    @retval 0                       设置成功
    @retval 非0                     设置失败，具体错误参见 \link ErrorCode \endlink
    */
    int AddValueOperation(IN const char* field_name, IN GORM_Operation operation);
    int AddValueOperation(IN int iFiledId, IN GORM_Operation operation);

    /*
    @func   GetData
    @brief  获取原始的pb数据
    @param [OUT] pPbMsg     此条数据对应的pb消息
    @retval 0                  设置成功
    @retval <0                 设置失败，具体错误参见 \link ErrorCode \endlink
    */
    int GetData(OUT PB_MSG_PTR &pPbMsg);    
    /**
    @brief  pb数据
    @param [IN] pPbMsg          组装好的pb消息
    @param [IN] data_version    数据版本号，参看SetVersion函数。默认值-1表示使用pPbMsg中的版本号
    @retval 0                  设置成功
    @retval <0                 设置失败，具体错误参见 \link ErrorCode \endlink
    @node   此函数会将之前创建的pb数据回收掉
    */
    int SetData(IN PB_MSG_PTR pPbMsg,   IN uint64 data_version = -1);
    /**
    @brief  设置操作的field
    @param [IN] szField        field字段
    @retval 0                  设置成功
    @retval <0                 设置失败，具体错误参见 \link ErrorCode \endlink
    @node   如果操作的时候使用SetData直接设置了原始数据，则需要使用此函数确认设置的字段
    */
    int AddFieldOpt(const char *szField);
    int AddFieldOpt(int iFieldId);
private:
    // 对record编码
    bool PackRecord();
    int SetCustomValue(const char* szField, const char * pValue, const size_t sSize);
    int SetCustomValue(const char* szField, const char * pValue);
    int SetCustomValue(const char *szField, int8 i8Value);
    int SetCustomValue(const char *szField, int16 i16Value);
    int SetCustomValue(const char *szField, int32 iValue);
    int SetCustomValue(const char *szField, int64 lValue);
    int SetCustomValue(const char *szField, double flValue);
    int SetCustomValue(const char *szField, uint8 i8Value);
    int SetCustomValue(const char *szField, uint16 i16Value);
    int SetCustomValue(const char *szField, uint32 iValue);
    int SetCustomValue(const char *szField, uint64 lValue);
public:
    PB_MSG_PTR      pPbMsg;             // 记录对应的实际pb数据,结构体为GORM_PB_TABLE
    PB_MSG_PTR      pCustomColumns;     // 存储配置中没有的列
    int             iTableId;           // 表的类型
    GORM_FieldsOpt  requestField;
    GORM_Log        *pLogger;           // 日志指针
    bool            bSetTableId = false;
    uint64          ulVersion = 0xFFFFFFFFFFFFFFFF;
    GORM_FieldsOpt  plusField;
    GORM_FieldsOpt  minusField;
};
}

#endif

