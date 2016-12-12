//
//  WorldMsg.h
//  ubserver
//  世界会话
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef WorldMsg_h
#define WorldMsg_h

#include <stdio.h>
#include "packet_buffer.h"
#include "CmdDefined.h"
#include "log.h"
#include "string_util.h"

#include "PlayerManager.h"
#include "DBServer.h"
#include "coupler.h"
#include "md5.h"

class GameUser;

class WorldMsg
{
    STATIC_CLASS(WorldMsg);
public:
    WorldMsg();
    
public:
    void OnPacketHandler(GameUser *packet);
    
private:
    void test(GameUser *packet);
    void Login(GameUser *packet);
    void Logout(GameUser *packet);
};


#endif /* WorldMsg_h */
