// control+c from <<深入应用C++11>> 代码清单5-6

#ifndef _GORM_QUEUE_H__
#define _GORM_QUEUE_H__

#include "gorm_sys_inc.h"
#include "gorm_array.h"

using namespace std;

template<typename T, int MAXSIZE>

class GORM_SyncQueue
{
public:
    GORM_SyncQueue(int iMaxSize):m_iMaxSize(MAXSIZE), m_bNeedStop(false)
    {
    }

    void Put(const T& x)
    {
        Add(x);
    }
    void Put(T &&x)
    {
        Add(forward<T>(x));
    }
    void Take(GORM_Array<T> &list)
    {
        unique_lock<mutex> locker(m_Mutex);
        m_cvNotEmpty.wait(locker, [this]{return m_bNeedStop || NotEmpty();});

        if (m_bNeedStop)
            return;
        list = move(m_vQueue);
        
        m_cvNotFull.notify_one();
    }
    void Take(T &x)
    {
        unique_lock<mutex> locker(m_Mutex);
        m_cvNotEmpty.wait(locker, [this]{return m_bNeedStop || NotEmpty();});

        if (m_bNeedStop)
            return;
        x = GORM_ARRAY_POP(m_vQueue);
        
        m_cvNotFull.notify_one();
    }
    void Stop()
    {
        {
            unique_lock<mutex> locker(m_Mutex);
            m_bNeedStop = true;
        }
        m_cvNotEmpty.notify_all();
        m_cvNotFull.notify_all();
    }

    bool Empty()
    {
        unique_lock<mutex> locker(m_Mutex);
        return GORM_ARRAY_EMPTY(m_vQueue);
    }

    bool Full()
    {
        unique_lock<mutex> locker(m_Mutex);
        return GORM_ARRAY_FULL(m_vQueue);
    }

    size_t Size()
    {
        unique_lock<mutex> locker(m_Mutex);
        return GORM_SIZE(m_vQueue);
    }

    int Count()
    {
        return GORM_SIZE(m_vQueue);
    }

private:
    bool NotFull() const
    {
        return !GORM_ARRAY_FULL(m_vQueue);
    }
    bool NotEmpty() const
    {
        return !GORM_ARRAY_EMPTY(m_vQueue);
    }

    template<typename F>
    void Add(F &&x)
    {
        /*unique_lock<mutex> locker(m_Mutex);
        m_cvNotFull.wait(locker, [this]{return m_bNeedStop || NotFull();});
        if (m_bNeedStop)
        {
            return;
        }
        
        //m_vQueue.push_back(forward<F>(x));
        GORM_ARRAY_PUSH(m_vQueue, forward<F>(x));
        
        m_cvNotEmpty.notify_one();*/
    }
    inline bool IsFull()
    {
        return GORM_ARRAY_FULL(m_vQueue);
    }
    inline bool IsEmpty()
    {
        return GORM_ARRAY_EMPTY(m_vQueue);
    }
private:
    int m_iMaxSize = MAXSIZE;
    mutex m_Mutex;
    condition_variable m_cvNotEmpty;
    condition_variable m_cvNotFull;
    GORM_Array<T, MAXSIZE> m_vQueue;

    bool m_bNeedStop;
};

#endif

