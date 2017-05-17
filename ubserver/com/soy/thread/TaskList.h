//
//  TaskList.h
//  test
//
//  Created by MikeRiy on 17/3/7.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef TaskList_h
#define TaskList_h

#include <stdio.h>
#include <list>

//#define DELETE_TASK(val) do{ if(val){ delete val; val = NULL;} }while(0)

//任务失败
enum TASK_EVENT
{
    TASK_COMPLETE = 0,
    TASK_PUSHERROR = 1,
    TASK_RELEASE = 2
};

class TaskBase
{
private:
    int m_type;
public:
    TaskBase(int type = 0)
    :m_type(type)
    {}
    
    virtual ~TaskBase()
    {
        //printf("delete task\n");
    }
    
    int getType()const
    {
        return m_type;
    }
    
    //异步处理
    virtual void asyn_handler(int code)
    {
        printf("task code=%d type=%d\n", code, m_type);
    };
    
};

//任务队列
class TaskList
{
private:
    std::list<TaskBase*> task_list;
    
public:
    TaskList()
    {}
    
    virtual ~TaskList()
    {
        clean();
    }
    
    //释放所有任务
    void clean()
    {
        for(std::list<TaskBase*>::iterator it = task_list.begin(); it != task_list.end(); ++it)
        {
            TaskBase* task = *it;
            task->asyn_handler(TASK_RELEASE);
        }
        task_list.clear();
    }
    
    bool AddTask(TaskBase* task)
    {
        if(overflow())
        {
            task->asyn_handler(TASK_PUSHERROR);
            return false;
        }
        task_list.push_back(task);
        return true;
    }
    
    bool overflow()
    {
        return task_list.size() >= task_list.max_size();
    }
    
    bool empty()const
    {
        return task_list.empty();
    }
    
    TaskBase* next()
    {
        if(task_list.empty()) return NULL;
        TaskBase* task = task_list.front();
        task_list.pop_front();
        return task;
    }
};

#endif /* TaskList_h */
