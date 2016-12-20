//
//  NetSocket.h
//  ubserver
//
//  Created by MikeRiy on 16/12/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef NetSocket_h
#define NetSocket_h

#include "thread.h"
#include "network.h"
#include "SocketEvent.h"
#include "EventBase.h"
#include "NetNode.h"
#include "MsgHandler.h"

class NetSocket : public NetNode, public IEventHandler
{
public:
    NetSocket();
    virtual ~NetSocket();
    bool connect(const char* host, int port);
private:
    void on_connect();
    void on_close();
    void on_read(MsgHandler* message);
    void read_handler(char* bytes, size_t size);
public:
    void epoll_socket();
    
public:
    void OnEvent(EventBase* event)override;
};

#endif /* NetSocket_h */
