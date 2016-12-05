
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
void GameManager::OnPacketHandler(SocketHandler* client)
{
    //LOG_DEBUG<<"game handler cmd = "<<client->getCmd()<<LOG_END;
    auto room = tab.getValue(client->getViewId());
    if(client->isNoLogin())
    {
        LOG_DEBUG<<"this is no login fd = "<<client->GetSocketFd()<<LOG_END;
        return;
    }
    //--
    if(room == NULL)
    {
        LOG_DEBUG<<"enter room error: no table"<<client->getViewId()<<LOG_END;
        return;
    };
    //--
    switch(client->getCmd())
    {
        case SERVER_CMD_GAME_ENTER:
            if(PlayerManager::getInstance()->EnterView(client->getUserID(), client->getViewId()))
            {
                room->EnterPlayer(new GamePlayer(client->getUserID(), client));
            }
            break;
        case SERVER_CMD_GAME_EXIT:
            room->ExitPlayer(client->getUserID());
            //世界退出
            PlayerManager::getInstance()->ExitView(client->getUserID());
            break;
        case SERVER_CMD_GAME_SITDOWN:
            //sid
            room->SitDown(client->getUserID(), client->readUint8());
            break;
        case SERVER_CMD_GAME_STAND:
            room->StandUp(client->getUserID());
            break;
        case SERVER_CMD_TIGER_GBET:
            //chip,type
            int8 type = client->readInt8();
            uint32 chips = client->readUint32();
            LOG_DEBUG<<"下注收到: type="<<(type+'\0')<<",chips="<<chips<<LOG_END;
            room->UserBet(client->getUserID(), type, chips);
            break;
    }
}