//
//  GateRep.c
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GateRep.h"

//未登录的玩家不具备心跳
void GateRep::HeartBead(NetContext* sock)
{
    SocketHandler packet;
    packet.setBegin(SERVER_CMD_HEARTBEAT);
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//0成功 1密码错误或者不存在
void GateRep::Login(NetContext* sock, int8 code)
{
    SocketHandler packet;
    packet.setBegin(SERVER_CMD_LOGIN);
    packet.writeByte(code);
    //添加玩家信息
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//1被踢
void GateRep::Logout(NetContext* sock, int8 code)
{
    SocketHandler packet;
    packet.setBegin(SERVER_CMD_LOGOUT);
    packet.writeByte(code);
    packet.WriteEnd();
    sock->SendPacket(packet);
}