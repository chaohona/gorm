#ifndef _GORM_LOG_H__
#define _GORM_LOG_H__
#include "gorm_singleton.h"
#include "gorm_sys_inc.h"
#include "gorm_define.h"

#define LOG_MAX_LEN 1024 /* max length of log message */


class GORM_DefaultLog;


#define GORM_LOG_INIT(PATH, NAME)\
GORM_DefaultLog::Instance()->Init(PATH, NAME)

#define GORM_LOGE(...)\
if (GORM_DefaultLog::Instance()->m_iLogLevel>=gorm::GORM_LOG_LEVEL_ERROR)\
GORM_DefaultLog::Instance()->Error(__FILE__, __LINE__, __VA_ARGS__)

#define GORM_LOGI(...)\
if (GORM_DefaultLog::Instance()->m_iLogLevel>=gorm::GORM_LOG_LEVEL_INFO)\
GORM_DefaultLog::Instance()->Info(__FILE__, __LINE__, __VA_ARGS__)

#define GORM_LOGD(...)\
if (GORM_DefaultLog::Instance()->m_iLogLevel>=gorm::GORM_LOG_LEVEL_DEBUG)\
GORM_DefaultLog::Instance()->Debug(__FILE__, __LINE__, __VA_ARGS__)

#define GORM_LOGW(...)\
if (GORM_DefaultLog::Instance()->m_iLogLevel>=gorm::GORM_LOG_LEVEL_WARNING)\
GORM_DefaultLog::Instance()->Error(__FILE__, __LINE__, __VA_ARGS__)

#define GORM_STDERR(...)\
GORM_DefaultLog::Instance()->StdErr(__FILE__, __LINE__, __VA_ARGS__)

#define GORM_CUSTOM_LOGE(pLogger, ...)                                               \
if (pLogger != nullptr && pLogger->m_iLogLevel>=gorm::GORM_LOG_LEVEL_ERROR)                 \
pLogger->Error(__FILE__, __LINE__,__VA_ARGS__);

#define GORM_CUSTOM_LOGI(pLogger, ...)                                               \
if (pLogger != nullptr && pLogger->m_iLogLevel>=gorm::GORM_LOG_LEVEL_INFO)                  \
pLogger->Info(__FILE__, __LINE__,__VA_ARGS__);

#define GORM_CUSTOM_LOGD(pLogger, ...)                                               \
if (pLogger != nullptr && pLogger->m_iLogLevel>=gorm::GORM_LOG_LEVEL_DEBUG)                 \
pLogger->Debug(__FILE__, __LINE__,__VA_ARGS__);

#define GORM_CUSTOM_LOGW(pLogger, ...)                                               \
if (pLogger != nullptr && pLogger->m_iLogLevel>=gorm::GORM_LOG_LEVEL_WARNING)               \
pLogger->Error(__FILE__, __LINE__,__VA_ARGS__);

#define GORM_CUSTOM_STDERR(pLogger, ...)     \
if (pLogger != nullptr)                      \
pLogger->StdErr(__FILE__, __LINE__,__VA_ARGS__);


class GORM_Log
{
public:
    virtual ~GORM_Log();

    virtual bool Init() = 0;

    virtual void Debug(const char *szFile, int iLine, const char *szArgs, ...) = 0;
    virtual void Info(const char *szFile, int iLine, const char *szArgs, ...) = 0;
    virtual void Error(const char *szFile, int iLine, const char *szArgs, ...) = 0;
    virtual void StdErr(const char *szFile, int iLine, const char *szArgs, ...) = 0;
    
    virtual void SetLogLevel(gorm::GORM_LOG_LEVEL logLevel);

public:
    gorm::GORM_LOG_LEVEL m_iLogLevel;
};

class GORM_DefaultLog: public GORM_Log
{
public:
    virtual ~GORM_DefaultLog();
    virtual bool Init();

    virtual void Debug(const char *szFile, int iLine, const char *szArgs, ...);
    virtual void Info(const char *szFile, int iLine, const char *szArgs, ...);
    virtual void Error(const char *szFile, int iLine, const char *szArgs, ...);
    virtual void StdErr(const char *szFile, int iLine, const char *szArgs, ...);

    static GORM_DefaultLog* Instance();
private:
    static GORM_DefaultLog *pInstance;
    mutex m_Mutex;
};


#endif

