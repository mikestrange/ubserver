//
//  keeper.h
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef keeper_h
#define keeper_h

#include <stdio.h>
#include "runtime.h"
#include "thread.h"
#include "time_util.h"

#include "KeepManager.h"

class Keeper;
class KeepManager;

class ITimeoutHandler
{
public:
    virtual void OnTimeProcess(Keeper* timer)=0;
};

class Keeper
{
private:
    friend class KeepManager;
    int timeid;
private:
    TIME_T delay;
    int currentCount;
    int repeatCount;
    int tag;
    ITimeoutHandler* delegate;
public:
    Keeper();
    
    Keeper(TIME_T delay, int repeatCount = 0);
    
    virtual ~Keeper();
    
    void restart(TIME_T value = 0);
    
    void start();
    
    void stop();
    
    bool isRunning()const;
    
    void reset(TIME_T delay, int repeatCount = 0);
    
    void setTag(int tag);
    
    int getTag();
    
    void setEventDelegate(ITimeoutHandler* target);
    
private:
    friend class KeepManager;
    void _OnTimeoutHandler();
};


#endif /* keeper_h */
