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
void WorldMsg::OnPacketHandler(SocketHandler *packet)
{
    //LOG_DEBUG<<"world handler cmd = "<<packet->getCmd()<<LOG_END;
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


void WorldMsg::Login(SocketHandler *packet)
{
    uint8 type = packet->readInt8();
    USER_T uid = packet->readUint32();
    std::string pass_word = packet->readString();
    //--
    LOG_DEBUG<<(type+'\0')<<",uid="<<uid<<",pws="<<pass_word<<LOG_END;
    DataQuery result;
    DBCoupler sql(DBServer::getInstance());
    //密码md5
    MD5 md5(pass_word);
    sql.SQL().findFormat(result, "select * from account where uid = '%d' and pwd = '%s'", uid, md5.md5().c_str());
    //result.toString();
    if(result.empty())
    {
        LOG_WARN<<"log error no match uid or pwd"<<LOG_END;
        packet->Disconnect();
    }else{
        LOG_WARN<<"log ok uid = "<<uid<<LOG_END;
        //未登录可以登录
        if(packet->isNoLogin())
        {
            PlayerManager::getInstance()->AddPlayer(new Player(uid, packet));
            //--
            PacketBuffer buffer;
            buffer.setBegin(SERVER_CMD_LOGIN);
            buffer.WriteBegin();
            //玩家信息
            buffer.WriteEnd();
            packet->SendPacket(buffer);
        }
    }
}

void WorldMsg::Logout(SocketHandler *packet)
{
    //no handler
}

void WorldMsg::test(SocketHandler *packet)
{
    int8 type = packet->readInt8();
    uint32 chips = packet->readUint32();
    
    LOG_DEBUG<<(type+'\0')<<",chips="<<chips<<LOG_END;
    
//    PacketBuffer bytes;
//    bytes.setBegin(packet->getCmd());
//    bytes.WriteBegin();
//    bytes.writeInt8(112);
//    bytes.writeUint32(1234);
//    bytes.WriteEnd();
//    GameManager::getInstance()->SendPacket(packet->getUserID(), bytes);
}