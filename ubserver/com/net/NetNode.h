//
//  NetNode.h
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef NetNode_h
#define NetNode_h

#include "global.h"
#include "network.h"
#include "EventBase.h"

class NetNode
{
private:
    SOCKET_T sock_fd;
    bool isconnect;
    
public:
    NetNode();
    
    virtual ~NetNode();
    
    SOCKET_T getSockID()const;
    
    bool isClosed()const;
    
    bool isConnect()const;
    //关闭
    SOCKET_T DisConnect();
    //连接
    NetNode* OnConnect(SOCKET_T fd);
    
    void SendPacket(const void* bytes, size_t size);
};

#endif /* NetNode_h */
