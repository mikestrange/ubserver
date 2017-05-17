//
//  GameLogic.h
//  ubserver
//  游戏房间逻辑中心(老虎机)
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GameLogic_h
#define GameLogic_h

#include "global.h"
#include "string_util.h"
#include "math_util.h"
#include "hashmap.h"

#include "TimePush.h"

#include "GamePlayer.h"
#include "GamePuzzle.h"
#include "ZoneManager.h"
#include "LogicBase.h"

#include "ZoneRep.h"

//游戏状态
enum
{
    TIGER_GAME_STOP_STATUS = 0,
    TIGER_GAME_START_STATUS,
    TIGER_GAME_WAIT_STATUS,
    
    TIGER_TIMER_START = 1,
    TIGER_TIMER_STOP,
};

class TigerLogic : public ITimeoutHandler, public LogicBase
{
private:
    int8 m_game_state;
    TIME_T start_time;
    uint64 pot_totals;
    uint32 pot_list[MAX_TYPE];
public:
    const int MAX_USER = 1000;              //房间最大人数
    const TIME_T CHIP_TIME = 10*1000;       //下注时间
    const TIME_T WAIT_TIME = 10*1000;       //等待开始时间
    const int max_chip = 10000000;          //1000万(最大投注)
    const int min_chip = 100;               //单次最小投注(不用)
    const int bet_time = 10;
    const int wait_time = 10;
private:
    HashMap<USER_T, GamePlayer*> m_players;
private://计时器
    TimePush m_clock;
public:
    TigerLogic();
    virtual ~TigerLogic();
    void OnPacketHandler(SocketHandler* packet)override;
protected:
    void EnterHome(USER_T uid);
    void LeaveHome(USER_T uid);
private:
    void UserBet(USER_T uid, uint8 type, uint32 chips);
private://req
    void EnterRep(int8 code, USER_T uid, GamePlayer* player);
    void ExitRep(int8 code, USER_T uid);
    void StartRep();
    void BetRep(GamePlayer* player, uint8 type, uint32 chips);
    void PotBetRep();
    void ResultRep(uint8 index, uint8 type, uint8 mult);
private:
    void GameStart();
    void GameOver();
    void CleanPotBets();
public:
    void OnTimeProcess(int type)override;
};

#endif /* GameLogic_h */
