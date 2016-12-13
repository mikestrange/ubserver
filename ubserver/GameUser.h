//
//  GameUser.h
//  ubserver
//  一人一链接
//  Created by MikeRiy on 16/12/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GameUser_h
#define GameUser_h

#include <stdio.h>
#include "NetNode.h"
#include "packet_buffer.h"
#include "Player.h"

class Player;

class GameUser : public NetNode , public PacketBuffer
{
    //1对1的用户
private:
    Player* player;
public:
    GameUser();
    //解绑用户
    virtual ~GameUser();
public://用户行为
    //是否登录
    bool isLogin()const;
    //是否登录
    bool isNoLogin()const;
    //获取用户
    Player* getPlayer()const;
    //发送
    void SendPacket(PacketBuffer& packet);
    
private:
    friend class Player;
    void UnBindPlayer();             //退出登录解绑用户
    void BindPlayer(Player* value);  //登录角色
};

#endif /* GameUser_h */
