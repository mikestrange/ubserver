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
void WorldRep::HeartBead(NetContext* sock)
{
    SocketHandler packet;
    packet.setBegin(SERVER_CMD_HEARTBEAT);
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//0成功 1密码错误或者不存在
void WorldRep::Login(NetContext* sock, int8 code)
{
    SocketHandler packet;
    packet.setBegin(SERVER_CMD_LOGIN);
    packet.writeByte(code);
    //添加玩家信息
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//1被踢
void WorldRep::Logout(NetContext* sock, int8 code)
{
    SocketHandler packet;
    packet.setBegin(SERVER_CMD_LOGOUT);
    packet.writeByte(code);
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//获取服务器时间
void WorldRep::SysTime(NetContext* sock)
{
    SocketHandler packet;
    packet.setBegin(SERVER_CMD_GET_PING);
    packet.writeUInt((uint32)TimeUtil::GetTimer());
    packet.WriteEnd();
    sock->SendPacket(packet);
}

//
void WorldRep::ChatMsg(NetContext* sock, int8 type, int8 waytype, USER_T uid, std::string& user_name, std::string& content)
{
    SocketHandler packet;
    packet.setBegin(SERVER_CMD_CHAR_MSG);
    packet.writeByte(type);         //发送的类型
    packet.writeByte(waytype);      //发送方式
    packet.writeUInt(uid);          //发送者
    packet.writeString(user_name);  //发送者名称
    packet.writeString(content);
    packet.WriteEnd();
    //返回给所有登录的人
    ObjectCollect::getInstance()->SendToAll(packet);
    //没有登录也返回
    if(sock) sock->SendPacket(packet);
}
