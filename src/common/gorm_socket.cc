#include "gorm_socket.h"
#include "gorm_log.h"
#include "gorm_inc.h"
#include "gorm_utils.h"
#include "gorm_sys_inc.h"


int GORM_Socket::CreateAndListen(const char *szIp, uint16 usPort, int iBackLog)
{
    int iFD = socket(AF_INET, SOCK_STREAM, 0);
    if (iFD <= 0)
    {
#ifndef _WIN32
        GORM_LOGE("create socket failed:%d, errmsg:%s", errno, strerror(errno));
#endif
		return iFD;
    }
    if (GORM_Socket::SetReuseAddr(iFD) != 0)
    {
#ifndef _WIN32
        GORM_LOGE("set resuse addr failed:%d,errmsg:%s", errno, strerror(errno));
#endif
		return GORM_ERROR;
    }
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
#ifdef _WIN32
	 inet_pton(AF_INET, szIp, (void*)&server_addr.sin_addr);
#else
	server_addr.sin_addr.s_addr = inet_addr(szIp);
#endif
    server_addr.sin_port = htons(usPort);

    int iRet = bind(iFD, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(iRet == -1) {
#ifndef _WIN32
        GORM_LOGE("bind failed:%d, errmsg:%s", errno, strerror(errno));
#endif
		return iRet;
    }
    if (iBackLog < 1)
    {
        iBackLog = 128;
    }
    iRet = listen(iFD, iBackLog);
    if(iRet == -1) {
#ifndef _WIN32
        GORM_LOGE("listen failed:%d, errmsg:%s", errno, strerror(errno));
#endif
		return iRet;
    }
    if (GORM_Socket::SetNonBlocking(iFD) != 0)
    {
#ifndef _WIN32
        GORM_LOGE("set socket nonblock failed:%d,errmsg:%s", errno, strerror(errno));
#endif
		return GORM_ERROR;
    }
    GORM_LOGD("create listen socket success, port:%d, fd:%d", usPort, iFD);
    return iFD;
}

int GORM_Socket::SetBlocking(GORM_FD iFD)
{
#ifdef _WIN32
	return 0;
#else
    int flags;

    flags = fcntl(iFD, F_GETFL, 0);
    if (flags < 0) {
        return flags;
    }

    return fcntl(iFD, F_SETFL, flags & ~O_NONBLOCK);
#endif
}

int GORM_Socket::SetNonBlocking(GORM_FD iFD)
{
#ifdef _WIN32
	unsigned long ul = 1;
	int ret;
	ret = ioctlsocket(iFD, FIONBIO, (unsigned long*)& ul);    //设置成非阻塞模式
	if (ret == SOCKET_ERROR)   //设置失败
	{
		return -1;
	}
	return 0;
#else
    int flags;

    flags = fcntl(iFD, F_GETFL, 0);
    if (flags < 0) {
        return flags;
    }

    return fcntl(iFD, F_SETFL, flags | O_NONBLOCK);
#endif
}

int GORM_Socket::SetReuseAddr(GORM_FD iFD)
{
#ifdef _WIN32
	return 0;
#else
    int reuse;
    socklen_t len;

    reuse = 1;
    len = sizeof(reuse);

    int iRet = 0;
    iRet = setsockopt(iFD, SOL_SOCKET, SO_REUSEADDR, &reuse, len);
    if (iRet < 0)
    {
        return iRet;
    }

    return 0;
#endif
}

int GORM_Socket::SetReuserPort(GORM_FD iFD)
{
#ifdef _WIN32
	return 0;
#else
    int reuse = 1;
    socklen_t len = sizeof(reuse);

    int iRet = setsockopt(iFD, SOL_SOCKET, SO_REUSEPORT, &reuse, len);
    if (iRet < 0)
    {
        return iRet;
    }
    return 0;
#endif
}

int GORM_Socket::SetTcpNoDelay(GORM_FD iFD)
{
    int nodelay;
    size_t len;

    nodelay = 1;
    len = sizeof(nodelay);

    return setsockopt(iFD, IPPROTO_TCP, TCP_NODELAY, (const char*)&nodelay, len);
}

int GORM_Socket::SetLinger(GORM_FD iFD, int iTimeOut)
{
    linger linger;
    size_t len;

    linger.l_onoff = 1;
    linger.l_linger = iTimeOut;

    len = sizeof(linger);

    return setsockopt(iFD, SOL_SOCKET, SO_LINGER, (const char*)&linger, len);
}

int GORM_Socket::SetTcpKeepAlive(GORM_FD iFD)
{
    int val = 1;
    return setsockopt(iFD, SOL_SOCKET, SO_KEEPALIVE, (const char*)&val, sizeof(val));
}

int GORM_Socket::SetSndBuff(GORM_FD iFD, int iSize)
{
    size_t len;

    len = sizeof(iSize);

    return setsockopt(iFD, SOL_SOCKET, SO_SNDBUF, (char*)&iSize, len);
}

int GORM_Socket::SetRevBuf(GORM_FD iFD, int iSize)
{
    size_t len;
    
    len = sizeof(iSize);

    return setsockopt(iFD, SOL_SOCKET, SO_RCVBUF, (char*)(&iSize), len);
}

int GORM_Socket::SetSndTimeO(GORM_FD iFD, int iMS)
{
    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = iMS * 1000;
    setsockopt(iFD, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof( timeval ) );

    return 0;
}

int GORM_Socket::SetRcvTimeO(GORM_FD iFD, int iMS)
{
    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = iMS * 1000;
    setsockopt(iFD, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof( timeval ) );

    return 0;
}

int GORM_Socket::SetSynCnt(GORM_FD iFD, int iCnt)
{
#ifdef _WIN32
	return 0;
#else
    setsockopt(iFD, IPPROTO_TCP, TCP_SYNCNT, &iCnt, sizeof(iCnt));
    return 0;
#endif
}

bool GORM_Socket::ConnectedCheck(GORM_FD iFD)
{
#ifdef _WIN32
	return true;
#else
    struct tcp_info info;
    int len = sizeof(info);
    getsockopt(iFD, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *) & len);
    if ((info.tcpi_state == TCP_ESTABLISHED)) {
        return true;
    }

    return false;
#endif
}

int GORM_Socket::GetSoError(GORM_FD iFD)
{
#ifdef _WIN32
	return 0;
#else
    int status, err;
    socklen_t len;

    err = 0;
    len = sizeof(err);

    status = getsockopt(iFD, SOL_SOCKET, SO_ERROR, &err, &len);
    if (status == 0) {
        errno = err;
    }

    return status;
#endif
}

int GORM_Socket::GetSndBuff(GORM_FD iFD)
{
#ifdef _WIN32
	return 0;
#else
    int status, size;
    socklen_t len;

    size = 0;
    len = sizeof(size);

    status = getsockopt(iFD, SOL_SOCKET, SO_SNDBUF, &size, &len);
    if (status < 0) {
        return status;
    }

    return size;
#endif
}

int GORM_Socket::GetRcvBuff(GORM_FD iFD)
{
#ifdef _WIN32
	return 0;
#else
    int status, size;
    socklen_t len;

    size = 0;
    len = sizeof(size);

    status = getsockopt(iFD, SOL_SOCKET, SO_RCVBUF, &size, &len);
    if (status < 0) {
        return status;
    }

    return size;
#endif
}

int GORM_Socket::GetError(GORM_FD iFD)
{
#ifdef _WIN32
	return 0;
#else
    int err = -1;
    socklen_t len = sizeof(int);
    if (getsockopt(iFD,  SOL_SOCKET, SO_ERROR ,&err, &len) < 0 )
    {
        return -1;
    }

    return err;
#endif
}

int GORM_Socket::ParseAddress(string &strAddr, GORM_Address &addr)
{
    auto results = split(strAddr, ":");
    if (results.size() != 2)
    {
        return GORM_ERROR;
    }
    addr.strIP = results[0];
    addr.uiPort = stoi(results[1], 0, 10);

    return GORM_OK;
}

