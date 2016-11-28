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

class Clock;
class KeepManager;

class ITimeoutHandler
{
public:
    virtual void OnTimeProcess(int type)=0;
};

class Clock
{
private:
    friend class KeepManager;
    int timeid;
private:
    TIME_T delay;
    int currentCount;
    int repeatCount;
    ITimeoutHandler* delegate;
    int m_type;
public:
    Clock();
    
    virtual ~Clock();
    
    void start(TIME_T value, int count = 1, int type = 0);
    
    void stop();
    
    bool isRunning()const;
    
    void setEventDelegate(ITimeoutHandler* target);
    
private:
    friend class KeepManager;
    void _OnTimeoutHandler();
};


#endif /* keeper_h */
