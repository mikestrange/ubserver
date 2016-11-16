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
        SOCKET_T max_fds = maxfd > serid ? maxfd : serid;
        net->launch();
        while(net->isRunning())
        {
            fd_set look = rset;
            int code = select(max_fds + 1, &look, 0, 0, 0);
            if(code == 0) continue;
            //新链接
            if(FD_ISSET(serid, &look))
            {
                int new_fd = accept(serid, NULL, NULL);
                if(new_fd > 0)
                {
                    trace("[accept ok sock = %d]",new_fd);
                    FD_SET(new_fd, &rset);
                    FD_SET(new_fd, &look);
                    net->OnSocketHandler(SOCKET_EVENT_CONNECT, new_fd, 0, 0);
                    if(new_fd > max_fds) max_fds = new_fd;
                }else{
                    trace("[accept error or connect is max]");
                }
            }
            //端口情况
            for(int fd = 0; fd < max_fds; fd++)
            {
                if(fd != serid && FD_ISSET(fd, &look))
                {
                    int ret = NET_RECV(fd, bytes, MAX_BUFFER);
                    if (ret > 0)
                    {
                        trace("[recv : size = %d fd = %d]",ret, fd);
                        net->OnSocketHandler(SOCKET_EVENT_READ, fd, bytes, ret);
                    }else {
                        trace("[close fd = %d code = %d]", fd, ret);
                        FD_CLR(fd, &rset);
                        NET_CLOSE(fd);
                        net->OnSocketHandler(SOCKET_EVENT_CLOSE, fd, 0, 0);
                    }
                }
            }
        }
        NET_CLOSE(serid);
        net->OnSocketHandler(SOCKET_EVENT_CLOSE, serid, 0, 0);
    }
}