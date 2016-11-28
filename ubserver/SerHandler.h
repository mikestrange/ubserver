//
//  SerHandler.h
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef SerHandler_h
#define SerHandler_h

#include <stdio.h>

#include "SerEvent.h"

#include "global.h"
#include "log.h"
#include "network.h"
#include "runtime.h"
#include "hashmap.h"
#include "client.h"
#include "lock.h"
#include "memorys.h"

#include "packet_buffer.h"
//
class SerHandler : public INet
{
    STATIC_CLASS(SerHandler);
private:
    HashMap<SOCKET_T, SocketHandler*> hash;
public:
    virtual ~SerHandler();
    //
    void OnConnect(NetLink* value)override;
    void OnClose(NetLink* value)override;
    void OnRead(NetLink* value, char* bytes, size_t size)override;
    
public:
    void OnCloseHandler(NetLink* value);
    
    SocketHandler* GetClient(SOCKET_T fd);
    
    void OnAcceptHandler(NetLink* value);
    
    void Print();
};

#endif /* SerHandler_h */
