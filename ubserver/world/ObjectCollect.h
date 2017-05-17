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
#include "NetContext.h"
#include "array.h"
#include "ByteArray.h"

class RoObject;
class NetContext;

class ObjectCollect : private HashMap<USER_T, RoObject*>
{
    STATIC_CLASS(ObjectCollect);
public:
    //登录处理
    RoObject* RegObject(USER_T uid, RoObject* player);
    //登出(删除)
    RoObject* UnRegObject(USER_T uid);
    //获取注册对象
    RoObject* getObject(USER_T uid);
    //关闭服务器连接时候
    void CloseObject(NetContext* context);
public:
    //发送个人
    void SendTo(USER_T uid, ByteArray& packet);
    //发送所有
    void SendToAll(ByteArray& packet);
    //发送部分
    void SendToAll(USER_T uids[], int count, ByteArray& packet);
private:
    void DelObject(USER_T uid);
};

#endif /* ObjectCollect_h */
