//
//  GSGThreadCondition.h
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#ifndef __GSGNetConsole__GSGThreadCondition__
#define __GSGNetConsole__GSGThreadCondition__

#include <iostream>
#include "GSGThreadLock.h"

#ifdef __MINGW32__
    #include <windows.h>
    #include <sys/timeb.h>
    #include <time.h>
    typedef CONDITION_VARIABLE GSGCondition_t;
#else
    #include <pthread.h>
    typedef pthread_cond_t GSGCondition_t;
#endif

class GSGThreadCondition
{
    GSGCondition_t m_condition;
    
    GSGThreadLock *m_lock;
    
public:
    GSGThreadCondition();
    ~GSGThreadCondition();
    
    void lock();
    void unlock();
    void wait();
    void signal();
    void broadcast();
    bool timed_wait(long timeout);
};

#endif /* defined(__GSGNetConsole__GSGThreadCondition__) */
