//
//  Player.c
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "Player.h"

Player::Player(USER_T uid, GameUser* sock)
:m_sock(NULL)
,user_id(uid)
,view_id(0)
{
    LinkSocket(sock);
}

Player::~Player()
{
    ExitRoom();
}


void Player::LinkSocket(GameUser* node)
{
    //解除之前的
    UnLinkSocket();
    m_sock = node;
    m_sock->BindPlayer(this);
}

void Player::UnLinkSocket()
{
    if(m_sock)
    {
        m_sock->UnBindPlayer();
        m_sock->DisConnect();
        m_sock = NULL;
    }
    //假设无引用，那么删除释放
}

bool Player::isLinkSocket()const
{
    return m_sock;
}

GameUser* Player::getSocket()const
{
    return m_sock;
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


USER_T Player::getUserID()const
{
    return user_id;
}