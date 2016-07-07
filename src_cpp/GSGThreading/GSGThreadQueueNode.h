//
//  GSGThreadQueueNode.h
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#ifndef __GSGNetConsole__GSGThreadQueueNode__
#define __GSGNetConsole__GSGThreadQueueNode__

#include <iostream>
#include "FastDelegate.h"

class GSGThreadQueueNode
{
    typedef fastdelegate::FastDelegate0<void> GSGQueueNodeDelegate;
    
    GSGThreadQueueNode *m_next;
    GSGQueueNodeDelegate *m_delegate;
    
public:
    GSGThreadQueueNode();
    ~GSGThreadQueueNode();
    
    GSGThreadQueueNode* next();
    void setNext(GSGThreadQueueNode* next);
    
    template < class X, class Y >
	inline void setDelegateAndFunction(Y *pthis, fastdelegate::detail::DefaultVoidToVoid<fastdelegate::detail::DefaultVoid>::type (X::* function_to_bind)())
    {
        m_delegate->bind(pthis, function_to_bind);
    }
    
    void run();
};

#endif /* defined(__GSGNetConsole__GSGThreadQueueNode__) */
