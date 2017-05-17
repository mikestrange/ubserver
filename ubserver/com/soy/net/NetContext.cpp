//
//  NetContext.c
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "NetContext.h"

NetContext::NetContext()
:sock_fd(0)
,isconnect(false)
,begin_time(0)
{
    begin_time = TimeUtil::GetTimer();
}

NetContext::NetContext(SOCKET_T fd)
:NetContext()
{
    if(fd > 0) OnConnect(fd);
}

NetContext::~NetContext()
{
    LOG_INFO("close fd=%d", sock_fd);
}

NetContext* NetContext::OnConnect(SOCKET_T fd)
{
    sock_fd = fd;
    isconnect = true;
    this->Setout();
    LOG_INFO("connect fd=%d", sock_fd);
    return this;
}

SOCKET_T NetContext::DisConnect()
{
    AUTO_LOCK(this);
    isconnect = false;
    LOG_INFO("fd[%d] is close", sock_fd);
    return sock_fd;
}

SOCKET_T NetContext::getSockID()const
{
    return sock_fd;
};

bool NetContext::isClosed()const
{
    return isconnect == false;
}

bool NetContext::isConnect()const
{
    return isconnect;
}

int NetContext::SendPacket(const void* bytes, size_t size)
{
    AUTO_LOCK(this);
    if(isConnect())
    {
        LOG_INFO("send fd=%d size=%ld", sock_fd, size);
        return NET_SEND(sock_fd, bytes, size);
    }
    return -1;
}

bool NetContext::HeartBeat(TIME_T value, TIME_T outtime)
{
    if(value - begin_time >= outtime)
    {
        begin_time = value;
        return true;
    }
    return false;
}

int NetContext::SendPacket(ByteArray& packet)
{
    return SendPacket(packet.contents(), packet.wpos());
}

//开始读
void NetContext::LoadBytes(const char* bytes, size_t len)
{
    Write((const uint8*)bytes, len);
}

//0无包，1有包,－1错误
bool NetContext::packet()
{
    if(packet_size > 0)
    {
        return wpos() >= packet_size + m_rpos;
    }
    //
    if(wpos() - rpos() >= PACKET_BEGIN)
    {
        packet_size = readInt();
        //trace("%d %d %d %d",this->contents(0),this->contents(1),this->contents(2),this->contents(3));
        m_rpos = rpos();
        if(packet_size <= 0 || packet_size > MESSAGE_PACKET_MAX)
        {
            LOG_ERROR("this packlen is overrun %u %ld", packet_size, wpos());
            return false;
        }else{
            LOG_DEBUG(">>##packet size=%d r=%d w=%d",packet_size, rpos(), wpos());
            return wpos() >= packet_size + m_rpos;
        }
    }
    return false;
}

SocketHandler* NetContext::NextMessage()
{
    SocketHandler* message = NULL;
    if(packet())
    {
        ReadBegin();
        message = new SocketHandler(this, m_rpos, packet_size);
        ReadEnd();
    }
    return message;
}