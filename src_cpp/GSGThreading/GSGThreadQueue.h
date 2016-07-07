//
//  GSGThreadQueue.h
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#ifndef __GSGNetConsole__GSGThreadQueue__
#define __GSGNetConsole__GSGThreadQueue__

#include <iostream>
#include "FastDelegate.h"
#include "GSGThreadLock.h"
#include "GSGThreadQueueNode.h"
#include "GSGThreadCondition.h"

class GSGThread;

class GSGThreadQueue
{
    GSGThread *m_thread;
    GSGThreadCondition *m_condition;
    GSGThreadQueueNode *m_head;
    GSGThreadQueueNode *m_tail;
    GSGThreadQueueNode *m_reusable;
    
    GSGThreadLock *m_queueLock;
    GSGThreadLock *m_reusableNodesLock;
    
public:
    static GSGThreadQueueNode *k_GSGThreadQueueNodeExit;
    
    GSGThreadQueue();
    ~GSGThreadQueue();
    
    GSGThreadCondition* condition();
    GSGThreadQueueNode* first();
    
    GSGThreadQueueNode* dequeueNode();
    template < class X, class Y >
	inline void enqueueNode(Y *pthis, fastdelegate::detail::DefaultVoidToVoid<fastdelegate::detail::DefaultVoid>::type (X::* function_to_bind)())
    {
        GSGThreadQueueNode *newNode = this->getUsableNode();
        newNode->setNext(NULL);
        newNode->setDelegateAndFunction(pthis, function_to_bind);
        
        m_queueLock->lock();
        {
            if (!m_head)
            {
                m_condition->lock();
                m_head = newNode;
                m_tail = newNode;
                m_condition->signal();
                m_condition->unlock();
            }
            else
            {
                m_tail->setNext(newNode);
                m_tail = newNode;
            }
        }
        m_queueLock->unlock();
    }
    
    GSGThreadQueueNode* getUsableNode();
    void registerReusableNode(GSGThreadQueueNode* node);
    
};

#endif /* defined(__GSGNetConsole__GSGThreadQueue__) */
