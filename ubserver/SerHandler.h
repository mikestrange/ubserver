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

#include "SerTask.h"

#include "global.h"
#include "log.h"
#include "network.h"
#include "runtime.h"
#include "hashmap.h"
#include "client.h"
#include "lock.h"
#include "memory_pool.h"
//
class SerHandler : public INet, private Locked
{
    STATIC_CLASS(SerHandler);
private:
    HashMap<SOCKET_T, SocketHandler*> hash;
public:
    virtual ~SerHandler();
    
    void OnSocketHandler(int type, SOCKET_T fd, const char* bytes, size_t size)override;
    
public:
    void DelClient(SOCKET_T fd);
    
    SocketHandler* GetClient(SOCKET_T fd);
    
    void Print();
    
private:
    bool AddClient(SOCKET_T fd);
};

#endif /* SerHandler_h */
