//
//  GSGThread.h
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#ifndef __GSGNetConsole__GSGThread__
#define __GSGNetConsole__GSGThread__

#include <iostream>

#ifdef __MINGW32__
    #include <windows.h>
    #include <process.h>
    #define GSGThreadDeclaration unsigned __stdcall
    typedef uintptr_t GSGThreadHandle;
#else
    #include <pthread.h>
    #define GSGThreadDeclaration void*
    typedef pthread_t GSGThreadHandle;
#endif

typedef GSGThreadDeclaration(*GSGThreadEntryPoint)(void*);

class GSGThread
{
    GSGThreadHandle m_threadHandle;
    GSGThreadEntryPoint m_entryPoint;
    
public:
    GSGThread(GSGThreadEntryPoint entryPoint);
    ~GSGThread();
    
    void start();
    void start(void *data);
    void stop(); // WARNING: Callinf stop will result in 
    void join();
};

#endif /* defined(__GSGNetConsole__GSGThread__) */
