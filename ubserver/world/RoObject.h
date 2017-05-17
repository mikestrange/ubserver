//
//  RoObject.h
//  ubserver
//  人物对象
//  Created by MikeRiy on 16/12/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef RoObject_h
#define RoObject_h

#include "global.h"
#include "ObjectCollect.h"
#include "NetContext.h"

class ObjectCollect;
class HookNode;

class RoObject
{
private:
    USER_T m_uid;
    uint8 m_type;
    TOKEN_T m_regid;
private:
    NetContext* m_context;
public:
    RoObject(USER_T uid, NetContext* context, uint8 type = 0);
    virtual ~RoObject();
public:
    NetContext* getContext()const;
    USER_T getUID()const;
};

#endif /* RoObject_h */
