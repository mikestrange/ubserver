//
//  BatLogic.c
//  ubserver
//
//  Created by MikeRiy on 17/1/5.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#include "BatLogic.h"

BatLogic::BatLogic(uint32 bid)
:bat_id(bid)
,game_state(0)
{
    
}

BatLogic::~BatLogic()
{
    playerMap.eachValues(block(BatPlayer* v)
    {
        SAFE_DELETE(v);
    });
}

void BatLogic::Launch()
{
    
}

int BatLogic::Windup()
{
    return 0;
}

int BatLogic::JoinPlayer(BatPlayer* player)
{
    if(playerMap.has(player->user_id))
    {
        SAFE_DELETE(player);
    }else{
        playerMap.put(player->user_id, player);
        LOG_DEBUG("join game uid=%d", player->user_id);
    }
    return 0;
}

int BatLogic::ExitPlayer(USER_T uid)
{
    auto player = playerMap.remove(uid);
    if(player)
    {
        LOG_DEBUG("exit game uid=%d", player->user_id);
        SAFE_DELETE(player);
    }
    return 0;
}


void BatLogic::Update(BatPlayer* player)
{
    
}


void BatLogic::MoveTo(USER_T uid, int16 x, int16 y, uint8 mid)
{
    auto player = playerMap.getValue(uid);
    if(player)
    {
        player->MoveTo(x, y, mid);
        //--
        Update(player);
    }
}

void BatLogic::ReleaseSkill(USER_T uid, int16 sid, int16 angle)
{
    auto player = playerMap.getValue(uid);
    if(player)
    {
        
    }
}

void BatLogic::ReleaseSkill(USER_T uid, int16 sid, Rect* rect)
{
    auto player = playerMap.getValue(uid);
    if(player)
    {
        
    }
}

void BatLogic::ReleaseSkill(USER_T uid, int16 sid, int16 count, USER_T uids[])
{
    auto player = playerMap.getValue(uid);
    if(player)
    {
        
    }
}

void BatLogic::ReleaseSkill(USER_T uid, int16 sid, USER_T aim)
{
    auto player = playerMap.getValue(uid);
    if(player)
    {
        
    }
}

//游戏流程
void BatLogic::StartGame()
{
    
}

void BatLogic::OverGame()
{
    
}






