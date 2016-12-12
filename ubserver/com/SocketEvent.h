//
//  ConnectEvent.h
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef ConnectEvent_h
#define ConnectEvent_h

#include "memorys.h"
#include "EventBase.h"
#include "NetNode.h"

class SocketEvent : public EventBase
{
private:
    NetNode* m_node;
    char* m_bytes;
    size_t m_size;
    
public:
    SocketEvent(int type, IEventHandler* target, NetNode* node = NULL, char* bytes = NULL, size_t size = 0);
    
    virtual ~SocketEvent();
    
public:
    char* getBytes()const;
    
    size_t getSize()const;
    
    NetNode* getNode()const;
};

#endif /* ConnectEvent_h */
