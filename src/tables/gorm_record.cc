#include "gorm_record.h"
#include "gorm_sys_inc.h"
#include "gorm_table_field_map.h"
#include "gorm_table_field_map_define.h"


namespace gorm{

int GORM_Record::Init(int iTableId, GORM_Log *pLogger)
{
    if (!InvalidTableCheck(iTableId))
    {
        return GORM_INVALID_TABLE;
    }
    if (this->bSetTableId && iTableId != this->iTableId)
    {
        return GORM_RESET;
    }
    this->bSetTableId= true;
    if (this->iTableId == 0)
    {
        this->iTableId = iTableId;
    }

    // 生成表的pb数据
    if (GORM_OK != GetTablePbMsgDefine(iTableId, this->pPbMsg))
    {
        GORM_CUSTOM_LOGD(pLogger, "get pb msg for table failed:%d", iTableId);
        return GORM_ERROR;
    }
    return GORM_OK;
}

int GORM_Record::Init(const char* szTable, GORM_Log *pLogger)
{
    int iTableId;
    if (GORM_OK != GORM_GetTableId(szTable, iTableId))
    {
        return GORM_INVALID_TABLE;
    }

    return this->Init(iTableId);
}

int GORM_Record::SetVersion(uint64 ulVer)
{
    this->SetFieldValue(0, ulVer);
    this->ulVersion = ulVer;
    return GORM_OK;
}

uint64 GORM_Record::GetVersion()
{
    return this->ulVersion;
}

int GORM_Record::SetFieldValue(const char* szField, const char * pValue, const size_t sSize)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, pValue, sSize);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, pValue, sSize);
}

int GORM_Record::SetFieldValue(int iFieldId, const char * pValue, const size_t sSize)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, pValue, sSize);

    this->AddFieldOpt(iFieldId);

    return GORM_OK;
}

int GORM_Record::SetFieldValue(const char* szField, const char * pValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, pValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, pValue);
}


int GORM_Record::SetFieldValue(int iFieldId, const char * pValue)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, pValue);

    this->AddFieldOpt(iFieldId);
    return GORM_OK;
}

int GORM_Record::SetFieldValue(const char *szField, int8 i8Value)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, i8Value);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, i8Value);
}

int GORM_Record::SetFieldValue(int iFieldId, int8 i8Value)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, i8Value);

    this->AddFieldOpt(iFieldId);

    if (iFieldId == 0)
        this->ulVersion = i8Value;
    return GORM_OK;
}

int GORM_Record::SetFieldValue(const char *szField, int16 i16Value)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, i16Value);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, i16Value);
}

int GORM_Record::SetFieldValue(int iFieldId, int16 i16Value)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, i16Value);

    this->AddFieldOpt(iFieldId);

    if (iFieldId == 0)
        this->ulVersion = i16Value;
    return GORM_OK;
}

int GORM_Record::SetFieldValue(const char *szField, int32 iValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, iValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, iValue);
}
    
int GORM_Record::SetFieldValue(int iFieldId, int32 iValue)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, iValue);

    this->AddFieldOpt(iFieldId);

    if (iFieldId == 0)
        this->ulVersion = iValue;
    return GORM_OK;
}

int GORM_Record::SetFieldValue(const char *szField, int64 lValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, lValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, lValue);
}

int GORM_Record::SetFieldValue(int iFieldId, int64 lValue)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, lValue);

    this->AddFieldOpt(iFieldId);

    if (iFieldId == 0)
        this->ulVersion = lValue;
    return GORM_OK;
}

int GORM_Record::SetFieldValue(const char *szField, double flValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, flValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, flValue);
}

int GORM_Record::SetFieldValue(int iFieldId, double flValue)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, flValue);

    this->AddFieldOpt(iFieldId);

    if (iFieldId == 0)
        this->ulVersion = flValue;
    return GORM_OK;
}


int GORM_Record::SetFieldValue(const char *szField, uint8 i8Value)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, i8Value);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, i8Value);
}

int GORM_Record::SetFieldValue(int iFieldId, uint8 i8Value)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, i8Value);

    this->AddFieldOpt(iFieldId);

    if (iFieldId == 0)
        this->ulVersion = i8Value;
    return GORM_OK;
}

int GORM_Record::SetFieldValue(const char *szField, uint16 i16Value)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, i16Value);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, i16Value);
}

int GORM_Record::SetFieldValue(int iFieldId, uint16 i16Value)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, i16Value);

    this->AddFieldOpt(iFieldId);

    if (iFieldId == 0)
        this->ulVersion = i16Value;
    return GORM_OK;
}

int GORM_Record::SetFieldValue(const char *szField, uint32 iValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, iValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, iValue);
}

int GORM_Record::SetFieldValue(int iFieldId, uint32 iValue)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, iValue);

    this->AddFieldOpt(iFieldId);

    if (iFieldId == 0)
        this->ulVersion = iValue;
    return GORM_OK;
}

int GORM_Record::SetFieldValue(const char *szField, uint64 lValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return SetCustomValue(szField, lValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
    
    return this->SetFieldValue(iFieldId, lValue);
}

int GORM_Record::SetFieldValue(int iFieldId, uint64 lValue)
{
    GORM_SetTableFieldValue(pPbMsg, iTableId, iFieldId, lValue);

    this->AddFieldOpt(iFieldId);

    if (iFieldId == 0)
        this->ulVersion = lValue;
    return GORM_OK;
}

#define GORM_SETCUSTOM_PRE()                                    \
if (pCustomColumns == nullptr)                                  \
{                                                               \
    if (GORM_OK != GORM_GetCustomPbMsg(this->pCustomColumns))   \
    {                                                           \
        return GORM_ERROR;                                      \
    }                                                           \
}

int GORM_Record::SetCustomValue(const char* szField, const char * pValue, const size_t sSize)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, pValue, sSize);
}

int GORM_Record::SetCustomValue(const char* szField, const char * pValue)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, pValue);
}

int GORM_Record::SetCustomValue(const char *szField, int8 i8Value)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, i8Value);
}
int GORM_Record::SetCustomValue(const char *szField, int16 i16Value)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, i16Value);
}
int GORM_Record::SetCustomValue(const char *szField, int32 iValue)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, iValue);
}
int GORM_Record::SetCustomValue(const char *szField, int64 lValue)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, lValue);
}
int GORM_Record::SetCustomValue(const char *szField, double flValue)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, flValue);
}
int GORM_Record::SetCustomValue(const char *szField, uint8 i8Value)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, i8Value);
}
int GORM_Record::SetCustomValue(const char *szField, uint16 i16Value)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, i16Value);
}
int GORM_Record::SetCustomValue(const char *szField, uint32 iValue)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, iValue);
}
int GORM_Record::SetCustomValue(const char *szField, uint64 lValue)
{
    GORM_SETCUSTOM_PRE();

    return GORM_SetCustomColumnValue(pCustomColumns, szField, lValue);
}

int GORM_Record::GetFieldValue(const char * szField, OUT string &strValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, strValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, strValue);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT string &strValue)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, strValue);
}

int GORM_Record::GetFieldValue(const char* szField, OUT uint8 *&pValue, OUT size_t &sSize)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, pValue, sSize);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, pValue, sSize);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT uint8 *&pValue, OUT size_t &sSize)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, pValue, sSize);
}

int GORM_Record::GetFieldValue(const char *szField, OUT int8 &i8Value)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, i8Value);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, i8Value);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT int8 &i8Value)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, i8Value);
}

int GORM_Record::GetFieldValue(const char *szField, OUT int16 &i16Value)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, i16Value);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, i16Value);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT int16 &i16Value)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, i16Value);
}

int GORM_Record::GetFieldValue(const char *szField, OUT int32 &iValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, iValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, iValue);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT int32 &iValue)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, iValue);
}

int GORM_Record::GetFieldValue(const char *szField, OUT int64 &lValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, lValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, lValue);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT int64 &lValue)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, lValue);
}

int GORM_Record::GetFieldValue(const char *szField, OUT uint8 &i8Value)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, i8Value);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, i8Value);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT uint8 &i8Value)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, i8Value);
}

int GORM_Record::GetFieldValue(const char *szField, OUT uint16 &i16Value)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, i16Value);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, i16Value);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT uint16 &i16Value)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, i16Value);
}

int GORM_Record::GetFieldValue(const char *szField, OUT uint32 &iValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, iValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, iValue);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT uint32 &iValue)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, iValue);
}

int GORM_Record::GetFieldValue(const char *szField, OUT uint64 &lValue)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_GetCustomColumnValue(pCustomColumns, szField, lValue);
    #else
        return GORM_INVALID_FIELD;
    #endif
    }

    return this->GetFieldValue(iFieldId, lValue);
}

int GORM_Record::GetFieldValue(int iFieldId, OUT uint64 &lValue)
{
    return GORM_GetTableFieldValue(pPbMsg, iTableId, iFieldId, lValue);
}

int GORM_Record::AddValueOperation(IN const char* field_name, IN GORM_Operation operation)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, field_name, iFieldId))
    {
    #ifdef GORM_DEBUG
        return GORM_OK;
    #else
        return GORM_INVALID_FIELD;
    #endif
    }
   
    return AddValueOperation(iFieldId, operation);
}

int GORM_Record::AddValueOperation(IN int iFieldId, IN GORM_Operation operation)
{
    if (operation == GORM_OP_PLUS)
    {
        this->plusField.AddField(iFieldId);
        this->minusField.DelField(iFieldId);
    }
    else
    {
        this->minusField.AddField(iFieldId);
        this->plusField.DelField(iFieldId);
    }
    
    return GORM_OK;
}

int GORM_Record::GetData(OUT PB_MSG_PTR &pPbMsg)
{
    pPbMsg = this->pPbMsg;

    return GORM_OK;
}

int GORM_Record::SetData(IN PB_MSG_PTR pPbMsg,   IN uint64 data_version)
{
    if (data_version > 0)
    {
        this->ulVersion = data_version;
    }

    if (this->pPbMsg != nullptr)
    {
        delete this->pPbMsg;
    }
    this->pPbMsg = pPbMsg;
    return GORM_OK;
}

int GORM_Record::AddFieldOpt(const char *szField)
{
    int iFieldId;
    if (GORM_OK != GORM_GetFieldID(iTableId, szField, iFieldId))
    {
        return GORM_INVALID_FIELD;
    }
    
    return this->AddFieldOpt(iFieldId);
}

int GORM_Record::AddFieldOpt(int iFieldId)
{
    this->requestField.AddField(iFieldId);
    return GORM_OK;
}

}
