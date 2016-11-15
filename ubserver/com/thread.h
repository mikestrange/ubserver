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

#include "lock.h"
#include "time_util.h"

class Thread
{
private:
    pthread_t pid_t;
    bool is_awake;
    bool is_change;
    bool is_run;
private:
    pthread_cond_t cond_t;
    Locked m_lock;
public:
    Thread();
    
    virtual ~Thread();
    
    bool start();
    
    void stop();
    
    void join();
    
    void resume();
    
    bool isRunning()const;
    
    void wait(struct timespec* time = NULL);
    
    void wait(TIME_T runtime);
    
    void kill();
    
protected:
    virtual void run()=0;
    
private:
    static void* ThreadHandler(void *target);
    
public:
    template <class T>
    static pthread_t create(T fun, void* args = NULL)
    {
        pthread_t pid_t;
        pthread_create(&pid_t, 0, fun, args);
        return pid_t;
    }
};
#endif /* thread_h */
