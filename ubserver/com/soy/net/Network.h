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
#include "ByteArray.h"
#include "log.h"

#define INVALID_SOCKET -1

#define MAX_LISTENE 10

#define MAX_SERVER 1024

#define MAX_BUFFER 1024

#define SET_TIMEOUT(t, m, s) t.tv_sec = m;t.tv_usec = s;

//第二版本事务
typedef enum
{
    SOCKET_LISTEN,          //端口监听成功
    SOCKET_CONNECT,         //套接字建立
    SOCKET_CLOSED,          //套接关闭
    SOCKET_HEARTBET,        //心跳
    SOCKET_READ_DATA,       //套接字信息
    SOCKET_OVEREND,         //端口终止
}SOCKET_EVENT;


//net
bool NET_CLOSE(SOCKET_T fd);

size_t NET_RECV(SOCKET_T fd, void* bytes, size_t len);

int NET_SEND(SOCKET_T fd, const void* bytes, size_t len);

int NET_SEND(SOCKET_T fd, ByteArray* packet);

int NET_SEND(SOCKET_T fd, ByteArray& packet);


#endif /* network_h */
