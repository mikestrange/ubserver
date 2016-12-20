//
//  TimePush.h
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef TimePush_h
#define TimePush_h

#include <stdio.h>
#include "TimeEvent.h"
#include "TimeRunning.h"

class ITimeoutHandler
{
public:
    virtual void OnTimeProcess(int type)=0;
};

class TimePush
{
private:
    int timeid;
private:
    TIME_T m_delay;
    int currentCount;
    int repeatCount;
    ITimeoutHandler* delegate;
public:
    TimePush();
    
    virtual ~TimePush();
    
    void start(TIME_T delay, int count = 1, int type = 0);
    
    void stop();
    
    bool isRunning()const;
    
    void setEventDelegate(ITimeoutHandler* target);
    
private:
    friend class TimeEvent;
    void OnTimeoutHandler(int type);
};


#endif /* TimePush_h */
