//
//  NetSocket.c
//  ubserver
//
//  Created by MikeRiy on 16/12/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "NetSocket.h"

//做推送主线服务
static void* socket_handler(void* args)
{
    NetSocket* sock = (NetSocket*)args;
    sock->epoll_socket();
    return 0;
}

static SOCKET_T net_connect(const char* host, int port)
{
    SOCKET_T listen_fd;
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        Log::Warn("socket af_inet error: %s:%d", host, port);
    }else{
        struct sockaddr_in sock_addr;
        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family        = AF_INET;
        sock_addr.sin_addr.s_addr   = inet_addr(host);
        sock_addr.sin_port          = htons(port);
        //
        if (::connect(listen_fd, (struct sockaddr *)&sock_addr, sizeof(struct sockaddr)) == -1)
        {
            Log::Warn("socket connect error: %s:%d", host, port);
        }else{
            Log::Debug("socket connect ok: %s:%d:%d", host, port, listen_fd);
            return listen_fd;
        }
    }
    return -0;
}


NetSocket::NetSocket()
{
    
}

NetSocket::~NetSocket()
{
    DisConnect();
}

//创建连接
bool NetSocket::connect(const char* host, int port)
{
    SOCKET_T fd = net_connect(host, port);
    if(fd > 0)
    {
        OnConnect(fd);
        Thread::create(&socket_handler, this);
        return true;
    }
    return false;
}

void NetSocket::epoll_socket()
{
    on_connect();
    char bytes[MAX_BUFFER];
    while(isConnect())
    {
        size_t ret = NET_RECV(getSockID(), bytes, MAX_BUFFER);
        if (ret > 0)
        {
            on_read(bytes, ret);
        }else if(ret == 0){
            break;
        }else{
            if((errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)){
                //正常接收
            }else{
                break;
            }
        }
    }
    DisConnect();
    NET_CLOSE(getSockID());
    on_close();
}

//主线程处理
void NetSocket::on_connect()
{
    RUN_MAIN(new SocketEvent(SOCKET_CONNECT, this));
}

void NetSocket::on_close()
{
    RUN_MAIN(new SocketEvent(SOCKET_CLOSED, this));
}

void NetSocket::on_read(char* bytes, size_t size)
{
    RUN_MAIN(new SocketEvent(SOCKET_READ_DATA, this, this, bytes, size));
}


void NetSocket::OnEvent(EventBase *event)
{
    
}
