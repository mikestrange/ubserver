
//
//  keeper.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "ticker.h"


Ticker::Ticker()
:timeid(0)
,delay(0)
,currentCount(0)
,repeatCount(0)
,delegate(NULL)
{
    
}

Ticker::~Ticker()
{
    stop();
}

void Ticker::start(TIME_T value, int count, int type)
{
    delay = value;
    repeatCount = count;
    m_type = type;
    currentCount = 0;
    stop();
    timeid = KeepManager::getInstance()->CreateTimer(this, delay);
}

void Ticker::stop()
{
    if(isRunning())
    {
        KeepManager::getInstance()->StopTimer(timeid);
        timeid = 0;
    }
}

bool Ticker::isRunning()const
{
    return timeid > 0;
}

void Ticker::OnTimeoutHandler()
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

void Ticker::setEventDelegate(ITimeoutHandler* target)
{
    delegate = target;
}