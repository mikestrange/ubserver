//
//  lock.h
//  ubserver
//
//  Created by MikeRiy on 16/11/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef lock_h
#define lock_h

#include "global.h"
#include <pthread.h>

#define AUTO_LOCK(t)                    AutoLocked private__lock(t)

//锁
class Locked
{
protected:
    pthread_mutex_t m_lock;
    volatile bool is_locked;
public:
    Locked()
    :is_locked(false)
    ,m_lock()
    {
        pthread_mutex_init(&m_lock, NULL);
    }
    
    virtual ~Locked()
    {
        if(is_locked) unlock();
        pthread_mutex_destroy(&m_lock);
    }
    
    void lock()
    {
        pthread_mutex_lock(&m_lock);
        is_locked = true;
    }
    
    void unlock()
    {
        is_locked = false;
        pthread_mutex_unlock(&m_lock);
    }
    
    pthread_mutex_t* mutex()
    {
        return &m_lock;
    }
};

//自动线程锁
class AutoLocked
{
private:
    Locked* _mutex;
public:
    AutoLocked(Locked *mutex)
    :_mutex(mutex)
    {
        _mutex->lock();
    }
    
    AutoLocked(Locked &mutex)
    :_mutex(&mutex)
    {
        _mutex->lock();
    }
    
    virtual ~AutoLocked()
    {
        _mutex->unlock();
    }
};

//信号
class CondLocked : public Locked
{
protected:
    pthread_cond_t m_cond;
public:
    CondLocked()
    {
        pthread_cond_init(&m_cond, NULL);
    }
    
    virtual ~CondLocked()
    {
        pthread_cond_destroy(&m_cond);
    }
    
    int broadcast()
    {
        return pthread_cond_broadcast(&m_cond);
    }
    
    void signal()
    {
        pthread_cond_signal(&m_cond);
    }
    
    void wait(struct timespec * delay = NULL)
    {
        if(delay){
            pthread_cond_timedwait(&m_cond, mutex(), delay);
        }else{
            pthread_cond_wait(&m_cond, mutex());
        }
    }
};

#endif /* lock_h */
