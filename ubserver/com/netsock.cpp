//
//  netsock.c
//  ubserver
//
//  Created by MikeRiy on 16/11/17.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "netsock.h"


bool NetSocket::Connect(const char* host, int port)
{
    if(isConnect())
    {
        return true;
    }
    sock_id = network::connect(host, port);
    isconnect = sock_id > 0;
    start();
    return isconnect;
}

void NetSocket::Close()
{
    if(isConnect())
    {
        isconnect = false;
        NET_CLOSE(sock_id);
        sock_id = 0;
    }
}

bool NetSocket::isConnect()const
{
    return isconnect;
}

void NetSocket::run()
{
    char bytes[MAX_BUFFER];
    while(isConnect())
    {
        size_t ret = NET_RECV(sock_id, bytes, MAX_BUFFER);
        if (ret > 0)
        {
            LOG_INFO<<"socket recv : size = "<<ret<<" fd = "<<sock_id<<LOG_END;
            RUN_MAIN(new SocketEvent(SOCKET_EVENT_READ, this, bytes, ret));
        }else {
            Close();
        }
    }
    //
    RUN_MAIN(new SocketEvent(SOCKET_EVENT_CLOSE, this));
}

void NetSocket::OnClose()
{
    
}

void NetSocket::OnPacketHandler()
{
    
}

void NetSocket::SendPacket(PacketBuffer& packet)
{
    if(isConnect())
    {
        NET_SEND_PACKET(sock_id, &packet);
    }
}