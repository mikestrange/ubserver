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

//事务处理器
class IEventHandler
{
public:
    virtual void OnEvent(EventBase* event)=0;
};

//事务处理
class EventBase : public RunTask
{
private:
    int m_type;
    IEventHandler* m_target;
    
public:
    EventBase(int type, IEventHandler* target);
    
    virtual ~EventBase(){};
    
    void OnTaskHandler()override;
public:
    int getType()const;
    IEventHandler* getTarget()const;
};


#endif /* EventBase_h */
