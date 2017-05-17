//
//  flash.c
//  ubserver
//
//  Created by MikeRiy on 16/12/29.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "flash.h"

STATIC_CLASS_INIT(FlashHandler);

void FlashHandler::OnReadHandler(NetContext *context, char *bytes, size_t size)
{
    LOG_INFO(">>>>收到843接口 %ld %s", size, bytes);
    std::string domian;
    domian += "<?xml version='1.0'?>\n";
    domian += "<cross-domain-policy>\n";
    domian += "<allow-access-from domain='*' to-ports='*'/>\n";
    domian += "</cross-domain-policy>\n\0";
    context->SendPacket(domian.c_str(), domian.length());
    context->DisConnect();
}

void FlashHandler::OnClosed(NetContext* context)
{
    SAFE_DELETE(context);
}

void FlashHandler::OnStop(NetContext* context)
{
    SAFE_DELETE(context);
}


void flash_domain()
{
    pid_t fpid = fork();
    if(fpid == 0)
    {
        LOG_DEBUG("start launch flash port 843");
        soy::launch(843, FlashHandler::getInstance());
    }
}
