//
//  WorldMsg.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "WorldMsg.h"

STATIC_CLASS_INIT(WorldMsg);


//所有消息处理
void WorldMsg::OnPacketHandler(SocketEvent* event)
{
    switch(event->getMessage()->getCmd())
    {
        case SERVER_CMD_LOGIN:
            Login(event->getNode(), event->getMessage());
            break;
        case SERVER_CMD_LOGOUT:
            Logout(event->getNode(), event->getMessage());
            break;
        case SERVER_CMD_TEST:
            test(event->getNode(), event->getMessage());
            break;
    }
};


void WorldMsg::Login(NetNode* sock, MsgHandler* packet)
{
    //数据读取
    uint8 type = packet->readByte();
    USER_T uid = packet->readUInt();
    std::string pass_word;
    std::string device_id;
    packet->readString(pass_word);
    packet->readString(device_id);
    //--
    LOG_DEBUG("login input uid=%d pws=%s device=%s", uid, pass_word.c_str(), device_id.c_str());
    bool is_check = false;
    //登录类型
    if(type == 1){
        //密码登录
        is_check = DBServer::getInstance()->login_with_user(uid, pass_word);
    }else if(type == 2){
        //设备登录
        is_check = DBServer::getInstance()->login_with_device(uid, device_id);
    }
    if(is_check)
    {
        auto user = ObjectCollect::getInstance()->getObject(uid);
        //不要重复登录
        if(user && user->isLogin())
        {
            WorldRep::Logout(user->getSock(), 1);
        }
        user = ObjectCollect::getInstance()->RegObject(uid, sock);
        WorldRep::Logout(user->getSock(), 0);
    }else{
        LOG_WARN("log error no match uid or pwd");
        WorldRep::Login(sock, 1);
        sock->DisConnect();
    }
}

void WorldMsg::Logout(NetNode* sock, MsgHandler* packet)
{
    //no handler
}

void WorldMsg::test(NetNode* sock, MsgHandler* packet)
{
    //int8 type = packet->readInt8();
    //uint32 chips = packet->readUint32();
//    PacketBuffer bytes;
//    bytes.setBegin(packet->getCmd());
//    bytes.WriteBegin();
//    bytes.writeInt8(112);
//    bytes.writeUint32(1234);
//    bytes.WriteEnd();
//    GameManager::getInstance()->SendPacket(packet->getUserID(), bytes);
}