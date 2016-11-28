//
//  SockEvent.h
//  ubserver
//
//  Created by MikeRiy on 16/11/17.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef SockEvent_h
#define SockEvent_h

#include <stdio.h>
#include "runtime.h"
#include "netsock.h"
#include "memorys.h"
#include "network.h"

class NetSocket;

class SocketEvent : public RunTask
{
private:
    int m_type;
    NetSocket* m_client;
    char* m_bytes;
    size_t m_size;
public:
    SocketEvent(int type, NetSocket* client);
    SocketEvent(int type, NetSocket* client, char* bytes, size_t size);
    
    ~SocketEvent();
    
    void OnTaskHandler()override;
};

#endif /* SockEvent_h */
