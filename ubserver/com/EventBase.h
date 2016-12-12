//
//  EventBase.h
//  ubserver
//
//  Created by MikeRiy on 16/12/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef EventBase_h
#define EventBase_h

#include <stdio.h>

#include "runtime.h"

class EventBase;

class IEventHandler
{
public:
    virtual void OnEvent(EventBase* event)=0;
};

class EventBase : public RunTask
{
private:
    int m_type;
    IEventHandler* m_target;
    
public:
    EventBase(int type, IEventHandler* target);
    
    void OnTaskHandler()override;
public:
    int getType()const;
    IEventHandler* getTarget()const;
};


#endif /* EventBase_h */
