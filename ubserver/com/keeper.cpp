
//
//  keeper.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "keeper.h"


Keeper::Keeper()
:timeid(0)
,delay(0)
,currentCount(0)
,repeatCount(0)
,tag(0)
,delegate(NULL)
{
    
}

Keeper::Keeper(TIME_T delay, int repeatCount)
:Keeper()
{
    reset(delay, repeatCount);
}

Keeper::~Keeper()
{
    stop();
}

void Keeper::reset(TIME_T value, int count)
{
    delay = value;
    repeatCount = count;
    currentCount = 0;
    stop();
}

void Keeper::start()
{
    stop();
    if(currentCount > repeatCount)
    {
        LOG_WARN<<"this currentCount > repeatCount please reset()"<<LOG_END;
        return;
    }
    KeepManager::getInstance()->AddTimer(this, delay);
}

void Keeper::restart(TIME_T value)
{
    if(value > 0) delay = value;
    currentCount = 0;
    start();
}

void Keeper::stop()
{
    if(isRunning())
    {
        KeepManager::getInstance()->DelTimer(this);
    }
}

bool Keeper::isRunning()const
{
    return timeid > 0;
}

void Keeper::_OnTimeoutHandler()
{
    if(repeatCount <= 0){
        start();
    }else{
        if(++currentCount == repeatCount){
            stop();
        }else{
            start();
        }
    }
    //
    if(delegate)
    {
        delegate->OnTimeProcess(this);
    }
}

void Keeper::setTag(int tag)
{
    this->tag = tag;
}

int Keeper::getTag()
{
    return tag;
}

void Keeper::setEventDelegate(ITimeoutHandler* target)
{
    delegate = target;
}