//
//  MsgHeader.c
//  ubserver
//
//  Created by MikeRiy on 16/12/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "SocketHandler.h"

SocketHandler::SocketHandler()
:cmd(0)
,type(0)
,view_id(0)
,ser_id(0)
,version(0)
,m_context(0)
{}

SocketHandler::SocketHandler(NetContext* context)
:cmd(0)
,type(0)
,view_id(0)
,ser_id(0)
,version(0)
,m_context(context)
{}

SocketHandler::SocketHandler(NetContext* context, size_t pos, size_t size)
:SocketHandler(context)
{
    context->read(*this, pos, size);
    //this->ReadBegin();
}

SocketHandler::~SocketHandler()
{
    
}

void SocketHandler::setBegin(MsgID $cmd, int32 $type, int32 $vid, int32 $sid, int32 $ver)
{
    cmd = $cmd;
    type = $type;
    view_id = $vid;
    ser_id = $sid;
    version = $ver;
    //头写入
    this->WriteBegin();
}

void SocketHandler::CopyBegin(SocketHandler& data)
{
    cmd = data.cmd;
    type = data.type;
    view_id = data.view_id;
    ser_id = data.ser_id;
    version = data.version;
}

MsgID SocketHandler::getCmd()
{
    return cmd;
}

int32 SocketHandler::getType()
{
    return type;
}

int32 SocketHandler::getViewId()
{
    return view_id;
}

int32 SocketHandler::getVersion()
{
    return version;
}

int32 SocketHandler::getSerId()
{
    return ser_id;
}

NetContext* SocketHandler::getContext()
{
    return m_context;
}

void SocketHandler::WriteCode(ByteStream& bytes)
{
    bytes<<cmd<<type<<view_id<<ser_id<<version;
    //LOG_DEBUG("write %d %d %d %d", cmd, type, version, view_id);
}

void SocketHandler::ReadCode(ByteStream& bytes)
{
    bytes>>cmd>>type>>view_id>>ser_id>>version;
    //LOG_DEBUG("read %d %d %d %d", cmd, type, version, view_id);
}