#include "runtime.h"


STATIC_CLASS_INIT(RunTime);


RunTime::RunTime()
{
    
}

RunTime::~RunTime()
{
    list.eachValues([](RunTask* v)
    {
        SAFE_DELETE(v);
    });
}

void RunTime::launch()
{
    LOG_DEBUG("[Runtime is Launch]");
    start();
}

void RunTime::AddTask(RunTask* v)
{
    if(push(v)) resume();
}

void RunTime::run()
{
    while(isRunning())
    {
        if(!call()) wait_next();
    }
}

bool RunTime::call()
{
    auto v = next();
    if(v)
    {
        v->OnTaskHandler();
        SAFE_DELETE(v);
        return true;
    }
    return false;
}

bool RunTime::push(RunTask* v)
{
    AUTO_LOCK(this);
    list.add(v);
    return true;
}

RunTask* RunTime::next()
{
    AUTO_LOCK(this);
    return list.shift();
}