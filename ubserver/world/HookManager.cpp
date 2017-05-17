
//
//  HookManager.c
//  ubserver
//
//  Created by MikeRiy on 16/12/28.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "HookManager.h"

STATIC_CLASS_INIT(HookManager);


bool HookManager::Register(int32 idx, NetContext* context, int8 type)
{
    HookNode* node = getValue(idx);
    if(!node)
    {
        node = this->put(idx, new HookNode());
        LOG_INFO("add hook:id=%d type=%d", idx, type);
    }else{
        LOG_INFO("cancel hook:id=%d type=%d to id=%d type=%d", node->getSerID(), node->getSerType(), idx, type);
    }
    //存在的话会替换之前的(并不会提醒之前的)
    node->Register(idx, context, type);
    return true;
}

void HookManager::UnRegister(int32 idx)
{
    HookNode* node = remove(idx);
    if(node)
    {
        node->UnRegister();
        SAFE_DELETE(node);
        LOG_INFO("remove hook:id=%d", idx);
    }
}

void HookManager::UnRegister(NetContext* context)
{
    std::vector<HookNode*> list;
    getValues(list);
    std::vector<HookNode*>::iterator iter;
    for(iter = list.begin(); iter!= list.end(); iter++)
    {
        if((*iter)->getContext() == context)
        {
            UnRegister((*iter)->getSerID());
        }
    }
}

void HookManager::SendToHook(int32 idx, ByteArray& packet)
{
    HookNode* node = getValue(idx);
    if(node)
    {
        node->getContext()->SendPacket(packet);
    }else{
        LOG_WARN("no hook id = %d", idx);
    }
}

void HookManager::SendToHook(ByteArray& packet, int8 type)
{
    HashMap<int, HookNode*>::Iterator iter;
    for(iter = begin(); iter!= end(); ++iter)
    {
        if(iter->second->getSerType() == type)
        {
            iter->second->getContext()->SendPacket(packet);
        }
    }
}