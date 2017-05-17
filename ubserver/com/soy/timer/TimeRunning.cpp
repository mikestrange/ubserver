//
//  TimeRunning.c
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "TimeRunning.h"

STATIC_CLASS_INIT(TimeRunning);

TimeRunning::TimeRunning()
:currentTimeid(0)
{
    start();
}

int TimeRunning::CreateTimer(TimePush* target, TIME_T delay, int type)
{
    AUTO_LOCK(this);
    while(m_table.has(++currentTimeid))
    {
        if(currentTimeid == MAX_INT32) currentTimeid = 0;
    };
    LOG_DEBUG("ADD TIME ID = %d", currentTimeid);
    m_table.put(currentTimeid, new TimeEvent(type, this, target, currentTimeid, delay));
    target->timeid = currentTimeid;
    return currentTimeid;
}

//主线程获取，不用上锁
void TimeRunning::_StopTime(int tid)
{
    AUTO_LOCK(this);
    TimeEvent* node = m_table.getValue(tid);
    if(node) node->stop();
    LOG_INFO("STOP TIME id=%d", tid);
}

void TimeRunning::_DelTime(int tid)
{
    AUTO_LOCK(this);
    m_table.remove(tid);
    LOG_INFO("DEL TIME id=%d", tid);
}

//返回最近的一个时间(不删除)
TIME_T TimeRunning::GetCompleteTimers(std::vector<TimeEvent*>& timers)
{
    HashMap<int, TimeEvent*>::Iterator iter;
    TIME_T next_time = 0;
    TIME_T current_time = TimeUtil::GetTimer();
    AUTO_LOCK(this);
    for(iter = m_table.begin(); iter!=m_table.end(); ++iter)
    {
        TimeEvent* node = iter->second;
        if(node->isRunning())
        {
            TIME_T runtime = node->getRuntime();
            if(current_time >= runtime)
            {
                //timers.push_back(node);
                RUN_MAIN(node);
            }else{
                if(next_time == 0){
                    next_time = runtime;
                }else{
                    if(next_time > runtime)
                    {
                        next_time = runtime;
                    }
                }
            }
        }else{
            RUN_MAIN(node);
            //timers.push_back(node);
        }
    }
    return next_time;
}

void TimeRunning::run()
{
    while(isRunning())
    {
        std::vector<TimeEvent*> timers;
        TIME_T wait_time = GetCompleteTimers(timers);
        //通知
//        std::vector<TimeEvent*>::iterator iter;
//        for(iter=timers.begin(); iter!=timers.end(); ++iter)
//        {
//            RUN_MAIN((TimeEvent*)*iter);
//        }
        //等待下一个唤醒时间
        wait_next(wait_time);
    }
}

//public
int TimeRunning::AddTimer(TimePush* target, TIME_T delay, int type)
{
    int time_id = CreateTimer(target, delay, type);
    resume();
    return time_id;
}

void TimeRunning::StopTimer(int timeid)
{
    if(timeid == 0) return;
    _StopTime(timeid);
    //重新刷新
    resume();
}

//主线程执行
void TimeRunning::OnEvent(EventBase *event)
{
    TimeEvent* time_event = (TimeEvent*)event;
    //移除(主线程移除)
    _DelTime(time_event->getTimerID());
    //调度时间任务
    time_event->OnTimeAttemper();
}
