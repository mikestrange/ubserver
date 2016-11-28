//
//  FdState.c
//  ubserver
//
//  Created by MikeRiy on 16/11/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "netlink.h"


NetLink::NetLink(SOCKET_T fd, bool value)
:sock_fd(fd)
,isconnect(value)
{
    
}

NetLink::~NetLink()
{
    
}

void NetLink::DisConnect()
{
    AUTO_LOCK(this);
    isconnect = false;
}

SOCKET_T NetLink::getSocketID()const
{
    return sock_fd;
};

bool NetLink::isClosed()const
{
    return isconnect == false;
}

bool NetLink::isConnect()const
{
    return isconnect;
}

int NetLink::SendPacket(const void* bytes, size_t size)
{
    AUTO_LOCK(this);
    if(isConnect())
    {
        return NET_SEND(sock_fd, bytes, size);
    }
    return -1;
}

int NetLink::OnRead(char *bytes, size_t size)
{
    return NET_RECV(sock_fd, bytes, size);
}


void NetLink::OnConnect()
{
    isconnect = true;
}