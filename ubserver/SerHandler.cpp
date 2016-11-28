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


void SerHandler::OnConnect(NetLink* value)
{
    RUN_MAIN(new SerEvent(SOCKET_EVENT_CONNECT, value));
};

void SerHandler::OnClose(NetLink* value)
{
    RUN_MAIN(new SerEvent(SOCKET_EVENT_CLOSE, value));
};

void SerHandler::OnRead(NetLink* value, char* bytes, size_t size)
{
    RUN_MAIN(new SerEvent(SOCKET_EVENT_READ, value, bytes, size));
};

void SerHandler::OnAcceptHandler(NetLink* value)
{
    if(hash.has(value->getSocketID()))
    {
        value->DisConnect();
    }else{
        LOG_INFO<<"add client fd = "<<value->getSocketID()<<LOG_END;
        hash.put(value->getSocketID(), new SocketHandler(value));
    }
}

void SerHandler::OnCloseHandler(NetLink* value)
{
    SocketHandler* sock = hash.remove(value->getSocketID());
    LOG_INFO<<"remove client fd = "<<value->getSocketID()<<LOG_END;
    if(sock)
    {
        PlayerManager::getInstance()->DelPlayer(sock->getUserID());
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
    LOG_DEBUG<<"SerHandler fds ={"<<LOG_END;
    for(iter = hash.begin();iter!=hash.end();iter++)
    {
        LOG_DEBUG<<"fd = "<<iter->second->GetSocketFd()<<LOG_END;
    }
    LOG_DEBUG<<"}"<<LOG_END;
}
