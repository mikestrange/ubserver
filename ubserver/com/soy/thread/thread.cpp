#include "thread.h"


Thread::Thread()
:pid_t(0)
,is_awake(true)
,is_change(false)
,is_run(false)
{
    pthread_cond_init(&cond_t, 0);
}

Thread::~Thread()
{
    pthread_cond_destroy(&cond_t);
    kill();
}

bool Thread::start()
{
    if(isRunning())
    {
        LOG_WARN("this thread is running %d", pid_t);
        return false;
    }
    is_run = true;
    int code = pthread_create(&pid_t, 0, &Thread::ThreadHandler, this);
    if(code != 0)
    {
        is_run = false;
        LOG_WARN("run thread error");
    }
    return code == 0;
}

void Thread::stop()
{
    is_run = false;
    resume();
}

void Thread::join()
{
    pthread_join(pid_t, 0);
}

void Thread::resume()
{
    AUTO_LOCK(&m_lock);
    is_change = true;
    if(is_awake == false)
    {
        is_awake = true;
        pthread_cond_signal(&cond_t);
    }
}

bool Thread::isRunning()const
{
    return is_run;
}

void Thread::wait(struct timespec* time)
{
    AUTO_LOCK(&m_lock);
    if(is_awake)
    {
        if(is_change)
        {
            is_change = false;
        }else{
            is_awake = false;
            if(time){
                pthread_cond_timedwait(&cond_t, m_lock.mutex(), time);
            }else{
                pthread_cond_wait(&cond_t, m_lock.mutex());
            }
            is_awake = true;
        }
    }
}

void Thread::wait_next(TIME_T runtime)
{
    if(runtime > 0){
        struct timespec delay;
        TimeUtil::ConverSpec(runtime, delay);
        wait(&delay);
    }else{
        wait();
    }
}

void Thread::wait_delay(TIME_T runtime)
{
    wait_next(TimeUtil::GetTimer() + runtime);
}

void Thread::kill()
{
    if(isRunning())
    {
        is_run = false;
        pthread_cancel(pid_t);
        pid_t = 0;
    }
}

void* Thread::ThreadHandler(void *target)
{
    Thread *thread = (Thread*)target;
    thread->run();
    return 0;
}
    