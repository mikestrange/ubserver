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
#include "time_util.h"
#include "EventBase.h"

class NetNode
{
private:
    SOCKET_T sock_fd;
    bool isconnect;
    TIME_T begin_time;
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
    
    bool HeartBeat(TIME_T value, TIME_T outtime);
    
    void SendPacket(const void* bytes, size_t size);
};

#endif /* NetNode_h */
