//
//  SerHandler.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "SerHandler.h"

STATIC_CLASS_INIT(SerHandler);

SerHandler::~SerHandler()
{
    hash.eachValues([](SocketHandler* v)
    {
        SAFE_DELETE(v);
    });
}

void SerHandler::OnSocketHandler(int type, SOCKET_T fd, const char* bytes, size_t size)
{
    switch(type)
    {
        case SOCKET_EVENT_CONNECT:
            RUN_MAIN(new SerTask(type, fd));
            break;
        case SOCKET_EVENT_CLOSE:
            RUN_MAIN(new SerTask(type, fd));
            break;
        case SOCKET_EVENT_READ:
            RUN_MAIN(new SerTask(type, fd, MemoryPool::getInstance()->alloc_copy((char*)bytes, size), size));
            break;
    }
};

void SerHandler::OnAccept(SOCKET_T fd)
{
    if(hash.has(fd))
    {
        NET_CLOSE(fd);
    }else{
        LOG_INFO<<"add client fd = "<<fd<<LOG_END;
        hash.put(fd, new SocketHandler(fd));
    }
}

void SerHandler::OnClose(SOCKET_T fd)
{
    SocketHandler* sock = hash.remove(fd);
    if(sock)
    {
        PlayerManager::getInstance()->DelPlayer(sock->user_id);
    }
    SAFE_DELETE(sock);
    LOG_INFO<<"remove client fd = "<<fd<<LOG_END;
}

SocketHandler* SerHandler::GetClient(SOCKET_T fd)
{
    return hash.getValue(fd);
}

void SerHandler::Print()
{
    HashMap<SOCKET_T, SocketHandler*>::Iterator iter;
    std::cout<<"SerHandler fds ={"<<std::endl;
    for(iter = hash.begin();iter!=hash.end();iter++)
    {
        std::cout<<"fd = "<<iter->second->GetSocketFd()<<std::endl;
    }
    std::cout<<"}"<<std::endl;
}
