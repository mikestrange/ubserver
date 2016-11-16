//
//  FdState.c
//  ubserver
//
//  Created by MikeRiy on 16/11/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "FdState.h"


FdState::FdState(SOCKET_T fd)
:sock_fd(fd)
,isconnect(true)
{
    
}

FdState::~FdState()
{
    
}

void FdState::DisConnect()
{
    AUTO_LOCK(this);
    isconnect = false;
}

SOCKET_T FdState::getSocketID()const
{
    return sock_fd;
};

bool FdState::isClosed()const
{
    return isconnect == false;
}

bool FdState::isConnect()const
{
    return isconnect;
}


int FdState::SendPacket(const void* bytes, size_t size)
{
    AUTO_LOCK(this);
    if(isConnect())
    {
        return NET_SEND(sock_fd, bytes, size);
    }
    return -1;
}