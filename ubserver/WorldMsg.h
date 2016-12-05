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
#include "event.h"
#include "packet_buffer.h"
#include "CmdDefined.h"
#include "client.h"
#include "log.h"
#include "string_util.h"

#include "PlayerManager.h"
#include "DBServer.h"
#include "coupler.h"
#include "md5.h"

class WorldMsg
{
    STATIC_CLASS(WorldMsg);
public:
    WorldMsg();
    
public:
    void OnPacketHandler(SocketHandler *packet);
    
private:
    void test(SocketHandler *packet);
    void Login(SocketHandler *packet);
    void Logout(SocketHandler *packet);
};


#endif /* WorldMsg_h */
