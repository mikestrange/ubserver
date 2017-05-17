//
//  GateSocket.h
//  ubserver
//  连接世界服务器
//  Created by MikeRiy on 16/12/27.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GateSocket_h
#define GateSocket_h

#include "SocketHandler.h"
#include "CmdDefined.h"
#include "BaseHandler.h"

class WorldSocket : public BaseHandler
{
    STATIC_CLASS(WorldSocket);
public:
    WorldSocket();
    
    bool connect(const char* host, int port);
    //
    
};
#endif /* GateSocket_h */
