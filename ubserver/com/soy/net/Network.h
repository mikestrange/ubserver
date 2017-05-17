//
//  Network.h
//  ubserver
//
//  Created by MikeRiy on 16/11/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef Network_h
#define Network_h

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include "arpa/inet.h"

#include <errno.h>
#include <fcntl.h>
#include <err.h>
#include <list>

#include "log.h"
#include "global.h"
#include "thread.h"
#include "NetContext.h"
#include "SocketHandler.h"

class NetContext;
class SocketHandler;

//监听数目
#define MAX_LISTENE 10
//服务器最大连接数目
#define MAX_SERVER 1023
//
#define WEB_RESULT_MAX 2048
//一次最大缓冲量
#define READ_BUFF_MAX 4096
//默认心跳时间
#define HEART_BEAT_TIME 1000*60*3
//超时设置
#define SET_TIMEOUT(t, m, s) t.tv_sec = m;t.tv_usec = s;

//第二版本事务
typedef enum
{
    SOCKET_LISTEN,          //端口监听成功
    SOCKET_OVEREND,         //端口终止
    
    SOCKET_CONNECT,         //套接字建立
    SOCKET_CLOSED,          //套接关闭
    
    SOCKET_HEARTBET,        //心跳
    SOCKET_READ_DATA,       //套接字信息
}SOCKET_EVENT;


//net
bool NET_CLOSE(SOCKET_T fd);

size_t NET_RECV(SOCKET_T fd, void* bytes, size_t len);

int NET_SEND(SOCKET_T fd, const void* bytes, size_t len);

int NET_SEND(SOCKET_T fd, ByteArray* packet);

int NET_SEND(SOCKET_T fd, ByteArray& packet);

//处理类
class INetHandler
{
public:
    //新连接
    virtual void OnConnect(NetContext* context){};
    //包处理
    virtual void OnPacket(SocketHandler* packet){};
    //服务器的启动
    virtual void OnStart(NetContext* context){};
    //服务器的退出
    virtual void OnStop(NetContext* context){};
    //关闭一个连接
    virtual void OnClosed(NetContext* context){};
public:
    //新链接
    virtual NetContext* alloc_context(SOCKET_T fd);
    //回收
    virtual bool die_context(NetContext* context);
    //心跳
    virtual void OnHeartBeat(NetContext* context){};
    //心跳时间
    virtual TIME_T GetHeartBeatTime()const{return HEART_BEAT_TIME;};
    //最大连接
    virtual int GetMaxConnect()const{return MAX_SERVER;};
public:
    //处理读出
    virtual void OnReadHandler(NetContext* context, char* bytes, size_t size);
    virtual NetContext* OnAcceptHandler(SOCKET_T fd, fd_set* rset, int max_fds, size_t current);
    virtual void OnCloseHandler(NetContext* context, fd_set* rset);
};

namespace soy
{
    //server
    SOCKET_T launch(int port, INetHandler* net);
    //socket
    SOCKET_T connect(const char* host, int port, INetHandler* net = NULL);
}

#endif /* Network_h */
