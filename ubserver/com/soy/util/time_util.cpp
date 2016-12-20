#include "time_util.h"

static TimeVal runtime;

namespace TimeUtil
{
    void GetTimer(TimeVal& tv)
    {
        gettimeofday(&tv, NULL);
    }
    
    //毫秒
    TIME_T GetTimer()
    {
        TimeVal tv;
        TimeUtil::GetTimer(tv);
        return ConverMSec(tv);
    }
    
    //秒
    TIME_T GetSTimer()
    {
        TimeVal tv;
        return ConverSec(tv);
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
        LOG_DEBUG("[消耗 秒=%d 微妙=%d 单位=%d", value.tv_sec - runtime.tv_sec, (value.tv_usec - runtime.tv_usec), 1000000/(value.tv_usec - runtime.tv_usec));
    }
}