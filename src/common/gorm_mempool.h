#ifndef _MEM_POOL_H__
#define _MEM_POOL_H__
#include "gorm_sys_inc.h"
#include "gorm_define.h"
#include "gorm_array.h"

// TODO 目前为全局共享，TODO改成一个线程一个内存池

using namespace std;

#define POOL_DATA_TOTAL_TYPE 12
#define POOL_DATA_INVALID_IDX POOL_DATA_TOTAL_TYPE
#define POOL_DATA_MIN_LEN   0x200 // 512B

#define GORM_MEMDATA_RELEASE(POOL_DATA)           \
if (POOL_DATA->m_cStaticFlag != 1)              \
{                                               \
    ASSERT(POOL_DATA->m_uszData != nullptr && POOL_DATA->m_uszEnd != nullptr && POOL_DATA->m_sCapacity != 0);\
    GORM_MEMPOOL_INSTANCE()->Release(POOL_DATA);  \
}

#define GORM_Reset_MemData_MemPool(memdata, newpool)\
if (memdata != nullptr)                             \
{                                                   \
    memdata->m_pMemPool = nullptr;                  \
    memdata->m_pMemPool = newpool;                  \
}

class GORM_MemPool;
// 内存
struct GORM_MemPoolData {
public:
    GORM_MemPoolData(char cStaticFlag=0);
    ~GORM_MemPoolData();
    bool Release();           // 回收内存到内存池
    int ReInit();
public:
    char            m_cStaticFlag = 0;  // 为1则不释放
    char           *m_uszData = nullptr;     // 内存起始地址
    char           *m_uszEnd = nullptr;      // 可使用的内存结束的地方
    uint16          m_uiIndex = 0;       // 在内存池中的下标,-1为大内存
    size_t          m_sCapacity = 0;    // 内存容量
    size_t          m_sUsedSize = 0;    // 有效内容的使用量
    GORM_MemPoolData  *m_pNext = nullptr;//   下一个
    shared_ptr<GORM_MemPool> m_pMemPool;
};


#define GORM_MallocFromSharedPool(sharedPool, data, len)\
data = sharedPool->GetData(len);                        \
data->m_pMemPool = sharedPool;

// 由于要适用网络层数据包缓存与命令缓存两种规格的内存使用场景
// 内存规格较多的较多小内存给命令使用，大内存给网络层使用
#define MAX_FREE_META_DATA 0xFFFF
class GORM_MemPool
{
public:
    GORM_MemPool();
    virtual ~GORM_MemPool();

public:
    GORM_MemPoolData *GetData(char *szData, int iLen, size_t iSize);        // 申请内存，并把szData的数据拷贝到内存中
    GORM_MemPoolData *GetData(size_t iSize);                // 申请sSize大小的内存
    GORM_MemPoolData *ReAlloc(GORM_MemPoolData *&pData, int iNeedSize);
    bool Release(GORM_MemPoolData *pData);                  // 回收申请的内存池

public:
    shared_ptr<GORM_MemPool> m_pMySelf;
private:
    int                     m_aSize[POOL_DATA_TOTAL_TYPE];
    GORM_Array<GORM_MemPoolData*, 128> m_FreePoolList[POOL_DATA_TOTAL_TYPE];
    int                     m_iMax;

    GORM_MemPoolData*        m_pFreeMetaData[MAX_FREE_META_DATA];// 缓存一万条数据(TODO和内存数据放在一起，不用单独管理)
    int                     m_iFreeMetaNum;
    mutex   m_Mutex;
};


#endif

