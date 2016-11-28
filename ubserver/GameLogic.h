//
//  GameLogic.h
//  ubserver
//  游戏房间逻辑中心(老虎机)
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GameLogic_h
#define GameLogic_h

#include <stdio.h>
#include "global.h"
#include "string_util.h"

#include "hashmap.h"
#include "GamePlayer.h"
#include "GameSeat.h"
#include "clock.h"
#include "GamePuzzle.h"
#include "GameManager.h"
#include "math_util.h"

class GameManager;

enum
{
    TIGER_GAME_STOP_STATUS = 0,
    TIGER_GAME_START_STATUS,
    TIGER_GAME_WAIT_STATUS,
    
    TIGER_TIMER_START = 1,
    TIGER_TIMER_STOP,
};

enum
{
    TIGER_APPLE = 5,
    TIGER_ORANGE = 10,
    TIGER_CANTALOUP = 15,
    TIGER_BELL = 20,
    TIGER_WATERMELON = 20,
    TIGER_STAR = 30,
    TIGER_SEVEN = 40,
    TIGER_GHOST = 25,
    TIGER_SMALL_GHOST = 50,
    TIGER_BIG_GHOST = 100,
};

class GameLogic : public ITimeoutHandler
{
private://房间数据
    TABLE_ID m_table_id;
private://游戏当前
    int m_game_state;
    TIME_T start_time;
    uint64 pot_totals;
    uint32 pot_list[MAX_TYPE];
private://固定参数
    const SEAT_T MAX_SEAT = 3;
    const int MAX_USER = 1000;
    const TIME_T CHIP_TIME = 10*1000;    //下注时间
    const TIME_T WAIT_TIME = 10*1000;    //等待开始时间
    const int BASE_CHIP = 1;            //底分
    const int bet_time = 10;
    const int wait_time = 10;
    const int max_chip = 1000000;
private:
    HashMap<USER_T, GamePlayer*> m_players;
    HashMap<SEAT_T, USER_T> m_seats;
private://计时器
    Clock m_clock;
public:
    GameLogic();
    virtual ~GameLogic();
    //启动和注销
    void OnLaunch(TABLE_ID tid);
    void OnExit();
public:
    int EnterPlayer(GamePlayer* player);
    int ExitPlayer(USER_T uid);
    int StandUp(USER_T uid);
    int SitDown(USER_T uid, SEAT_T sid);
private:
    void GameStart();
    void GameOver();
    void AddPotBet(uint8 type, uint32 chip);
    void CleanPotBets();
public:
    void UserBet(USER_T uid, uint8 type, uint32 chip);
    //--
    void OnTimeProcess(int type)override;
};

#endif /* GameLogic_h */
