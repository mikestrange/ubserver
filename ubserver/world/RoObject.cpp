//
//  RoObject.c
//  ubserver
//
//  Created by MikeRiy on 16/12/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "RoObject.h"


RoObject::RoObject(USER_T uid, uint8 type)
:m_uid(uid)
,m_node(NULL)
,m_regid(0)
,m_type(type)
,is_login(false)
{};

RoObject::~RoObject()
{}

void RoObject::OnLoginReg(NetNode* node)
{
    m_node = node;
    is_login = true;
    LOG_DEBUG("login uid=%d", m_uid);
}

bool RoObject::OnLogoutReg()
{
    is_login = false;
    m_node = NULL;
    LOG_DEBUG("logout uid=%d", m_uid);
    return true;
}

bool RoObject::isLogin()const
{
    return is_login;
}

NetNode* RoObject::getSock()const
{
    return m_node;
}

USER_T RoObject::getUID()const
{
    return m_uid;
}

SOCKET_T RoObject::getSockID()
{
    if(m_node)
    {
        return m_node->getSockID();
    }
    return -1;
}