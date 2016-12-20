#include "lock.h"
#include <iostream>

Locked::Locked()
:is_locked(false)
{
    pthread_mutex_init(&m_lock, 0);
}

Locked::~Locked()
{
    while(is_locked);
    unlock();
    pthread_mutex_destroy(&m_lock);
}

void Locked::lock()
{
    pthread_mutex_lock(&m_lock);
    is_locked = true;
}

void Locked::unlock()
{
    is_locked = false;
    pthread_mutex_unlock(&m_lock);
}

pthread_mutex_t* Locked::mutex()
{
    return &m_lock;
}

//
AutoLocked::AutoLocked(Locked *mutex)
:_mutex(mutex)
{
    _mutex->lock();
}

AutoLocked::AutoLocked(Locked &mutex)
:AutoLocked(&mutex)
{}

AutoLocked::~AutoLocked()
{
    _mutex->unlock();
}