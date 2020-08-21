#include "gorm_thread_pool.h"


GORM_Thread::GORM_Thread(shared_ptr<GORM_ThreadPool>& pPool, string &strThreadName):m_strThreadName(strThreadName), 
                        m_pPool(pPool), m_bJoined(false), m_bDetached(false)
{
}

GORM_Thread::~GORM_Thread()
{
    this->m_pPool = nullptr;
    this->m_pSysThread = nullptr;
}

void GORM_Thread::Join()
{
    this->m_pSysThread->join();    
}

void GORM_Thread::Detach()
{
    this->m_pSysThread->detach();
}

GORM_ThreadPool::GORM_ThreadPool(string strThreadType):m_strThreadType(strThreadType)
{
}

GORM_ThreadPool::~GORM_ThreadPool()
{
    Stop();
}

void GORM_ThreadPool::Stop()
{
    call_once(m_OnceFlag, [this]{StopThreadGroup();});
}

void GORM_ThreadPool::StartWork(shared_ptr<GORM_Thread> pThread)
{
    if (pThread == nullptr)
    {
        return;
    }

    pThread->m_pSysThread = make_shared<thread>(&GORM_Thread::Work, pThread, &this->m_Mutex);
    m_mapThreadGroup[pThread->m_pSysThread->get_id()] = pThread;
    pThread->Detach();
    pThread->m_threadId = pThread->m_pSysThread->get_id();
    return;
}

void GORM_ThreadPool::StopThreadGroup()
{
    m_bRunning = false;

    for(auto &thread : m_mapThreadGroup)
    {
        thread.second->Join();
    }

    m_mapThreadGroup.clear();
}

