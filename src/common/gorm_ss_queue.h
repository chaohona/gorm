#ifndef _GORM_SS_QUEUE_H__
#define _GORM_SS_QUEUE_H__

// 单写单读(只支持一个线程写，一个线程读)，队列
// 使用原子操作，比锁方式快3倍

#include "gorm_define.h"
#include "gorm_error.h"
#include "gorm_sys_inc.h"

template<class T, uint64 TOTALNUM>
class GORM_SSQueue
{
public:
    GORM_SSQueue():m_readIdx(0), m_writeIdx(0), m_nowNum(0)
    {
    }
    inline bool Put(const T& x)
    {
        if (this->Full())
            return false;
        int idx = this->m_writeIdx % TOTALNUM;
        this->m_data[idx] = x;
        ++this->m_writeIdx;
        ++this->m_nowNum;

        return true;
    }
    inline bool Take(T &out, int64 &leftNum)
    {
        if (this->Empty())
            return false;
        int idx = this->m_readIdx % TOTALNUM;
        out = m_data[idx];

        ++this->m_readIdx;
        leftNum = --this->m_nowNum;

        return true;
    }
    inline bool Take(T &out)
    {
        if (this->Empty())
            return false;
        int idx = this->m_readIdx % TOTALNUM;
        out = m_data[idx];

        ++this->m_readIdx;
        --this->m_nowNum;

        return true;
    }
    inline bool Full()
    {
        return m_nowNum == TOTALNUM;
    }
    inline bool Empty()
    {
        return m_nowNum == 0;
    }
public:
    atomic<T> m_data[TOTALNUM];
    uint64 m_readIdx;
    uint64 m_writeIdx;
    atomic<int64> m_nowNum;
};



#endif
