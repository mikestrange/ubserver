//
//  ConnectEvent.c
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "SocketEvent.h"

SocketEvent::SocketEvent(int type, IEventHandler* target, NetNode* node, MsgHandler* message)
:EventBase(type, target)
,m_node(node)
,m_packet(message)
{
    
}

SocketEvent::~SocketEvent()
{
    SAFE_DELETE(m_packet);
}

NetNode* SocketEvent::getNode()const
{
    return m_node;
}

MsgHandler* SocketEvent::getMessage()const
{
    return m_packet;
}