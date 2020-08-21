#ifndef _TEST_ASYNC_MYSQL_H__
#define _TEST_ASYNC_MYSQL_H__

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>
#include <unistd.h>

#include "test_pb.h"
#include "test_mysql.h"
#include "test_thread.h"


/* change following connection parameters as necessary */
static char * c_host = "127.0.0.1";
static char * c_user = "root";
static char * c_auth = "ztgame@123";
static int          c_port = 3306;
static char * c_sock = "/usr/local/mysql/mysql.sock";
static char * c_dbnm = "recordserver_test";

//mysql://ztgame:123456@192.168.181.191:3066/recordserver_test1
//static const char * c_host = "192.168.181.191";
//static const char * c_user = "ztgame";
//static const char * c_auth = "123456";
//static int          c_port = 8066;
//static const char * c_sock = "/usr/local/mysql/mysql.sock";
//static const char * c_dbnm = "recordserver_test1";

void perform_arithmetic() {
  //cout<<"dummy function invoked\n";
  for (int i = 0; i < 1000; i++)
    i*i;
}

void TestAsyncMySql()
{  
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
    while ((status = mysql_real_connect_nonblocking(mysql_local, c_host, c_user,
                                                  c_auth, c_dbnm, c_port,
                                                  c_sock, 0))
            == NET_ASYNC_NOT_READY)
    ; /* empty loop */
    if (status == NET_ASYNC_ERROR) 
    {
        cout<<"mysql_real_connect_nonblocking() failed\n";
        exit(1);
    }

    char insert_data[100];
    char *insert_string = "this is a test";
    memcpy(insert_data, insert_string, strlen(insert_string));

    std::ostringstream strSql;
    strSql << "insert into buildcityland(`LANDID`,`ALLBINARY`) values(0,";
    strSql << "\'" << insert_data << "\'";

    int ret=mysql_real_query(mysql_local, strSql.str().c_str(), strSql.str().size());

    if(ret)
    {
        cout << "got error:" << mysql_error(mysql_local) << endl;
        cout << strSql.str() <<endl;
    }

    MYSQL_RES *resultInsert;
    mysql_fetch_row(resultInsert);

    /* run query asynchronously */
    stmt_text = "SELECT * FROM BUILDCITYLAND limit 3";
    status = mysql_real_query_nonblocking(mysql_local, stmt_text,
                                        (unsigned long)strlen(stmt_text));
    /* do some other task before checking function result */
    perform_arithmetic();
    while (status == NET_ASYNC_NOT_READY) {
        status = mysql_real_query_nonblocking(mysql_local, stmt_text,
                                              (unsigned long)strlen(stmt_text));
        perform_arithmetic();
    }
    if (status == NET_ASYNC_ERROR) 
    {
        cout<<"mysql_real_query_nonblocking() failed\n";
        exit(1);
    }

    /* retrieve query result asynchronously */
    status = mysql_store_result_nonblocking(mysql_local, &result);
    /* do some other task before checking function result */
    perform_arithmetic();
    while (status == NET_ASYNC_NOT_READY) {
        status = mysql_store_result_nonblocking(mysql_local, &result);
        perform_arithmetic();
    }
    if (status == NET_ASYNC_ERROR) 
    {
        cout<<"mysql_store_result_nonblocking() failed\n";
        exit(1);
    }
    if (result == NULL) 
    {
        cout<<"mysql_store_result_nonblocking() found 0 records\n";
        exit(1);
    }

    /* fetch a row synchronously */
    row = mysql_fetch_row(result);
    if (row != NULL)
        cout<<"ROW: " << row[0] << "\n";
    else
        cout<<"incorrect result fetched\n";

    /* fetch a row asynchronously, but without doing other work */
    while (mysql_fetch_row_nonblocking(result, &row) != NET_ASYNC_COMPLETE)
    ; /* empty loop */
    /* 2nd row fetched */
    if (row != NULL)
        cout<<"ROW: " << row[0] << "\n";
    else
        cout<<"incorrect result fetched\n";

    /* fetch a row asynchronously, doing other work while waiting */
    status = mysql_fetch_row_nonblocking(result, &row);
    /* do some other task before checking function result */
    perform_arithmetic();
    while (status != NET_ASYNC_COMPLETE) 
    {
        status = mysql_fetch_row_nonblocking(result, &row);
        perform_arithmetic();
    }
    /* 3rd row fetched */
    if (row != NULL)
        cout<<"ROW: " << row[0] << "\n";
    else
        cout<<"incorrect result fetched\n";

    /* fetch a row asynchronously (no more rows expected) */
    while ((status = mysql_fetch_row_nonblocking(result, &row))
           != NET_ASYNC_COMPLETE)
    ; /* empty loop */
    if (row == NULL)
        cout <<"No more rows to process.\n";
    else
        cout <<"More rows found than expected.\n";

    /* free result set memory asynchronously */
    while (mysql_free_result_nonblocking(result) != NET_ASYNC_COMPLETE)
    ; /* empty loop */

    mysql_close(mysql_local);
}


#endif
