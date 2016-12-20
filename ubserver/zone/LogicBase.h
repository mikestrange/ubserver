//
//  LogicBase.h
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef LogicBase_h
#define LogicBase_h

#include <stdio.h>
#include "global.h"
#include "MsgHandler.h"

class LogicBase
{
private:
    TABLE_ID m_table_id;
    int m_game_type;
    int m_rule_id;
public:
    LogicBase();
    
    virtual ~LogicBase();
    
    virtual void OnLaunch(TABLE_ID table_id, int gtype = 0, int rule_id = 0);
    
    virtual void OnExit();
    
    virtual void OnPacketHandler(MsgHandler* packet)=0;
    
public:
    TABLE_ID getTableID()const;
    int getGameType()const;
    int getRuleID()const;
};

#endif /* LogicBase_h */
