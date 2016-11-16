//
//  Player.c
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "Player.h"


Player::Player(USER_T uid, SocketHandler* sock)
:user_id(uid)
,_sock(sock)
,sock_id(sock->GetSocketFd())
{
    sock->user_id = uid;
}

Player::~Player()
{
    _sock->user_id = 0;
}


SocketHandler* Player::getSocket()const
{
    return _sock;
}