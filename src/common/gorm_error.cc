#include "gorm_error.h"


static const RetStringTable StringsOfBaseRet[] = {
    {GORM_ERROR,                "unkown error"},
    {GORM_EAGAIN,               "socket error eagain"},
    {GORM_INVALID_CLIENT,       "invalid client"},
    {GORM_PART_FAILED,          "part failed"},
    
    {GORM_OK,                   "okay"},
};

inline const char *GORM_ErrStr(int iRet)
{
    for (RetStringTable itr: StringsOfBaseRet)
    {
        if (itr.iCode == iRet)
        {
            return itr.pString;
        }
    }

    return "invalid error code";
}

