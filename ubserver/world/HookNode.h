//
//  HookNode.h
//  ubserver
//  服务器挂钩
//  Created by MikeRiy on 16/12/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef HookNode_h
#define HookNode_h

#include "global.h"
#include "NetNode.h"

class HookNode :public NetNode
{
private:
    int32 m_reg_id; //挂钩id
    uint8 m_type;   //挂钩类型
public:
    HookNode();
    virtual ~HookNode();
    void RegType(int32 rid, uint8 type);
public:
    uint8 getType()const;
    int32 getRegID()const;
};

#endif /* HookNode_h */
