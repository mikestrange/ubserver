
//
//  ByteStream.h
//  ubserver
//
//  Created by MikeRiy on 16/12/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef ByteStream_h
#define ByteStream_h

#include <vector>
#include "global.h"
#include "log.h"

#define BIT_SIZE 1024

class IBitStream{
private:
    size_t m_rpos, m_wpos, m_size, m_cap;
    uint8 *m_bits;
public:
    IBitStream()
    :m_rpos(0)
    ,m_wpos(0)
    ,m_size(0)
    ,m_cap(0)
    ,m_bits(NULL)
    {
        initWithSize(BIT_SIZE);
    }
    
    virtual ~IBitStream(){
        clear();
    }
    
private:
    void initWithSize(size_t size){
        m_bits = (uint8*)malloc(size);
        m_cap = size;
    }
    
    void grow(size_t size){
        size_t newsize = size + m_size;
        if(newsize > m_cap){
            uint8* old = m_bits;
            m_cap = BIT_SIZE*(int(newsize/BIT_SIZE) + 1);
            m_bits = new uint8[m_cap];
            if(old){
                memcpy(&m_bits[0], old, m_size);
                FREE(old);
            }
        }
    }
public:
    size_t rpos()const
    {
        return m_rpos;
    }
    
    size_t rpos(size_t rpos)
    {
        m_rpos = rpos;
        return m_rpos;
    }
    
    size_t wpos()const
    {
        return m_wpos;
    }
    
    size_t wpos(size_t wpos)
    {
        m_wpos = wpos;
        return m_wpos;
    }
    
    void clear()
    {
        FREE(m_bits);
        m_rpos = 0;
        m_wpos = 0;
        m_size = 0;
        m_cap = 0;
    }
    
    void reset()
    {
        m_rpos = m_wpos = m_size = 0;
    }
    
    size_t getAvailable()
    {
        return m_size - m_rpos;
    }
    
    size_t Size() const{
        return m_size;
    }
    
public:
    uint8& operator[](size_t const pos)
    {
        if (pos >= m_size)
        {
            LOG_ERROR("get error 1: %ld %ld", pos, m_size);
        }
        return m_bits[pos];
    }
    
    uint8 const& operator[](size_t const pos) const
    {
        if (pos >= m_size)
        {
            LOG_ERROR("get error 2: %ld %ld", pos, m_size);
        }
        return m_bits[pos];
    }
    
    const uint8* contents(int pos = 0)const
    {
        return &m_bits[pos];
    }

public:
    void Write(const uint8* src, size_t size)
    {
        grow(size);
        memcpy(&m_bits[m_wpos], src, size);
        m_wpos += size;
        if(m_wpos > m_size){
            m_size = m_wpos;
        }
    }
    
    void Read(char* dest, size_t size)
    {
        if(m_rpos  + size > m_size)
        {
            LOG_ERROR("read uint8 error: %ld %ld %ld", m_rpos, size, m_size);
        }
        memcpy(dest, &m_bits[m_rpos], size);
        m_rpos += size;
    }
    
protected:
    template <typename T> T Read()
    {
        T r = Read<T>(m_rpos);
        m_rpos += sizeof(T);
        return r;
    }
    
    template <typename T> T Read(size_t pos)const
    {
        if(pos + sizeof(T) > m_size)
        {
            LOG_ERROR("read T error: %ld %ld %ld", pos, sizeof(T), m_size);
        }
        T val = *((T const*)&m_bits[pos]);
        return val;
    }
};

//class ByteStream
class ByteStream : public IBitStream
{
public:
    
    ByteStream &self()
    {
        return *this;
    }
    //appends
private:
    void Append(const std::string& str)
    {
        Append((uint8 const*)str.c_str(), str.length());
    }
    
    void Append(const char* src, size_t size)
    {
        Append((const uint8 *)src, size);
    }
    
    template<class T>
    void Append(const T* src, size_t size)
    {
        Append((const uint8 *)src, size * sizeof(T));
    }
    
    template <typename T>
    void Append(T value)
    {
        Append((uint8*)&value, sizeof(value));
    }
    
    void Append(const uint8* src, size_t size)
    {
        Write(src, size);
    }
    
public:
    ByteStream& Append(ByteStream& bytes, size_t pos, size_t size)
    {
        Append(&bytes[pos], size);
        return *this;
    }
    
    //reads
public:
    ByteStream& read(ByteStream& bytes, size_t pos, size_t size)
    {
        bytes.Append(*this, pos, size);
        return *this;
    }
    
public:
    //read
    ByteStream &operator>>(bool &value)
    {
        value = Read<char>()> 0 ? true : false;
        return *this;
    }
    
    ByteStream &operator>>(uint8 &value)
    {
        value = Read<uint8>();
        return *this;
    }
    
    ByteStream &operator>>(uint16 &value)
    {
        value = Read<uint16>();
        return *this;
    }
    
    ByteStream &operator>>(uint32 &value)
    {
        value = Read<uint32>();
        return *this;
    }
    
    ByteStream &operator>>(uint64 &value)
    {
        value = Read<uint64>();
        return *this;
    }
    
    ByteStream &operator>>(int8 &value)
    {
        value = Read<int8>();
        return *this;
    }
    
    ByteStream &operator>>(int16 &value)
    {
        value = Read<int16>();
        return *this;
    }
    
    ByteStream &operator>>(int32 &value)
    {
        value = Read<int32>();
        return *this;
    }
    
    ByteStream &operator>>(int64 &value)
    {
        value = Read<int64>();
        return *this;
    }
    
    ByteStream &operator>>(float &value)
    {
        value = Read<float>();
        return *this;
    }
    
    ByteStream &operator>>(double &value)
    {
        value = Read<double>();
        return *this;
    }
    
    ByteStream &operator>>(std::string& str)
    {
        str.clear();
        int32 len = Read<int32>();
        //
        for(int i = 0; i < len; i++)
        {
            str += Read<char>();
        }
        return *this;
    }
    
    ByteStream &readString(std::string& str)
    {
        str.clear();
        int32 len = Read<int32>();
        //
        for(int i = 0; i < len; i++)
        {
            str += Read<char>();
        }
        return *this;
    }
    
    //快速写入
    //write
    ByteStream &operator<<(uint8 value)
    {
        Append<uint8>(value);
        return *this;
    }
    
    ByteStream &operator<<(uint16 value)
    {
        Append<uint16>(value);
        return *this;
    }
    
    ByteStream &operator<<(uint32 value)
    {
        Append<uint32>(value);
        return *this;
    }
    
    ByteStream &operator<<(uint64 value)
    {
        Append<uint64>(value);
        return *this;
    }
    
    ByteStream &operator<<(int8 value)
    {
        Append<int8>(value);
        return *this;
    }
    
    ByteStream &operator<<(int16 value)
    {
        Append<int16>(value);
        return *this;
    }
    
    ByteStream &operator<<(int32 value)
    {
        Append<int32>(value);
        return *this;
    }
    
    ByteStream &operator<<(int64 value)
    {
        Append<int64>(value);
        return *this;
    }
    
    // floating points
    ByteStream &operator<<(float value)
    {
        Append<float>(value);
        return *this;
    }
    
    ByteStream &operator<<(double value)
    {
        Append<double>(value);
        return *this;
    }
    
    ByteStream &operator<<(const char *str)
    {
        int32 len = (int32)strlen(str);
        Append<int32>(len);
        if(len > 0){
            Append(str, len);
        }
        return *this;
    }
    
    ByteStream &operator<<(const std::string &value)
    {
        int32 size = (int32)value.length();
        Append<int32>(size);
        if(size > 0)
        {
            Append((const char*)value.c_str(), size);
        }
        return *this;
    }
    
    ByteStream &writeChars(const char* bytes, size_t size)
    {
        Append<int32>((int32)size);
        if(size > 0)
        {
            Append(bytes, size);
        }
        return *this;
    }
    
    ByteStream &writeString(const std::string &str)
    {
        int32 size = (int32)str.length();
        Append<int32>(size);
        if(size > 0)
        {
            Append((const char*)str.c_str(), size);
        }
        return *this;
    }
};

#endif /* ByteStream_h */
