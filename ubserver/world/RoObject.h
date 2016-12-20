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
#include "NetNode.h"

class ObjectCollect;
class HookNode;

class RoObject
{
private:
    USER_T m_uid;
    uint8 m_type;
    TOKEN_T m_regid;
    bool is_login;
private:
    NetNode* m_node;
public:
    RoObject(USER_T uid, uint8 type = 0);
    virtual ~RoObject();
private:
    friend class ObjectCollect;
    void OnLoginReg(NetNode* node);
    bool OnLogoutReg();
public:
    bool isLogin()const;
    NetNode* getSock()const;
    SOCKET_T getSockID();
    USER_T getUID()const;
};

#endif /* RoObject_h */
