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
#include "ticker.h"
#include "time_util.h"
//#include "lock.h"

class Ticker;

class TimeObserver
{
private:
    int timeid;
    TIME_T runtime;
    TIME_T delay;
    Ticker* target;
    bool isrunning;
public:
    TimeObserver(int tid, Ticker* value, TIME_T delay);
    
    virtual ~TimeObserver();
    
    void stop();
    
    void reset(TIME_T current);
    
    //Ticker* getClock()const;
    void OnTimeoutHandler();
    
    TIME_T getRuntime()const;
    
    int getTimerID()const;
    
    bool isRunning();
};

#endif /* TimeObserver_h */
