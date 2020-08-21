#ifndef _GORM_SOCKET_H__
#define _GORM_SOCKET_H__
#include "gorm_noncopyable.h"
#include "gorm_sys_inc.h"

#include <errno.h>

#include <cstdlib>

#include <sys/types.h>
#include <string.h>

#include <fcntl.h>

#include <assert.h>
#include <iostream>
#include <queue>

#include <string>

#ifdef _WIN32
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#else
#include <unistd.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <sys/socket.h>
#include <zlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#endif

#include "gorm_type.h"

struct GORM_Address
{
public:
    std::string  strIP;
    uint16  uiPort;
};

// socket常见操作函数封装
class GORM_Socket: private GORM_Noncopyable
{
public:
    static int CreateAndListen(const char *szIp, uint16 usPort, int iBackLog=1024);

    static int SetBlocking(GORM_FD iFD);
    static int SetNonBlocking(GORM_FD iFD);
    static int SetReuseAddr(GORM_FD iFD);
    static int SetReuserPort(GORM_FD iFD);
    static int SetTcpNoDelay(GORM_FD iFD);
    static int SetLinger(GORM_FD iFD, int iTimeOut);
    static int SetTcpKeepAlive(GORM_FD iFD);
    static int SetSndBuff(GORM_FD iFD, int iSize);
    static int SetRevBuf(GORM_FD iFD, int iSize);
    static int SetSndTimeO(GORM_FD iFD, int iMS);
    static int SetRcvTimeO(GORM_FD iFD, int iMS);
    //SYN重传次数影响connect超时时间，当重传次数为6时，超时时间为1+2+4+8+16+32+64=127秒。
    static int SetSynCnt(GORM_FD iFD, int iCnt);
    // 判断连接是否处于连接状态
    static bool ConnectedCheck(GORM_FD iFD);
    static int GetSoError(GORM_FD iFD);
    static int GetSndBuff(GORM_FD iFD);
    static int GetRcvBuff(GORM_FD iFD);
    static int GetError(GORM_FD iFD);
    static char* GetPeerAddr(GORM_FD);

    static int ParseAddress(std::string &strAddr, GORM_Address &addr);
};


#endif
