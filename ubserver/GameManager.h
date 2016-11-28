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
#include "PlayerManager.h"

class GameLogic;

//mananger
class GameManager
{
    STATIC_CLASS(GameManager);
private:
    HashMap<TABLE_ID, GameLogic*> tab;
public:
    GameManager();
    
    void launch(TABLE_ID tid, int ruleid = 0, int type = 0);
    
    void shut(TABLE_ID tid);
    
    void OnPacketHandler(SocketHandler* client);
    
    void SendPacket(USER_T uid, PacketBuffer& packet);
    
    void ExitGame(USER_T uid, TABLE_ID tid);
    
private:
    GameLogic* getLogic(TABLE_ID tid);
};

#endif /* GameManager_h */
