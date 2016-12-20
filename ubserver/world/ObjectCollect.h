//
//  ObjectCollect.h
//  ubserver
//
//  Created by MikeRiy on 16/12/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef ObjectCollect_h
#define ObjectCollect_h

#include "global.h"
#include "RoObject.h"
#include "hashmap.h"
#include "NetNode.h"
#include "array.h"
#include "ByteArray.h"

class RoObject;

class ObjectCollect
{
    STATIC_CLASS(ObjectCollect);
private:
    HashMap<USER_T, RoObject*> uMap;
public:
    //登录处理
    RoObject* RegObject(USER_T uid, NetNode* node, uint8 type = 0);
    //登出(删除)
    void UnRegObject(USER_T uid);
    //获取注册对象
    RoObject* getObject(USER_T uid);
    //关闭服务器连接时候
    void CloseNode(SOCKET_T sockid);
    //挂钩通知
    void SendTo(USER_T uid, ByteArray& packet);
private:
    void DelObject(USER_T uid);
};

#endif /* ObjectCollect_h */
