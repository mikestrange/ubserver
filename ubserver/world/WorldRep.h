//
//  WorldRep.h
//  ubserver
//
//  Created by MikeRiy on 16/12/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef WorldRep_h
#define WorldRep_h

#include <stdio.h>
#include "global.h"
#include "CmdDefined.h"
#include "NetNode.h"
#include "MsgHandler.h"

class WorldRep
{
    STATIC_CLASS(WorldRep);
public:
    static void HeartBead(NetNode* sock);
    static void Login(NetNode* sock, int8 code);
    static void Logout(NetNode* sock, int8 code);
};

#endif /* WorldRep_h */
