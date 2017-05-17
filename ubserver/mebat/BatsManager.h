//
//  BatsManager.h
//  ubserver
//  战斗逻辑管理
//  Created by MikeRiy on 17/1/5.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef BatsManager_h
#define BatsManager_h

#include "global.h"
#include "hashmap.h"
#include "BatLogic.h"
#include "BatPlayer.h"
#include "SocketHandler.h"

class BatsManager
{
    STATIC_CLASS(BatsManager);
private:
    uint32 current_batid;
    HashMap<uint32, BatLogic*> batMap;
public:
    BatsManager();
    //启动战场
    uint32 create_battle();
    int finish_battler(uint32 bat_id);
    //加入和退出
    int join_battle(uint32 bat_id, BatPlayer* player);
    int exit_battle(uint32 bat_id, USER_T uid);
    //处理
    void OnPacketHandler(SocketHandler* packet);
};

#endif /* BatsManager_h */
