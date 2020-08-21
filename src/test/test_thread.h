#ifndef _TEST_THREAD_H__
#define _TEST_THREAD_H__

#include <thread>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <vector>
#include <chrono>
#include <typeinfo>
#include <condition_variable>

using namespace std;

class TestConditionVariable
{
public:
    
};

class TestThread
{
public:
    timed_mutex tMutex;
    //mutex mutex;
    vector<thread>  vThreadList;
    vector<shared_ptr<thread>>  vSharedThreadList;  
};

TestThread  g_thread_var;

void TestTimedMutexLock()
{
    cout << "enter func TestTimedMutexLock" << endl;
    lock_guard<timed_mutex> locker(g_thread_var.tMutex);
    this_thread::sleep_for(chrono::seconds(5));
    cout << "mutex lock exists" << endl;
}

void TestTimedMutexTryLock()
{
    cout << "enter func TestTimedMutexTryLock" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    chrono::seconds timeouts(1);
    if (g_thread_var.tMutex.try_lock_for(timeouts))
    {
        cout << "try lock got mutex" << endl;
    }
    else
    {
        cout << "try lock does not got mutex" << endl;
    }
}

void TestMutexFunc()
{
    thread t1(TestTimedMutexTryLock);
    t1.detach();
    thread t2(TestTimedMutexLock);
    t2.detach();
    g_thread_var.vThreadList.push_back(move(t1));
    g_thread_var.vThreadList.push_back(move(t2));
}

void TestThread_Func(int iNum, const char *szStr)
{
    for(int i=0;;i++)
    {
        cout << i << " input num is:" << iNum << ", string is:" << szStr<< endl;
        sleep(1);
    }
    
}

void TestThread()
{
    thread t(TestThread_Func, 1, "123456");
    t.detach();
}

class UsedForThreadTest
{
public:
    void Print()
    {
        cout << "my num is:" << this->i << endl;
    }

public:
    int i = 10;

    shared_ptr<thread> m_pSysThread;
};

void TestClassThread()
{
    UsedForThreadTest *pClass = new UsedForThreadTest();
    pClass->m_pSysThread = make_shared<thread>(&UsedForThreadTest::Print, pClass);

    pClass->m_pSysThread->join();
}

#endif
