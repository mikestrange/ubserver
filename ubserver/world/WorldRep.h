//
//  WorldRep.h
//  ubserver
//
//  Created by MikeRiy on 16/12/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef WorldRep_h
#define WorldRep_h

#include "global.h"
#include "CmdDefined.h"
#include "NetContext.h"
#include "SocketHandler.h"
#include "ObjectCollect.h"

class WorldRep
{
    STATIC_CLASS(WorldRep);
public:
    static void HeartBead(NetContext* sock);
    static void Login(NetContext* sock, int8 code);
    static void Logout(NetContext* sock, int8 code);
    static void SysTime(NetContext* sock);
    //消息
    static void ChatMsg(NetContext* sock, int8 type, int8 waytype,
                        USER_T uid, std::string& user_name, std::string& content);
};

#endif /* WorldRep_h */
