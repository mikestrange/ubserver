//
//  client.h
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef client_h
#define client_h

#include <stdio.h>
#include "packet_buffer.h"
#include "network.h"
#include "lock.h"

class SocketHandler : public PacketBuffer, private Locked
{
public:
    SocketHandler();
    
    SocketHandler(SOCKET_T sockt_fd);
    
    virtual ~SocketHandler();
    
    SOCKET_T GetSocketFd();
    
    void UpdateTime();
    
    bool isConnect()const;
    
    void Disconnect();
    
    int SendPacket(const void* bytes, size_t size);
    
    int SendPacket(PacketBuffer& packet);
    
    int SendPacket(PacketBuffer* packet);
private:
    SOCKET_T  m_sock_fd;
};

#endif /* client_h */
