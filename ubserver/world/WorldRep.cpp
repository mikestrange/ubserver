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
void WorldRep::HeartBead(NetNode* sock)
{
    MsgHandler packet;
    packet.setBegin(SERVER_CMD_HEARTBEAT);
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//0成功 1密码错误或者不存在
void WorldRep::Login(NetNode* sock, int8 code)
{
    MsgHandler packet;
    packet.setBegin(SERVER_CMD_LOGIN);
    packet.writeByte(code);
    //添加玩家信息
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//1被踢
void WorldRep::Logout(NetNode* sock, int8 code)
{
    MsgHandler packet;
    packet.setBegin(SERVER_CMD_LOGOUT);
    packet.writeByte(code);
    packet.WriteEnd();
    sock->SendPacket(packet);
}