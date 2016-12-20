//
//  WorldMsg.h
//  ubserver
//  世界会话
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef WorldMsg_h
#define WorldMsg_h

#include "CmdDefined.h"
#include "log.h"
#include "string_util.h"

#include "DBServer.h"
#include "md5.h"
#include "WorldRep.h"
#include "SocketEvent.h"
#include "ObjectCollect.h"


class WorldMsg
{
    STATIC_CLASS(WorldMsg);
public:
    void OnPacketHandler(SocketEvent* event);
    
private:
    void test(NetNode* node, MsgHandler* message);
    void Login(NetNode* node, MsgHandler* message);
    void Logout(NetNode* node, MsgHandler* message);
};


#endif /* WorldMsg_h */
