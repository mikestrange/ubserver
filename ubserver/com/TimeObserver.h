//
//  TimeObserver.h
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef TimeObserver_h
#define TimeObserver_h

#include <stdio.h>
#include "clock.h"
#include "time_util.h"
//#include "lock.h"

class Clock;

class TimeObserver
{
private:
    int timeid;
    Clock* target;
    TIME_T runtime;
    TIME_T delay;
public:
    TimeObserver(int tid, Clock* value, TIME_T delay);
    
    virtual ~TimeObserver();
    
    void stop();
    
    void reset(TIME_T current);
    
    Clock* getClock()const;
    
    TIME_T getRuntime()const;
    
    int getTimerID()const;
    
    bool isRunning();
};

#endif /* TimeObserver_h */
