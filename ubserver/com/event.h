//
//  suppot.h
//  ubserver
//
//  Created by MikeRiy on 16/11/9.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef suppot_h
#define suppot_h

#include <stdio.h>
#include "global.h"
#include "hashmap.h"
#include "comqueue.h"

template <class T>
class MsgEvent
{
private:
    HashMap<MsgID, ComQueue<T>*> tab;
public:
    typedef typename HashMap<MsgID, ComQueue<T>*>::Iterator Iterator;
public:
    virtual ~MsgEvent()
    {
        Clean();
    }
public:
    bool AddListener(MsgID mid, Command<T>* command)
    {
        ComQueue<T>* sup = tab.getValue(mid);
        if(!sup)
        {
            sup = CreateComQueue();
            tab.put(mid, sup);
        }
        sup->AddCommand(command);
        return true;
    }
    
    void DelListener(MsgID mid, Command<T>* command)
    {
        Iterator iter = tab.get(mid);
        if(iter != tab.end())
        {
            ComQueue<T>* list = iter->second;
            list->DelCommand(command);
            if(list->Empty())
            {
                tab.remove(iter);
                delete list;
            }
        }
    }
    
    bool HasListener(MsgID mid, Command<T>* command)
    {
        ComQueue<T>* list = tab.find(mid);
        if(list)
        {
            return list->HasCommand(command);
        }
        return false;
    }
    
    bool Invoke(MsgID mid, T msg)
    {
        ComQueue<T>* list = tab.getValue(mid);
        if(list)
        {
            list->InvokeHandler(msg);
            return true;
        }
        return false;
    }
    
    void Clean()
    {
        tab.eachValues([](ComQueue<T>* v)
        {
            delete v;
        });
        tab.clear();
    }
protected:
    virtual ComQueue<T>* CreateComQueue()
    {
        return new ComQueue<T>;
    }
};

#endif /* suppot_h */
