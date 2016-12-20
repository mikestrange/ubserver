//
//  ZoneMsg.h
//  ubserver
//
//  Created by MikeRiy on 16/12/19.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef ZoneMsg_h
#define ZoneMsg_h

#include "CmdDefined.h"
#include "log.h"
#include "string_util.h"

#include "DBServer.h"
#include "SocketEvent.h"
#include "ZoneManager.h"

class ZoneMsg
{
    STATIC_CLASS(ZoneMsg);
    
public:
    void OnPacketHandler(SocketEvent* event);
    
};

#endif /* ZoneMsg_h */
