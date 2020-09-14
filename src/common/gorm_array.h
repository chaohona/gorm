#ifndef _GORM_ARRAY_H__
#define _GORM_ARRAY_H__

#include "gorm_define.h"
#include "gorm_error.h"
#include "gorm_sys_inc.h"

template<class T, int MAXSIZE>
class GORM_Array
{
public:
    T m_pTArray[MAXSIZE];
    int m_iMaxTotal = MAXSIZE;
    volatile int m_iIndex = 0;
};

#define GORM_ARRAY_PUSH_PTR(array, data)\
if ((array).m_iIndex >= (array).m_iMaxTotal) \
delete data;\
else\
{\
(array).m_pTArray[(array).m_iIndex] = data;\
++((array).m_iIndex);\
}


#define GORM_ARRAY_PUSH(array, data)\
if ((array).m_iIndex < (array).m_iMaxTotal) \
{\
(array).m_pTArray[(array).m_iIndex] = data;\
++((array).m_iIndex);\
}

#define GORM_ARRAY_POP(array)\
((array).m_pTArray[--((array).m_iIndex)])

#define GORM_ARRAY_EMPTY(array)\
((array).m_iIndex==0)

#define GORM_ARRAY_FULL(array)\
((array).m_iIndex==(array).m_iMaxTotal)

#define GORM_SIZE(array)\
((array).m_iIndex+1)

#endif


