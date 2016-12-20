//
//  ObjectCollect.c
//  ubserver
//
//  Created by MikeRiy on 16/12/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "ObjectCollect.h"

STATIC_CLASS_INIT(ObjectCollect);

RoObject* ObjectCollect::RegObject(USER_T uid, NetNode* node, uint8 type)
{
    auto role = getObject(uid);
    if(role){
        //通知之前的关闭
        role->OnLoginReg(node);
    }else{
        role = new RoObject(uid, type);
        uMap.put(uid, role);
        role->OnLoginReg(node);
    }
    return role;
}

void ObjectCollect::UnRegObject(USER_T uid)
{
    auto role = getObject(uid);
    if(role && role->OnLogoutReg())
    {
        DelObject(uid);
    }
}

RoObject* ObjectCollect::getObject(USER_T uid)
{
    return uMap.getValue(uid);
}

void ObjectCollect::DelObject(USER_T uid)
{
    auto role = uMap.remove(uid);
    SAFE_DELETE(role);
}

void ObjectCollect::SendTo(USER_T uid, ByteArray& packet)
{
    auto role = getObject(uid);
    if(role && role->isLogin())
    {
        role->getSock()->SendPacket(packet);
    }
}

void ObjectCollect::CloseNode(SOCKET_T sockid)
{
    std::vector<RoObject*> list;
    uMap.getValues(list);
    std::vector<RoObject*>::iterator iter;
    //节点关闭，所有登录取消
    for(iter=list.begin();iter!=list.end();++iter)
    {
        RoObject* role = *iter;
        if(role->isLogin() && role->getSockID() == sockid && role->OnLogoutReg())
        {
            DelObject(role->getUID());
        }
    }
}