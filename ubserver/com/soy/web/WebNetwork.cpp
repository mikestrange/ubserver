//
//  WebNetwork.c
//  ubserver
//
//  Created by MikeRiy on 17/1/3.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#include "WebNetwork.h"

STATIC_CLASS_INIT(WebNetwork);

void WebNetwork::OnReadHandler(NetContext *context, char *bytes, size_t size)
{
    //LOG_INFO("## websocket size=%ld {\n%s\n}", size, bytes);
    WebContext* handler = (WebContext*) context;
    try{
        if(handler->process(bytes) == 0)
        {
            try{
                SocketHandler* packet = NULL;
                while((packet = context->NextMessage()))
                {
                    this->OnPacket(packet);
                }
            }catch(...){
                context->DisConnect();
            }
        };
    }catch(...){
        context->DisConnect();
    }
}

NetContext* WebNetwork::alloc_context(SOCKET_T fd)
{
    return new WebContext(fd);
}