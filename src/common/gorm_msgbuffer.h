#ifndef _GORM_MSG_BUFFER_H__
#define _GORM_MSG_BUFFER_H__
#include "gorm_define.h"
#include "gorm_mempool.h"
#include "gorm_log.h"

#define MSGBUFFER_RESET(msg_buffer, inpData, bRelaseData)\
if (msg_buffer->m_szMsgEnd > msg_buffer->m_szMsgStart)                                                  \
{                                                                                                       \
    memcpy(inpData->m_uszData, msg_buffer->m_szMsgStart, msg_buffer->m_szMsgEnd-msg_buffer->m_szMsgStart);\
}                                                                                                       \
msg_buffer->m_szMsgEnd = inpData->m_uszData + (msg_buffer->m_szMsgEnd-msg_buffer->m_szMsgStart);          \
msg_buffer->m_szMsgStart = inpData->m_uszData;                                                            \
if (bRelaseData) msg_buffer->m_pData->Release();                                           \
msg_buffer->m_pData = inpData;

#define MSGBUFFER_READ(msgBuffer, inReadLen)\
msgBuffer.m_szMsgStart += inReadLen

#define MSGBUFFER_WRITE(msgBuffer, inReadLen)\
msgBuffer.m_szMsgEnd += inReadLen



// 二进制数据管理类
// 单向内存池(end比start大)
class GORM_MsgBufferMgr
{
public:
    GORM_MsgBufferMgr();
    ~GORM_MsgBufferMgr();

    void Init(GORM_MemPoolData *pData);
    int Init(int iSize);
    // 准备重用数据
    int ReInit();
    // 将数据拷贝进pData中(只能扩容不能缩容)
    void ResetMemPool(GORM_MemPoolData *pData, bool bRelaseData = true);
    // 重新申请大小为iSize长度的内存块
    int ResetMemPool(int iSize, bool bRelaseData = true);
    // 将缓存的数据扩大2倍或者iAtLeast的最大者
    int Expand(int iAtLeast=0);
    // 将数据拷贝到起始地址
    void ResetBuffer();
    // 缓存数据增加
    int Write(int iLen);
    // 从缓存中读取iLen数据
    int Read(int iLen);
    // 剩余可用空间
    int LeftCapcity();
    int LeftCapcityToEnd();
public:
    GORM_MemPoolData  *m_pData = nullptr;       // data数据
    char            *m_szMsgStart = nullptr;  // 当前数据的开始地址
    char            *m_szMsgEnd = nullptr;    // 当前数据的结束地址
};

// 二进制数据管理类
// 环形内存池
class GORM_RingMsgBufferMgr
{
public:
    GORM_RingMsgBufferMgr();
    ~GORM_RingMsgBufferMgr();

    void Init(GORM_MemPoolData *pData);
    int Init(int iSize);
    // 将数据拷贝进pData中(只能扩容不能缩容)
    void ResetMemPool(GORM_MemPoolData *pData);
    // 将缓存的数据扩大一倍
    int Expand(int iLen);
    // 从缓存中读取iLen数据
    int Read(int iLen);
    // 将szSrc的数据拷贝进环形内存池
    int Write(const char *szSrc, int iLen);
    int Write(GORM_MemPoolData *pData);
    // 池子是否空了
    bool Empty();
    // 池子中总可用空间
    int LeftCapcity();
    // 池子中到末尾总可用空间
    int LeftCapcityToEnd();
    // 到缓存的结尾以使用的消息的长度
    int MsgLenToEnd(bool &bHasRing);

    int Reuse();
private:
    void ResetIdx();

public:
    GORM_MemPoolData  *m_pData = nullptr;       // data数据
    char            *m_szMsgStart = nullptr;  // 当前数据的开始地址
    char            *m_szMsgEnd = nullptr;    // 当前数据的结束地址
    int             m_iLeft = 0;        // 剩余可用空间  end到buffer尾的数据
    uint64          m_ulStartIdx = 0;
    uint64          m_ulEndIdx = 0;
    uint64          m_ulTmp;
};

#endif

