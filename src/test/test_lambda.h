#ifndef _TEST_LAMBDA_H__
#define _TEST_LAMBDA_H__

#include "gorm_sys_inc.h"
#include "gorm_singleton.h"
#include "gorm_utils.h"
/*
class TestLambda: public Singleton<TestLambda>
{
public:

public:
    atomic<int> iCallTimes ;
};

void TestLambdaFunc()
{
    TestLambda::GetMe().iCallTimes = 0;
    for(int i=0; i<10000; i++)
    {
        thread t([]{
            ThreadSleepMilliSeconds(10);
            TestLambda::GetMe().iCallTimes++;
        });
        t.detach();
    }
    ThreadSleepMilliSeconds(100);
    cout << TestLambda::GetMe().iCallTimes++ << endl;
}*/

#endif
