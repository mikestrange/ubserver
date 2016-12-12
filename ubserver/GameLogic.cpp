//
//  GameLogic.c
//  ubserver
//
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GameLogic.h"

GameLogic::GameLogic()
:m_table_id(0)
,m_game_state(TIGER_GAME_STOP_STATUS)
,start_time(0)
,pot_totals(0)
{
    m_clock.setEventDelegate(this);
    CleanPotBets();
};

GameLogic::~GameLogic()
{
    m_players.eachValues([](GamePlayer* v)
    {
        SAFE_DELETE(v);
    });
}

void GameLogic::OnLaunch(TABLE_ID table_id)
{
    m_table_id = table_id;
}

void GameLogic::OnExit()
{
    
}

//packet
int GameLogic::EnterPlayer(GamePlayer* player)
{
    if(m_players.length() == MAX_USER)
    {
        SAFE_DELETE(player);
        Log::Info("enter room error: room=%d is full", m_table_id);
        return 2;
    }
    if(m_players.has(player->getUserID()))
    {
        SAFE_DELETE(player);
        Log::Info("enter room error uid=%d is in this room", player->getUserID());
        return 1;
    }
    m_players.put(player->getUserID(), player);
    player->OnEnter();
    Log::Info("enter room ok: room =%d uid=", m_table_id, player->getUserID());
    //通知个人获取房间数据
    PacketBuffer game_data;
    game_data.setBegin(SERVER_CMD_GAME_ROOM_DATA);
    game_data.WriteBegin();
    game_data.writeInt32(m_table_id);
    game_data.writeInt8(bet_time);
    game_data.writeInt32(max_chip);
    game_data.writeInt8(m_game_state);
    game_data.writeInt64(player->getUserMoney());
    if(m_game_state == TIGER_GAME_START_STATUS){
        TIME_T d_time = (TimeUtil::GetTimer() - start_time);
        game_data.writeInt8((bet_time - d_time)/1000);
    }else{
        TIME_T d_time = (TimeUtil::GetTimer() - start_time);
        game_data.writeInt8((wait_time - d_time)/1000);
    }
    game_data.WriteEnd();
    GameManager::getInstance()->SendPacket(player->getUserID(), game_data);
    //通知其他玩家此人进入房间
    PacketBuffer packet;
    packet.setBegin(SERVER_CMD_GAME_ENTER);
    packet.WriteBegin();
    packet.writeInt32(player->getUserID());
    packet.WriteEnd();
    m_players.eachValues([&packet,&player](GamePlayer* value)
                         {
                             if(value->getUserID() != player->getUserID()){
                                  GameManager::getInstance()->SendPacket(value->getUserID(), packet);
                             }
                         });
    //是否开始游戏
    GameStart();
    return 0;
}

int GameLogic::ExitPlayer(USER_T uid)
{
    GamePlayer* player = m_players.remove(uid);
    if(player)
    {
        SEAT_T seat_id = player->StandUp();
        if(seat_id > 0)
        {
            //m_seats.remove(seat_id);
        }
        Log::Debug("exit room ok: room=%d uid=%d",m_table_id, uid);
        player->OnExit();
        //通知其他玩家
        PacketBuffer packet;
        packet.setBegin(SERVER_CMD_GAME_EXIT);
        packet.WriteBegin();
        packet.writeInt32(uid);
        packet.WriteEnd();
        m_players.eachValues([&packet,&uid](GamePlayer* value)
                             {
                                 if(value->getUserID() != uid)
                                 {
                                     GameManager::getInstance()->SendPacket(value->getUserID(), packet);
                                 }
                             });
        return 0;
    }
    SAFE_DELETE(player);
    return 1;
};

int GameLogic::SitDown(USER_T uid, SEAT_T sid)
{
//    if(m_seats.length() == MAX_SEAT)
//    {
//        LOG_DEBUG<<"sitdown error: room = "<<m_table_id<<" seat is full"<<LOG_END;
//        return 3;
//    }
//    if(m_seats.has(sid))
//    {
//        LOG_DEBUG<<"sitdown error: room = "<<m_table_id<<" msg = has user, seat = "<<UNIT::parseInt(sid)<<LOG_END;
//        return 2;
//    };
//    GamePlayer* player = m_players.getValue(uid);
//    if(player && player->isStand())
//    {
//        player->SitDown(sid);
//        m_seats.put(sid, uid);
//        LOG_DEBUG<<"sitdown ok: room = "<<m_table_id<<" seat = "<<UNIT::parseInt(sid)<<LOG_END;
//        //---
//        return 0;
//    }
    return 1;
};

int GameLogic::StandUp(USER_T uid)
{
//    GamePlayer* player = m_players.getValue(uid);
//    if(player)
//    {
//        SEAT_T seat_id = player->StandUp();
//        if(seat_id > 0)
//        {
//            m_seats.remove(seat_id);
//            LOG_DEBUG<<"stand ok: room "<<m_table_id<<" seat = "<<UNIT::parseInt(seat_id)<<" uid = "<<uid<<LOG_END;
//            return 0;
//        }
//        return 2;
//    }
    return 1;
};


//game
void GameLogic::GameStart()
{
    if(m_players.empty() || m_game_state != TIGER_GAME_STOP_STATUS)
    {
        return;
    }
    //通知房间所有玩家
    PacketBuffer packet;
    packet.setBegin(SERVER_CMD_TIGER_GSTART);
    packet.WriteBegin();
    packet.WriteEnd();
    m_players.eachValues([&packet](GamePlayer* player)
                       {
                           player->CleanBets();
                           GameManager::getInstance()->SendPacket(player->getUserID(), packet);
                       });
    //10秒结束
    m_game_state = TIGER_GAME_START_STATUS;
    start_time = TimeUtil::GetTimer();
    m_clock.start(CHIP_TIME, 1, TIGER_TIMER_START);
    //
    Log::Info("start game room=%d count=%d", m_table_id, m_players.length());
}


void GameLogic::GameOver()
{
    Log::Info("end game room=%d count=%d", m_table_id, m_players.length());
    m_game_state = TIGER_GAME_STOP_STATUS;
    //清空池
    CleanPotBets();
    //结果
    uint8 index = Math::Random(1, MAX_BET);      //落点位置
    uint8 type = TIGER_TYPE_LIST[index - 1];     //类型
    uint8 mult = TIGER_BET_LIST[index - 1];     //倍数
    //结果啊
    Log::Info("game result index=%d type=%d mult=%d", index, type, mult);
    //赢最多
    uint32 first_user = 0;
    uint32 max_value = 0;
    //
    HashMap<USER_T, GamePlayer*>::Iterator iter;
    //自己的游戏结果
    for(iter=m_players.begin();iter!=m_players.end();++iter)
    {
        uint32 change_value = iter->second->Reslut(type, mult);
        if(change_value > 0 &&change_value > max_value)
        {
            max_value = change_value;
            first_user = iter->second->getUserID();
        };
        PacketBuffer packet;
        packet.setBegin(SERVER_CMD_TIGER_GSTOP);
        packet.WriteBegin();
        packet.writeInt8(index);
        packet.writeInt8(type);
        packet.writeInt8(mult);
        packet.writeInt32(change_value);
        packet.writeInt64(iter->second->getUserMoney());
        packet.WriteEnd();
        GameManager::getInstance()->SendPacket(iter->second->getUserID(), packet);
    }
    //第一名通知所有玩家
    if(first_user > 0)
    {
        PacketBuffer win_packet;
        win_packet.setBegin(SERVER_CMD_TIGER_GRESULT);
        win_packet.WriteBegin();
        win_packet.writeInt32(first_user);
        win_packet.writeInt32(max_value);
        win_packet.WriteEnd();
        m_players.eachValues([&win_packet](GamePlayer* player)
                             {
                                 GameManager::getInstance()->SendPacket(player->getUserID(), win_packet);
                             });
    }
    //如果有人，等待开始
    if(!m_players.empty())
    {
        m_game_state = TIGER_GAME_WAIT_STATUS;
        start_time = TimeUtil::GetTimer();
        m_clock.start(WAIT_TIME, 1, TIGER_TIMER_STOP);
    }
}


//玩家下注(不在房间的玩家，不能发送) 玩家，倍数，类型
void GameLogic::UserBet(USER_T uid, uint8 type, uint32 chips)
{
    if(type == 0 || type > MAX_TYPE) return;
    //
    if(m_game_state == TIGER_GAME_START_STATUS)
    {
        //超过上限
        if(pot_list[type - 1] + chips > max_chip)
        {
            return;
        }
        GamePlayer* player = m_players.getValue(uid);
        if(player && player->AddBet(type, chips))
        {
            PacketBuffer packet;
            packet.setBegin(SERVER_CMD_TIGER_GBET);
            packet.WriteBegin();
            packet.writeInt8(type);
            packet.writeUint32(player->getBetTotals(type));
            packet.writeInt64(player->getUserMoney());
            packet.WriteEnd();
            GameManager::getInstance()->SendPacket(uid, packet);
            //--
            AddPotBet(type, chips);
        }
    }
}

void GameLogic::OnTimeProcess(int type)
{
    switch(type)
    {
        case TIGER_TIMER_START:
            GameOver();
            break;
        case TIGER_TIMER_STOP:
            m_game_state = TIGER_GAME_STOP_STATUS;
            GameStart();
            break;
    }
};


void GameLogic::AddPotBet(uint8 type, uint32 chips)
{
    pot_list[type - 1] += chips;
    pot_totals += chips;
    uint32 totals = pot_list[type - 1];
    //池通知
    PacketBuffer packet;
    packet.setBegin(SERVER_CMD_TIGER_GPOT_CHIPS);
    packet.WriteBegin();
    packet.writeInt8(type);
    packet.writeUint32(totals);
    packet.WriteEnd();
    m_players.eachValues([&packet](GamePlayer* player)
                         {
                             GameManager::getInstance()->SendPacket(player->getUserID(), packet);
                         });
}

void GameLogic::CleanPotBets()
{
    pot_totals = 0;
    for(int i = 0; i < MAX_TYPE ; i++)
    {
        pot_list[i] = 0;
    }
}



