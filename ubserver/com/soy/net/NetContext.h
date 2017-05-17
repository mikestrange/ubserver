//
//  NetContext.h
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef NetContext_h
#define NetContext_h

#include "global.h"
#include "Network.h"
#include "time_util.h"
#include "ByteArray.h"
#include "PacketBuffer.h"
#include "SocketHandler.h"
#include "lock.h"

class SocketHandler;

class NetContext : public PacketBuffer, private Locked
{
private:
    SOCKET_T sock_fd;
    bool isconnect;
    TIME_T begin_time;
public:
    NetContext();
    
    NetContext(SOCKET_T fd);
    
    virtual ~NetContext();
    
    SOCKET_T getSockID()const;
    
    bool isClosed()const;
    
    bool isConnect()const;
    //关闭
    SOCKET_T DisConnect();
    //连接
    NetContext* OnConnect(SOCKET_T fd);
    
    bool HeartBeat(TIME_T value, TIME_T outtime);
    
    int SendPacket(const void* bytes, size_t size);
    
public:
    virtual int SendPacket(ByteArray& packet);
    
public:
    //加载字节
    virtual void LoadBytes(const char* bytes, size_t len);
    //获取数据消息
    virtual SocketHandler* NextMessage();
    
private:
    bool packet();
};

#endif /* NetContext_h */
