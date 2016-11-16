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


void SerHandler::OnConnect(FdState* value)
{
    RUN_MAIN(new SerTask(SOCKET_EVENT_CONNECT, value));
};

void SerHandler::OnClose(FdState* value)
{
    RUN_MAIN(new SerTask(SOCKET_EVENT_CLOSE, value));
};

void SerHandler::OnRead(FdState* value, const char* bytes, size_t size)
{
    RUN_MAIN(new SerTask(SOCKET_EVENT_READ, value, MemoryPool::getInstance()->alloc_copy((char*)bytes, size), size));
};

void SerHandler::OnAcceptHandler(FdState* value)
{
    if(hash.has(value->getSocketID()))
    {
        value->DisConnect();
    }else{
        LOG_INFO<<"add client fd = "<<value->getSocketID()<<LOG_END;
        hash.put(value->getSocketID(), new SocketHandler(value));
    }
}

void SerHandler::OnCloseHandler(FdState* value)
{
    SocketHandler* sock = hash.remove(value->getSocketID());
    LOG_INFO<<"remove client fd = "<<value->getSocketID()<<LOG_END;
    if(sock)
    {
        PlayerManager::getInstance()->DelPlayer(sock->user_id);
    }else{
        SAFE_DELETE(value);
    }
    SAFE_DELETE(sock);
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
