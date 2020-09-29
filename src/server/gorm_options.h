#ifndef _GORM_OPTIONS_H__#define _GORM_OPTIONS_H__#include "gorm_define.h"#include "gorm_singleton.h"#include <getopt.h>int GORM_GetOptions(int argc, char **argv);static struct option long_options[] = {    { "help",           no_argument,        NULL,   'h' },    { "version",        no_argument,        NULL,   'V' },    { "daemonize",      no_argument,        NULL,   'd' },    { "config",         required_argument,  NULL,   'c' },    { "pid-file",       required_argument,  NULL,   'p' }, // pid    { "addr",           required_argument,  NULL,   'a' }, // 监听地址    { "works",          required_argument,  NULL,   'w' }, // 工作子进程个数    { NULL,             0,                  NULL,    0  }};static char short_options[] = "hVd:c:p:a:";class GORM_Options : public GORM_Singleton<GORM_Options>{public:    int showHelp = 0;    int showVersion = 0;    int daemonize = 0;    int works   = 1;    char *pidFile = nullptr;        char *confFileName = (char*)"./conf/gorm-server.yml";    // FOR TEST    char *dbname = "test1";};#endif