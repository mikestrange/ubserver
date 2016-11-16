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
            trace("open server ok port = %d serid = %d", port, listen_fd);
            return listen_fd;
        }else{
            trace("open server error port = %d", port);
        }
        return -1;
    }
    
    //链接一个远程
    SOCKET_T connect(const char* ip, int port)
    {
        SOCKET_T listen_fd;
        if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            trace("socket af_inet error: %s:%d", ip, port);
        }else{
            struct sockaddr_in sock_addr;
            memset(&sock_addr, 0, sizeof(sock_addr));
            sock_addr.sin_family        = AF_INET;
            sock_addr.sin_addr.s_addr   = inet_addr(ip);
            sock_addr.sin_port          = htons(port);
            //
            if (::connect(listen_fd, (struct sockaddr *)&sock_addr, sizeof(struct sockaddr)) == -1)
            {
                trace("socket connect error: %s:%d %d", ip, port, listen_fd);
            }else{
                trace("socket connect ok: %s:%d %d", ip, port, listen_fd);
                return listen_fd;
            }
        }
        return -1;
    }
    
    void epoll_server(SOCKET_T serid, INet* net, int maxfd)
    {
        trace("[epoll server sock = %d]", serid);
        char bytes[MAX_BUFFER];
        fd_set rset;
        FD_ZERO(&rset);
        FD_SET(serid, &rset);
        const SOCKET_T max_fds = maxfd > MAX_SERVER ? MAX_SERVER : maxfd;
        FdState* fd_list[MAX_SERVER] = {};
        fd_list[0] = new FdState(serid);
        net->launch();
        struct timeval timeout;
        while(net->isRunning())
        {
            //init
            SET_TIMEOUT(timeout, 3, 0);
            fd_set mt = rset;
            //select
            int code = select(max_fds, &mt, NULL, NULL, &timeout);
            if(code < 0) exit(1);
            std::cout<<"select code:"<<code<<", error:"<<errno<<std::endl;
            //端口情况
            for(int i = 0 ;i < MAX_SERVER; i++)
            {
                if(fd_list[i] == NULL) continue;
                FdState* target = fd_list[i];
                SOCKET_T fd = target->getSocketID();
                if(target->isClosed())
                {
                    trace("[this fd is close = %d]", fd);
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
                                trace("[accept ok sock = %d]",new_fd);
                                FD_SET(new_fd, &rset);
                                FdState* proxy = new FdState(new_fd);
                                for(int m = 0; m < MAX_SERVER; m++)
                                {
                                    if(fd_list[m] == NULL)
                                    {
                                        fd_list[m] = proxy;
                                        break;
                                    }
                                }
                                net->OnConnect(proxy);
                            }else{
                                trace("[accept error or connect is max]");
                            }
                        }else{
                            int ret = NET_RECV(fd, bytes, MAX_BUFFER);
                            if (ret > 0)
                            {
                                trace("[recv : size = %d fd = %d]",ret, fd);
                                net->OnRead(target, bytes, ret);
                            }else {
                                trace("[close fd = %d code = %d]", fd, ret);
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
        //--
        for(int i = 1; i < MAX_SERVER; i++)
        {
            FdState* target = fd_list[i];
            if(target)
            {
                NET_CLOSE(target->getSocketID());
                target->DisConnect();
                net->OnClose(target);
            }
        }
        SAFE_DELETE(fd_list[0]);
        //
        NET_CLOSE(serid);
    }
}