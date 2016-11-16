//
//  network.h
//  ubserver
//
//  Created by MikeRiy on 16/11/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef network_h
#define network_h

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

#include "global.h"
#include "packet_buffer.h"
#include "FdState.h"

#define INVALID_SOCKET -1

#define MAX_LISTENE 10

#define MAX_SERVER 1024

#define MAX_BUFFER 1024

#define SET_TIMEOUT(t, m, s) t.tv_sec = m;t.tv_usec = s;

//socket event
enum{
    SOCKET_EVENT_CONNECT = 1,
    SOCKET_EVENT_CLOSE,
    SOCKET_EVENT_READ,
    SOCKET_EVENT_SEND,
};

class FdState;
//class
class INet
{
private:
    bool is_running;
public:
    INet():is_running(false){};
    
    void launch(){is_running = true;};
    
    void close(){is_running = false;};
    
    virtual bool isRunning()const
    {
        return is_running;
    };
    
    virtual void OnConnect(FdState* value)=0;
    virtual void OnClose(FdState* value)=0;
    virtual void OnRead(FdState* value, const char* bytes, size_t size)=0;
};


//net
bool NET_CLOSE(SOCKET_T fd);

int NET_RECV(SOCKET_T fd, void* bytes, size_t len);

int NET_SEND(SOCKET_T fd, const void* bytes, size_t len);

int NET_SEND_PACKET(SOCKET_T fd, PacketBuffer* packet);

namespace network
{
    //开放一个端口
    SOCKET_T listener(int port);
    
    //链接一个远程
    SOCKET_T connect(const char* ip, int port);
    
    void epoll_server(SOCKET_T serid, INet* net, int maxfd = 0);
}

#endif /* network_h */
