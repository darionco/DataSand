//
//  GSGThreadQueueNode.cpp
//  GSGNetConsole
//
//  Created by dario on 2/20/2014.
//  Copyright (c) 2014 Get Set Games Inc. All rights reserved.
//

#include "GSGThreadQueueNode.h"

GSGThreadQueueNode::GSGThreadQueueNode()
{
    m_next = NULL;
    m_delegate = new GSGQueueNodeDelegate();
}

GSGThreadQueueNode::~GSGThreadQueueNode()
{
    delete m_delegate;
}

GSGThreadQueueNode* GSGThreadQueueNode::next()
{
    return m_next;
}

void GSGThreadQueueNode::setNext(GSGThreadQueueNode* next)
{
    m_next = next;
}

void GSGThreadQueueNode::run()
{
    (*m_delegate)();
}

