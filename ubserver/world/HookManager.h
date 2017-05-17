//
//  HookManager.h
//  ubserver
//
//  Created by MikeRiy on 16/12/28.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef HookManager_h
#define HookManager_h

#include <stdio.h>
#include "HookNode.h"
#include "hashmap.h"

class HookManager : private HashMap<int, HookNode*>
{
    STATIC_CLASS(HookManager);
public:
    //注册一个节点，必定成功
    bool Register(int32 idx, NetContext* context, int8 type);
    //取消一个注册节点
    void UnRegister(int32 idx);
    //一个连接取消所有节点
    void UnRegister(NetContext* context);
public:
    //通知节点
    void SendToHook(int32 idx, ByteArray& packet);
    //通知同类型的节点
    void SendToHook(ByteArray& packet, int8 type = 0);
};

#endif /* HookManager_h */
