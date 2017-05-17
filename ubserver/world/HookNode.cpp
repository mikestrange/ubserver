//
//  HookNode.c
//  ubserver
//
//  Created by MikeRiy on 16/12/28.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "HookNode.h"


HookNode::HookNode()
{
    UnRegister();
}

HookNode::~HookNode()
{
    
}

void HookNode::Register(int32 idx, NetContext* context, int8 type)
{
    m_hook_id = idx;
    m_ser_type = type;
    m_context = context;
}

bool HookNode::isRegister()
{
    return m_hook_id > 0;
}

void HookNode::UnRegister()
{
    m_ser_type = 0;
    m_hook_id = 0;
    m_context = NULL;
}

NetContext* HookNode::getContext()const
{
    return m_context;
}

int32 HookNode::getSerType()const
{
    return m_ser_type;
}

int8 HookNode::getSerID()const
{
    return m_hook_id;
}