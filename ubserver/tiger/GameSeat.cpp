//
//  GameSeat.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GameSeat.h"


GameSeat::GameSeat(USER_T uid)
:seat_id(0)
,user_id(uid)
{
    
}

GameSeat::~GameSeat()
{
    
}

SEAT_T GameSeat::StandUp()
{
    SEAT_T sid = seat_id;
    seat_id = 0;
    return sid;
}

void GameSeat::SitDown(SEAT_T sid)
{
    seat_id = sid;
}

bool GameSeat::isSitDown()const
{
    return seat_id > 0;
}

bool GameSeat::isStand()const
{
    return seat_id == 0;
}

USER_T GameSeat::getUserID()const
{
    return user_id;
}

SEAT_T GameSeat::getSeatID()const
{
    return seat_id;
}
