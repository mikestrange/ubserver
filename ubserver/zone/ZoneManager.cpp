
//
//  GameManager.c
//  ubserver
//
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "ZoneManager.h"

STATIC_CLASS_INIT(ZoneManager);

ZoneManager::ZoneManager()
{
    launch(101, new TigerLogic);
}

void ZoneManager::launch(TABLE_ID tid, LogicBase* target, int gtype, int rid)
{
    if(tab.has(tid)) return;
    tab.put(tid, target);
    target->OnLaunch(tid, gtype, rid);
}

void ZoneManager::shut(TABLE_ID tid)
{
    auto logic = tab.remove(tid);
    if(logic)
    {
        logic->OnExit();
    }
    SAFE_DELETE(logic);
}

void ZoneManager::OnPacketHandler(SocketHandler* packet)
{
    TABLE_ID room_id = packet->getViewId();
    LogicBase* game = tab.getValue(room_id);
    if(game){
        game->OnPacketHandler(packet);
    }else{
        LOG_WARN("no room id goto uid=%d", room_id);
    }
}
