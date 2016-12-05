//
//  client.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//
#include "client.h"

SocketHandler::SocketHandler(NetLink* link)
:m_link(link)
,user_id(0)
{
    
}

bool SocketHandler::isNoLogin()const
{
    return user_id == 0;
}

void SocketHandler::BindUser(USER_T uid)
{
    user_id = uid;
}

void SocketHandler::UnBindUser()
{
    user_id = 0;
}

USER_T SocketHandler::getUserID()const
{
    return user_id;
}

SocketHandler::~SocketHandler()
{
    SAFE_DELETE(m_link);
}

void SocketHandler::Disconnect()
{
    m_link->DisConnect();
}

bool SocketHandler::isConnect()const
{
    return m_link->isConnect();
}

void SocketHandler::UpdateTime()
{
    
}

SOCKET_T SocketHandler::GetSocketFd()
{
    return m_link->getSocketID();
}

int SocketHandler::SendPacket(PacketBuffer& packet)
{
    return m_link->SendPacket(&packet[0], packet.wpos());
}

int SocketHandler::SendPacket(PacketBuffer* packet)
{
    return SendPacket(*packet);
}