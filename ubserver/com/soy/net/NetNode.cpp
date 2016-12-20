//
//  NetNode.c
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "NetNode.h"

NetNode::NetNode()
:sock_fd(0)
,isconnect(false)
,begin_time(0)
{
    begin_time = TimeUtil::GetTimer();
}

NetNode::~NetNode()
{
    
}

NetNode* NetNode::OnConnect(SOCKET_T fd)
{
    sock_fd = fd;
    isconnect = true;
    return this;
}

SOCKET_T NetNode::DisConnect()
{
    isconnect = false;
    return sock_fd;
}

SOCKET_T NetNode::getSockID()const
{
    return sock_fd;
};

bool NetNode::isClosed()const
{
    return isconnect == false;
}

bool NetNode::isConnect()const
{
    return isconnect;
}

void NetNode::SendPacket(const void* bytes, size_t size)
{
    if(isConnect())
    {
        NET_SEND(sock_fd, bytes, size);
    }
}

bool NetNode::HeartBeat(TIME_T value, TIME_T outtime)
{
    if(value - begin_time >= outtime)
    {
        begin_time = value;
        return true;
    }
    return false;
}

void NetNode::SendPacket(ByteArray& packet)
{
    SendPacket(packet.contents(), packet.length());
}

//开始读
void NetNode::LoadBytes(const char* bytes, size_t len)
{
    append(bytes, len);
}

//0无包，1有包,－1错误
bool NetNode::packet()
{
    if(packet_size > 0)
    {
        return wpos() >= packet_size + m_rpos;
    }
    //
    if(wpos() - rpos() >= PACKET_BEGIN)
    {
        packet_size = readInt();
        m_rpos = rpos();
        if(packet_size <= 0 || packet_size > PACKET_MAX)
        {
            LOG_ERROR("this packlen is overrun %u %ld", packet_size, wpos());
            return false;
        }else{
            //LOG_DEBUG(">>##ReadBegin Pocket: size=%d r=%d w=%d",packet_size,rpos(),wpos());
            return wpos() >= packet_size + m_rpos;
        }
    }
    return false;
}

MsgHandler* NetNode::NextMessage()
{
    MsgHandler* message = NULL;
    if(packet())
    {
        ReadBegin();
        message = new MsgHandler(*this, m_rpos, packet_size);
        ReadEnd();
    }
    return message;
}