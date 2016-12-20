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
#include "ByteArray.h"
#include "PacketBuffer.h"
#include "MsgHandler.h"

class NetNode : public PacketBuffer
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
    
    void SendPacket(ByteArray& packet);
    
public:
    //加载字节
    virtual void LoadBytes(const char* bytes, size_t len);
    //获取数据消息
    virtual MsgHandler* NextMessage();
    
private:
    bool packet();
};

#endif /* NetNode_h */
