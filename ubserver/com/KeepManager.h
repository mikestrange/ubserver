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
#include "keeper.h"
#include "hashmap.h"
#include "TimeObserver.h"
#include "thread.h"
#include "runtime.h"
#include "lock.h"
#include "log.h"
#include "time_util.h"

class TimeObserver;
class Keeper;

class KeepManager : private Thread, private Locked
{
private:
    int currentTimeid;
    HashMap<int, TimeObserver*> hash;
public:
    STATIC_CLASS(KeepManager);
    
    KeepManager();
    
    void AddTimer(Keeper* timer, TIME_T delay = 0);
    
    void DelTimer(Keeper* timer);
    
    void MainHandlerTimer(int timeid);
    
protected:
    void run()override;
    
private:
    TIME_T CompleteTimer(std::vector<uint32>& ticks);
};

#endif /* KeepManager_h */
