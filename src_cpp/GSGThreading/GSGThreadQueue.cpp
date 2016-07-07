//
//  GSGThreadQueue.cpp
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#include "GSGThreadQueue.h"
#include "GSGThread.h"
#include "GSGThreadCondition.h"
#include "GSGThreadQueueNode.h"

GSGThreadQueueNode *GSGThreadQueue::k_GSGThreadQueueNodeExit = new GSGThreadQueueNode();

GSGThreadDeclaration GSGThreadQueueEntryPoint(void *args);

GSGThreadQueue::GSGThreadQueue()
{
    m_head = NULL;
    m_tail = NULL;
    m_reusable = NULL;
    
    m_condition = new GSGThreadCondition();
    m_queueLock = new GSGThreadLock();
    m_reusableNodesLock = new GSGThreadLock();
    
    for (int i = 0; i < 3; ++i)
    {
        GSGThreadQueueNode *newNode = new GSGThreadQueueNode();
        this->registerReusableNode(newNode);
    }
    
    m_thread = new GSGThread(GSGThreadQueueEntryPoint);
    m_thread->start(this);
}

GSGThreadQueue::~GSGThreadQueue()
{
    delete m_condition;
    delete m_queueLock;
    delete m_reusableNodesLock;
    
    while (m_head)
    {
        GSGThreadQueueNode *node = m_head;
        m_head = node->next();
        delete node;
    }
    
    while (m_reusable)
    {
        GSGThreadQueueNode *node = m_reusable;
        m_reusable = node->next();
        delete node;
    }
    
    delete m_thread;
}

GSGThreadCondition* GSGThreadQueue::condition()
{
    return m_condition;
}

GSGThreadQueueNode* GSGThreadQueue::first()
{
    return m_head;
}

GSGThreadQueueNode* GSGThreadQueue::dequeueNode()
{
    GSGThreadQueueNode *ret = NULL;
    m_queueLock->lock();
    {
        if (m_head)
        {
            ret = m_head;
            m_head = ret->next();
            ret->setNext(NULL);
        }
    }
    m_queueLock->unlock();
    return ret;
}

GSGThreadQueueNode* GSGThreadQueue::getUsableNode()
{
    GSGThreadQueueNode *ret = NULL;
    
    m_reusableNodesLock->lock();
    {
        if (!m_reusable)
        {
            ret = new GSGThreadQueueNode();
        }
        else
        {
            ret = m_reusable;
            m_reusable = ret->next();
            ret->setNext(NULL);
        }
    }
    m_reusableNodesLock->unlock();
    
    return ret;
}

void GSGThreadQueue::registerReusableNode(GSGThreadQueueNode* node)
{
    m_reusableNodesLock->lock();
    {
        node->setNext(m_reusable);
        m_reusable = node;
    }
    m_reusableNodesLock->unlock();
}


GSGThreadDeclaration GSGThreadQueueEntryPoint(void *args)
{
    GSGThreadQueue *queue = (GSGThreadQueue*)args;
    
    while (1)
    {
        queue->condition()->lock();
        while (!queue->first())
        {
            queue->condition()->wait();
        }
        queue->condition()->unlock();
        
        // printing //
        GSGThreadQueueNode *node = queue->dequeueNode();
        
        if (!node) continue;
        if (node == GSGThreadQueue::k_GSGThreadQueueNodeExit) break;
        
        node->run();
        
        queue->registerReusableNode(node);
    }
    queue->condition()->unlock();
    return 0;
}

