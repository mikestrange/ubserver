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
#include "MsgHandler.h"


class SocketEvent : public EventBase
{
private:
    NetNode* m_node;
    MsgHandler* m_packet;
    
public:
    SocketEvent(int type, IEventHandler* target, NetNode* node = NULL, MsgHandler* message = NULL);
    
    virtual ~SocketEvent();
    
public:
    NetNode* getNode()const;
    
    MsgHandler* getMessage()const;
};

#endif /* ConnectEvent_h */
