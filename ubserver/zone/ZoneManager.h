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
#include "log.h"

#include "CmdDefined.h"
#include "LogicBase.h"
#include "TigerLogic.h"
#include "UserObj.h"
#include "SocketHandler.h"

class LogicBase;
class TigerLogic;

//mananger
class ZoneManager
{
    STATIC_CLASS(ZoneManager);
private:
    HashMap<TABLE_ID, LogicBase*> tab;
public:
    ZoneManager();
    //启动房间
    void launch(TABLE_ID tid, LogicBase* target, int gtype = 0, int rid = 0);
    //关闭房间
    void shut(TABLE_ID tid);
    //分发(房间和用户)
    void OnPacketHandler(SocketHandler* packet);
};

#endif /* GameManager_h */
