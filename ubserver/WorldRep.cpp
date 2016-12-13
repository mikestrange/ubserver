//
//  WorldRep.c
//  ubserver
//
//  Created by MikeRiy on 16/12/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "WorldRep.h"

STATIC_CLASS_INIT(WorldRep);

//未登录的玩家不具备心跳
void WorldRep::HeartBead(GameUser* sock)
{
    if(sock->isNoLogin()) return;
    PacketBuffer packet;
    packet.setBegin(SERVER_CMD_HEARTBEAT);
    packet.WriteBegin();
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//0成功 1密码错误或者不存在
void WorldRep::Login(GameUser* sock, int8 code)
{
    PacketBuffer packet;
    packet.setBegin(SERVER_CMD_LOGIN);
    packet.WriteBegin();
    packet.writeInt8(code);
    //添加玩家信息
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//1被踢
void WorldRep::Logout(GameUser* sock, int8 code)
{
    PacketBuffer packet;
    packet.setBegin(SERVER_CMD_LOGOUT);
    packet.WriteBegin();
    packet.writeInt8(code);
    packet.WriteEnd();
    sock->SendPacket(packet);
}