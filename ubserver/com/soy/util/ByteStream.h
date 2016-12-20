
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

class ByteStream
{
protected:
    size_t _rpos, _wpos;
    std::vector<uint8> _storage;
    
public:
    ByteStream()
    : _rpos(0)
    , _wpos(0)
    {}
    
    
    ByteStream &self()
    {
        return *this;
    }
    //appends
public:
    ByteStream& append(const std::string& str)
    {
        return append((uint8 const*)str.c_str(), str.length());
    }
    
    ByteStream& append(const char* src, size_t size)
    {
        return append((const uint8 *)src, size);
    }
    
    template<class T>
    ByteStream& append(const T* src, size_t size)
    {
        return append((const uint8 *)src, size * sizeof(T));
    }
    
    ByteStream& append(ByteStream& bytes, size_t pos, size_t size)
    {
        append(&bytes[pos], size);
        return *this;
    }
    
    template <typename T>
    ByteStream& append(T value)
    {
        return append((uint8*)&value, sizeof(value));
    }
    
    ByteStream& append(const uint8* src, size_t size)
    {
        if (_storage.size() < _wpos + size)
        {
            _storage.resize(_wpos + size);
        }
        memcpy(&_storage[_wpos], src, size);
        _wpos += size;
        return *this;
    }
    
    size_t wpos()const
    {
        return _wpos;
    }
    
    size_t wpos(size_t wpos_)
    {
        _wpos = wpos_;
        return _wpos;
    }
    
    //reads
public:
    template <typename T> T read()
    {
        T r = read<T>(_rpos);
        _rpos += sizeof(T);
        return r;
    }
    
    template <typename T> T read(size_t pos) const
    {
        if(pos + sizeof(T) > length())
        {
            LOG_ERROR("read T error: %ld %ld %ld", pos, sizeof(T), length());
        }
        T val = *((T const*)&_storage[pos]);
        return val;
    }
    
    ByteStream& read(char* dest, size_t size)
    {
        if(_rpos  + size > length())
        {
            LOG_ERROR("read uint8 error: %ld %ld %ld", _rpos, size, length());
        }
        memcpy(dest, &_storage[_rpos], size);
        _rpos += size;
        return *this;
    }
    
    ByteStream& read(ByteStream& bytes, size_t pos, size_t size)
    {
        bytes.append(*this, pos, size);
        return *this;
    }
    
    size_t rpos()const
    {
        return _rpos;
    }
    
    size_t rpos(size_t rpos_)
    {
        _rpos = rpos_;
        return _rpos;
    }
    
public:
    const uint8* contents(int pos = 0)const
    {
        return &_storage[pos];
    }
    
    size_t length() const
    {
        return _storage.size();
    }
    
    bool empty() const
    {
        return _storage.empty();
    }
    
    uint8& operator[](size_t const pos)
    {
        if (pos >= length())
        {
            LOG_ERROR("get error 1: %ld %ld", pos, length());
        }
        return _storage[pos];
    }
    
    uint8 const& operator[](size_t const pos) const
    {
        if (pos >= length())
        {
            LOG_ERROR("get error 2: %ld %ld", pos, length());
        }
        return _storage[pos];
    }
    
    void clear()
    {
        _rpos = _wpos = 0;
        _storage.clear();
    }
    
    void reset()
    {
        _rpos = _wpos = 0;
    }
    
    //0-newsize合法，之外不合法（直接构造了新元素）
    void resize(size_t newsize)
    {
        if (newsize > length())
        {
            _storage.resize(newsize);
        }
    }
    
    // 新元素还没有构造, 此时不能用[]访问元素
    void reserve(size_t ressize)
    {
        if (ressize > length())
        {
            _storage.reserve(ressize);
        }
    }
    
    //快速读取
    //read
    ByteStream &operator>>(bool &value)
    {
        value = read<char>()> 0 ? true : false;
        return *this;
    }
    
    ByteStream &operator>>(uint8 &value)
    {
        value = read<uint8>();
        return *this;
    }
    
    ByteStream &operator>>(uint16 &value)
    {
        value = read<uint16>();
        return *this;
    }
    
    ByteStream &operator>>(uint32 &value)
    {
        value = read<uint32>();
        return *this;
    }
    
    ByteStream &operator>>(uint64 &value)
    {
        value = read<uint64>();
        return *this;
    }
    
    ByteStream &operator>>(int8 &value)
    {
        value = read<int8>();
        return *this;
    }
    
    ByteStream &operator>>(int16 &value)
    {
        value = read<int16>();
        return *this;
    }
    
    ByteStream &operator>>(int32 &value)
    {
        value = read<int32>();
        return *this;
    }
    
    ByteStream &operator>>(int64 &value)
    {
        value = read<int64>();
        return *this;
    }
    
    ByteStream &operator>>(float &value)
    {
        value = read<float>();
        return *this;
    }
    
    ByteStream &operator>>(double &value)
    {
        value = read<double>();
        return *this;
    }
    
    ByteStream &operator>>(std::string& str)
    {
        str.clear();
        int32 len = read<int32>();
        //
        for(int i = 0; i < len; i++)
        {
            str += read<char>();
        }
        return *this;
    }
    
    ByteStream &readString(std::string& str)
    {
        str.clear();
        int32 len = read<int32>();
        //
        for(int i = 0; i < len; i++)
        {
            str += read<char>();
        }
        return *this;
    }
    
    //快速写入
    //write
    ByteStream &operator<<(uint8 value)
    {
        append<uint8>(value);
        return *this;
    }
    
    ByteStream &operator<<(uint16 value)
    {
        append<uint16>(value);
        return *this;
    }
    
    ByteStream &operator<<(uint32 value)
    {
        append<uint32>(value);
        return *this;
    }
    
    ByteStream &operator<<(uint64 value)
    {
        append<uint64>(value);
        return *this;
    }
    
    ByteStream &operator<<(int8 value)
    {
        append<int8>(value);
        return *this;
    }
    
    ByteStream &operator<<(int16 value)
    {
        append<int16>(value);
        return *this;
    }
    
    ByteStream &operator<<(int32 value)
    {
        append<int32>(value);
        return *this;
    }
    
    ByteStream &operator<<(int64 value)
    {
        append<int64>(value);
        return *this;
    }
    
    // floating points
    ByteStream &operator<<(float value)
    {
        append<float>(value);
        return *this;
    }
    
    ByteStream &operator<<(double value)
    {
        append<double>(value);
        return *this;
    }
    
    ByteStream &operator<<(const char *str)
    {
        int32 len = (int32)strlen(str);
        append<int32>(len);
        if(len > 0){
            append(str, len);
        }
        return *this;
    }
    
    ByteStream &operator<<(const std::string &value)
    {
        int32 size = (int32)value.length();
        append<int32>(size);
        if(size > 0)
        {
            append((const char*)value.c_str(), size);
        }
        return *this;
    }
    
    ByteStream &writeBytes(const char* bytes, size_t size)
    {
        append<int32>((int32)size);
        if(size > 0)
        {
            append(bytes, size);
        }
        return *this;
    }
    
    
};

#endif /* ByteStream_h */
