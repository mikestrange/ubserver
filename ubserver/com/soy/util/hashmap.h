//
//  pmap.h
//  ubserver
//
//  Created by MikeRiy on 16/11/9.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef hashmap_h
#define hashmap_h

#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>

template<class K,class V>
class HashMap
{
private:
    std::map<K,V> elements;
public:
    typedef typename std::map<K, V>::iterator Iterator;
public:
    HashMap(){}
    
    HashMap(HashMap<K,V>& target)
    {
        copy(target);
    }
    
    virtual ~HashMap()
    {
        clear();
    }
    
    Iterator find(K k)
    {
        return elements.find(k);
    }
    
    V getValue(K k)
    {
        Iterator iter = elements.find(k);
        if(iter != elements.end())
        {
            return iter->second;
        }
        return NULL;
    }
    
    bool has(K k)
    {
        return elements.find(k) != elements.end();
    }
    
    void put(K k, V v)
    {
        elements.insert(std::pair<K,V>(k, v));
    }
    
    int length()
    {
        return (int)elements.size();
    }
    
    V remove(K k)
    {
        Iterator iter = elements.find(k);
        if(iter != elements.end())
        {
            V v = iter->second;
            elements.erase(iter);
            return v;
        }
        return NULL;
    }
    
    void remove(Iterator& iter)
    {
        elements.erase(iter);
    }
    
    void copy(HashMap<K,V>& src)
    {
        Iterator iter;
        for(iter = src.begin(); iter!=src.end(); ++iter)
        {
            put(iter->first, iter->second);
        }
    }
    
    void getValues(std::vector<V>& src)
    {
        Iterator iter;
        for(iter = elements.begin(); iter!=elements.end(); ++iter)
        {
            src.push_back(iter->second);
        }
    }
    
    void getKeys(std::vector<K>& src)
    {
        Iterator iter;
        for(iter = elements.begin(); iter!=elements.end(); ++iter)
        {
            src.push_back(iter->first);
        }
    }
    
    void clear()
    {
        elements.clear();
    }
    
    template<class Block>
    void eachValues(Block fun)
    {
        Iterator iter;
        for(iter = elements.begin(); iter != elements.end(); ++iter)
        {
            fun(iter->second);
        }
    }
    
    template<class Block>
    void eachKeys(Block fun)
    {
        Iterator iter;
        for(iter = elements.begin(); iter != elements.end(); ++iter)
        {
            fun(iter->first);
        }
    }
    
    V operator[](K k)
    {
        return elements[k];
    }
    
    Iterator begin()
    {
        return elements.begin();
    }
    
    Iterator end()
    {
        return elements.end();
    }
    
    std::map<K, V>& getElements()
    {
        return elements;
    }
    
    bool empty()const
    {
        return elements.empty();
    }
    
    void print()
    {
        Iterator iter;
        std::cout<<"map["<<length()<<"]={"<<std::endl;
        for(iter = elements.begin(); iter != elements.end(); ++iter)
        {
            std::cout<<"    key="<<(iter->first)<<", value="<<iter->second<<";"<<std::endl;
        }
        std::cout<<"}"<<std::endl;
    }
};

#endif /* hashmap_h */
