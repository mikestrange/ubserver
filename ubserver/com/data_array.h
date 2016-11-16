//
//  data_array.hpp
//  ServerPlugIn
//
//  Created by MikeRiy on 16/8/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef data_array_h
#define data_array_h

#include "read_bytes.h"
#include "write_bytes.h"

class ReadBytes;
class WriteBytes;
class IReader;

//快速读写
class IReader
{
public:
    virtual void WriteTo(WriteBytes& bytes)=0;
    virtual void ReadFor(ReadBytes& bytes)=0;
};

//数据流
class DataArray : public ReadBytes , public WriteBytes
{
public:
    DataArray(){};
    
    virtual ~DataArray(){};
    
public:
    void WriteObject(IReader& data)
    {
        data.WriteTo(*this);
    };
    
    void ReadObject(IReader& data)
    {
        data.ReadFor(*this);
    }
    
    int8 readInt8()
    {
        int8 v;
        self()>>v;
        return v;
    }
    
    int16 readInt16()
    {
        int16 v;
        self()>>v;
        return v;
    }
    
    int32 readInt32()
    {
        int32 v;
        self()>>v;
        return v;
    }
    
    int64 readInt64()
    {
        int64 v;
        self()>>v;
        return v;
    }
    
    
    uint8 readUint8()
    {
        uint8 v;
        self()>>v;
        return v;
    }
    
    uint16 readUint16()
    {
        uint16 v;
        self()>>v;
        return v;
    }
    
    uint32 readUint32()
    {
        uint32 v;
        self()>>v;
        return v;
    }
    
    uint64 readUint64()
    {
        uint64 v;
        self()>>v;
        return v;
    }
    
    DataArray& self()
    {
        return *this;
    }
    
    //write
    void writeInt8(int8 v)
    {
        self()<<v;
    }
    
    void writeInt16(int16 v)
    {
        self()<<v;
    }
    
    void writeInt32(int32 v)
    {
        self()<<v;
    }
    
    void writeInt64(int64 v)
    {
        self()<<v;
    }
    
    void writeUint8(uint8 v)
    {
        self()<<v;
    }
    
    void writeUint16(uint16 v)
    {
        self()<<v;
    }
    
    void writeUint32(uint32 v)
    {
        self()<<v;
    }
    
    void writeUint64(uint64 v)
    {
        self()<<v;
    }
};

#endif /* data_array_hpp */
