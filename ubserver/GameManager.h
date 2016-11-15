//
//  GameManager.h
//  ubserver
//  游戏的房间管理(房间会话)
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h


#include <stdio.h>
#include "global.h"
#include "hashmap.h"
#include "client.h"
#include "log.h"
#include "GameLogic.h"
#include "CmdDefined.h"

//mananger
class GameManager
{
    STATIC_CLASS(GameManager);
private:
    HashMap<TABLE_ID, GameLogic*> tab;
public:
    void launch(GameData* data);
    
    void shut(TABLE_ID tid);
    
    void OnPacketHandler(SocketHandler* client);
    
private:
    GameLogic* getLogic(TABLE_ID tid);
};

#endif /* GameManager_h */
