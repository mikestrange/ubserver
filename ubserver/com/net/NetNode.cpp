//
//  NetNode.c
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "NetNode.h"

NetNode::NetNode()
:sock_fd(0)
,isconnect(false)
,begin_time(0)
{
    begin_time = TimeUtil::GetTimer();
}

NetNode::~NetNode()
{
    
}

NetNode* NetNode::OnConnect(SOCKET_T fd)
{
    sock_fd = fd;
    isconnect = true;
    return this;
}

SOCKET_T NetNode::DisConnect()
{
    isconnect = false;
    return sock_fd;
}

SOCKET_T NetNode::getSockID()const
{
    return sock_fd;
};

bool NetNode::isClosed()const
{
    return isconnect == false;
}

bool NetNode::isConnect()const
{
    return isconnect;
}

void NetNode::SendPacket(const void* bytes, size_t size)
{
    if(isConnect())
    {
        NET_SEND(sock_fd, bytes, size);
    }
}

bool NetNode::HeartBeat(TIME_T value, TIME_T outtime)
{
    if(value - begin_time >= outtime)
    {
        begin_time = value;
        return true;
    }
    return false;
}
