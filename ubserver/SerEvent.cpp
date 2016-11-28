//
//  SerTask.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "SerEvent.h"

SerEvent::SerEvent(int type1, NetLink* fd1, char* bytes1, size_t size1)
:type(type1)
,m_link(fd1)
,bytes(bytes1)
,size(size1){
    
}

SerEvent::SerEvent(int type1, NetLink* fd1)
:type(type1)
,m_link(fd1)
,bytes(NULL)
,size(0)
{
    MemoryPool::getInstance()->alloc_copy(bytes, size);
}

SerEvent::~SerEvent()
{
    if(bytes)
    {
        if(!MemoryPool::getInstance()->share(bytes))
        {
            SAFE_DELETE(bytes);
        };
    }
}

void SerEvent::OnTaskHandler()
{
    switch(type)
    {
        case SOCKET_EVENT_CONNECT:
            SerHandler::getInstance()->OnAcceptHandler(m_link);
            break;
        case SOCKET_EVENT_CLOSE:
            SerHandler::getInstance()->OnCloseHandler(m_link);
            break;
        case SOCKET_EVENT_READ:
            auto sock = SerHandler::getInstance()->GetClient(m_link->getSocketID());
            if(sock->isConnect())
            {
                sock->LoadBytes(bytes, size);
                try{
                    while(sock->HasPacket())
                    {
                        sock->ReadBegin();
                        OnPacketHandler(sock);
                        sock->ReadEnd();
                    }
                }catch(...){
                    sock->Disconnect();
                }
            }
            break;
    }
}

//所有消息处理
void SerEvent::OnPacketHandler(SocketHandler *packet)
{
    LOG_DEBUG<<"read: cmd = "<<packet->getCmd()<<" type = "<<packet->getType()<<LOG_END;
    //
    switch(packet->getType())
    {
        case SERVER_WORLD_MESSAEGE:
                WorldMsg::getInstance()->OnPacketHandler(packet);
            break;
        case SERVER_GAME_MESSAGE:
                GameManager::getInstance()->OnPacketHandler(packet);
            break;
        default:
                WorldMsg::getInstance()->OnPacketHandler(packet);
            break;
    }
};
