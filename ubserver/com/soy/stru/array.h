//
//  array.h
//  ubserver
//
//  Created by MikeRiy on 16/11/9.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef array_h
#define array_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <map>

template <class V>
class Array
{
private:
    std::vector<V> elements;
public:
    typedef typename std::vector<V>::iterator Iterator;
public:
    Array(){}
    
    Array(Array<V>& target)
    {
        copy(target);
    }
    
    virtual ~Array()
    {
        clear();
    }
    
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
    
    int indexOf(V v)
    {
        int len = length();
        for(int i = 0; i < len; i++)
        {
            if(elements[i] == v) return i;
        }
        return -1;
    }
    
    int indexOfLast(V v)
    {
        for(int i = length(); i>=0; i--)
        {
            if(elements[i] == v) return i;
        }
        return -1;
    }
    
    V pop()
    {
        if(elements.empty()) return NULL;
        return splice(length() - 1);
    }
    
    V shift()
    {
        if(elements.empty()) return NULL;
        return splice(0);
    }
    
    int unshift(V v)
    {
        insert(v);
        return length();
    }
    
    int length()
    {
        return (int)elements.size();
    }
    
    bool full()
    {
        return elements.size() >= elements.max_size();
    }
    
    //默认头部
    void insert(V v, int index = 0)
    {
        elements.insert(elements.begin() + index, v);
    }
    
    void remove(V v)
    {
        elements.remove(v);
    }
    
    void remove(Iterator& iter)
    {
        elements.erase(iter);
    }
    
    V splice(int index)
    {
        V v = elements[index];
        elements.erase(elements.begin() + index);
        return v;
    }
    
    void clear()
    {
        elements.clear();
    }
    
    V operator[](int index)
    {
        return elements[index];
    }
    
    void copy(Array<V>& src)
    {
        Iterator iter;
        for(iter = src.begin(); iter != src.end(); ++iter)
        {
            add(*iter);
        }
    }
    
    void copy(std::list<V>& src)
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
    
    bool empty()const
    {
        return elements.empty();
    }
    
    Iterator begin()
    {
        return elements.begin();
    }
    
    Iterator end()
    {
        return elements.end();
    }
    
    std::vector<V>* getElements()
    {
        return &elements;
    }
    
    void print()
    {
        int len = length();
        std::cout<<"array["<<len<<"]=";
        for(int i = 0; i < len; i++)
        {
            std::cout<<elements[i];
            if(i != len - 1)
            {
                std::cout<<",";
            }
        }
        std::cout<<std::endl;
    }
};

#endif /* array_h */
