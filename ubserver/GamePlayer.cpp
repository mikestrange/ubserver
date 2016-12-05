//
//  GamePlayer.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GamePlayer.h"

GamePlayer::GamePlayer(USER_T uid, PacketBuffer* bytes)
:GameSeat(uid)
,user_money(100000)
,bet_totals(0)
{
    ReadFor(*bytes);
    CleanBets();
}

GamePlayer::~GamePlayer()
{
    
}

void GamePlayer::WriteTo(WriteBytes& bytes)
{
    
};

void GamePlayer::ReadFor(ReadBytes& bytes)
{
    
};

void GamePlayer::OnEnter()
{
    
};

void GamePlayer::OnExit()
{
    
};

uint32 GamePlayer::AddBet(uint8 type, uint32 chips)
{
    if(type > MAX_TYPE) return 0;
    uint32 value = bet_list[type - 1];
    LOG_DEBUG<<"下注Begin: "<<parseByte(type)<<",money="<<user_money<<",chip="<<chips<<",prev="<<value<<LOG_END;
    uint32 sub_value = chips - value;
    if(sub_value <= 0)
    {
        LOG_DEBUG<<"下注金币少于之前:chips="<<chips<<",old="<<value<<LOG_END;
        return 0;
    }
    if(sub_value > user_money)
    {
        LOG_DEBUG<<"下注金币不足:"<<user_money<<","<<sub_value<<LOG_END;
        return 0;
    }
    bet_totals += sub_value;    //总下注
    user_money -= sub_value;    //下注之后剩余金币
    bet_list[type - 1] = chips;
    LOG_DEBUG<<"下注成功: uid="<<getUserID()<<",money="<<user_money<<",sub="<<sub_value<<LOG_END;
    return sub_value;
}

void GamePlayer::CleanBets()
{
    bet_totals = 0;
    for(int i = 0; i < MAX_TYPE ; i++)
    {
        bet_list[i] = 0;
    }
}

uint64 GamePlayer::getUserMoney()const
{
    return user_money;
}

bool GamePlayer::isNoBet()const
{
    return bet_totals == 0;
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
        user_money += win_money;
    }
    //写入数据库，扣除还是收益
    LOG_DEBUG<<"玩家结算 收益="<<win_money<<",金币="<<user_money<<",uid="<<getUserID()<<LOG_END;
    return win_money;
}