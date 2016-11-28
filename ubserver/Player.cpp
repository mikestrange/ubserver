//
//  Player.c
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "Player.h"


Player::Player(USER_T uid, SocketHandler* sock)
:_sock(sock)
,user_id(uid)
,sock_id(sock->GetSocketFd())
,view_id(0)
{
    sock->BindUser(uid);
}

Player::~Player()
{
    ExitRoom();
    _sock->BindUser(0);
}


SocketHandler* Player::getSocket()const
{
    return _sock;
}

void Player::ExitRoom()
{
    if(view_id > 0)
    {
        GameManager::getInstance()->ExitGame(user_id, view_id);
        view_id = 0;
    }
}

bool Player::EnterRoom(TABLE_ID tid)
{
    if(view_id > 0) return false;
    view_id = tid;
    return true;
}