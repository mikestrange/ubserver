//
//  TimeEvent.c
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "TimeEvent.h"

TimeEvent::TimeEvent(int type, IEventHandler* mlisten, TimePush* node, int timeid, TIME_T delay)
:EventBase(type, mlisten)
,m_timeid(timeid)
,m_isrunning(true)
,m_target(node)
{
    m_runtime = TimeUtil::GetTimer() + delay;
}

void TimeEvent::stop()
{
    m_isrunning = false;
}

bool TimeEvent::isRunning()
{
    return m_isrunning;
}

TIME_T TimeEvent::getRuntime()const
{
    return m_runtime;
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
        m_target->OnTimeoutHandler(getType());
    }
}