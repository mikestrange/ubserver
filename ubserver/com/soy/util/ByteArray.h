//
//  data_array.hpp
//  ServerPlugIn
//
//  Created by MikeRiy on 16/8/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef data_array_h
#define data_array_h

#include "ByteStream.h"

class ReadBytes;
class WriteBytes;
class IReader;

//快速读写
class IReader
{
public:
    virtual void WriteTo(ByteStream& bytes)=0;
    virtual void ReadFor(ByteStream& bytes)=0;
};

//数据流
class ByteArray : public ByteStream
{
public:
    ByteArray(){};
    
    virtual ~ByteArray(){};
    
public:
    void WriteObject(IReader& data)
    {
        data.WriteTo(*this);
    };
    
    void ReadObject(IReader& data)
    {
        data.ReadFor(*this);
    }
    
    //read
    int8 readByte()
    {
        int8 v;
        self()>>v;
        return v;
    }
    
    int16 readShort()
    {
        int16 v;
        self()>>v;
        return v;
    }
    
    int32 readInt()
    {
        int32 v;
        self()>>v;
        return v;
    }
    
    int64 readLong()
    {
        int64 v;
        self()>>v;
        return v;
    }
    
    
    uint8 readUByte()
    {
        uint8 v;
        self()>>v;
        return v;
    }
    
    uint16 readUShort()
    {
        uint16 v;
        self()>>v;
        return v;
    }
    
    uint32 readUInt()
    {
        uint32 v;
        self()>>v;
        return v;
    }
    
    uint64 readULong()
    {
        uint64 v;
        self()>>v;
        return v;
    }
    
    //write
    void writeByte(int8 v)
    {
        self()<<v;
    }
    
    void writeShort(int16 v)
    {
        self()<<v;
    }
    
    void writeInt(int32 v)
    {
        self()<<v;
    }
    
    void writeLong(int64 v)
    {
        self()<<v;
    }
    
    void writeUByte(uint8 v)
    {
        self()<<v;
    }
    
    void writeUShort(uint16 v)
    {
        self()<<v;
    }
    
    void writeUInt(uint32 v)
    {
        self()<<v;
    }
    
    void writeULong(uint64 v)
    {
        self()<<v;
    }
};

#endif /* data_array_hpp */
