#ifndef _GR_RING_BUFFER_H__
#define _GR_RING_BUFFER_H__
#include "gorm_inc.h"
#include "gorm_sys_inc.h"
#include "gorm_log.h"

#define GORM_RB_EMPTY(pool)\
(pool->m_iDataNum == 0)


#define GORM_RB_POOLFULL(pool)\
(pool->m_iDataNum == pool->m_iPoolCapacity)

#define GORM_RB_POPFRONT(result_type, result, rb) \
{                                               \
    if (rb->m_iDataNum == 0)                    \
    {                                           \
        result = nullptr;                       \
    }                                           \
    else                                        \
    {                                           \
        rb->m_iDataNum -= 1;                    \
        T *pRet = *(rb->m_pStart);           \
        T **tmp = rb->m_pStart;              \
        rb->m_pStart += 1;                      \
        *tmp = nullptr;                         \
        if (rb->m_pStart >= rb->m_pWaitMsgEnd)  \
        {                                       \
            rb->m_pStart = rb->m_pWaitMsgPool;  \
        }                                       \
        result = (result_type)pRet;             \
    }                                           \
}

#define GORM_RB_GETFRONT(result_type, result, rb) \
{                                               \
    if (rb->m_iDataNum == 0)                    \
    {                                           \
        result =  nullptr;                      \
    }                                           \
    result = (result_type)*(rb->m_pStart);      \
}

#define GORM_RB_GETDATA(result_type, result, ulNextIndex, rb)\
result=(result_type)rb->m_pWaitMsgPool[ulNextIndex%(rb->m_iPoolCapacity)];

// 环形池子,不能自动伸缩大小
template<class T>
class GORM_RingBuffer
{
public:
    GORM_RingBuffer(int iPoolLen)
    {
        this->Init(iPoolLen);
    }
    GORM_RingBuffer()
    {
        this->Init(1024);
    }
    ~GORM_RingBuffer()
    {
        if(this->m_pWaitMsgPool != nullptr)
        {
            delete []this->m_pWaitMsgPool;
            this->m_pWaitMsgPool = nullptr;
        }
    }
public:
    // 将返回标记放入pool中
    inline bool AddData(T* pData)
    {
        if (GORM_RB_POOLFULL(this))
        {
            return false;
        }

        this->m_iDataNum += 1;
        *this->m_pEnd = pData;
        this->m_pEnd += 1;
        if (this->m_pEnd == this->m_pWaitMsgEnd)
        {
            this->m_pEnd = this->m_pWaitMsgPool;
        }
        return true;
    }
    inline bool AddData(T *pData, uint64 ulIndex)
    {
        if (GORM_RB_POOLFULL(this))
        {
            return false;
        }

        int index = ulIndex%(m_iPoolCapacity);
        if (this->m_pEnd != this->m_pWaitMsgPool + index)
        {
            GORM_LOGE("ring buffer add failed");
            return false;
        }
        *this->m_pEnd = pData;
        this->m_pEnd += 1;
        if (this->m_pEnd == this->m_pWaitMsgEnd)
        {
            this->m_pEnd = this->m_pWaitMsgPool;
        }
        this->m_iDataNum += 1;
        return true;
    }
    // pool是否已经满了
    inline bool PoolFull()
    {
        return this->m_iDataNum == this->m_iPoolCapacity;
    }
    // 返回元素个数
    inline int  GetNum()
    {
        return this->m_iDataNum;
    }
    inline T* PopFront()
    {
        if (this->m_iDataNum == 0)
        {
            return nullptr;
        }
        this->m_iDataNum -= 1;
        T *pRet = *m_pStart;
        T **tmp = m_pStart;
        m_pStart += 1;
        *tmp = nullptr;

        if (m_pStart >= this->m_pWaitMsgEnd)
        {
            m_pStart = this->m_pWaitMsgPool;
        }
        return pRet;
    }
    inline T* PopFront(int iNum)
    {
        T* pRet;
        for(int i=0; i<iNum; i++)
        {
            pRet = this->PopFront();
            if (pRet == nullptr)
            {
                return nullptr;
            }
        }

        return nullptr;
    }
    inline T* GetFront()
    {
        if (this->m_iDataNum == 0)
        {
            return nullptr;
        }
        return *m_pStart;
    }
    inline  T *GetFront(T **pNow)
    {
        if (this->m_iDataNum == 0)
        {
            return nullptr;
        }
        pNow = m_pStart;
        return *m_pStart;
    }
    
    inline T *GetBack()
    {
        if (this->m_iDataNum == 0)
        {
            return nullptr;
        }
        T **pBack;
        if (m_pEnd == m_pWaitMsgPool || m_pEnd == m_pWaitMsgEnd)
        {
            pBack = m_pWaitMsgEnd-1;
            return *pBack;
        }
        
        pBack = m_pEnd-1;
        return *(pBack);
    }
    // bValid表示返回的是否是有效数据
    inline T *GetData(uint64 ulIndex, bool &bValid)
    {
        return this->m_pWaitMsgPool[ulIndex%(this->m_iPoolCapacity)];
    }
    inline T *GetPre(T **pData, bool &bValid)
    {
        if(pData-1 >= this->m_pWaitMsgPool)
        {
            return *(pData-1);
        }
        return *(this->m_pWaitMsgEnd-1);
    }
    inline T *GetPre(uint64 ulIndex, bool &bValid)
    {
        return this->m_pWaitMsgPool[(ulIndex-1)%(this->m_iPoolCapacity)];
    }
    inline T *GetNext(T **pData, bool &bValid)
    {
        if (pData+1 < this->m_pWaitMsgEnd)
        {
            return *(pData+1);
        }
        return *(this->m_pWaitMsgPool);
    }
    inline T *GetNext(uint64 ulIndex, bool &bValid)
    {
        return this->m_pWaitMsgPool[(ulIndex+1)%(this->m_iPoolCapacity)];
    }
    inline T *GetData(uint64 ulIndex)
    {
        return this->m_pWaitMsgPool[ulIndex%(this->m_iPoolCapacity)];
    }
    inline T *GetPre(T **pData)
    {
        if(pData-1 >= this->m_pWaitMsgPool)
        {
            return *(pData-1);
        }
        return *(this->m_pWaitMsgEnd-1);
    }
    inline T *GetPre(uint64 ulIndex)
    {
        return this->m_pWaitMsgPool[(ulIndex-1)%(this->m_iPoolCapacity)];
    }
    inline T *GetNext(T **pData)
    {
        if (pData+1 < this->m_pWaitMsgEnd)
        {
            return *(pData+1);
        }
        return *(this->m_pWaitMsgPool);
    }
    inline T *GetNext(uint64 ulIndex)
    {
        return this->m_pWaitMsgPool[(ulIndex+1)%(this->m_iPoolCapacity)];
    }

    int ReInit()
    {
        memset(this->m_pWaitMsgPool, 0, this->m_iPoolCapacity*sizeof(char*));
        this->m_pStart = this->m_pWaitMsgPool;
        this->m_pEnd = this->m_pWaitMsgPool;
        this->m_pWaitMsgEnd = this->m_pWaitMsgPool + this->m_iPoolCapacity;
        this->m_iDataNum = 0;
        return GORM_OK;
    }
    inline bool Empty()
    {
        return this->m_iDataNum == 0;
    }
    inline bool Full()
    {
        return this->m_iDataNum == m_iPoolCapacity;
    }
    inline int GetCapcity()
    {
        return this->m_iPoolCapacity;
    }
private:
    bool Init(int iPoolLen)
    {
        this->m_pWaitMsgPool = new T*[iPoolLen];
        this->m_iPoolCapacity = iPoolLen;
        this->ReInit();
        return true;
    }
public:
    int         m_iPoolCapacity = 0;
    T        **m_pStart = nullptr;         // 池子的起点(固定的起点)
    T        **m_pEnd = nullptr;           // 池子的尾点(固定的结尾)
    T        **m_pWaitMsgPool = nullptr;   // 移动的有效数据的起点
    T        **m_pWaitMsgEnd = nullptr;    // 移动的有效数据的尾点
    int         m_iDataNum = 0;
};

#endif

