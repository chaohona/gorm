#ifndef _GORM_OBJECT_POOL_H__
#define _GORM_OBJECT_POOL_H__


#include "gorm_define.h"
#include "gorm_error.h"
#include "gorm_sys_inc.h"

class GORM_Object{};

typedef GORM_Object* (*ObjectBuilder)();
typedef void (*ObjectRelease)(GORM_Object*);

template <typename T, int iCapacity>
class GORM_ObjectPool
{
public:
    GORM_ObjectPool()
    {
    }
    ~GORM_ObjectPool()
    {
    }
    inline T* Get()
    {
        return new T();
    }
    inline void Release(T *&pData)
    {
        if (pData != nullptr)
            delete pData;
        pData = nullptr;
    }
public:
    T **m_pTArray;
    int m_iMaxTotal;
    int m_iIndex;
};


#endif
