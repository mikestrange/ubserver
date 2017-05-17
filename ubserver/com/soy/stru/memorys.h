//
//  memory_pool.hpp
//  ServerPlugIn
//  字节缓存池
//  Created by MikeRiy on 16/8/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef memory_pool_h
#define memory_pool_h

#include "global.h"
#include "lock.h"

#include <vector>

#define MAX_MEMORY_LEN 2048

#define NEW_CHAR_LEN 1024

template<class V>
class MemoryPool : private Locked
{
private:
    size_t _maxLen;
private:
    std::vector<V*> pools;
public:
    MemoryPool()
    :_maxLen(MAX_MEMORY_LEN)
    {}
    
    MemoryPool(size_t maxLen)
    :_maxLen(maxLen)
    {}
    
    virtual ~MemoryPool()
    {
        clean();
    }
    
public:
    //获取一个
    V* back()
    {
        AUTO_LOCK(this);
        if(pools.empty())
        {
            return NULL;
        }
        V* val = pools.back();
        pools.pop_back();
        return val;
    }
    
    bool share(V* obj)
    {
        AUTO_LOCK(this);
        if(pools.size() >= _maxLen)
        {
            return false;
        }
        pools.push_back(obj);
        return true;
    }
    
    void clean()
    {
        AUTO_LOCK(this);
        typename std::vector<V*>::iterator iter;
        for(iter=pools.begin(); iter!=pools.end(); ++iter)
        {
            SAFE_DELETE(*iter);
        }
        pools.clear();
    }
//    char* alloc_copy(char* src, size_t size)
//    {
//        char* chars = peel();
//        memcpy(chars, src, size);
//        return chars;
//    }
};

#endif /* memory_pool_h */
