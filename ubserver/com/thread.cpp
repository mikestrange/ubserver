#include "thread.h"


Thread::Thread()
:pid_t(0)
,is_awake(true)
,is_change(false)
,is_run(true)
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
    if(pid_t > 0){
        perror("please cancel first");
        return false;
    }
    int code = pthread_create(&pid_t, 0, &Thread::ThreadHandler, this);
    if(code != 0)
    {
        perror("run thread error");
    }
    //create thread
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

void Thread::wait(TIME_T runtime)
{
    if(runtime > 0){
        struct timespec delay;
        TimeUtil::ConverSpec(runtime, delay);
        wait(&delay);
    }else{
        wait();
    }
}

//延迟多少毫秒
void Thread::wait_delay(TIME_T runtime)
{
    wait(TimeUtil::GetTimer() + runtime);
}


void Thread::kill()
{
    if(pid_t > 0){
        pthread_cancel(pid_t);
    }
}

void* Thread::ThreadHandler(void *target)
{
    Thread *thread = (Thread*)target;
    thread->run();
    return 0;
}
    