//
//  ThreadBase.h
//  test
//
//  Created by MikeRiy on 17/3/7.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef ThreadBase_h
#define ThreadBase_h

#include <stdio.h>
#include <pthread.h>
#include <signal.h>

class ThreadBase
{
protected:
    bool m_isover;
    bool m_isrunning;
    pthread_t m_pid;
public:
    ThreadBase()
    :m_isover(true)
    ,m_isrunning(false)
    ,m_pid()
    {}
    
    virtual ~ThreadBase()
    {
        stop();
    }
    
    bool start()
    {
        if(isRunning()) return false;
        m_isrunning = true;
        int code = pthread_create(&m_pid, 0, thread_handler, this);
        if(code != 0)
        {
            m_isrunning = false;
            perror("run thread error");
        }
        return isRunning();
    }
    
    bool isRunning()
    {
        return m_isrunning;
    }
    
    void stop()
    {
        if(!isRunning()) return;
        m_isrunning = false;
        resume();
        join();
        printf("#thread over\n");
    }
    
protected:
    virtual void join()
    {
        //阻塞，直到线程结束
        pthread_join(m_pid, 0);
    }
    
    virtual void resume()
    {
        //perror("no sign is can vil");
    }
    
    virtual void run()
    {
        
    }
    
private:
    static void* thread_handler(void* args)
    {
        ThreadBase* target = (ThreadBase*)args;
        target->run();
        return 0;
    }
};

#endif /* ThreadBase_h */
