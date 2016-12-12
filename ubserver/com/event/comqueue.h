//
//  supporter.h
//  ubserver
//
//  Created by MikeRiy on 16/11/9.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef supporter_h
#define supporter_h

#include <stdio.h>
#include "hashlist.h"
#include "array.h"

#include "command.h"

template <class T>
class ComQueue
{
private:
    HashList<ComApplyer<T>*> ls;
public:
    typedef typename HashList<ComApplyer<T>*>::Iterator Iterator;
public:
    virtual ~ComQueue()
    {
        Clean();
    }
public:
    virtual void InvokeHandler(T msg)
    {
        Array<ComApplyer<T>*> list;
        //复制
        ls.eachValues([&list](ComApplyer<T>* value)
        {
            list.add(value);
        });
        //调用
        list.eachValues([&msg](ComApplyer<T>* value)
        {
            value->call(msg);
        });
    }
    
    virtual bool AddCommand(Command<T>* command)
    {
        ls.add(new ComApplyer<T>(command));
        return true;
    }
    
    virtual void DelCommand(Command<T>* command)
    {
        Iterator iter;
        for(iter = ls.begin();iter != ls.end(); iter++)
        {
            ComApplyer<T>* com = *iter;
            if(com->match(command))
            {
                ls.remove(iter);
                delete com;
                break;
            };
        }
    }
    
    virtual bool HasCommand(Command<T>* command)
    {
        Iterator iter;
        for(iter = ls.begin();iter != ls.end(); iter++)
        {
            ComApplyer<T>* com = *iter;
            if(com->match(command))
            {
                return true;
            };
        }
        return false;
    }
    
    virtual void Clean()
    {
        ls.eachValues([](ComApplyer<T>* v)
        {
            delete v;
        });
        ls.clear();
    }
    
    virtual bool Empty()
    {
        return ls.empty();
    }
};

#endif /* supporter_h */
