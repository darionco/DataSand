//
//  GSGThreadLock.cpp
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#include "GSGThreadLock.h"

GSGThreadLock::GSGThreadLock()
{
#ifdef __MINGW32__
    InitializeCriticalSection(&m_mutex);
#else
    pthread_mutex_init(&m_mutex, NULL);
#endif
}

GSGThreadLock::~GSGThreadLock()
{
#ifdef __MINGW32__
    DeleteCriticalSection(&m_mutex);
#else
    pthread_mutex_destroy(&m_mutex);
#endif
}

void GSGThreadLock::lock()
{
#ifdef __MINGW32__
    EnterCriticalSection(&m_mutex);
#else
    pthread_mutex_lock(&m_mutex);
#endif
}

void GSGThreadLock::unlock()
{
#ifdef __MINGW32__
    LeaveCriticalSection(&m_mutex);
#else
    pthread_mutex_unlock(&m_mutex);
#endif
}

bool GSGThreadLock::trylock()
{
#ifdef __MINGW32__
    return TryEnterCriticalSection(&m_mutex) ? 0 : EBUSY;
#else
    return pthread_mutex_trylock(&m_mutex);
#endif
}

GSGMutex_t* GSGThreadLock::mutex()
{
    return &m_mutex;
}
