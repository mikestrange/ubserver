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

int TimeRunning::_AddTime(TimePush* target, TIME_T delay, int type)
{
    AUTO_LOCK(this);
    while(tMap.has(++currentTimeid))
    {
        if(currentTimeid == MAX_INT32) currentTimeid = 0;
    };
    tMap.put(currentTimeid, new TimeEvent(type, this, target, currentTimeid, delay));
    return currentTimeid;
}

//主线程获取，不用上锁
void TimeRunning::_StopTime(int tid)
{
    AUTO_LOCK(this);
    TimeEvent* node = tMap.getValue(tid);
    if(node) node->stop();
    LOG_INFO("STOP TIME id=%d", tid);
}

void TimeRunning::_DelTime(int tid)
{
    AUTO_LOCK(this);
    tMap.remove(tid);
}

//返回最近的一个时间(不删除)
TIME_T TimeRunning::GetCompleteTimers(std::vector<TimeEvent*>& timers)
{
    HashMap<int, TimeEvent*>::Iterator iter;
    TIME_T next_time = 0;
    TIME_T current_time = TimeUtil::GetTimer();
    AUTO_LOCK(this);
    for(iter = tMap.begin(); iter!=tMap.end(); iter++)
    {
        TimeEvent* node = iter->second;
        if(node->isRunning())
        {
            TIME_T runtime = node->getRuntime();
            if(current_time >= runtime)
            {
                timers.push_back(node);
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
            timers.push_back(node);
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
        //
        if(!timers.empty())
        {
            size_t length = timers.size();
            for(size_t i = 0; i < length; i++)
            {
                RUN_MAIN((TimeEvent*)timers[i]);
            }
        }
        //等待下一个唤醒时间
        wait_next(wait_time);
    }
}

//public
int TimeRunning::AddTimer(TimePush* target, TIME_T delay, int type)
{
    int time_id = _AddTime(target, delay, type);
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

void TimeRunning::OnEvent(EventBase *event)
{
    TimeEvent* time_event = (TimeEvent*)event;
    //移除(主线程移除)
    _DelTime(time_event->getTimerID());
    //调度时间任务
    time_event->OnTimeAttemper();
}
