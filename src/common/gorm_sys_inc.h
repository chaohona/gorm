#ifndef _GORM_SYS_INC_H__
#define _GORM_SYS_INC_H__


// 常规操作
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdarg.h>
#include <memory>

#include <sys/types.h>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#else
#include <sys/un.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#endif

// stl
#include <vector>
#include <list>
#include <unordered_map>
#include <vector>

// 多线程相关
#include <mutex>
#include <chrono>
#include <typeinfo>
#include <condition_variable>
#include <thread>
#include <atomic>


using namespace std;


#endif
