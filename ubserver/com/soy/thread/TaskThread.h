//
//  TaskThread.h
//  test
//  单一任务
//  Created by MikeRiy on 17/3/7.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef TaskThread_h
#define TaskThread_h

#include <stdio.h>
#include <assert.h>

#include "ThreadBase.h"
#include "lock.h"
#include "TaskList.h"

class TaskThread : public ThreadBase
{
protected:
    CondLocked* m_locked;
    TaskList* m_list;
public:
    TaskThread(CondLocked* locked = NULL, TaskList* list = NULL)
    :ThreadBase()
    ,m_locked(locked)
    ,m_list(list)
    {
        if(!m_locked)
        {
            m_locked = new CondLocked();
        }
        if(!m_list)
        {
            m_list = new TaskList();
        }
    }
    
    void push(TaskBase* task)
    {
        AUTO_LOCK(m_locked);
        m_list->AddTask(task);
        resume();
    }
    
protected:
    void resume()override
    {
        m_locked->broadcast();
    }
    
    void run()override
    {
        while(isRunning())
        {
            TaskBase* task = popTask();
            if (task)
            {
                task->asyn_handler(TASK_COMPLETE);
            }else{
                printf("thread will exit!\n");
            }
        }
    }
    
    TaskBase* next()
    {
        return m_list->next();
    }
    
    bool empty()const
    {
        return m_list->empty();
    }
    
    TaskBase* popTask()
    {
        TaskBase* task = NULL;
        while(!task)
        {
            AUTO_LOCK(m_locked);
            while (empty() && isRunning())
            {
                m_locked->wait();
            }
            if(!isRunning())
            {
                break;
            }
            //assert(!empty());
            task = next();
        }
        return task;
    }
};

#endif /* TaskThread_h */
