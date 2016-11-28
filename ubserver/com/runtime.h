//
//  runtime.h
//  ubserver
//
//  Created by MikeRiy on 16/11/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef runtime_h
#define runtime_h

#include <stdio.h>

#include "global.h"
#include "lock.h"
#include "command.h"
#include "thread.h"
#include "hashlist.h"
#include "log.h"

//类处理任务
class RunTask
{
public:
    RunTask(){};
    
    virtual ~RunTask(){};
    //任务自己处理
    virtual void OnTaskHandler()=0;
};

//全局函数处理任务
template <class V>
class BlockTask : public RunTask
{
private:
    typedef void(*Method)(V);
    V value;
    Method func;
public:
    BlockTask(V v, Method f)
    :value(v),func(f){}
    
    void OnTaskHandler()override
    {
        func(value);
    };
};


//全局构造
template <class T, class F>
BlockTask<T>* NewBlock(T v, F f)
{
    return new BlockTask<T>(v, f);
}


//添加主线程任务
#define RUN_MAIN(task)  RunTime::getInstance()->AddTask(task)

//启动主线
class RunTime : private Locked , Thread
{
    STATIC_CLASS(RunTime);
private:
    HashList<RunTask*> list;
public:
    RunTime();
    virtual ~RunTime();
    
    void launch();
    
    void AddTask(RunTask* v);
   
protected:
    void run()override;
    
private:
    bool call();
    
    bool push(RunTask* v);
    
    RunTask* next();
};

#endif /* runtime_h */
