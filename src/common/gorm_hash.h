#ifndef _GORM_HASH_H__
#define _GORM_HASH_H__
#include "gorm_inc.h"

class GORM_Hash;

#define HASH_INSTANCE()\
GORM_Hash::m_pInstance;

class GORM_Hash
{
public:
    static GORM_Hash* Instance();
    ~GORM_Hash();

    static uint32 Md5(const char *szKey, size_t iKeyLen);
    static uint32 Crc16(const char *szKey, size_t iKeyLen);
    static uint32 Crc32(const char *szKey, size_t iKeyLen);
    static uint32 Crc32_1(const char *szKey, size_t iKeyLen);
    static uint32 Crc32_2(const char *szKey, size_t iKeyLen, const char *szKey1, size_t iKeyLen1);
    static uint32 Crc32_3(const char *szKey, size_t iKeyLen, const char *szKey1, size_t iKeyLen1, const char *szKey2, size_t iKeyLen2);
    static uint32 Crc32_4(const char *szKey, size_t iKeyLen, const char *szKey1, size_t iKeyLen1, const char *szKey2, size_t iKeyLen2, const char *szKey3, size_t iKeyLen3);
    static uint32 Crc32a(const char *szKey, size_t iKeyLen);
    static uint32 Fnv164(const char *szKey, size_t iKeyLen);
    static uint32 Fnv1a64(const char *szKey, size_t iKeyLen);
    static uint32 Fnv132(const char *szKey, size_t iKeyLen);
    static uint32 Fnv1a32(const char *szKey, size_t iKeyLen);
    static uint32 Hsieh(const char *szKey, size_t iKeyLen);
    static uint32 Jenkins(const char *szKey, size_t iKeyLen);
    static uint32 Murmur(const char *szKey, size_t iKeyLen);
public:
    static void Md5Signature(unsigned char *key, unsigned long length, unsigned char *result);

public:
    GORM_Hash();
    static GORM_Hash* m_pInstance;
};

#endif

