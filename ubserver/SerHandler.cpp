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
            if(!AddClient(fd)) NET_CLOSE(fd);
            break;
        case SOCKET_EVENT_CLOSE:
            RUN_MAIN(new SerTask(type, fd));
            break;
        case SOCKET_EVENT_READ:
            RUN_MAIN(new SerTask(type, fd, MemoryPool::getInstance()->alloc_copy((char*)bytes, size), size));
            break;
    }
};

bool SerHandler::AddClient(SOCKET_T fd)
{
    AUTO_LOCK(this);
    if(hash.has(fd)) return false;
    LOG_INFO<<"add client fd = "<<fd<<LOG_END;
    hash.put(fd, new SocketHandler(fd));
    return true;
}

void SerHandler::DelClient(SOCKET_T fd)
{
    AUTO_LOCK(this);
    SocketHandler* sock = hash.remove(fd);
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
