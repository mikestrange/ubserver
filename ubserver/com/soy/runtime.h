//
//  runtime.h
//  ubserver
//
//  Created by MikeRiy on 16/11/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef runtime_h
#define runtime_h

#include "global.h"
#include "lock.h"
#include "thread.h"
#include "hashlist.h"
#include "log.h"

//类处理任务
class RunTask
{
private:
    int8 taskLv;
public:
    RunTask(int8 lv = 0):taskLv(lv){};
    //任务等级
    int8 getTaskLv()const{ return taskLv;};
    //未进入任务列表
    virtual void destroy(){};
    //析构
    virtual ~RunTask(){};
    //任务自己处理
    virtual void OnTaskHandler()=0;
};

//全局函数处理任务
template <class V>
class BlockTask : public RunTask
{
private:
    typedef void(*Method)(V, int);
private:
    Method func;
    V value;
    int type;
public:
    BlockTask(Method f, V v, int t)
    :func(f),value(v),type(t){}
    
    void OnTaskHandler()override
    {
        func(value, type);
    };
};

//全局构造
template <class F, class T>
BlockTask<T>* NewBlock(F f, T v, int t)
{
    return new BlockTask<T>(f, v, t);
}

//添加主线程任务
#define RUN_MAIN(task)                  RunTime::getInstance()->AddTask(task)
#define RUN_SMAIN(func, data, type)     RunTime::getInstance()->AddTask(func, data, type)

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
    
    template <class F, class T>
    void AddTask(F f, T v, int type = 0)
    {
        AddTask(NewBlock(f, v, type));
    }
   
protected:
    void run()override;
    
private:
    bool call();
    
    bool push(RunTask* v);
    
    RunTask* next();
};

#endif /* runtime_h */
