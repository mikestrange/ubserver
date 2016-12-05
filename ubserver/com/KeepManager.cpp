//
//  KeepManager.c
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "KeepManager.h"

STATIC_CLASS_INIT(KeepManager);

KeepManager::KeepManager()
:currentTimeid(0)
{
    start();
}

//a线程
int KeepManager::CreateTimer(Ticker* timer, TIME_T delay)
{
    int time_id = AddTime(timer, delay);
    resume();
    return time_id;
}

//a线程
void KeepManager::StopTimer(int timeid)
{
    if(timeid == 0) return;
    do{
        TimeObserver* obser = hash.getValue(timeid);
        if(obser)
        {
            obser->stop();
        }
        LOG_DEBUG<<"STOP TIME : id = "<<timeid<<LOG_END;
    }while(0);
    //--
    resume();
}

//a线程
void KeepManager::MainHandlerTimer(int timeid)
{
    TimeObserver* obser = RemoveTime(timeid);
    //如果obser为null,证明程序泄漏
    if(obser)
    {
        obser->OnTimeoutHandler();
    }
    SAFE_DELETE(obser);
}


void KeepManager::run()
{
    while(isRunning())
    {
        std::vector<uint32> timers;
        TIME_T wait_time = GetCompleteTimers(timers);
        //
        if(!timers.empty())
        {
            size_t length = timers.size();
            for(size_t i = 0; i < length; i++)
            {
                int tid = timers[i];
                RUN_MAIN(NewBlock(tid, block(int tid)
                {
                    KeepManager::getInstance()->MainHandlerTimer(tid);
                }));
            }
        }
        //等待
        wait(wait_time);
    }
}

//返回最近的一个时间
TIME_T KeepManager::GetCompleteTimers(std::vector<uint32>& timers)
{
    HashMap<int, TimeObserver*>::Iterator iter;
    TIME_T next_time = 0;
    TIME_T current_time = TimeUtil::GetTimer();
    AUTO_LOCK(this);
    for(iter = hash.begin(); iter!=hash.end(); iter++)
    {
        auto obser = iter->second;
        if(obser->isRunning())
        {
            TIME_T runtime = obser->getRuntime();
            if(current_time >= runtime)
            {
                obser->reset(current_time);
                timers.push_back(obser->getTimerID());
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
            timers.push_back(obser->getTimerID());
        }
    }
    return next_time;
}

int KeepManager::AddTime(Ticker* timer, TIME_T delay)
{
    AUTO_LOCK(this);
    while(hash.has(++currentTimeid))
    {
        if(currentTimeid == MAX_INT32) currentTimeid = 0;
    };
    hash.put(currentTimeid, new TimeObserver(currentTimeid, timer, delay));
    return currentTimeid;
}

TimeObserver* KeepManager::RemoveTime(int timeid)
{
    AUTO_LOCK(this);
    return hash.remove(timeid);
}