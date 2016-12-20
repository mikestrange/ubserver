//
//  HookNode.c
//  ubserver
//
//  Created by MikeRiy on 16/12/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "HookNode.h"

HookNode::HookNode()
:m_reg_id(0)
,m_type(0){}

HookNode::~HookNode()
{
    
}

void HookNode::RegType(int32 rid, uint8 type)
{
    m_reg_id = rid;
    m_type = type;
}

uint8 HookNode::getType()const
{
    return m_type;
}


int32 HookNode::getRegID()const
{
    return m_reg_id;
}