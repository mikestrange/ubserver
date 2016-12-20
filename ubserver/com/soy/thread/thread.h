//
//  thread.h
//  ubserver
//
//  Created by MikeRiy on 16/11/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef thread_h
#define thread_h

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>

#include "log.h"
#include "lock.h"
#include "time_util.h"

typedef pthread_t THREAD_T;
typedef pthread_cond_t THREAD_COND_T;

class Thread
{
private:
    THREAD_T pid_t;
    bool is_awake;
    bool is_change;
    bool is_run;
private:
    THREAD_COND_T cond_t;
    Locked m_lock;
public:
    Thread();
    virtual ~Thread();
    //开启线程
    bool start();
    //停止，唤醒程序，isrun=false
    void stop();
    //加入到进程，形成堵塞
    void join();
    //唤醒
    void resume();
    //是否运行
    bool isRunning()const;
    //等待下一个时间点
    void wait_next(TIME_T runtime = 0);
    //延迟多少毫秒执行
    void wait_delay(TIME_T runtime);
    //强制删除，可能会存在内存泄漏
    void kill();
private:
    //等待
    void wait(struct timespec* time = NULL);
protected:
    virtual void run()=0;
    
private:
    static void* ThreadHandler(void *target);
    
public:
    template <class T>
    static THREAD_T create(T fun, void* args = NULL)
    {
        THREAD_T pid_t;
        if(pthread_create(&pid_t, 0, fun, args) != 0)
        {
            return 0;
        };
        return pid_t;
    }
};
#endif /* thread_h */
