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
#include "keeper.h"
#include "time_util.h"

class Keeper;

class TimeObserver
{
public:
    int timeid;
    Keeper* target;
    TIME_T runtime;
private:
    TIME_T delay;
public:
    TimeObserver(int tid, Keeper* value, TIME_T delay);
    
    virtual ~TimeObserver();
    
    void stop();
    
    void reset(TIME_T current);
    
    bool isLive();
};

#endif /* TimeObserver_h */
