//
//  client.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//
#include "client.h"

SocketHandler::SocketHandler()
:m_sock_fd(-1)
,user_id(0)
{
    
}

SocketHandler::SocketHandler(SOCKET_T sockt_fd)
:m_sock_fd(sockt_fd)
,user_id(0)
{
    
}

SocketHandler::~SocketHandler()
{
    Disconnect();
}

void SocketHandler::Disconnect()
{
    if(isConnect())
    {
        NET_CLOSE(m_sock_fd);
        m_sock_fd = -1;
    }
}

bool SocketHandler::isConnect()const
{
    return m_sock_fd > 0;
}


void SocketHandler::UpdateTime()
{
    
}

SOCKET_T SocketHandler::GetSocketFd()
{
    return m_sock_fd;
}

int SocketHandler::SendPacket(const void* bytes, size_t size)
{
    if(isConnect())
    {
        return NET_SEND(m_sock_fd, bytes, size);
    }
    return -1;
}

int SocketHandler::SendPacket(PacketBuffer& packet)
{
    return SendPacket(&packet[0], packet.wsize());
}

int SocketHandler::SendPacket(PacketBuffer* packet)
{
    return SendPacket(*packet);
}