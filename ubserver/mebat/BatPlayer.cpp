//
//  BatPlayer.c
//  ubserver
//
//  Created by MikeRiy on 17/1/5.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#include "BatPlayer.h"

BatPlayer::BatPlayer()
:user_id()
,camp_id()
,map_id()
,state()
,x()
,y()
,state_time()
,begin_time()
{
    
}

BatPlayer::BatPlayer(ByteStream& bytes)
:BatPlayer()
{
    ReadCode(bytes);
}


void BatPlayer::ReadCode(ByteStream &bytes)
{
    
}

void BatPlayer::MoveTo(int16 x, int16 y, uint8 mid)
{
    if(mid > 0) this->map_id = mid;
    this->x = x;
    this->y = y;
    LOG_DEBUG("move uid=%d x=%d y=%d mid=%d", user_id, x, y, mid);
}

void BatPlayer::UpdateState(int8 val)
{
    this->state = val;
    this->state_time = TimeUtil::GetTimer();
}

//获取毫秒
void BatPlayer::UpdateTime()
{
    begin_time = TimeUtil::GetTimer();
}