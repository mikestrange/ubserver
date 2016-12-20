//
//  LogicBase.c
//  ubserver
//
//  Created by MikeRiy on 16/12/13.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "LogicBase.h"

LogicBase::LogicBase()
:m_table_id(0)
,m_game_type(0)
,m_rule_id(0)
{
    
}

LogicBase::~LogicBase()
{
    
}

void LogicBase::OnExit()
{
    
}

void LogicBase::OnLaunch(TABLE_ID table_id, int gtype, int rule_id)
{
    m_table_id = table_id;
    m_game_type = gtype;
    m_rule_id = rule_id;
}

TABLE_ID LogicBase::getTableID()const
{
    return m_table_id;
};

int LogicBase::getGameType()const
{
    return m_game_type;
};

int LogicBase::getRuleID()const
{
    return m_rule_id;
};