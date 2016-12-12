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
#include "global.h"

class KeepManager;

class ITimeoutHandler
{
public:
    virtual void OnTimeProcess(int type)=0;
};

class Ticker
{
private:
    int timeid;
private:
    TIME_T delay;
    int currentCount;
    int repeatCount;
    ITimeoutHandler* delegate;
    int m_type;
public:
    Ticker();
    
    virtual ~Ticker();
    
    void start(TIME_T value, int count = 1, int type = 0);
    
    void stop();
    
    bool isRunning()const;
    
    void setEventDelegate(ITimeoutHandler* target);
    
public:
    void OnTimeoutHandler();
};


#endif /* keeper_h */
