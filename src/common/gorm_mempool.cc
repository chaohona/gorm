#include "gorm_mempool.h"
#include "gorm_utils.h"
#include "gorm_error.h"


GORM_MemPoolData::GORM_MemPoolData(char cStaticFlag)
{
    this->m_cStaticFlag = cStaticFlag;
}

GORM_MemPoolData::~GORM_MemPoolData()
{
    this->m_pMemPool = nullptr;
}

bool GORM_MemPoolData::Release()
{
    if (this->m_cStaticFlag == 1)
    {
        return true;
    }
    ASSERT(this->m_uszData != nullptr && this->m_uszEnd != nullptr && this->m_sCapacity != 0);
    this->m_pMemPool->Release(this);
    return true;
}

int GORM_MemPoolData::ReInit()
{
    ASSERT(this->m_cStaticFlag!=1);
    this->m_sUsedSize = 0;
    return GORM_OK;
}

GORM_MemPoolData *GORM_MemPool::GetData(char *szData, int iLen, size_t iSize)
{
    ASSERT(iSize>iLen);
    if (iSize < iLen)
        iSize = iLen;
    GORM_MemPoolData *pData = this->GetData(iSize);
    if (pData == nullptr)
    {
        return nullptr;
    }
    memcpy(pData->m_uszData, szData, iLen);
    pData->m_sUsedSize = iLen;
    return pData;
}

GORM_MemPoolData *GORM_MemPool::GetData(size_t sSize)
{
    int iIndex = POOL_DATA_INVALID_IDX;
    int iNewSize = sSize;
    // 计算index
    for(int i=0; i<POOL_DATA_TOTAL_TYPE; i++)
    {
        if (sSize <= this->m_aSize[i])
        {
            iIndex = i;
            iNewSize = m_aSize[i];
            break;
        }
    }
    if (iIndex < POOL_DATA_TOTAL_TYPE && !GORM_ARRAY_EMPTY(this->m_FreePoolList[iIndex])) // 从free链表中获取
    {
        GORM_MemPoolData* ret = GORM_ARRAY_POP(this->m_FreePoolList[iIndex]);
        ASSERT(ret!=nullptr && ret->m_uszData!=nullptr && ret->m_sCapacity==iNewSize);
        return ret;
    }

    GORM_MemPoolData *pData = nullptr;
    if (this->m_iFreeMetaNum > 0)
    {
        --this->m_iFreeMetaNum;
        pData = this->m_pFreeMetaData[this->m_iFreeMetaNum];
    }
    else
    {
        pData = new GORM_MemPoolData();
    }

    pData->m_pMemPool = this->m_pMySelf;
    pData->m_uiIndex = iIndex;
    pData->m_uszData = new char[iNewSize];
    pData->m_uszEnd = pData->m_uszData + iNewSize;
    pData->m_sCapacity = iNewSize;
    ASSERT(pData!=nullptr && pData->m_uszData!=nullptr && pData->m_uiIndex<=POOL_DATA_TOTAL_TYPE);
    return pData;
}

GORM_MemPoolData *GORM_MemPool::ReAlloc(GORM_MemPoolData *&pData, int iNeedSize)
{
    if (pData == nullptr)
    {
        pData = this->GetData(iNeedSize);
        return pData;
    }
    if (pData->m_sUsedSize >= iNeedSize)
        return pData;
    else
    {
        this->Release(pData);
        pData = this->GetData(iNeedSize);
    }
    return pData;
}

GORM_MemPool::GORM_MemPool()
{
    this->m_iFreeMetaNum = 0;
    // 预计算4个规格的池子可以申请内存的大小
    int iSize = POOL_DATA_MIN_LEN;
    for (int i=0; i<POOL_DATA_TOTAL_TYPE; i++)
    {
        this->m_aSize[i] = iSize;
        this->m_iMax = iSize;
        iSize = iSize << 1;
    }
}

// 单实例模式，析构函数暂时啥也不做
GORM_MemPool::~GORM_MemPool()
{
    
}

bool GORM_MemPool::Release(GORM_MemPoolData * pData)
{
    ASSERT(pData != nullptr && pData->m_uiIndex<=POOL_DATA_TOTAL_TYPE && pData->m_uszData!=nullptr && 
        pData->m_cStaticFlag==0 );
    if (pData == nullptr)
    {
        return true;
    }
    
    pData->m_sUsedSize = 0;
    if (pData->m_uiIndex < POOL_DATA_TOTAL_TYPE &&
        !GORM_ARRAY_FULL(this->m_FreePoolList[pData->m_uiIndex]))
    {
        GORM_ARRAY_PUSH( this->m_FreePoolList[pData->m_uiIndex], pData);
        ASSERT(pData->m_uszData!=nullptr && pData->m_uszEnd!=nullptr && pData->m_sCapacity!=0 && pData->m_uiIndex<POOL_DATA_TOTAL_TYPE);
        return true;
    } 
    else if (pData->m_uszData != nullptr)
    {
        delete []pData->m_uszData;
        pData->m_uszData = nullptr;
        pData->m_uszEnd = nullptr;
        pData->m_uiIndex = POOL_DATA_INVALID_IDX;
        pData->m_sCapacity = 0;
    }

    if (this->m_iFreeMetaNum < MAX_FREE_META_DATA)
    {
        this->m_pFreeMetaData[this->m_iFreeMetaNum] = pData;
        ++this->m_iFreeMetaNum;
    }
    else 
    {
        delete pData;
    }
    return true;
}


