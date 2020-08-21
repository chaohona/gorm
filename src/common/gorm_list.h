#ifndef _GORM_LIST_H__
#define _GORM_LIST_H__

#include "gorm_sys_inc.h"
#include "gorm_define.h"

using namespace std;

template<typename T>

class GORM_SyncList
{
public:
    GORM_SyncList(int iMaxSize = 1024):m_iMaxSize(iMaxSize), m_bNeedStop(false)
    {
    }

    uint64 Put(const T& x)
    {
        return Add(x);
    }
    uint64 Put(T &&x)
    {
        return Add(forward<T>(x));
    }
    void Take(list<T> &list)
    {
        unique_lock<mutex> locker(m_Mutex);

        if (m_bNeedStop)
            return;
        if (this->m_vList.empty())
            return;
        list = move(m_vList);
    }
    void Take(T &x)
    {
        unique_lock<mutex> locker(m_Mutex);
        if (m_bNeedStop)
            return;
        if (this->m_vList.empty())
            return;
        x = m_vList.front();
        m_vList.pop_front();
    }
    void Front(T &x)
    {
        unique_lock<mutex> locker(m_Mutex);
        x = m_vList.front();
    }
    void Stop()
    {
        {
            unique_lock<mutex> locker(m_Mutex);
            m_bNeedStop = true;
        }
    }

    bool Empty()
    {
        unique_lock<mutex> locker(m_Mutex);
        return m_vList.empty();
    }

    bool Full()
    {
        unique_lock<mutex> locker(m_Mutex);
        return m_vList.size() == m_iMaxSize;
    }

    size_t Size()
    {
        unique_lock<mutex> locker(m_Mutex);
        return m_vList.size();
    }

    int Count()
    {
        return m_vList.size();
    }

private:
    template<typename F>
    uint64 Add(F &&x)
    {
        unique_lock<mutex> locker(m_Mutex);
        if (m_ulSeq > 0xEFFFFF)
        {
            m_ulSeq = 0;
        }
        if (m_bNeedStop)
        {
            return 0;
        }
        
        m_vList.push_back(forward<F>(x));

        return ++m_ulSeq;
    }
private:
    int m_iMaxSize;
    mutex m_Mutex;
    list<T> m_vList;

    bool m_bNeedStop;
    uint64  m_ulSeq = 0;
};

#endif
