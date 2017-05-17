//
//  PacketBuffer.h
//  ubserver
//
//  Created by MikeRiy on 16/12/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef PacketBuffer_h
#define PacketBuffer_h

#include "ByteArray.h"

//包头字节长度
#define PACKET_BEGIN 4
//最大1MB的包长
#define MESSAGE_PACKET_MAX 1024*1024

class PacketBuffer : public ByteArray , public IReader
{
protected:
    int32 m_wpos;
    size_t m_rpos;
    size_t packet_size;
public:
    PacketBuffer();
    
    virtual void WriteBegin();
    //自定义
    virtual void WriteBegin(IReader& data);
    
    virtual int32 WriteEnd();
    
    virtual void ReadBegin();
    //自定义读取头
    virtual void ReadBegin(IReader& data);
    
    virtual void ReadEnd();
    
    virtual void Setout();
};

#endif /* PacketBuffer_h */
