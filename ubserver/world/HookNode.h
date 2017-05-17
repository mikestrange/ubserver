//
//  HookNode.h
//  ubserver
//
//  Created by MikeRiy on 16/12/28.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef HookNode_h
#define HookNode_h

#include <stdio.h>
#include "global.h"
#include "NetContext.h"

class HookNode
{
private:
    //服务器编号
    int32 m_hook_id;
    //服务器类型
    int8 m_ser_type;
    //--
    NetContext* m_context;
public:
    HookNode();
    
    virtual~ HookNode();
    
    void Register(int32 idx, NetContext* context, int8 type = 0);
    
    bool isRegister();
    
    void UnRegister();
    
    NetContext* getContext()const;
    
    int32 getSerType()const;
    
    int8 getSerID()const;
};

#endif /* HookNode_h */
