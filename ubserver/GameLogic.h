//
//  GameLogic.h
//  ubserver
//  游戏房间逻辑中心
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GameLogic_h
#define GameLogic_h

#include <stdio.h>
#include "GameData.h"
#include "global.h"

#include "hashmap.h"
#include "GamePlayer.h"
#include "GameSeat.h"

#define MAX_SEAT 3

class GameLogic
{
private:
    GameData* _data;
    HashMap<USER_T, GamePlayer*> players;
    HashMap<SEAT_T, GameSeat*> seats;
public:
    GameLogic();
    virtual ~GameLogic();
    //启动和注销
    void OnLaunch(GameData* info);
    void OnExit();
    //基础数据
    GameData* getData()const;
public:
    void EnterPlayer(GamePlayer* player);
    void ExitPlayer(USER_T uid);
    void StandUp(USER_T uid);
    void SitDown(USER_T uid, SEAT_T sid);
};

#endif /* GameLogic_h */
