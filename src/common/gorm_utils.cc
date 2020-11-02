#include "gorm_utils.h"


using namespace gorm;

#ifndef _WIN32
# define GORM_HAVE_BACKTRACE 1
#endif

#ifdef GORM_HAVE_BACKTRACE
# include <execinfo.h>
#endif

int
_vscnprintf(char *buf, size_t size, const char *fmt, va_list args)
{
    int n;

    if (size > 1024)
    {
        size = 1024;
    }
    n = vsnprintf(buf, size, fmt, args);

    /*
     * The return value is the number of characters which would be written
     * into buf not including the trailing '\0'. If size is == 0 the
     * function returns 0.
     *
     * On error, the function also returns 0. This is to allow idiom such
     * as len += _vscnprintf(...)
     *
     * See: http://lwn.net/Articles/69419/
     */
    if (n <= 0) {
        return 0;
    }

    if (n < (int) size) {
        return n;
    }

    return (int)(size - 1);
}


void
GORM_Stacktrace(int skip_count)
{
#ifdef GORM_HAVE_BACKTRACE
    void *stack[64];
    char **symbols;
    int size, i, j;

    size = backtrace(stack, 64);
    symbols = backtrace_symbols(stack, size);
    if (symbols == NULL) {
        return;
    }

    skip_count++; /* skip the current frame also */

    for (i = skip_count, j = 0; i < size; i++, j++) {
        cout <<"["<< j <<"]" <<  symbols[i] << endl;
    }

    free(symbols);
#endif
}


void GORM_Assert(const char *cond, const char *file, int line, int panic)
{
    return;
    if (panic) {
        GORM_Stacktrace(1);
        abort();
    }
    return;
}

#ifdef WIN32
int gettimeofday(struct timeval* tp, void* tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
#endif

uint64  GORM_GetNowMS()
{
    timeval tv;

    gettimeofday(&tv, NULL); // linux系统实现是从共享内存中获取时间，不涉及到系统调用，速度满足要求
    return tv.tv_sec * 1000 + tv.tv_usec/1000 + 28800000; // +28800000 取东8区时间
}

void ThreadSleepSeconds(int iSeconds)
{
    this_thread::sleep_for(chrono::seconds(iSeconds));
}



void ThreadSleepMilliSeconds(long lMSeconds)
{
    this_thread::sleep_for(chrono::milliseconds(lMSeconds));
}

vector<string> split(const string& str, const string& delim)
{
	vector<string> res;
	if("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型
	int destLen = str.length() + 1;
	char * strs = new char[destLen] ; //不要忘了
	GORM_StrNCpy(strs, destLen, str.c_str(), str.length());

    destLen = delim.length() + 1;
	char * d = new char[destLen];
	GORM_StrNCpy(d, destLen, delim.c_str(), delim.length());
 
#ifdef _WIN32
        char *pTmp;
        char* p = strtok_s(strs, d, &pTmp);
        while(p) {
            string s = p; //分割得到的字符串转换为string类型
            res.push_back(s); //存入结果数组
            p = strtok_s(NULL, d, &pTmp);
        }
#else
        char* p = strtok(strs, d);
        while(p) {
            string s = p; //分割得到的字符串转换为string类型
            res.push_back(s); //存入结果数组
            p = strtok(NULL, d);
        }
 #endif

 
	return res;
}

vector<string> split(char *szSrc, int iSrcLen, char *szDelim, int iDelimLen)
{
    vector<string> res;
	if(iSrcLen==0) return res;

	//先将要切割的字符串从string类型转换为char*类型
	int destLen = iSrcLen + 1;
	char * strs = new char[destLen] ; //不要忘了
	strs[iSrcLen] = '\n';
	GORM_StrNCpy(strs, destLen, szSrc, iSrcLen);

    destLen = iDelimLen + 1;
	char * d = new char[destLen];
	d[iDelimLen] = '\n';
	GORM_StrNCpy(d, destLen, szDelim, iDelimLen);

#ifdef _WIN32
    char *pTmp;
    char* p = strtok_s(strs, d, &pTmp);
	while(p) {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok_s(NULL, d, &pTmp);
	}
#else
	char* p = strtok(strs, d);
	while(p) {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok(NULL, d);
	}
 #endif
	return res;
}

int is_hex_digit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

int hex_digit_to_int(char c) {
    switch(c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    default: return 0;
    }
}


vector<int> GORM_FieldsOpt::GetFields(const char *szFields, int iLen)
{
    if (iLen > 128)
        iLen = 128;
    vector<int> v;
    int iField = 0;
    char cField = 0;
    for (int i = 0; i < iLen; i++)
    {
        iField = (i<<3);
        cField = szFields[i];
        if ((cField & 0b1) > 0)
        {
            v.push_back(iField);
        }
        if ((cField & 0b10) > 0)
        {
            v.push_back(iField+1);
        }
        if ((cField & 0b100) > 0)
        {
            v.push_back(iField + 2);
        }
        if ((cField & 0b1000) > 0)
        {
            v.push_back(iField + 3);
        }
        if ((cField & 0b10000) > 0)
        {
            v.push_back(iField + 4);
        }
        if ((cField & 0b100000) > 0)
        {
            v.push_back(iField + 5);
        }
        if ((cField & 0b1000000) > 0)
        {
            v.push_back(iField + 6);
        }
        if ((cField & 0b10000000) > 0)
        {
            v.push_back(iField + 7);
        }
    }

    return std::move(v);
}


