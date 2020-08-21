#ifndef _GORM_LISTEN_EVENT_H__
#define _GORM_LISTEN_EVENT_H__

#include "gorm_singleton.h"
#include "gorm_event.h"

class GORM_ListenEvent : public GORM_Event
{
public:
};

class GORM_ListenMgr : public GORM_Singleton<GORM_ListenMgr>
{
public:
    
};

#endif
