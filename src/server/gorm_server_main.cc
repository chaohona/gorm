#include "gorm_sys_inc.h"
#include "gorm_server_instance.h"
#include "gorm_error.h"
#include "gorm_config.h"
#include "gorm_daemonize.h"
#include "gorm_options.h"
#include "gorm_utils.h"
#include "gorm_work_thread.h"
#include "gorm_frontend_thread.h"
#include "gorm_db_config.h"
#include "gorm_table_field_map.h"
#include "gorm_mysql_sdk_test.h"

static bool bGlobalStopFlag = false;

// 启动工作进程
bool StartWorkThread(int iWorkNum)
{
    if (GORM_OK != GORM_WorkThreadPool::Instance()->CreateThread(iWorkNum))
        return false;
    return true;
}

// 启动前端监听进程
bool StartFrontendThread()
{
    if (GORM_OK != GORM_FrontEndThreadPool::Instance()->CreateThread(1))
        return false;
    return true;
}

// 主线程，管理线程，处理各种管理消息
bool MainLoop()
{
    for(;!bGlobalStopFlag;)
    {
        ThreadSleepSeconds(1);
    }
}

GORM_Ret PreRun()
{
    // 1、解析配置文件
    char *szCfgFile = GORM_Options::Instance()->confFileName;
    if (!GORM_Config::Instance()->Init(szCfgFile))
    {
        cout << "parse config file failed." << endl;
        return GORM_ERROR;
    }

    GORM_DefaultLog::Instance()->SetLogLevel(GORM_Config::Instance()->m_iLogLevel);

    if (GORM_OK != GORM_TableFieldMapInstance::Instance()->Init(GORM_DefaultLog::Instance()))
    {
        cout << "init table field map failed." << endl;
        return GORM_ERROR;
    }

    // 加载db路由等信息
    if (GORM_OK != ReloadRoute(GORM_Config::Instance()->m_strDbCfg.c_str()))
    {
        cout << "parse database config failed" << endl;
        return GORM_ERROR;
    }
    // 2、设置后台运行
    if (GORM_Config::Instance()->m_bDaemonize)
        GORM_Daemonize();
    return GORM_OK;
}

int main(int argc, char** argv)
{
//#ifdef GORM_MYSQL_TEST
//    GORM_MySQLSDKTest(argc, argv);
//    return 0;
//#endif
    // 准备工作
    if (GORM_OK != GORM_GetOptions(argc, argv))
    {
        cout << "parse args failed." << endl;
        return -1;
    }
    if (GORM_OK != PreRun())
    {
        cout << "prepare to work failed." << endl;
        return -1;
    }
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGALRM);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGTERM);
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
        cout << "sigprocmask failed, errno:" << errno <<", errmsg:" << strerror(errno) << endl;;
        return GORM_ERROR;
    }
    // 1、启动工作线程
    if (!StartWorkThread(GORM_Config::Instance()->m_iWorkThreadNum))
    {
        cout << "start work thread failed." << endl;
        return -1;
    }
    // 2、启动前端监听线程
    if (!StartFrontendThread())
    {
        cout << "start frontend thread failed." << endl;
        return -1;
    }

    MainLoop();
    
    return 0;
}

