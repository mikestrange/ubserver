#include "network.h"

//net
bool NET_CLOSE(SOCKET_T fd)
{
    return ::close(fd) == 0;
}

int NET_RECV(SOCKET_T fd, void* bytes, size_t len)
{
    return (int)::recv(fd, bytes, len, 0);
}

int NET_SEND(SOCKET_T fd, const void* bytes, size_t len)
{
    return (int)::send(fd, bytes, len, 0);
}

int NET_SEND_PACKET(SOCKET_T fd, PacketBuffer* packet)
{
    return NET_SEND(fd, &packet->get(0), packet->wsize());
}

namespace network
{
    //开放一个端口
    SOCKET_T listener(int port)
    {
        SOCKET_T listen_fd = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(port);
        //绑定端口
        if(::bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0 &&
           listen(listen_fd, MAX_LISTENE) == 0)
        {
            LOG_DEBUG<<"open server ok port = "<<port<<" serid = "<<listen_fd<<LOG_END;
            return listen_fd;
        }else{
            LOG_WARN<<"open server error port = "<<port<<LOG_END;
        }
        return -1;
    }
    
    //链接一个远程
    SOCKET_T connect(const char* ip, int port)
    {
        SOCKET_T listen_fd;
        if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            LOG_WARN<<"socket af_inet error: "<<ip<<":"<<port<<LOG_END;
        }else{
            struct sockaddr_in sock_addr;
            memset(&sock_addr, 0, sizeof(sock_addr));
            sock_addr.sin_family        = AF_INET;
            sock_addr.sin_addr.s_addr   = inet_addr(ip);
            sock_addr.sin_port          = htons(port);
            //
            if (::connect(listen_fd, (struct sockaddr *)&sock_addr, sizeof(struct sockaddr)) == -1)
            {
                LOG_WARN<<"socket connect error: "<<ip<<":"<<port<<":"<<listen_fd<<LOG_END;
            }else{
                LOG_WARN<<"socket connect ok: "<<ip<<":"<<port<<":"<<listen_fd<<LOG_END;
                return listen_fd;
            }
        }
        return -1;
    }
    
    void epoll_server(SOCKET_T serid, INet* net, int maxfd)
    {
        char bytes[MAX_BUFFER];
        fd_set rset;
        FD_ZERO(&rset);
        FD_SET(serid, &rset);
        NetLink* fd_list[MAX_SERVER] = {};
        fd_list[0] = NetLink::create(serid, true);
        //输入的是链接数目
        const SOCKET_T max_fds = maxfd >= MAX_SERVER ? MAX_SERVER : maxfd + 1;
        LOG_DEBUG<<"[epoll server serid = "<<serid<<" max = "<<max_fds<<"]"<<LOG_END;
        net->launch();
        struct timeval timeout;
        while(net->isRunning())
        {
            //init
            SET_TIMEOUT(timeout, 3, 0);
            fd_set mt = rset;
            //select
            int code = select(MAX_SERVER, &mt, NULL, NULL, &timeout);
            if(code < 0) exit(1);
            //LOG_DEBUG<<"select code:"<<code<<", error:"<<errno<<LOG_END;
            //端口情况
            for(int i = 0 ;i < max_fds; i++)
            {
                if(fd_list[i] == NULL) continue;
                NetLink* target = fd_list[i];
                SOCKET_T fd = target->getSocketID();
                if(target->isClosed())
                {
                    //LOG_INFO<<"server cut fd = "<<fd<<LOG_END;
                    target->DisConnect();
                    fd_list[i] = NULL;
                    FD_CLR(fd, &rset);
                    NET_CLOSE(fd);
                    net->OnClose(target);
                }else{
                    if(FD_ISSET(fd, &mt))
                    {
                        if(fd == serid){
                            //新链接
                            int new_fd = accept(fd, NULL, NULL);
                            if(new_fd > 0)
                            {
                                //LOG_INFO<<"accept ok fd = "<<new_fd<<LOG_END;
                                FD_SET(new_fd, &rset);
                                NetLink* new_link = NetLink::create(new_fd);
                                //第一个被占
                                for(int m = 1; m < max_fds; m++)
                                {
                                    if(fd_list[m] == NULL)
                                    {
                                        fd_list[m] = new_link;
                                        new_link->OnConnect();
                                        break;
                                    }
                                }
                                //--
                                if(new_link->isConnect())
                                {
                                    net->OnConnect(new_link);
                                }else{
                                    FD_CLR(new_fd, &rset);
                                    NET_CLOSE(new_fd);
                                    SAFE_DELETE(new_link);
                                    //LOG_INFO<<"accept over max close fd = "<<new_fd<<LOG_END;
                                }
                            }else{
                                LOG_INFO<<"accept error or over max"<<LOG_END;
                            }
                        }else{
                            int ret = target->OnRead(bytes, MAX_BUFFER);
                            if (ret > 0)
                            {
                                //LOG_INFO<<"recv : size = "<<ret<<" fd = "<<fd<<LOG_END;
                                net->OnRead(target, bytes, ret);
                            }else {
                                //LOG_INFO<<"client close fd = "<<fd<<" ret = "<<ret<<LOG_END;
                                target->DisConnect();
                                fd_list[i] = NULL;
                                FD_CLR(fd, &rset);
                                NET_CLOSE(fd);
                                net->OnClose(target);
                            }
                        }
                    }
                }
            }
        }
        //--(释放所有链接)
        for(int i = 1; i < max_fds; i++)
        {
            NetLink* target = fd_list[i];
            if(target)
            {
                NET_CLOSE(target->getSocketID());
                target->DisConnect();
                net->OnClose(target);
            }
        }
        SAFE_DELETE(fd_list[0]);
        NET_CLOSE(serid);
    }
}