//
//  NetServer.c
//  ubserver
//
//  Created by MikeRiy on 16/12/10.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "NetServer.h"

//做推送主线服务
static void* socket_handler(void* args)
{
    NetServer* server = (NetServer*)args;
    server->epoll_server();
    return 0;
}

NetServer::NetServer()
:m_listen_fd(0)
,m_maxfd(0)
,m_isopen(false){}

bool NetServer::listener(int port, int maxfd)
{
    m_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    if(::bind(m_listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0 &&
       listen(m_listen_fd, MAX_LISTENE) == 0)
    {
        Log::Debug("open server ok port=%d serid=%d", port, m_listen_fd);
        this->m_maxfd = maxfd;
        this->m_isopen = true;
        Thread::create(socket_handler, this);
        return true;
    }else{
        Log::Warn("open server error port=%d", port);
    }
    return false;
}

bool NetServer::isopen()const
{
    return m_isopen;
}

void NetServer::stop()
{
    m_isopen = false;
}

TIME_T NetServer::getHeartBeatTime()
{
    return 1000*60*3;//3分钟默认
}

void NetServer::epoll_server()
{
    on_listen();
    char bytes[MAX_BUFFER];
    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(m_listen_fd, &rset);
    NetNode* fd_list[MAX_SERVER] = {};
    //输入的是链接数目
    const SOCKET_T max_fds = m_maxfd >= MAX_SERVER ? MAX_SERVER : m_maxfd;
    struct timeval timeout;
    while(isopen())
    {
        //init
        SET_TIMEOUT(timeout, 3, 0);
        fd_set mt = rset;
        //select
        int code = select(MAX_SERVER, &mt, NULL, NULL, &timeout);
        //错误，退出程序
        if(code < 0) break;
        //查看新连接
        if(FD_ISSET(m_listen_fd, &mt))
        {
            accept_handler(&rset, max_fds, fd_list);
        }
        //端口情况
        for(int i = 0 ;i < max_fds; i++)
        {
            NetNode* node = fd_list[i];
            if(!node) continue;
            if(node->isClosed())
            {
                close_handler(i, node, &rset, fd_list);
            }else{
                //心跳
                if(node->HeartBeat(TimeUtil::GetTimer(), getHeartBeatTime()))
                {
                    on_heartbeat(node);
                };
                //读写
                if(FD_ISSET(node->getSockID(), &mt))
                {
                    size_t ret = NET_RECV(node->getSockID(), bytes, MAX_BUFFER);
                    if (ret > 0)
                    {
                        on_read(node, bytes, ret);
                    }else if(ret == 0){
                        close_handler(i, node, &rset, fd_list);
                    }else{
                        if((errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)){
                            //正常接收
                        }else{
                            close_handler(i, node, &rset, fd_list);
                        }
                    }
                }
            }
        }
    }
    stop();
    //关闭端口
    NET_CLOSE(m_listen_fd);
    //回执
    on_overend();
    //---
    Log::Warn("[服务器关闭]");
}

NetNode* NetServer::create_node()
{
    return new NetNode();
}

int NetServer::accept_handler(fd_set* rset, int max_fds, NetNode* fd_list[])
{
    int new_fd = accept(m_listen_fd, NULL, NULL);
    if(new_fd > 0)
    {
        FD_SET(new_fd, rset);
        NetNode* new_link = create_node();
        for(int m = 0; m < max_fds; m++)
        {
            if(fd_list[m] == NULL)
            {
                fd_list[m] = new_link->OnConnect(new_fd);
                break;
            }
        }
        //判断是否连接了
        if(new_link->isConnect())
        {
            on_accept(new_link);
        }else{
            FD_CLR(new_fd, rset);
            NET_CLOSE(new_fd);
            SAFE_DELETE(new_link);
        }
    }else{
        Log::Warn("accept error or over max");
    }
    //返回最大连接
    return 0;
}

void NetServer::close_handler(int index, NetNode* node, fd_set* rset, NetNode* fd_list[])
{
    SOCKET_T fd = node->DisConnect();
    fd_list[index] = NULL;
    FD_CLR(fd, rset);
    NET_CLOSE(fd);
    on_close(node);
}

//交给主线程处理
void NetServer::on_listen()
{
    RUN_MAIN(new SocketEvent(SOCKET_LISTEN, this));
}

void NetServer::on_overend()
{
    RUN_MAIN(new SocketEvent(SOCKET_OVEREND, this));
}

void NetServer::on_accept(NetNode* node)
{
    RUN_MAIN(new SocketEvent(SOCKET_CONNECT, this, node));
}

void NetServer::on_close(NetNode* node)
{
    RUN_MAIN(new SocketEvent(SOCKET_CLOSED, this, node));
}

void NetServer::on_heartbeat(NetNode* node)
{
    RUN_MAIN(new SocketEvent(SOCKET_HEARTBET, this, node));
}

void NetServer::on_read(NetNode* node, char* bytes, size_t size)
{
    RUN_MAIN(new SocketEvent(SOCKET_READ_DATA, this, node, bytes, size));
}

//主线程执行任务
void NetServer::OnEvent(EventBase *event)
{
    
}