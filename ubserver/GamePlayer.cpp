//
//  GamePlayer.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GamePlayer.h"

GamePlayer::GamePlayer(PacketBuffer* bytes)
:user_id(0)
,seat_id(0){
    ReadFor(*bytes);
}

GamePlayer::~GamePlayer()
{
    
}

void GamePlayer::WriteTo(WriteBytes& bytes)
{
    
};

void GamePlayer::ReadFor(ReadBytes& bytes)
{
    
};
