//
//  TimeRunning.h
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef TimeRunning_h
#define TimeRunning_h

#include "lock.h"
#include "array.h"
#include "hashmap.h"

#include "TimePush.h"
#include "TimeEvent.h"

class TimeEvent;
class TimePush;

class TimeRunning : private Locked, private Thread, public IEventHandler
{
    STATIC_CLASS(TimeRunning);
public:
    TimeRunning();
    
private:
    int currentTimeid;
    
    HashMap<int, TimeEvent*> m_table;
    
    int CreateTimer(TimePush* target, TIME_T delay = 0, int type = 0);
    
    void _StopTime(int tid);
    
    void _DelTime(int tid);
    
    TIME_T GetCompleteTimers(std::vector<TimeEvent*>& timers);
    
    friend class TimePush;
    int AddTimer(TimePush* target, TIME_T delay = 0, int type = 0);
    
    void StopTimer(int timeid);
    
public:
    void OnEvent(EventBase* event)override;
    
    void run()override;
};

#endif /* TimeRunning_h */
