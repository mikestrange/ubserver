//
//  hashlist.h
//  ubserver
//
//  Created by MikeRiy on 16/11/9.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef hashlist_h
#define hashlist_h

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>

#include <stdarg.h>

template <class V>
class HashList
{
private:
    std::list<V> elements;
public:
    typedef typename std::list<V>::iterator Iterator;
public:
    HashList(){};
    
    HashList(HashList<V>& target)
    {
        copy(target);
    }
    
    virtual ~HashList()
    {
        clear();
    };
    
    int add(V v)
    {
        elements.push_back(v);
        return length();
    }
    
    int push(V v, ...)
    {
        va_list ap;
        va_start(ap, v);
        V _v = v;
        while(_v)
        {
            elements.push_back(_v);
            _v = va_arg(ap, V);
        }
        va_end(ap);
        return length();
    }
    
    V pop()
    {
        if(elements.empty()) return NULL;
        V v = elements.back();
        elements.pop_back();
        return v;
    }
    
    V shift()
    {
        if(elements.empty()) return NULL;
        V v = elements.front();
        elements.pop_front();
        return v;
    }
    
    int unshift(V v)
    {
        elements.push_front(v);
        return length();
    }
    
    void remove(V v)
    {
        elements.remove(v);
    }
    
    void remove(Iterator& iter)
    {
        elements.erase(iter);
    }
    
    int length()
    {
        return (int)elements.size();
    }
    
    void clear()
    {
        elements.clear();
    }
    
    void copy(HashList<V>& src)
    {
        Iterator iter;
        for(iter = src.begin(); iter!=src.end(); ++iter)
        {
            add(*iter);
        }
    }
    
    void copy(std::vector<V>& src)
    {
        typename std::list<V>::iterator iter;
        for(iter = src.begin(); iter != src.end(); ++iter)
        {
            add(*iter);
        }
    }
    
    template<class Block>
    void eachValues(Block fun)
    {
        Iterator iter;
        for(iter = elements.begin(); iter != elements.end(); ++iter)
        {
            fun(*iter);
        }
    }
    
    Iterator begin()
    {
        return elements.begin();
    }
    
    Iterator end()
    {
        return elements.end();
    }
    
    bool empty()const
    {
        return elements.empty();
    }
    
    std::list<V>& getElements()
    {
        return elements;
    }
    
    void print()
    {
        Iterator iter;
        std::cout<<"list["<<length()<<"]=";
        int i = 0;
        int len = length();
        for(iter = elements.begin(); iter != elements.end(); ++iter)
        {
            std::cout<<*iter;
            if(++i != len)
            {
                std::cout<<",";
            }
        }
        std::cout<<std::endl;
    }
};


#endif /* hashlist_h */
