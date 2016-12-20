//
//  MsgHeader.c
//  ubserver
//
//  Created by MikeRiy on 16/12/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "MsgHandler.h"

MsgHandler::MsgHandler()
:cmd(0)
,type(0)
,view_id(0)
,version(0)
{}


MsgHandler::MsgHandler(ByteArray& packet, size_t pos, size_t size)
:MsgHandler()
{
    packet.read(*this, pos, size);
    this->ReadBegin();
}

MsgHandler::~MsgHandler()
{
    
}

void MsgHandler::setBegin(MsgID $cmd, int32 $type, int32 $vid, int32 $ver)
{
    cmd = $cmd;
    type = $type;
    view_id = $vid;
    version = $ver;
    //头写入
    this->WriteBegin();
}

void MsgHandler::CopyBegin(MsgHandler& data)
{
    cmd = data.cmd;
    type = data.type;
    version = data.version;
    view_id = data.view_id;
}

MsgID MsgHandler::getCmd()
{
    return cmd;
}

int32 MsgHandler::getType()
{
    return type;
}

int32 MsgHandler::getViewId()
{
    return view_id;
}

int32 MsgHandler::getVersion()
{
    return version;
}

void MsgHandler::WriteTo(ByteStream& bytes)
{
    bytes<<cmd<<type<<view_id<<version;
    //LOG_DEBUG("write %d %d %d %d", cmd, type, version, view_id);
}

void MsgHandler::ReadFor(ByteStream& bytes)
{
    bytes>>cmd>>type>>view_id>>version;
    //LOG_DEBUG("read %d %d %d %d", cmd, type, version, view_id);
}