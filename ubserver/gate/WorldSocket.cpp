//
//  GateSocket.c
//  ubserver
//
//  Created by MikeRiy on 16/12/27.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "WorldSocket.h"

static void packet_handler(SocketHandler* packet, int type)
{
    packet->ReadBegin();
    WorldSocket::getInstance()->SendEvent(packet->getCmd(), packet, packet->getType());
    SAFE_DELETE(packet);
}

static void socket_handler(NetContext* context, int type)
{
    
}

static void w_login(MsgID cmd, SocketHandler* packet, int mtype)
{
    
}

static void w_logout(MsgID cmd, SocketHandler* packet, int mtype)
{
    
}

//
STATIC_CLASS_INIT(WorldSocket);

WorldSocket::WorldSocket()
{
    setLoopCall(packet_handler, socket_handler);
    //events
    AddEvent(SERVER_CMD_LOGIN, w_login);
    AddEvent(SERVER_CMD_LOGOUT, w_logout);
}

bool WorldSocket::connect(const char *host, int port)
{
    return soy::connect(host, port) > 0;
}