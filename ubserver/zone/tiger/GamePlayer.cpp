//
//  GamePlayer.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GamePlayer.h"

GamePlayer::GamePlayer(UserObj* obj)
:data(obj)
,bet_totals(0)
{
    CleanBets();
}

GamePlayer::~GamePlayer()
{
    
}

void GamePlayer::OnEnter()
{
    
};

void GamePlayer::OnExit()
{
    
};

USER_T GamePlayer::getUserID()const
{
    return data->user_id;
}

bool GamePlayer::AddBet(uint8 type, uint32 chips)
{
    if(type==0 || type > MAX_TYPE || chips <= 0) return false;
    if(getUserMoney() >= chips)
    {
        bet_list[type - 1] += chips;
        data->update_money(-chips);
        bet_totals += chips;
        //--
        LOG_DEBUG("bet ok: type=%d money=%lld chip=%d",type,getUserMoney(),chips);
        return true;
    }else{
        LOG_DEBUG("no money=%lld chip=%d",getUserMoney(),chips);
    }
    return false;
}

void GamePlayer::CleanBets()
{
    bet_totals = 0;
    for(int i = 0; i < MAX_TYPE ; i++)
    {
        bet_list[i] = 0;
    }
}

int64 GamePlayer::getUserMoney()const
{
    return data->money;
}

bool GamePlayer::isNoBet()const
{
    return bet_totals == 0;
}

uint32 GamePlayer::getBetTotals(uint8 type)const
{
    return bet_list[type - 1];
}

uint32 GamePlayer::Reslut(uint8 type, int32 mult)
{
    //未下注
    if(isNoBet()) return 0;
    //win
    int32 win_money = bet_list[type - 1]*mult;
    //赢了
    if(win_money > 0)
    {
        data->update_money(win_money);
    }
    //写入数据库，扣除还是收益
    LOG_DEBUG("玩家结算 收益=%d money=%lld uid=%d",win_money,getUserMoney(),getUserID());
    return win_money;
}