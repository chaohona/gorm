/**
 * \file
 * \version  $Id: zType.h 68 2013-06-19 08:05:28Z chengxie $
 * \author  Songsiliang,songsiliang@netease.com
 * \date 2004年12月15日 19时16分10秒 CST
 * \brief 定义基本类型
 *
 * 
 */

#ifndef _zType_h_
#define _zType_h_

#include <stdint.h>
#include <time.h>

#ifdef _WIN32
#include <string.h>
#else
#include <strings.h>
#endif
#include <string>
#include <stdlib.h>

#include "my_inttypes.h"

/*
typedef unsigned char   uchar;
typedef char            int8;
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef short           int16;
typedef unsigned int        uint32;
typedef int         int32;
typedef unsigned long long int        uint64;
typedef long long int         int64; 
*/


typedef int GORM_FD;

#endif

