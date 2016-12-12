//
//  ConnectEvent.c
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "SocketEvent.h"

SocketEvent::SocketEvent(int type, IEventHandler* target, NetNode* node, char* bytes, size_t size)
:EventBase(type, target)
,m_node(node)
,m_bytes(bytes)
,m_size(size)
{
    if(bytes && size > 0)
    {
        m_bytes = MemoryPool::getInstance()->alloc_copy(bytes, m_size);
    }
}

SocketEvent::~SocketEvent()
{
    if(m_bytes)
    {
        if(!MemoryPool::getInstance()->share(m_bytes))
        {
            SAFE_DELETE(m_bytes);
        };
    }
}

char* SocketEvent::getBytes()const
{
    return m_bytes;
}

size_t SocketEvent::getSize()const
{
    return m_size;
}

NetNode* SocketEvent::getNode()const
{
    return m_node;
}