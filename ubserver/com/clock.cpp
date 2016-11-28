
//
//  keeper.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "clock.h"


Clock::Clock()
:timeid(0)
,delay(0)
,currentCount(0)
,repeatCount(0)
,delegate(NULL)
{
    
}

Clock::~Clock()
{
    stop();
}

void Clock::start(TIME_T value, int count, int type)
{
    delay = value;
    repeatCount = count;
    m_type = type;
    currentCount = 0;
    stop();
    timeid = KeepManager::getInstance()->CreateTimer(this, delay);
}

void Clock::stop()
{
    if(isRunning())
    {
        KeepManager::getInstance()->DelTimer(timeid);
        timeid = 0;
    }
}

bool Clock::isRunning()const
{
    return timeid > 0;
}

void Clock::_OnTimeoutHandler()
{
    if(repeatCount <= 0)
    {
         KeepManager::getInstance()->CreateTimer(this, delay);
    }else{
        if(++currentCount == repeatCount){
            stop();
        }else{
            KeepManager::getInstance()->CreateTimer(this, delay);
        }
    }
    //---
    if(delegate)
    {
        delegate->OnTimeProcess(m_type);
    }
}

void Clock::setEventDelegate(ITimeoutHandler* target)
{
    delegate = target;
}