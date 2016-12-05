//
//  TimeObserver.c
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "TimeObserver.h"


TimeObserver::TimeObserver(int tid, Ticker* value,TIME_T t2)
:timeid(tid)
,runtime(0)
,delay(t2)
,target(value)
,isrunning(true)
{
    reset(TimeUtil::GetTimer());
}

TimeObserver::~TimeObserver()
{
    
}

void TimeObserver::reset(TIME_T current)
{
    runtime = delay + current;
}

void TimeObserver::stop()
{
    isrunning = false;
}

bool TimeObserver::isRunning()
{
    return isrunning;
}

void TimeObserver::OnTimeoutHandler()
{
    if(isRunning())
    {
        target->OnTimeoutHandler();
    }
}

TIME_T TimeObserver::getRuntime()const
{
    return runtime;
}

int TimeObserver::getTimerID()const
{
    return timeid;
}