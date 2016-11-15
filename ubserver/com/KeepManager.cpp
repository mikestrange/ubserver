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

void KeepManager::AddTimer(Keeper* timer, TIME_T delay)
{
    //AUTO_LOCK(this);
    while(hash.has(++currentTimeid))
    {
        if(currentTimeid == MAX_INT32) currentTimeid = 0;
    };
    int time_id = currentTimeid;
    timer->timeid = time_id;
    hash.put(time_id, new TimeObserver(time_id, timer, delay));
    LOG_DEBUG<<"START TIME : id = "<<timer->timeid<<LOG_END;
    resume();
}


void KeepManager::DelTimer(Keeper* timer)
{
    int timeid = timer->timeid;
    if(timeid == 0) return;
    //AUTO_LOCK(this);
    TimeObserver* obser = hash.getValue(timeid);
    timer->timeid = 0;
    if(obser)
    {
        obser->stop();
    }
    LOG_DEBUG<<"STOP TIME : id = "<<timeid<<LOG_END;
    resume();
}

//主线处理
void KeepManager::MainHandlerTimer(int timeid)
{
    TimeObserver* obser = hash.remove(timeid);
    //如果obser为null,证明程序泄漏
    if(obser->isLive())
    {
        obser->target->_OnTimeoutHandler();
    }
    SAFE_DELETE(obser);
}


void KeepManager::run()
{
    while(isRunning())
    {
        std::vector<uint32> timers;
        TIME_T wait_time = CompleteTimer(timers);
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
TIME_T KeepManager::CompleteTimer(std::vector<uint32>& timers)
{
    //AUTO_LOCK(this);
    HashMap<int, TimeObserver*>::Iterator iter;
    TIME_T next_time = 0;
    TIME_T current_time = TimeUtil::GetTimer();
    for(iter = hash.begin(); iter!=hash.end(); iter++)
    {
        auto obser = iter->second;
        if(obser->isLive())
        {
            if(current_time >= obser->runtime)
            {
                obser->reset(current_time);
                timers.push_back(obser->timeid);
            }else{
                if(next_time == 0){
                    next_time = obser->runtime;
                }else{
                    if(next_time > obser->runtime)
                    {
                        next_time = obser->runtime;
                    }
                }
            }
        }else{
            timers.push_back(obser->timeid);
        }
    }
    return next_time;
}