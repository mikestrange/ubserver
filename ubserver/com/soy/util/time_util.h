//
//  time_util.h
//  ubserver
//
//  Created by MikeRiy on 16/11/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef time_util_h
#define time_util_h

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "log.h"

typedef struct timeval TimeVal;
typedef long TIME_T;

//毫秒
#define MVAL_TIME 1000
//微妙
#define UVAL_TIME 1000000
//纳秒
#define NVAL_TIME 1000000000

namespace TimeUtil
{
    void GetTimer(TimeVal& tv);
    //获取毫秒
    TIME_T GetTimer();
    //获取秒
    TIME_T GetSTimer();
    //转化秒
    TIME_T ConverSec(TimeVal& tv);
    //转化毫秒
    TIME_T ConverMSec(TimeVal& tv);
    //转化微秒
    TIME_T ConverUSec(TimeVal& tv);
    //转化纳秒
    void ConverSpec(TIME_T v, struct timespec& t);
    //消耗打印
    void begin();
    void end();
    void end(size_t size);
}


#endif /* time_util_h */
