//
//  GSGThreadCondition.cpp
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#include "GSGThreadCondition.h"

#ifdef __MINGW32__

#else

#endif

GSGThreadCondition::GSGThreadCondition()
{
#ifdef __MINGW32__
    InitializeConditionVariable(&m_condition);
#else
    pthread_cond_init(&m_condition, NULL);
#endif
    
    m_lock = new GSGThreadLock();
}

GSGThreadCondition::~GSGThreadCondition()
{
#if !defined(__MINGW32__)
    pthread_cond_destroy(&m_condition);
#endif
    delete m_lock;
}

void GSGThreadCondition::lock()
{
    m_lock->lock();
}

void GSGThreadCondition::unlock()
{
    m_lock->unlock();
}

void GSGThreadCondition::wait()
{
#ifdef __MINGW32__
    SleepConditionVariableCS(&m_condition, m_lock->mutex(), INFINITE);
#else
    pthread_cond_wait(&m_condition, m_lock->mutex());
#endif
}

void GSGThreadCondition::signal()
{
#ifdef __MINGW32__
    WakeConditionVariable(&m_condition);
#else
    pthread_cond_signal(&m_condition);
#endif
}

void GSGThreadCondition::broadcast()
{
#ifdef __MINGW32__
    WakeAllConditionVariable(&m_condition);
#else
    pthread_cond_broadcast(&m_condition);
#endif
}

bool GSGThreadCondition::timed_wait(long timeout)
{
#ifdef __MINGW32__
    struct __timeb64 tb;
	_ftime64(&tb);
    unsigned long long threadTime = tb.time * 1000 + tb.millitm;
    unsigned long long timeoutTime = (time(NULL) + timeout) * 1000;
    
    unsigned long long finalTimeout = (timeoutTime < threadTime) ? 1 : (timeoutTime - threadTime);
	
	if (!SleepConditionVariableCS(&m_condition, m_lock->mutex(), finalTimeout)) return false;
    
    _ftime64(&tb);
    threadTime = tb.time * 1000 + tb.millitm;
    finalTimeout = (timeoutTime < threadTime) ? 1 : (timeoutTime - threadTime);
	if (!finalTimeout) return false;
	
	return true;
#else
    struct timespec targetTime;
    targetTime.tv_sec = time(NULL) + timeout;
    targetTime.tv_nsec = 0;
    return (pthread_cond_timedwait(&m_condition, m_lock->mutex(), &targetTime) == 0);
#endif
}

