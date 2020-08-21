#ifndef _TEST_GORM_QUEUE_H__
#define _TEST_GORM_QUEUE_H__

#include "gorm_sys_inc.h"

#include "gorm_queue.h"

static const int g_queue_siz = 10;
GORM_SyncQueue<int> g_sync_queue(g_queue_siz);

void TestGORMQueuePut()
{
    for(int i=0; i<g_queue_siz; i++)
    {
        g_sync_queue.Put(i);
    }

    cout << "TestGORMQueuePut put 10 data to queue" << endl;
    this_thread::sleep_for(chrono::seconds(5));

    int iOutValue;
    g_sync_queue.Take(iOutValue);
    cout << "TestGORMQueuePut take 1 from queue" << endl;

    return;
}

void TestGORMQueueTask()
{
    this_thread::sleep_for(chrono::seconds(1));

    cout << "TestGORMQueueTask want put 1 to queue" << endl;
    g_sync_queue.Put(1);
    cout << "TestGORMQueueTask put 1 to queue success" << endl;

    return;
}

void TestQueueThread()
{
    thread t1(TestGORMQueuePut);
    thread t2(TestGORMQueueTask);

    t1.detach();
    t2.detach();
}

#endif

