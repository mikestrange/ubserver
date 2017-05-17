//
//  ThreadPool.h
//  test
//  线程池
//  Created by MikeRiy on 17/3/7.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef ThreadPool_h
#define ThreadPool_h

#include <stdio.h>
#include <vector>

#include "TaskThread.h"

class ThreadPool : private TaskList, private CondLocked
{
private:
    int threadsNum_;
private:
    std::vector<TaskThread*> threads_;
public:
    ThreadPool(int threadNum)
    {
        threadsNum_ = threadNum;
    }
    
    bool start()
    {
        if(threads_.empty())
        {
            create_threads();
            return true;
        }
        return false;
    }
    
    virtual ~ThreadPool()
    {
        stopAll();
    }
    
    void push(TaskBase* task)
    {
        AUTO_LOCK(this);
        AddTask(task);
        broadcast();//惊群
    }
    
    void stopAll()
    {
        if(threads_.empty()) return;
        for(std::vector<TaskThread*>::iterator it = threads_.begin(); it != threads_.end(); ++it)
        {
            TaskThread* thread = *it;
            thread->stop();
            delete thread;
        }
        threads_.clear();
    }
    
private:
    int create_threads()
    {
        int totals = 0;
        for (int i = 0; i < threadsNum_; i++)
        {
            TaskThread* thread = new TaskThread(this, this);
            if(thread->start())
            {
                threads_.push_back(thread);
            }else{
                thread->stop();
                delete thread;
            }
        }
        return totals;
    }
};

#endif /* ThreadPool_h */
