//
//  GateHandler.h
//  ubserver
//
//  Created by MikeRiy on 16/12/27.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GateHandler_h
#define GateHandler_h

#include <stdio.h>
#include "SocketHandler.h"
#include "CmdDefined.h"
#include "BaseHandler.h"
#include "GameUser.h"
#include "GateRep.h"

class GateHandler : public BaseHandler
{
    STATIC_CLASS(GateHandler);
public:
    GateHandler();
    //--
    NetContext* alloc_context(SOCKET_T fd)override;
};

#endif /* GateHandler_h */
