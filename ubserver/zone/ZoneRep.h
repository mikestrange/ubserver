//
//  ZoneRep.h
//  ubserver
//
//  Created by MikeRiy on 16/12/19.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef ZoneRep_h
#define ZoneRep_h

#include <stdio.h>
#include "MsgHandler.h"
#include "NetNode.h"
#include "CmdDefined.h"

class ZoneRep
{
    STATIC_CLASS(ZoneRep);
public:
    static void SendTo(USER_T uid, MsgHandler& packet);
};

#endif /* ZoneRep_h */
