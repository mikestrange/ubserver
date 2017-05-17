#include "Network.h"

//屏蔽send导致线程挂掉
static void protect_send_handler()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &set, NULL);
}

//net
bool NET_CLOSE(SOCKET_T fd)
{
    return ::close(fd) == 0;
}

size_t NET_RECV(SOCKET_T fd, void* bytes, size_t len)
{
    return ::recv(fd, bytes, len, 0);
}

int NET_SEND(SOCKET_T fd, const void* bytes, size_t len)
{
    return (int)::send(fd, bytes, len, 0);
}

int NET_SEND(SOCKET_T fd, ByteArray* packet)
{
    return NET_SEND(fd, packet->contents(), packet->Size());
}

int NET_SEND(SOCKET_T fd, ByteArray& packet)
{
    return NET_SEND(fd, packet.contents(), packet.Size());
}

//通过线程需要
struct NetProxy
{
    INetHandler* m_net;
    SOCKET_T m_fd;
    //--new
    NetProxy(INetHandler* net, SOCKET_T fd)
    :m_net(net)
    ,m_fd(fd){}
};


NetContext* INetHandler::alloc_context(SOCKET_T fd)
{
    return new NetContext(fd);
}


bool INetHandler::die_context(NetContext* context)
{
    context->DisConnect();
    SAFE_DELETE(context);
    return false;
}


//处理
void INetHandler::OnReadHandler(NetContext *context, char *bytes, size_t size)
{
    LOG_INFO("read fd=%d size=%ld", context->getSockID(), size);
    if(size <=0 )
    {
        LOG_WARN("fd[%d] read is error", context->getSockID());
        exit(1);
    }
    try{
        context->LoadBytes(bytes, size);
        SocketHandler* packet = NULL;
        while((packet = context->NextMessage()))
        {
            this->OnPacket(packet);
        }
    }catch(...){
        context->DisConnect();
    }
}

NetContext* INetHandler::OnAcceptHandler(SOCKET_T fd, fd_set *rset, int max_fds, size_t current)
{
    int new_fd = accept(fd, NULL, NULL);
    if(new_fd > 0)
    {
        if(current > max_fds)
        {
            NET_CLOSE(new_fd);
        }else{
            FD_SET(new_fd, rset);
            return this->alloc_context(new_fd);
        }
    }else{
        LOG_WARN("accept error or over max");
    }
    return NULL;
}

void INetHandler::OnCloseHandler(NetContext* context, fd_set* rset)
{
    SOCKET_T fd = context->DisConnect();
    FD_CLR(fd, rset);
    NET_CLOSE(fd);
    OnClosed(context);
}

static void net_epoll_server(INetHandler* net, SOCKET_T listen_fd, SOCKET_T max_fds)
{
    NetContext* root = net->alloc_context(listen_fd);
    net->OnStart(root);
    char bytes[READ_BUFF_MAX];
    //设置
    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(listen_fd, &rset);
    std::list<NetContext*> fd_list;
    //线程保护
    protect_send_handler();
    //超时
    struct timeval timeout;
    while(root->isConnect())
    {
        //init
        SET_TIMEOUT(timeout, 1, 0);
        fd_set mt = rset;
        //select
        int code = select(max_fds, &mt, NULL, NULL, &timeout);
        //错误，退出程序
        if(code < 0) break;
        //查看新连接
        if(FD_ISSET(listen_fd, &mt))
        {
            NetContext* new_context = net->OnAcceptHandler(listen_fd, &rset, max_fds, fd_list.size());
            if(new_context)
            {
                fd_list.push_back(new_context);
                net->OnConnect(new_context);
            }
        }
        //端口情况
        std::list< NetContext*>::iterator iter;
        for(iter = fd_list.begin();iter != fd_list.end();)
        {
            NetContext* context = *iter;
            if(context->isClosed())
            {
                fd_list.erase(iter++);
                net->OnCloseHandler(context, &rset);
                continue;
            }else{
                //心跳
                if(context->HeartBeat(TimeUtil::GetTimer(), net->GetHeartBeatTime()))
                {
                    net->OnHeartBeat(context);
                };
                //读写
                if(FD_ISSET(context->getSockID(), &mt))
                {
                    size_t ret = NET_RECV(context->getSockID(), bytes, READ_BUFF_MAX);
                    if (ret > 0)
                    {
                        net->OnReadHandler(context, bytes, ret);
                    }else if(ret == 0){
                        fd_list.erase(iter++);
                        net->OnCloseHandler(context, &rset);
                        continue;
                    }else{
                        if((errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)){
                            //正常接收
                        }else{
                            fd_list.erase(iter++);
                            net->OnCloseHandler(context, &rset);
                            continue;
                        }
                    }
                }
            }
            //
            iter++;
        }
    }
    //关闭所有连接
    std::list< NetContext*>::iterator iter;
    for(iter = fd_list.begin();iter != fd_list.end(); iter++)
    {
        net->OnCloseHandler(*iter, &rset);
    }
    //关闭服务器
    NET_CLOSE(root->DisConnect());
    //服务器停止调用
    net->OnStop(root);
    LOG_WARN("[服务器关闭]");
}

static void net_epoll_socket(INetHandler* net, SOCKET_T listen_fd)
{
    char bytes[READ_BUFF_MAX];
    NetContext* context = net->alloc_context(listen_fd);
    net->OnConnect(context);
    while(context->isConnect())
    {
        size_t ret = NET_RECV(context->getSockID(), bytes, READ_BUFF_MAX);
        if (ret > 0)
        {
            net->OnReadHandler(context, bytes, ret);
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
    //正在执行关闭
    NET_CLOSE(context->DisConnect());
    //关闭回执
    net->OnClosed(context);
}

//服务器处理
static void* on_server_handler(void* args)
{
    NetProxy* proxy = (NetProxy*)args;
    net_epoll_server(proxy->m_net, proxy->m_fd, proxy->m_net->GetMaxConnect());
    SAFE_DELETE(proxy);
    return 0;
}

//socket处理
static void* on_socket_handler(void* args)
{
    NetProxy* proxy = (NetProxy*)args;
    net_epoll_socket(proxy->m_net, proxy->m_fd);
    SAFE_DELETE(proxy);
    return 0;
}

//端口监听
static SOCKET_T net_listener(int port, INetHandler* net)
{
    SOCKET_T listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    if(::bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0 &&
       listen(listen_fd, MAX_LISTENE) == 0)
    {
        LOG_DEBUG("open server ok port=%d serid=%d", port, listen_fd);
        Thread::create(on_server_handler, new NetProxy(net, listen_fd));
    }else{
        listen_fd = -1;
        LOG_WARN("open server error port=%d", port);
    }
    return listen_fd;
}

//端口连接
static SOCKET_T net_connect(const char* host, int port, INetHandler* net)
{
    SOCKET_T listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1)
    {
        LOG_WARN("socket af_inet error: %s:%d", host, port);
    }else{
        struct sockaddr_in sock_addr;
        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family        = AF_INET;
        sock_addr.sin_addr.s_addr   = inet_addr(host);
        sock_addr.sin_port          = htons(port);
        if (::connect(listen_fd, (struct sockaddr *)&sock_addr, sizeof(struct sockaddr)) == -1)
        {
            LOG_WARN("socket error: %s:%d", host, port);
            listen_fd = -1;
        }else{
            if(net){
                LOG_DEBUG("socket ok: %s:%d:%d", host, port, listen_fd);
                Thread::create(&on_socket_handler, new NetProxy(net, listen_fd));
            }else{
                LOG_DEBUG("socket ok warn no delegate: %s:%d:%d", host, port, listen_fd);
            }
        }
    }
    return listen_fd;
}

namespace soy
{
    SOCKET_T launch(int port, INetHandler* net)
    {
        return net_listener(port, net);
    }
    
    SOCKET_T connect(const char* host, int port, INetHandler* net)
    {
        return net_connect(host, port, net);
    }
}