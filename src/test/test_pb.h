#ifndef _TEST_PB_H__
#define _TEST_PB_H__

#include "test.pb.h"
#include <iostream>

using namespace db;
using namespace std;

char *getMyCat(int &iLen)
{
    Person* person = new Person();
    person->set_id(1);
    person->set_email("123");
    TestMyCat *mycat = new TestMyCat(); 
    mycat->set_id(2);
    mycat->set_allocated_man(person);

    iLen = mycat->ByteSize();
    char *pbBuffer = new char[iLen];
    mycat->SerializeToArray(pbBuffer, iLen);

    return pbBuffer;
}

void testMyCat(char *inBuffer, int iLen)
{
    TestMyCat mycatOut;
    mycatOut.ParseFromArray(inBuffer, iLen);
    cout << "id:" << mycatOut.man().id() << endl;
    cout << "email:" << mycatOut.man().email() << endl;
    cout << "mycat id:" << mycatOut.id() << endl;
}

int testPb() 
{
    Person* person = new Person();
    person->set_id(1);
    person->set_email("123");
    TestMyCat *mycat = new TestMyCat(); 
    mycat->set_id(2);
    mycat->set_allocated_man(person);

    int length = mycat->ByteSize();
    char *pbBuffer = new char[length];
    mycat->SerializeToArray(pbBuffer, length);

    TestMyCat mycatOut;
    mycatOut.ParseFromArray(pbBuffer, length);
    cout << "id:" << mycat->man().id() << endl;
    cout << "email:" << mycat->man().email() << endl;
    cout << "mycat id:" << mycat->id() << endl;
    
    return 0;
}

#endif
