//
//  NetServer.h
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef NetServer_h
#define NetServer_h

#include <stdio.h>
#include "global.h"
#include "NetNode.h"
#include "SocketEvent.h"

class NetServer : public IEventHandler
{
private:
    SOCKET_T m_listen_fd;
    int m_maxfd;
    bool m_isopen;
public:
    NetServer();
    
    bool listener(int port, int maxfd = 1024);
    
    void epoll_server();
    
    bool isopen()const;
    
    void stop();
    
public:
     //为了保证数据的可变性，可以自己定义绑定节点类型
     virtual NetNode* create_node();
    
private://handlers
    int accept_handler(fd_set* rset,int max_fds, NetNode* fd_list[]);
    
    void close_handler(int index, NetNode* node, fd_set* rset, NetNode* fd_list[]);
    
    void read_handler();
 
private:
    void on_listen();
    void on_accept(NetNode* node);
    void on_close(NetNode* node);
    void on_read(NetNode* node, char* bytes, size_t size);
    void on_overend();
    
public:
    void OnEvent(EventBase* event)override;
};



#endif /* NetServer_h */
