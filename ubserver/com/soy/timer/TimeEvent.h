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
    int m_retcount;
    bool m_isrunning;
    TimePush* m_target;
private:
    TIME_T m_runtime;
public:
    TimeEvent(int type, IEventHandler* mlisten, TimePush* target, int timeid, TIME_T delay);
    
    virtual ~TimeEvent(){};
    
public:
    void stop();
    
    bool isRunning();
    
    TIME_T getRuntime()const;
    
    int getTimerID()const;
    
    void OnTimeAttemper();
};

#endif /* TimeEvent_h */
