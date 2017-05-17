//
//  ObjectCollect.c
//  ubserver
//
//  Created by MikeRiy on 16/12/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "ObjectCollect.h"

STATIC_CLASS_INIT(ObjectCollect);

RoObject* ObjectCollect::RegObject(USER_T uid, RoObject* player)
{
    //删除之前的
    RoObject* before = UnRegObject(uid);
    //注册
    this->put(uid, player);
    //之前的信息
    return before;
}

RoObject* ObjectCollect::UnRegObject(USER_T uid)
{
    return remove(uid);
}

RoObject* ObjectCollect::getObject(USER_T uid)
{
    return getValue(uid);
}

void ObjectCollect::DelObject(USER_T uid)
{
    RoObject* player = remove(uid);
    SAFE_DELETE(player);
}

void ObjectCollect::SendTo(USER_T uid, ByteArray& packet)
{
    RoObject* player = getObject(uid);
    if(player)
    {
        player->getContext()->SendPacket(packet);
    }
}

void ObjectCollect::CloseObject(NetContext* context)
{
    std::vector<RoObject*> list;
    getValues(list);
    std::vector<RoObject*>::iterator iter;
    //节点关闭，所有登录取消
    for(iter=list.begin();iter!=list.end();++iter)
    {
        if((*iter)->getContext() == context)
        {
            DelObject((*iter)->getUID());
        }
    }
}

void ObjectCollect::SendToAll(ByteArray& packet)
{
    HashMap<USER_T, RoObject*>::Iterator iter;
    for(iter = begin(); iter!= end(); ++iter)
    {
        iter->second->getContext()->SendPacket(packet);
    }
}

void ObjectCollect::SendToAll(USER_T uids[], int count, ByteArray& packet)
{
    for(int i = 0; i < count; i++)
    {
        RoObject* player = getValue(uids[i]);
        if(player)
        {
            player->getContext()->SendPacket(packet);
        }
    }
}