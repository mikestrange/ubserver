//
//  ZoneMsg.c
//  ubserver
//
//  Created by MikeRiy on 16/12/19.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "ZoneMsg.h"

STATIC_CLASS_INIT(ZoneMsg);

//所有消息处理(每个房间处理不一样/所以交给房间处理)
void ZoneMsg::OnPacketHandler(SocketEvent* event)
{
    ZoneManager::getInstance()->OnPacketHandler(event->getMessage());
};