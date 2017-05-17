//
//  GateRep.h
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GateRep_h
#define GateRep_h

#include "global.h"
#include "CmdDefined.h"
#include "NetContext.h"
#include "SocketHandler.h"

class GateRep
{
public:
    static void HeartBead(NetContext* sock);
    static void Login(NetContext* sock, int8 code);
    static void Logout(NetContext* sock, int8 code);
};

#endif /* GateRep_h */
