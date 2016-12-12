//
//  WorldMsg.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "WorldMsg.h"

STATIC_CLASS_INIT(WorldMsg);


WorldMsg::WorldMsg()
{
    
}

//所有消息处理
void WorldMsg::OnPacketHandler(GameUser *packet)
{
    switch(packet->getCmd())
    {
        case SERVER_CMD_LOGIN:
            Login(packet);
            break;
        case SERVER_CMD_LOGOUT:
            Logout(packet);
            break;
        case SERVER_CMD_TEST:
            test(packet);
            break;
    }
};


void WorldMsg::Login(GameUser *packet)
{
    //数据读取
    uint8 type = packet->readInt8();
    USER_T uid = packet->readUint32();
    std::string pass_word = packet->readString();
    std::string device_id = packet->readString();
    //--
    Log::Debug("login input uid=%d pws=%s device=%s",uid,pass_word.c_str(),device_id.c_str());
    bool is_login = false;
    //登录类型
    if(type == 1){
        //密码登录
        //is_login = DBServer::getInstance()->login_with_user(uid, pass_word);
    }else if(type == 2){
        //设备登录
        //is_login = DBServer::getInstance()->login_with_device(uid, device_id);
    }
    if(!is_login)
    {
        Log::Warn("log error no match uid or pwd");
        packet->DisConnect();
    }else{
        //未登录可以登录(先注销)
        if(packet->isNoLogin())
        {
             Log::Debug("log ok uid=%d",uid);
            auto player = PlayerManager::getInstance()->getPlayer(uid);
            //存在用户
            if(player)
            {
                //之前的socket会断开
                player->LinkSocket(packet);
            }else{
                //不存在的用户
                PlayerManager::getInstance()->AddPlayer(new Player(uid, packet));
            }
            //--
            PacketBuffer buffer;
            buffer.setBegin(SERVER_CMD_LOGIN);
            buffer.WriteBegin();
            //玩家信息
            buffer.WriteEnd();
            packet->SendPacket(buffer);
        }else{
            Log::Debug("log error this socket is login");
        }
    }
}

void WorldMsg::Logout(GameUser *packet)
{
    //no handler
}

void WorldMsg::test(GameUser *packet)
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