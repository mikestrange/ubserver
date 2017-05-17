//
//  TimePush.c
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "TimePush.h"

TimePush::TimePush()
:timeid(0)
,m_delay(0)
,currentCount(0)
,repeatCount(0)
,delegate(NULL)
{}

TimePush::~TimePush()
{
    stop();
}

void TimePush::start(TIME_T delay, int count, int type)
{
    m_delay = delay;
    repeatCount = count;
    currentCount = 0;
    stop();
    TimeRunning::getInstance()->AddTimer(this, delay, type);
}

void TimePush::stop()
{
    if(isRunning())
    {
        TimeRunning::getInstance()->StopTimer(timeid);
        timeid = 0;
    }
}

bool TimePush::isRunning()const
{
    return timeid > 0;
}

void TimePush::setEventDelegate(ITimeoutHandler* target)
{
    delegate = target;
}

void TimePush::OnTimeoutHandler(int type)
{
    if(repeatCount <= 0)
    {
        TimeRunning::getInstance()->AddTimer(this, m_delay, type);
    }else{
        if(++currentCount == repeatCount){
            stop();
        }else{
            TimeRunning::getInstance()->AddTimer(this, m_delay, type);
        }
    }
    //任务最终坐落
    if(delegate)
    {
        delegate->OnTimeProcess(type);
    }
}