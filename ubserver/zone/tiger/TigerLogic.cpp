//
//  GameLogic.c
//  ubserver
//
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "TigerLogic.h"

TigerLogic::TigerLogic()
:m_game_state(TIGER_GAME_STOP_STATUS)
,start_time(0)
,pot_totals(0)
{
    m_clock.setEventDelegate(this);
    CleanPotBets();
};

TigerLogic::~TigerLogic()
{
    m_players.eachValues([](GamePlayer* v)
    {
        SAFE_DELETE(v);
    });
}

void TigerLogic::OnPacketHandler(MsgHandler* packet)
{
    switch(packet->getCmd())
    {
        case SERVER_CMD_GAME_ENTER:
            EnterHome(packet->readUInt());
        case SERVER_CMD_GAME_EXIT:
            LeaveHome(packet->readUInt());
        case SERVER_CMD_TIGER_GBET:
            int8 type = packet->readByte();
            uint32 chips = packet->readUInt();
            UserBet(packet->readUInt(), type, chips);
            break;
    }
}

//进入房间处理
void TigerLogic::EnterHome(USER_T uid)
{
    if(m_players.length() == MAX_USER)
    {
        EnterRep(1, uid, NULL);
        LOG_INFO("enter room error: room=%d is full", getTableID());
        return;
    }
    if(m_players.has(uid))
    {
        EnterRep(2, uid, NULL);
        LOG_INFO("enter room error uid=%d is in this room", uid);
        return;
    }
    //捕获用户数据
    UserObj *obj = new UserObj(uid);
    if(obj->result())
    {
        auto player = new GamePlayer(obj);
        LOG_INFO("enter room ok: room =%d uid=%d", getTableID(), player->getUserID());
        m_players.put(player->getUserID(), player);
        player->OnEnter();
        //通知个人获取房间数据
        EnterRep(0, uid, player);
        //是否开始游戏
        GameStart();
    }else{
        SAFE_DELETE(obj);
        EnterRep(3, uid, NULL);
    }
}

//退出房间
void TigerLogic::LeaveHome(USER_T uid)
{
    GamePlayer* player = m_players.remove(uid);
    if(player)
    {
        LOG_DEBUG("exit room ok: room=%d uid=%d", getTableID(), uid);
        player->OnExit();
        ExitRep(0, uid);
    }else{
        ExitRep(1, uid);
    }
    SAFE_DELETE(player);
}


//game
void TigerLogic::GameStart()
{
    //没有人或者没停止则不开始
    if(m_players.empty() || m_game_state != TIGER_GAME_STOP_STATUS)
    {
        return;
    }
    LOG_DEBUG("Start game room=%d players=%d", getTableID(), m_players.length());
    //通知
    StartRep();
    //10秒结束
    m_game_state = TIGER_GAME_START_STATUS;
    start_time = TimeUtil::GetSTimer();
    m_clock.start(CHIP_TIME, 1, TIGER_TIMER_START);
}

void TigerLogic::GameOver()
{
    LOG_DEBUG("End game room=%d players=%d", getTableID(), m_players.length());
    //结果
    uint8 index = Math::Random(1, MAX_BET);      //落点位置
    uint8 type = TIGER_TYPE_LIST[index - 1];     //类型
    uint8 mult = TIGER_BET_LIST[index - 1];     //倍数
    LOG_DEBUG("game result index=%d type=%d mult=%d", index, type, mult);
    //发送结果
    ResultRep(index, type, mult);
    //清空池
    CleanPotBets();
    //如果有人,等待开始
    if(m_players.empty())
    {
         m_game_state = TIGER_GAME_STOP_STATUS;
    }else{
        m_game_state = TIGER_GAME_WAIT_STATUS;
        start_time = TimeUtil::GetSTimer();
        m_clock.start(WAIT_TIME, 1, TIGER_TIMER_STOP);
    }
}

//玩家下注(不在房间的玩家，不能发送) 玩家，倍数，类型
void TigerLogic::UserBet(USER_T uid, uint8 type, uint32 chips)
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
            BetRep(player, type, chips);
        }
    }
}

void TigerLogic::CleanPotBets()
{
    pot_totals = 0;
    for(int i = 0; i < MAX_TYPE ; i++)
    {
        pot_list[i] = 0;
    }
}

void TigerLogic::OnTimeProcess(int type)
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

//reps
//进入房间发送
void TigerLogic::EnterRep(int8 code, USER_T uid, GamePlayer* player)
{
    //通知房管
    //ZoneManager::getInstance()->OnEnterHandler(code, uid, getTableID());
    //处理
    if(code != 0)
    {
        MsgHandler packet;
        packet.setBegin(SERVER_CMD_GAME_ENTER_ERROR);
        packet.writeByte(code);
        packet.WriteEnd();
        return;
    }
    //自己返回
    MsgHandler game_data;
    game_data.setBegin(SERVER_CMD_GAME_ROOM_DATA);
    //必须的三个
    game_data.writeInt(getTableID());
    game_data.writeInt(getGameType());
    game_data.writeInt(getRuleID());
    //下注时间
    game_data.writeByte(bet_time);
    //单池最大下注
    game_data.writeInt(max_chip);
    //游戏状态
    game_data.writeByte(m_game_state);
    //自己钱数
    game_data.writeLong(player->getUserMoney());
    //剩余时间
    if(m_game_state == TIGER_GAME_START_STATUS)
    {
        TIME_T d_time = (TimeUtil::GetSTimer() - start_time);
        game_data.writeByte(bet_time - d_time);
    }else{
        TIME_T d_time = (TimeUtil::GetSTimer() - start_time);
        game_data.writeByte(wait_time - d_time);
    }
    game_data.WriteEnd();
    ZoneRep::SendTo(player->getUserID(), game_data);
    //通知其他玩家此人进入房间(自己也通知)
    MsgHandler packet;
    packet.setBegin(SERVER_CMD_GAME_ENTER);
    packet.writeInt(player->getUserID());
    packet.WriteEnd();
    m_players.eachValues([&packet](GamePlayer* value)
                         {
                             ZoneRep::SendTo(value->getUserID(), packet);
                         });
}

//退出房间发送
void TigerLogic::ExitRep(int8 code, USER_T uid)
{
    //通知房管
    //ZoneManager::getInstance()->OnExitHandler(code, uid, getTableID());
    //
    MsgHandler packet;
    packet.setBegin(SERVER_CMD_GAME_EXIT);
    packet.writeByte(code);
    packet.writeInt(uid);
    packet.WriteEnd();
    if(code == 0)
    {
        m_players.eachValues([&packet,&uid](GamePlayer* value)
                             {
                                 ZoneRep::SendTo(value->getUserID(), packet);
                             });
    }
}

//开始通知
void TigerLogic::StartRep()
{
    MsgHandler packet;
    packet.setBegin(SERVER_CMD_TIGER_GSTART);
    packet.WriteEnd();
    m_players.eachValues([&packet](GamePlayer* player)
                         {
                             //清理所有玩家的下注
                             player->CleanBets();
                             //通知玩家开始
                             ZoneRep::SendTo(player->getUserID(), packet);
                         });
}

//下注推送
void TigerLogic::BetRep(GamePlayer* player, uint8 type, uint32 chips)
{
    //自己通知
    MsgHandler self_rep;
    self_rep.setBegin(SERVER_CMD_TIGER_GBET);
    self_rep.writeByte(type);
    self_rep.writeUInt(player->getBetTotals(type));
    self_rep.writeLong(player->getUserMoney());
    self_rep.WriteEnd();
    ZoneRep::SendTo(player->getUserID(), self_rep);
    //总池增益
    pot_list[type - 1] += chips;
    pot_totals += chips;
    uint32 totals = pot_list[type - 1];
    //池通知
    MsgHandler packet;
    packet.setBegin(SERVER_CMD_TIGER_GPOT_CHIPS);
    packet.writeByte(type);
    packet.writeUInt(totals);
    packet.WriteEnd();
    m_players.eachValues([&packet](GamePlayer* value)
                         {
                             ZoneRep::SendTo(value->getUserID(), packet);
                         });
}

//游戏结果
void TigerLogic::ResultRep(uint8 index, uint8 type, uint8 mult)
{
    //TOP ONE 赢最多
    uint32 first_user = 0;
    uint32 max_value = 0;
    HashMap<USER_T, GamePlayer*>::Iterator iter;
    //自己的游戏结果
    for(iter=m_players.begin();iter!=m_players.end();++iter)
    {
        GamePlayer* player = iter->second;
        uint32 change_value = player->Reslut(type, mult);
        if(change_value > 0 &&change_value > max_value)
        {
            max_value = change_value;
            first_user = player->getUserID();
        };
        MsgHandler packet;
        packet.setBegin(SERVER_CMD_TIGER_GSTOP);
        packet.writeByte(index);
        packet.writeByte(type);
        packet.writeByte(mult);
        packet.writeInt(change_value);
        packet.writeLong(player->getUserMoney());
        packet.WriteEnd();
        ZoneRep::SendTo(player->getUserID(), packet);
    }
    //第一名通知所有玩家
    if(first_user > 0)
    {
        MsgHandler win_packet;
        win_packet.setBegin(SERVER_CMD_TIGER_GRESULT);
        win_packet.writeInt(first_user);
        win_packet.writeInt(max_value);
        win_packet.WriteEnd();
        m_players.eachValues([&win_packet](GamePlayer* value)
                             {
                                 ZoneRep::SendTo(value->getUserID(), win_packet);
                             });
    }
}
