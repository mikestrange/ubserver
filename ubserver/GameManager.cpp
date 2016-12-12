
//
//  GameManager.c
//  ubserver
//
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GameManager.h"

STATIC_CLASS_INIT(GameManager);

GameManager::GameManager()
{
    launch(101);
}

void GameManager::launch(TABLE_ID table_id, int ruleid, int type)
{
    if(tab.has(table_id))
    {
        return;
    }
    auto logic = new GameLogic();
    tab.put(table_id, logic);
    logic->OnLaunch(table_id);
}


void GameManager::shut(TABLE_ID tid)
{
    auto logic = tab.remove(tid);
    if(logic)
    {
        logic->OnExit();
    }
    SAFE_DELETE(logic);
}

void GameManager::SendPacket(USER_T uid, PacketBuffer& packet)
{
    PlayerManager::getInstance()->SendPlayer(uid, packet);
}

void GameManager::ExitGame(USER_T uid, TABLE_ID tid)
{
    auto room = tab.getValue(tid);
    if(room)
    {
        room->ExitPlayer(uid);
    }
}
//
void GameManager::OnPacketHandler(GameUser* client)
{
    auto room = tab.getValue(client->getViewId());
    if(client->isNoLogin())
    {
        Log::Warn("this is no login fd = %d", client->getSockID());
        return;
    }
    //--
    if(room == NULL)
    {
        Log::Warn("enter room error: no table %d",client->getViewId());
        return;
    };
    //--
    USER_T uid = client->getPlayer()->getUserID();
    switch(client->getCmd())
    {
        case SERVER_CMD_GAME_ENTER:
            //获取用户数据
            OnEnter(room, client);
            break;
        case SERVER_CMD_GAME_EXIT:
            room->ExitPlayer(uid);
            //世界退出
            PlayerManager::getInstance()->ExitView(uid);
            break;
        case SERVER_CMD_GAME_SITDOWN:
            //sid
            room->SitDown(uid, client->readUint8());
            break;
        case SERVER_CMD_GAME_STAND:
            room->StandUp(uid);
            break;
        case SERVER_CMD_TIGER_GBET:
            //chip,type
            int8 type = client->readInt8();
            uint32 chips = client->readUint32();
            room->UserBet(uid, type, chips);
            break;
    }
}

void GameManager::OnEnter(GameLogic* room, GameUser* client)
{
    USER_T uid = client->getPlayer()->getUserID();
    UserObj *obj = new UserObj(uid);
    //--
    if(obj->result())
    {
        if(PlayerManager::getInstance()->EnterView(uid, client->getViewId()))
        {
            room->EnterPlayer(new GamePlayer(uid, obj));
        }else{
            SAFE_DELETE(obj);
        }
    }else{
        SAFE_DELETE(obj);
    }
}