// control+c from <<深入应用C++11>> 9-2

#ifndef _GORM_THREAD_POOL_H__
#define _GORM_THREAD_POOL_H__

#include "gorm_sys_inc.h"
#include "gorm_type.h"
#include "gorm_mempool.h"
class GORM_ThreadPool;
class GORM_Thread
{
public:
    GORM_Thread(shared_ptr<GORM_ThreadPool>& pPool, string &strThreadName);
    virtual ~GORM_Thread();

    virtual void Work(mutex *m) = 0;
    // 通知事件回调
    // 用于在本线程处理io等待阶段(epoll_wait)，别的线程唤醒本线程的时候的回调
    virtual void SignalCB() = 0;
    //static void Start(shared_ptr<GORM_Thread> &pThread);
public:
    virtual void Join();
    virtual void Detach();

public:
    string                  m_strThreadName;
    shared_ptr<thread>      m_pSysThread;
    shared_ptr<GORM_ThreadPool> m_pPool;
    atomic_bool             m_bJoined;
    atomic_bool             m_bDetached;
    std::thread::id         m_threadId;
    shared_ptr<GORM_MemPool> m_pMemPool;
};

class GORM_ThreadPool
{
public:
    GORM_ThreadPool(string strThreadType);
    virtual ~GORM_ThreadPool();

    void Stop();
    // 创建iNum个线程
    virtual int CreateThread(int iNum) = 0;
    // m 为
    void StartWork(shared_ptr<GORM_Thread> pThread);

private:
    void StopThreadGroup();

public:
    mutex m_Mutex;
    string  m_strThreadType;
    unordered_map<std::thread::id, shared_ptr<GORM_Thread>> m_mapThreadGroup;
private:
    atomic_bool m_bRunning;
    once_flag m_OnceFlag;
};

#endif

