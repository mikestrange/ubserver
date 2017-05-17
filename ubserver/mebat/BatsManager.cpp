//
//  BatsManager.c
//  ubserver
//
//  Created by MikeRiy on 17/1/5.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#include "BatsManager.h"

STATIC_CLASS_INIT(BatsManager);

BatsManager::BatsManager()
{
    create_battle();
}

uint32 BatsManager::create_battle()
{
    while(batMap.has(++current_batid))
    {
        if(current_batid == UINT32_MAX) current_batid = 0;
    }
    //--
    auto logic = new BatLogic(current_batid);
    batMap.put(current_batid, logic);
    //启动
    logic->Launch();
    return current_batid;
}

int BatsManager::finish_battler(uint32 bat_id)
{
    BatLogic* logic = batMap.getValue(bat_id);
    if(logic && logic->Windup() == 0)
    {
        SAFE_DELETE(logic);
    }
    return -1;
}

int BatsManager::join_battle(uint32 bat_id, BatPlayer* player)
{
    BatLogic* logic = batMap.getValue(bat_id);
    if(logic){
        return logic->JoinPlayer(player);
    }else{
        SAFE_DELETE(player);
    }
    return -1;
}

int BatsManager::exit_battle(uint32 bat_id, USER_T uid)
{
    BatLogic* logic = batMap.getValue(bat_id);
    if(logic)
    {
        return logic->ExitPlayer(uid);
    }
    return -1;
}

void BatsManager::OnPacketHandler(SocketHandler* packet)
{
    BatLogic* logic = batMap.getValue(packet->getViewId());
    if(!logic){
        LOG_WARN("no room:%d", packet->getViewId());
        return;
    }
    switch (packet->getCmd())
    {
        case SERVER_CLIENT_BAT_JOIN:
        {
            logic->JoinPlayer(new BatPlayer(*packet));
        }
            break;
        case SERVER_CLIENT_BAT_PLAYER_MOVE:
        {
            logic->MoveTo(packet->readUInt(), packet->readShort(), packet->readShort(),packet->readUByte());
        }
            break;
        case SERVER_CLIENT_BAT_RELEASE_SKILL:
        {
            
        }
            break;
        case SERVER_CLIENT_BAT_EXIT:
        {
            logic->ExitPlayer(packet->readUInt());
        }
            break;
    }
}