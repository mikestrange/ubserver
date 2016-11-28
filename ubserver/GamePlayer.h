//
//  GamePlayer.h
//  ubserver
//  游戏房间的玩家逻辑
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GamePlayer_h
#define GamePlayer_h

#include <stdio.h>
#include "global.h"
#include "packet_buffer.h"
#include "GameSeat.h"
#include "GamePuzzle.h"
#include "string_util.h"

#include "log.h"

class GamePlayer : public IReader , public GameSeat
{
private:
    uint64 user_money;
    uint64 bet_totals;
    uint32 bet_list[MAX_TYPE];
public:
    GamePlayer(USER_T uid, PacketBuffer* bytes);
    
    virtual ~GamePlayer();
    
    void WriteTo(WriteBytes& bytes)override;
    
    void ReadFor(ReadBytes& bytes)override;
    
    uint64 getUserMoney()const;
    
public:
    void OnEnter();
    
    void OnExit();
    
    uint32 AddBet(uint8 type, uint32 chips);
    
    void CleanBets();
    
    bool isNoBet()const;
    
    uint32 Reslut(uint8 type, int32 mult);
};

#endif /* GamePlayer_h */
