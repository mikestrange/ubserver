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

class FdState : private Locked
{
private:
    SOCKET_T sock_fd;
    bool isconnect;
    
public:
    FdState(SOCKET_T fd);
    
    virtual ~FdState();
    
    SOCKET_T getSocketID()const;
    
    bool isClosed()const;
    
    bool isConnect()const;
    
    void DisConnect();
    
    int SendPacket(const void* bytes, size_t size);
};

#endif /* FdState_h */
