//
//  GSGThread.cpp
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#include "GSGThread.h"

GSGThread::GSGThread(GSGThreadEntryPoint entryPoint) : m_entryPoint(entryPoint) {}

GSGThread::~GSGThread()
{
    this->stop();
    m_entryPoint = NULL;
    m_threadHandle = 0;
}

void GSGThread::start()
{
    this->start(NULL);
}

void GSGThread::start(void *data)
{
#ifdef __MINGW32__
    m_threadHandle = _beginthreadex(NULL, 0, m_entryPoint, data, 0, NULL);
#else
    pthread_create(&m_threadHandle, NULL, m_entryPoint, data);
#endif
}

void GSGThread::stop()
{
#ifdef __MINGW32__
    TerminateThread((HANDLE)m_threadHandle, 0);
    CloseHandle((HANDLE)m_threadHandle);
#else
    // pthread_cancel(m_threadHandle);
#endif
}

void GSGThread::join()
{
#ifdef __MINGW32__
    WaitForSingleObject((HANDLE)m_threadHandle, INFINITE);
#else
    pthread_join(m_threadHandle, NULL);
#endif
}

