#include "gorm_log.h"
#include "gorm_inc.h"

#include <stdio.h>

using namespace gorm;

GORM_Log::~GORM_Log()
{
}

void GORM_Log::SetLogLevel(GORM_LOG_LEVEL logLevel)
{
    m_iLogLevel = logLevel;
}

GORM_DefaultLog *GORM_DefaultLog::pInstance = new GORM_DefaultLog();

GORM_DefaultLog* GORM_DefaultLog::Instance()
{
    return GORM_DefaultLog::pInstance;
}

GORM_DefaultLog::~GORM_DefaultLog()
{
}

bool GORM_DefaultLog::Init()
{
    return true;
}

// 需要修改glog增加一个debug级别的日志
void GORM_DefaultLog::Debug(const char *szFile, int iLine, const char * szArgs, ...)
{
#ifndef _WIN32
    unique_lock<mutex> locker(m_Mutex);
    int len, size, errno_save;
    char buf[4 * LOG_MAX_LEN];
    va_list args;
    size_t n;

    errno_save = errno;
    len = 0;                /* length of output buffer */
    size = 4 * LOG_MAX_LEN; /* size of output buffer */

    uint64 ulNow = CURRENT_MS();
    va_start(args, szArgs);
    len += snprintf(buf+len, size-len, "%ld %s:%d] ", ulNow, szFile, iLine);
    len += GORM_VscnPrintf(buf+len, size-len, szArgs, args);
    va_end(args);

    buf[len++] = '\n';
    buf[len] = '\0';

    GORM_Write(STDERR_FILENO, buf, len);
#endif
	return;
}

void GORM_DefaultLog::Info(const char *szFile, int iLine, const char * szArgs, ...)
{
#ifndef _WIN32
    unique_lock<mutex> locker(m_Mutex);
    int len, size, errno_save;
    char buf[4 * LOG_MAX_LEN];
    va_list args;
    int n;

    errno_save = errno;
    len = 0;                /* length of output buffer */
    size = 4 * LOG_MAX_LEN; /* size of output buffer */

    uint64 ulNow = CURRENT_MS();
    va_start(args, szArgs);
    len += snprintf(buf+len, size-len, "%ld %s:%d] ", ulNow, szFile, iLine);
    len += GORM_VscnPrintf(buf+len, size-len, szArgs, args);
    va_end(args);

    buf[len++] = '\n';
    buf[len] = '\0';

    GORM_Write(STDERR_FILENO, buf, len);
#endif
	return;
}

void GORM_DefaultLog::Error(const char *szFile, int iLine, const char *szArgs, ...)
{
#ifndef _WIN32
    unique_lock<mutex> locker(m_Mutex);
    int len, size, errno_save;
    char buf[4 * LOG_MAX_LEN];
    va_list args;
    size_t n;

    errno_save = errno;
    len = 0;                /* length of output buffer */
    size = 4 * LOG_MAX_LEN; /* size of output buffer */

    uint64 ulNow = CURRENT_MS();
    va_start(args, szArgs);
    len += snprintf(buf+len, size-len, "%ld %s:%d] ", ulNow, szFile, iLine);
    len += GORM_VscnPrintf(buf+len, size-len, szArgs, args);
    va_end(args);

    buf[len++] = '\n';
    buf[len] = '\0';

    GORM_Write(STDERR_FILENO, buf, len);
#endif
	return;
}

void GORM_DefaultLog::StdErr(const char *szFile, int iLine, const char *szArgs, ...)
{
#ifndef _WIN32
    unique_lock<mutex> locker(m_Mutex);
    int len, size, errno_save;
    char buf[4 * LOG_MAX_LEN];
    va_list args;
    size_t n;

    errno_save = errno;
    len = 0;                /* length of output buffer */
    size = 4 * LOG_MAX_LEN; /* size of output buffer */

    uint64 ulNow = CURRENT_MS();
    va_start(args, szArgs);
    len += snprintf(buf+len, size-len, "%ld %s:%d] ", ulNow, szFile, iLine);
    len += GORM_VscnPrintf(buf+len, size-len, szArgs, args);
    va_end(args);

    buf[len++] = '\n';
    buf[len] = '\0';

    GORM_Write(STDERR_FILENO, buf, len);
#endif
    return;
}


