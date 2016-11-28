//
//  TimeObserver.c
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "TimeObserver.h"


TimeObserver::TimeObserver(int tid, Clock* t1, TIME_T t2)
:timeid(tid)
,target(t1)
,runtime(0)
,delay(t2)
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
    target = NULL;
}

bool TimeObserver::isRunning()
{
    return target != NULL;
}

Clock* TimeObserver::getClock()const
{
    return target;
}

TIME_T TimeObserver::getRuntime()const
{
    return runtime;
}

int TimeObserver::getTimerID()const
{
    return timeid;
}