//
//  GameLogic.c
//  ubserver
//
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GameLogic.h"

GameLogic::GameLogic()
:_data(NULL)
{
    
};

GameLogic::~GameLogic()
{
    SAFE_DELETE(_data);
    //
    seats.eachValues([](GameSeat* v)
    {
        SAFE_DELETE(v);
    });
    //
    players.eachValues([](GamePlayer* v)
    {
        SAFE_DELETE(v);
    });
}

void GameLogic::OnLaunch(GameData* data)
{
    _data = data;
}


GameData* GameLogic::getData()const
{
    return _data;
}


void GameLogic::OnExit()
{
    
}


//packet
void GameLogic::EnterPlayer(GamePlayer* player)
{
    
}

void GameLogic::ExitPlayer(USER_T uid)
{
    
};

void GameLogic::StandUp(USER_T uid)
{
    
};

void GameLogic::SitDown(USER_T uid, SEAT_T sid)
{
    
};
