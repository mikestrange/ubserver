//
//  SerTask.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "SerTask.h"

SerTask::SerTask(int type1, SOCKET_T fd1, char* bytes1, size_t size1)
:type(type1)
,fd(fd1)
,bytes(bytes1)
,size(size1){
    
}

SerTask::SerTask(int type1, SOCKET_T fd1)
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
    if(type == SOCKET_EVENT_CLOSE)
    {
        SerHandler::getInstance()->DelClient(fd);
    }else if( type == SOCKET_EVENT_READ){
        auto sock = SerHandler::getInstance()->GetClient(fd);
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
    }
}

//所有消息处理
void SerTask::OnPacketHandler(SocketHandler *packet)
{
    std::string str;
    packet->self()>>str;
    LOG_DEBUG<<"read: cmd = "<<packet->getCmd()<<" type = "<<packet->getType()<<" msg = "<<str<<LOG_END;
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
