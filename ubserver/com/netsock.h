//
//  netsock.h
//  ubserver
//
//  Created by MikeRiy on 16/11/17.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef netsock_h
#define netsock_h

#include <stdio.h>
#include "thread.h"
#include "network.h"
#include "lock.h"

#include "packet_buffer.h"
#include "SockEvent.h"

class SocketEvent;

class NetSocket : private Thread , private Locked, public PacketBuffer
{
private:
    SOCKET_T sock_id;
    bool isconnect;
public:
    bool Connect(const char* host, int port);
    void SendPacket(PacketBuffer& packet);
    bool isConnect()const;
    void Close();
    SOCKET_T getSocketID()const;
public:
    virtual void OnClose();
    virtual void OnPacketHandler();
protected:
    void run()override;
};

#endif /* netsock_h */
