//
//  packet_buffer.h
//  ubserver
//
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef packet_buffer_h
#define packet_buffer_h

#include "data_array.h"
#include "packet_header.h"
#include "log.h"

//头大小
#define PACKET_BEGIN 4
//长度
#define PACKET_MAX 2048

class DataArray;
class PacketHeader;

class PacketBuffer : public DataArray , public PacketHeader
{
private:
    int32 m_wpos;
private:
    size_t m_rpos;
private:
    size_t packet_size;
    
public:
    PacketBuffer()
    :m_wpos(0)
    ,m_rpos(0)
    ,packet_size(0)
    {}
    
public:
    virtual void WriteBegin()
    {
        wpos(m_wpos + PACKET_BEGIN);
        WriteObject(*this);
    }
    
    //自定义
    virtual void WriteBegin(IReader& data)
    {
        wpos(m_wpos + PACKET_BEGIN);
        WriteObject(data);
    }
    
    virtual int32 WriteEnd()
    {
        int32 mark = (int32)wpos() - m_wpos;
        wpos(m_wpos);
        append(mark - PACKET_BEGIN);
        wpos(mark + m_wpos);
        m_wpos = (int32)wpos();
        //返回包长度
        return mark;
    }
    
    //开始读
    virtual void LoadBytes(const char* bytes, size_t len)
    {
        append(bytes, len);
    }
    
    virtual bool HasPacket()
    {
        if(packet_size > 0)
        {
            return wpos() >= packet_size + m_rpos;
        }
        //
        if(wpos() - rpos() >= PACKET_BEGIN)
        {
            packet_size = readInt32();
            m_rpos = rpos();
            if(packet_size <= 0 || packet_size > PACKET_MAX)
            {
                ERROR_LOG("this packlen is overrun %u %ld", packet_size, wpos());
            }else{
                Log::Debug(">>##ReadBegin Pocket: size=%d r=%d w=%d",packet_size,rpos(),wpos());
                return HasPacket();
            }
        }
        return false;
    }
    
    virtual void ReadBegin()
    {
        ReadBegin(*this);
    }
    
    //自定义读取头
    virtual void ReadBegin(IReader& data)
    {
        rpos(m_rpos);
        ReadObject(data);
    }
    
    virtual void ReadEnd()
    {
        //max overflow
        if(rpos() > wpos())
        {
            ERROR_LOG("this is get overout %u %ld", rpos(), wpos());
        }
        //reset
        if(packet_size > 0)
        {
            rpos(m_rpos + packet_size);
            packet_size = 0;
            m_rpos = 0;
            if(rpos() == wpos()) clear();
            Log::Debug(">>##ReadEnd is Flush");
        }
    }
};

#endif /* packet_buffer_h */
