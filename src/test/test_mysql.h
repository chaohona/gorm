#ifndef _TEST_MYSQL_H__
#define _TEST_MYSQL_H__

#include "test_pb.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>

#include "gorm_type.h"

using namespace std;

int GetFromMySQL(char *&mysqlRow, int &iResultLen)
{
    char * c_host = "192.168.150.39";
    char * c_user = "mark";
    char * c_auth = "123456";
    int          c_port = 3306;
    char * c_sock = "/usr/local/mysql/mysql.sock";
    char * c_dbnm = "recordserver_test";

    MYSQL *mysql_local;
    MYSQL_RES *result;
    MYSQL_ROW row;
    net_async_status status;
    const char *stmt_text;

    if (!(mysql_local = mysql_init(NULL))) 
    {
        cout<<"mysql_init() failed\n";
        exit(1);
    }
    if(mysql_real_connect(mysql_local, c_host, c_user,
                          c_auth, c_dbnm, c_port,
                          nullptr, CLIENT_COMPRESS|CLIENT_MULTI_STATEMENTS|CLIENT_INTERACTIVE) == NULL)
    {
        cout << "connect to mysql failed" << endl;
        cout << mysql_error(mysql_local) << endl;
        return 1;
    }


    std::ostringstream strSql;
    char strData[100 * 2 + 1];
    strSql << "select ALLBINARY from buildcityland where LANDID=1;";

    int ret=mysql_real_query(mysql_local,strSql.str().c_str(),strSql.str().size());
    if(ret)
    {
        cout << "select failed:" << mysql_error(mysql_local) << endl;
    }
    else
    {
        cout << "select success" << endl;
    }

    result=mysql_store_result(mysql_local);
    if(result==NULL)
    {
    	cout << mysql_error(mysql_local) << endl;
    	return ret;
    }
    if (result == nullptr)
    {
        cout << "result is nullptr" << endl;
        return 0;
    }

    int iRowNum =mysql_num_rows(result);
    if(iRowNum == 0)
    {
        cout << "row num is zero" << endl;
        return 0;
    }
    cout << "got result from mysql, row num is:" << iRowNum << endl;

    
    
    row = mysql_fetch_row(result);
    unsigned long *lengths;
    lengths = mysql_fetch_lengths(result);

    //DWORD bin2size = *((DWORD *)row[0])+sizeof(DWORD);

    iResultLen = lengths[0];
	mysqlRow = new char[iResultLen];
	bcopy(row[0],mysqlRow,iResultLen);

	//testMyCat(mysqlRow, iResultLen);

    mysql_free_result(result);
    mysql_close(mysql_local);
    return 0;
}

int InsertToMyCat(char *pPutBuffer, int iLen)
{
    char * c_host = "192.168.150.39";
    char * c_user = "ztgame";
    char * c_auth = "123456";
    int          c_port = 8066;
    char * c_sock = "/usr/local/mysql/mysql.sock";
    char * c_dbnm = "recordserver_test";
    //int iLen;
    //char *pPutBuffer = getMyCat(iLen);
    cout << "protobuffer length:" << iLen << endl;

    MYSQL *mysql_local;
    MYSQL_RES *result;
    MYSQL_ROW row;
    net_async_status status;
    const char *stmt_text;

    if (!(mysql_local = mysql_init(NULL))) 
    {
        cout<<"mysql_init() failed\n";
        exit(1);
    }
    if(mysql_real_connect(mysql_local, c_host, c_user,
                          c_auth, c_dbnm, c_port,
                          nullptr, CLIENT_COMPRESS|CLIENT_MULTI_STATEMENTS|CLIENT_INTERACTIVE) == NULL)
    {
        cout << "connect to mysql failed" << endl;
        cout << mysql_error(mysql_local) << endl;
        return 1;
    }


    std::ostringstream strSql;
    char strData[iLen * 2 + 1];
    strSql << "insert into buildcityland(`LANDID`,`ALLBINARY`) values(0,";
    mysql_real_escape_string(mysql_local, strData,pPutBuffer,iLen);
    strSql << "\'" << strData << "\')";

    int ret=mysql_real_query(mysql_local,strSql.str().c_str(),strSql.str().size());

    if(ret)
    {
        cout << "insert failed:" << mysql_error(mysql_local) << endl;
    }
    else
    {
        cout << "insert success" << endl;
    }

    result=mysql_store_result(mysql_local);
    if(result==NULL)
    {
    	cout << mysql_error(mysql_local) << endl;
    	return ret;
    }
    if (result == nullptr)
    {
        cout << "result is nullptr" << endl;
        return 0;
    }

    int iRowNum =mysql_num_rows(result);
    if(iRowNum == 0)
    {
        cout << "row num is zero" << endl;
        return 0;
    }

    mysql_free_result(result);
    mysql_close(mysql_local);
    return 0;
}

#endif
