#ifndef _GORM_UTILS_H__
#define _GORM_UTILS_H__

#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "gorm_sys_inc.h"
#include "gorm_define.h"

#define USE_SETPROCTITLE
#define INIT_SETPROCTITLE_REPLACEMENT
void spt_init(int argc, char *argv[]);
void setproctitle(const char *fmt, ...);

int is_hex_digit(char c);
int hex_digit_to_int(char c);

//strncpy(d, szDelim, iDelimLen);
inline char* GORM_StrNCpy(char* dest, size_t destLen, const char* src, size_t n);
char* GORM_StrNCpy(char* dest, size_t destLen, const char* src, size_t n)
{
#ifdef _WIN32
	strncpy_s(dest, destLen, src, n);
	return dest;
#else
	return strncpy(dest, src, n);
#endif
}

inline char* GORM_strtok(char* str, const char* delim);
char* GORM_strtok(char* str, const char* delim)
{
#ifdef _WIN32
	char* pBuff;
	return strtok_s(str, delim, &pBuff);
#else
	return strtok(str, delim);
#endif
}

inline char* GORM_strerror(int errno);
char* GORM_strerror(int errno)
{
#ifdef _WIN32
	return (char*)"";
#else
	return strerror(errno);
#endif
}

vector<string> split(const string& str, const string& delim);
vector<string> split(char *szSrc, int iSrcLen, char *szDelim, int iDelimLen);

void ThreadSleepSeconds(int iSeconds);

void ThreadSleepMilliSeconds(long lMSeconds);
/*
 * Wrappers to read or write data to/from (multiple) buffers
 * to a file or socket descriptor.
 */
#define GORM_Read(_d, _b, _n)     \
    read(_d, _b, (size_t)(_n))

#define GORM_Readv(_d, _b, _n)    \
    readv(_d, _b, (int)(_n))

#define GORM_Write(_d, _b, _n)    \
    write(_d, _b, (size_t)(_n))

#define GORM_Writev(_d, _b, _n)   \
    writev(_d, _b, (int)(_n))

int
_vscnprintf(char *buf, size_t size, const char *fmt, va_list args);

#define GORM_VscnPrintf(_s, _n, _f, _a)   \
    _vscnprintf((char *)(_s), (size_t)(_n), _f, _a)

inline int GORM_SafeSnprintf(char *buf, size_t size, const char *fmt, ...);

int GORM_SafeSnprintf(char *buf, size_t size, const char *fmt, ...)
{
    if (size <=0 )
        return 0;

    va_list ap;
    va_start(ap, fmt);
    int iResult = vsnprintf(buf, size, fmt, ap);
    va_end(ap);

    if (iResult > size)
        iResult = size;

    return iResult;
}


void GORM_Stacktrace(int skip_count);
void GORM_Assert(const char *cond, const char *file, int line, int panic);

#define ASSERT(_x)\
do{\
    if (!(_x)){\
        GORM_Assert(#_x, __FILE__, __LINE__, 1);\
    }\
}while(0);

#define NOT_REACHED() ASSERT(0)

//

uint64  GORM_GetNowMS();

// 提高效率，不调用函数
#define CURRENT_MS()\
GORM_GetNowMS()

#define GORM_ADD_FIELD(opt, filed)\
int idx_____ = filed >> 3;                              \
opt->szFieldCollections[idx_____] |= 1<<(filed & 0x07); \
if (opt->iUsedIdx <= idx_____)                          \
    opt->iUsedIdx = idx_____+1;                         \

struct GORM_FieldsOpt
{
public:
    GORM_FieldsOpt(GORM_FieldsOpt &other);
    GORM_FieldsOpt(string &strFields);
    GORM_FieldsOpt();
    GORM_FieldsOpt& operator=(GORM_FieldsOpt &other);
    bool AddField(int iField);
    bool DelField(int iField);
    // 获取字符串所对应的fileds
    static vector<int> GetFields(const char *szFields, int iLen);
    static bool FieldInMode(const char *szFields, int iLen, int iField);
public:
    char szFieldCollections[128];    // 列的集合，最多支持64*8 = 1024个字段
    int  iUsedIdx;      // 使用了几个字符
};

#endif

