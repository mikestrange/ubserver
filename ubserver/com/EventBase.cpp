//
//  EventBase.c
//  ubserver
//
//  Created by MikeRiy on 16/12/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "EventBase.h"


EventBase::EventBase(int type, IEventHandler* target)
:m_type(type)
,m_target(target){
    
}

void EventBase::OnTaskHandler()
{
    m_target->OnEvent(this);
};

int EventBase::getType()const
{
    return m_type;
}

IEventHandler* EventBase::getTarget()const
{
    return m_target;
}