#include "time_util.h"

static TimeVal runtime;

namespace TimeUtil
{
    void GetTimer(TimeVal& tv)
    {
        gettimeofday(&tv, NULL);
    }
    
    TIME_T GetTimer()
    {
        TimeVal tv;
        TimeUtil::GetTimer(tv);
        return ConverMSec(tv);
    }
    
    //秒
    TIME_T ConverSec(TimeVal& tv)
    {
        return tv.tv_sec;
    }
    
    //毫秒
    TIME_T ConverMSec(TimeVal& tv)
    {
        return tv.tv_sec*1000 + tv.tv_usec/1000;
    }
    
    //微秒
    TIME_T ConverUSec(TimeVal& tv)
    {
        return tv.tv_sec*1000000 + tv.tv_usec;
    }
    
    void ConverSpec(TIME_T v, struct timespec& t)
    {
        t.tv_sec = v/MVAL_TIME;
        t.tv_nsec = (v - t.tv_sec*MVAL_TIME)*UVAL_TIME;
    }
    
    void begin()
    {
        gettimeofday(&runtime, NULL);
    }
    
    void end()
    {
        TimeVal value;
        gettimeofday(&value, NULL);
        auto usec = value.tv_usec - runtime.tv_usec;
        LOG_DEBUG<<"[消耗 秒 = "<<value.tv_sec - runtime.tv_sec<<", 微秒 = "<<usec<<", pic = "<<1000000/usec<<"]"<<LOG_END;
    }
}