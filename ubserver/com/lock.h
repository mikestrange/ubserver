//
//  lock.h
//  ubserver
//
//  Created by MikeRiy on 16/11/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef lock_h
#define lock_h

#include <stdio.h>
#include <pthread.h>

#include "global.h"


#define AUTO_LOCK(t)                    AutoLocked __am(t)
//
#define OBJ_RETAIN(obj)                 do{ if(obj){ obj->retain(); } }while(0)
#define OBJ_RELEASE(obj)                do{ if(obj){ obj->release(); obj = NULL;} }while(0)

class Locked
{
public:
    Locked();
    
    virtual ~Locked();
    
    void lock();
    
    void unlock();
    
    pthread_mutex_t* mutex();
    //属性
protected:
    pthread_mutex_t m_lock;
    volatile bool is_locked;
};

//自动线程锁
class AutoLocked
{
private:
    Locked* _mutex;
public:
    AutoLocked(Locked *mutex);
    
    virtual ~AutoLocked();
};

class RefObject
{
private:
    unsigned int m_count;
public:
    RefObject()
    :m_count(1)
    {}
    
    virtual ~RefObject()
    {
        
    }
    
    bool release()
    {
        ERROR_ASSERT(m_count>0);
        --m_count;
        if(!m_count)
        {
            delete this;
            return true;
        }
        return false;
    }
    
    void retain()
    {
        ++m_count;
    }
};

#endif /* lock_h */
