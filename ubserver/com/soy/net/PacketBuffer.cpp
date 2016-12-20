//
//  PacketBuffer.c
//  ubserver
//
//  Created by MikeRiy on 16/12/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "PacketBuffer.h"

PacketBuffer::PacketBuffer()
:m_wpos(0)
,m_rpos(0)
,packet_size(0)
{}

void PacketBuffer::WriteBegin()
{
    WriteBegin(*this);
}

//自定义
void PacketBuffer::WriteBegin(IReader& data)
{
    wpos(m_wpos + PACKET_BEGIN);
    WriteObject(data);
}

int32 PacketBuffer::WriteEnd()
{
    int32 mark = (int32)wpos() - m_wpos;
    wpos(m_wpos);
    append(mark - PACKET_BEGIN);
    wpos(mark + m_wpos);
    m_wpos = (int32)wpos();
    //返回包长度
    return mark;
}

void PacketBuffer::ReadBegin()
{
    ReadBegin(*this);
}

//自定义读取头
void PacketBuffer::ReadBegin(IReader& data)
{
    rpos(m_rpos);
    ReadObject(data);
}

void PacketBuffer::ReadEnd()
{
    //max overflow
    if(rpos() > wpos())
    {
        LOG_ERROR("this is get overout %u %ld", rpos(), wpos());
    }
    //reset
    if(packet_size > 0)
    {
        rpos(m_rpos + packet_size);
        packet_size = 0;
        m_rpos = 0;
        if(rpos() == wpos()) clear();
        //LOG_DEBUG(">>##ReadEnd is Flush");
    }
}

void PacketBuffer::WriteTo(ByteStream &bytes)
{
    
}

void PacketBuffer::ReadFor(ByteStream &bytes)
{
    
}