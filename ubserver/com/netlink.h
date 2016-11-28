//
//  FdState.h
//  ubserver
//
//  Created by MikeRiy on 16/11/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef FdState_h
#define FdState_h

#include <stdio.h>
#include "global.h"
#include "network.h"
#include "lock.h"

class NetLink : private Locked
{
private:
    SOCKET_T sock_fd;
    bool isconnect;
    
public:
    NetLink(SOCKET_T fd, bool value = false);
    
    virtual ~NetLink();
    
    SOCKET_T getSocketID()const;
    
    bool isClosed()const;
    
    bool isConnect()const;
    
    void DisConnect();
    
    void OnConnect();
    
    int SendPacket(const void* bytes, size_t size);
    
    int OnRead(char* bytes, size_t size);
    
public:
    static NetLink* create(SOCKET_T fd, bool value = false)
    {
        return new NetLink(fd, value);
    }
};

#endif /* FdState_h */
