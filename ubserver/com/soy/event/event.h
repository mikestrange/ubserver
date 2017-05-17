//
//  event.h
//  ubserver
//
//  Created by MikeRiy on 16/12/27.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef event_h
#define event_h

#include <stdio.h>
#include "global.h"
#include "hashlist.h"
#include "hashmap.h"

#define EMPTY_EVENT 0

template<class T>
class EventHandler
{
private:
    typedef void(* EVENT_CALL)(MsgID, T, int);
private:
    EVENT_CALL m_fun;
public:
    EventHandler(EVENT_CALL fun)
    :m_fun(fun){}
    
    void handler(MsgID cmd, T args, int type)
    {
        if(m_fun)
        {
            m_fun(cmd, args, type);
        }
    }
    
    bool match(EVENT_CALL fun)
    {
        return m_fun == fun;
    }
    
    void destroy()
    {
        m_fun = NULL;
        delete this;
    }
};

template<class T>
class Event
{
private:
    int m_type;
private:
    typedef void(* EVENT_CALL)(MsgID, T, int);
private:
    HashList<EventHandler<T>*> m_list;
public:
    Event(int type = 0)
    :m_type(type){};
    
    virtual ~Event()
    {
        m_list.eachValues(block(EventHandler<T>* v)
        {
            v->destroy();
        });
    }
    
    int getType()const
    {
        return m_type;
    }
    
    bool matchType(int type)
    {
        if(m_type == 0) return true;
        return type == m_type;
    }
    
    void AddHandler(EVENT_CALL func)
    {
        m_list.add(new EventHandler<T>(func));
    }
    
    size_t DelHandler(EVENT_CALL func)
    {
        typename HashList<EventHandler<T>*>::Iterator iter;
        for(iter=m_list.begin();iter!=m_list.end();++iter)
        {
            EventHandler<T>* data = *iter;
            if(data->match(func))
            {
                m_list.remove(data);
                data->destroy();
                break;
            }
        }
        return m_list.length();
    }
    
    void SendHandler(MsgID cmd, T args, int type)
    {
        HashList<EventHandler<T>*>& _list = m_list;
        //复制-- m_list.copy(_list);
        //派送--
        typename HashList<EventHandler<T>*>::Iterator iter;
        for(iter=_list.begin();iter!=_list.end();++iter)
        {
            EventHandler<T>* data = *iter;
            data->handler(cmd, args, type);
        }
    }
};

template<class T>
class EventSet
{
private:
    typedef void(* EVENT_CALL)(MsgID, T, int);
private:
    HashMap<MsgID, Event<T>*> m_map;
public:
    //拷贝而已
    void CopyDispater(EventSet<T>* eventset)
    {
        m_map.cop(eventset->m_map);
    }
    
    void AddEvent(MsgID cmd, EVENT_CALL func, int m_type = 0)
    {
        Event<T>* handlers = m_map.getValue(cmd);
        if(!handlers)
        {
            handlers = new Event<T>(m_type);
            m_map.put(cmd, handlers);
        }
        handlers->AddHandler(func);
    }
    
    void DelEvent(MsgID cmd, EVENT_CALL func)
    {
        Event<T>* handlers = m_map.getValue(cmd);
        if(handlers->DelHandler(func) == EMPTY_EVENT)
        {
            m_map.remove(cmd);
            SAFE_DELETE(handlers);
        }
    }
    
    void SendEvent(MsgID cmd, T args, int type = 0)
    {
        Event<T>* handlers = m_map.getValue(cmd);
        if(handlers && handlers->matchType(type))
        {
            handlers->SendHandler(cmd, args, type);
        }
    }
    
    bool HasEvent(MsgID cmd)
    {
        return m_map.has(cmd);
    }
};

#endif /* event_h */
