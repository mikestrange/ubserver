
//
//  GameManager.c
//  ubserver
//
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GameManager.h"

STATIC_CLASS_INIT(GameManager);


void GameManager::launch(GameData* data)
{
    if(tab.has(data->table_id))
    {
        std::cout<<"has room id launch "<<data->table_id<<std::endl;
        SAFE_DELETE(data);
        return;
    }
    auto logic = new GameLogic();
    tab.put(data->table_id, logic);
    logic->OnLaunch(data);
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


void GameManager::OnPacketHandler(SocketHandler* client)
{
    LOG_DEBUG<<"game handler cmd = "<<client->getCmd()<<LOG_END;
    auto room = tab.getValue(client->getViewId());
    if(!room)
    {
        return;
    };
    switch(client->getCmd())
    {
        case SERVER_CMD_GAME_ENTER:
            room->EnterPlayer(new GamePlayer(client));
            break;
        case SERVER_CMD_GAME_EXIT:
            room->ExitPlayer(client->readUint32());
            break;
        case SERVER_CMD_GAME_SITDOWN:
            room->SitDown(client->readUint32(), client->readUint8());
            break;
        case SERVER_CMD_GAME_STAND:
            room->StandUp(client->readUint32());
            break;
    }
    
}