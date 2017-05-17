//
//  RoObject.c
//  ubserver
//
//  Created by MikeRiy on 16/12/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "RoObject.h"


RoObject::RoObject(USER_T uid, NetContext* context, uint8 type)
:m_uid(uid)
,m_context(context)
,m_regid(0)
,m_type(type)
{
    LOG_INFO("add user %d", uid);
};

RoObject::~RoObject()
{
    LOG_INFO("remove user %d", m_uid);
}

NetContext* RoObject::getContext()const
{
    return m_context;
}

USER_T RoObject::getUID()const
{
    return m_uid;
}
