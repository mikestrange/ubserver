//
//  PlayerManager.c
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "PlayerManager.h"

STATIC_CLASS_INIT(PlayerManager);


bool PlayerManager::AddPlayer(Player *player)
{
    //之前不能存在的用户才能加入
    m_players.put(player->getUserID(), player);
    Log::Info("add player uid=%d", player->getUserID());
    return true;
}


void PlayerManager::DelPlayer(USER_T uid)
{
    if(uid == 0) return;
    Player* player = m_players.remove(uid);
    if(player)
    {
        player->getSocket()->DisConnect();
        Log::Info("del player uid=%d",uid);
    }
    SAFE_DELETE(player);
}

void PlayerManager::SendPlayer(USER_T uid, PacketBuffer& buffer)
{
    Player* player = m_players.getValue(uid);
    if(player)
    {
        player->getSocket()->SendPacket(buffer);
    }
}

Player* PlayerManager::getPlayer(USER_T uid)
{
    return m_players.getValue(uid);
}

bool PlayerManager::EnterView(USER_T uid, TABLE_ID tid)
{
    Player* player = m_players.getValue(uid);
    if(player)
    {
        return player->EnterRoom(tid);
    }
    return false;
}

void PlayerManager::ExitView(USER_T uid)
{
    Player* player = m_players.getValue(uid);
    if(player)
    {
        player->ExitRoom();
    }
}