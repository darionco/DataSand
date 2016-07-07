//
//  GSGThreadLock.h
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#ifndef __GSGNetConsole__GSGThreadLock__
#define __GSGNetConsole__GSGThreadLock__

#include <iostream>

#ifdef __MINGW32__
    #include <windows.h>
    typedef struct _RTL_CRITICAL_SECTION GSGMutex_t;
#else
    #include <pthread.h>
    typedef pthread_mutex_t GSGMutex_t;
#endif

class GSGThreadLock
{
    GSGMutex_t m_mutex;
    
public:
    GSGThreadLock();
    ~GSGThreadLock();
    
    void lock();
    void unlock();
    bool trylock();
    
    GSGMutex_t* mutex();
};

#endif /* defined(__GSGNetConsole__GSGThreadLock__) */
