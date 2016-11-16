//
//  SerTask.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "SerTask.h"

SerTask::SerTask(int type1, FdState* fd1, char* bytes1, size_t size1)
:type(type1)
,fd(fd1)
,bytes(bytes1)
,size(size1){
    
}

SerTask::SerTask(int type1, FdState* fd1)
:type(type1)
,fd(fd1)
,bytes(NULL)
,size(0){
    
}

SerTask::~SerTask()
{
    if(bytes)
    {
        if(!MemoryPool::getInstance()->share(bytes))
        {
            SAFE_DELETE(bytes);
        };
    }
}

void SerTask::OnTaskHandler()
{
    switch(type)
    {
        case SOCKET_EVENT_CONNECT:
                SerHandler::getInstance()->OnAcceptHandler(fd);
            break;
        case SOCKET_EVENT_CLOSE:
                SerHandler::getInstance()->OnCloseHandler(fd);
            break;
        case SOCKET_EVENT_READ:
            trace("read handler");
                auto sock = SerHandler::getInstance()->GetClient(fd->getSocketID());
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
void SerTask::OnPacketHandler(SocketHandler *packet)
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
