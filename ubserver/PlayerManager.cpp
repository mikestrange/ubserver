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
    Player* old_p = m_players.remove(player->user_id);
    //删除之前的登录
    if(old_p)
    {
        LOG_INFO<<"tick uid = "<<old_p->user_id<<LOG_END;
        //被踢
        old_p->getSocket()->Disconnect();
        SAFE_DELETE(old_p);
    }
    m_players.put(player->user_id, player);
    LOG_INFO<<"add player uid = "<<player->user_id<<LOG_END;
    return true;
}


void PlayerManager::DelPlayer(USER_T uid)
{
    if(uid == 0) return;
    Player* player = m_players.remove(uid);
    if(player)
    {
        //player->getSocket()->Disconnect();
        LOG_INFO<<"del player uid = "<<uid<<LOG_END;
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