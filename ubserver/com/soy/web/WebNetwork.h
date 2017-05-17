//
//  WebNetwork.h
//  ubserver
//
//  Created by MikeRiy on 17/1/3.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef WebNetwork_h
#define WebNetwork_h

#include "Network.h"
#include "WebContext.h"
#include "BaseHandler.h"
#include "WebRespond.h"
//test
#include "WorldHandler.h"

class WebNetwork : public WorldHandler
{
    STATIC_CLASS(WebNetwork);
public:
    void OnReadHandler(NetContext* context, char* bytes, size_t size)override;
    //--
    NetContext* alloc_context(SOCKET_T fd)override;
};

#endif /* WebNetwork_h */
