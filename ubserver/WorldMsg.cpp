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
    LOG_DEBUG<<"world handler cmd = "<<packet->getCmd()<<LOG_END;
    switch(packet->getCmd())
    {
        case SERVER_CMD_LOGIN:
            Login(packet);
            break;
        case SERVER_CMD_LOGOUT:
            Logout(packet);
            break;
    }
};


void WorldMsg::Login(SocketHandler *packet)
{
    USER_T uid = packet->readUint32();
    std::string pass_word = packet->readString();
    DataQuery result;
    DBServer::getInstance()->findFormat(result, "select * from account where uid = '%d' and pwd = '%s'",
                                        uid, pass_word.c_str());
    //result.toString();
    if(result.empty())
    {
        LOG_WARN<<"log error no match uid or pwd"<<LOG_END;
        packet->Disconnect();
    }else{
        LOG_WARN<<"log ok uid = "<<uid<<LOG_END;
        //未登录可以登录
        if(packet->user_id == 0)
        {
            PlayerManager::getInstance()->AddPlayer(new Player(uid, packet));
        }
    }
}

void WorldMsg::Logout(SocketHandler *packet)
{
    //no handler
}