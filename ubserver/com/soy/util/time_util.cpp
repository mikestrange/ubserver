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
        return tv.tv_sec*MVAL_TIME + tv.tv_usec/MVAL_TIME;
    }
    
    //微秒
    TIME_T ConverUSec(TimeVal& tv)
    {
        return tv.tv_sec*UVAL_TIME + tv.tv_usec;
    }
    
    void ConverSpec(TIME_T v, struct timespec& t)
    {
        t.tv_sec = v/MVAL_TIME;
        t.tv_nsec = (v - t.tv_sec*MVAL_TIME)*UVAL_TIME;
    }
    
    void begin()
    {
        TimeUtil::GetTimer(runtime);
    }
    
    void end()
    {
        TimeVal value;
        TimeUtil::GetTimer(value);
        long sub_s = value.tv_sec - runtime.tv_sec;
        double sub_us = (double)(value.tv_usec - runtime.tv_usec)/UVAL_TIME;
        double sub_ss = sub_s + sub_us;     //经历多少秒
        long count = 1/sub_ss;              //1秒执行次数
        trace("[s=%d微妙 %ldmsg/s]", int(sub_us*UVAL_TIME), count);
    }
    
    void end(size_t size)
    {
        TimeVal value;
        TimeUtil::GetTimer(value);
        long sub_s = value.tv_sec - runtime.tv_sec;
        double sub_us = (double)(value.tv_usec - runtime.tv_usec)/UVAL_TIME;
        double sub_ss = sub_s + sub_us;
        long count = 1/sub_ss;
        trace("[s=%f %ldMib/s]", sub_ss, count*size/(1024*1024));
    }
}