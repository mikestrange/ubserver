//
//  GamePlayer.h
//  ubserver
//  游戏房间的玩家逻辑
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GamePlayer_h
#define GamePlayer_h

#include "global.h"

#include "GamePuzzle.h"
#include "string_util.h"
#include "UserObj.h"

#include "log.h"

class GamePlayer
{
private:
    UserObj* data;
private:
    uint32 bet_totals;
    uint32 bet_list[MAX_TYPE];
public:
    GamePlayer(UserObj* obj);
    
    virtual ~GamePlayer();
    
    int64 getUserMoney()const;
    
public:
    void OnEnter();
    
    void OnExit();
    
    bool AddBet(uint8 type, uint32 chips);
    
    void CleanBets();
    
    bool isNoBet()const;
    
    uint32 Reslut(uint8 type, int32 mult);
    
    uint32 getBetTotals(uint8 type)const;
    
    USER_T getUserID()const;
};

#endif /* GamePlayer_h */
