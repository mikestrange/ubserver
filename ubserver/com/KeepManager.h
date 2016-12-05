//
//  KeepManager.h
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef KeepManager_h
#define KeepManager_h

#include <stdio.h>
#include "hashmap.h"
#include "thread.h"
#include "runtime.h"
#include "lock.h"
#include "log.h"
#include "time_util.h"

#include "ticker.h"
#include "TimeObserver.h"

class Ticker;
class TimeObserver;

class KeepManager : private Thread, private Locked
{
private:
    int currentTimeid;
    HashMap<int, TimeObserver*> hash;
public:
    STATIC_CLASS(KeepManager);
    
    KeepManager();
    
    int CreateTimer(Ticker* timer, TIME_T delay = 0);
    
    void StopTimer(int timeid);
    
    void MainHandlerTimer(int timeid);
    
protected:
    void run()override;
    
private:
    TIME_T GetCompleteTimers(std::vector<uint32>& ticks);
    
    int AddTime(Ticker* timer, TIME_T delay);
    
    TimeObserver* RemoveTime(int timeid);
};

#endif /* KeepManager_h */
