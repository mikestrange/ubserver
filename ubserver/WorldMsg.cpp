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
    
}

void WorldMsg::Logout(SocketHandler *packet)
{
    
}