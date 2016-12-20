//
//  TimeEvent.c
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "TimeEvent.h"

TimeEvent::TimeEvent(int type, IEventHandler* target, TimePush* node, int timeid, TIME_T delay)
:EventBase(type, target)
,m_timeid(timeid)
,isrunning(true)
,m_timer(node)
{
    runtime = TimeUtil::GetTimer() + delay;
}

TimePush* TimeEvent::getTimer()const
{
    return m_timer;
}

void TimeEvent::stop()
{
    isrunning = false;
}

bool TimeEvent::isRunning()
{
    return isrunning;
}

TIME_T TimeEvent::getRuntime()const
{
    return runtime;
}


int TimeEvent::getTimerID()const
{
    return m_timeid;
}

//主线程任务
void TimeEvent::OnTimeAttemper()
{
    if(isRunning())
    {
        m_timer->OnTimeoutHandler(getType());
    }
}