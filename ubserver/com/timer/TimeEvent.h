//
//  TimeEvent.h
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef TimeEvent_h
#define TimeEvent_h

#include "EventBase.h"
#include "TimePush.h"

class TimePush;

class TimeEvent : public EventBase
{
private:
    int m_timeid;
    bool isrunning;
    TimePush* m_timer;
private:
    TIME_T runtime;
public:
    TimeEvent(int type, IEventHandler* target, TimePush* node, int timeid, TIME_T delay);
    
public:
    void stop();
    
    bool isRunning();
    
    TimePush* getTimer()const;
    
    TIME_T getRuntime()const;
    
    int getTimerID()const;
    
    void OnTimeAttemper();
};

#endif /* TimeEvent_h */
