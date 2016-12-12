//
//  GameUser.c
//  ubserver
//
//  Created by MikeRiy on 16/12/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GameUser.h"

GameUser::GameUser()
:player(NULL)
{
    
}

GameUser::~GameUser()
{
    if(player)
    {
        player->UnLinkSocket();
    }
}

void GameUser::BindPlayer(Player* value)
{
    player = value;
}

bool GameUser::isLogin()const
{
    return player != NULL;
}

bool GameUser::isNoLogin()const
{
    return player == NULL;
}

void GameUser::UnBindPlayer()
{
    player = NULL;
}

Player* GameUser::getPlayer()const
{
    return player;
}

void GameUser::SendPacket(PacketBuffer& packet)
{
    this->NetNode::SendPacket(&packet[0], packet.wpos());
}