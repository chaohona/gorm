#include "gorm_sys_inc.h"
#include "gorm_utils.h"

#include "test_pb.h"
#include "test_mysql.h"
#include "test_thread.h"
#include "test_async_mysql.h"
#include "test_gorm_queue.h"
#include "test_lambda.h"
#include "test_database_route.h"

using namespace std;

int main(int argc, char ** argv)
{
    TestLoadRoute();
    return 0;
}

