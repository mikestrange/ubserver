//
//  SerHandler.c
//  ubserver
//
//  Created by MikeRiy on 16/12/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "SerHandler.h"


STATIC_CLASS_INIT(SerHandler);

NetNode* SerHandler::create_node()
{
    return new GameUser;
}

void SerHandler::OnEvent(EventBase *event)
{
    SocketEvent* sock_event = (SocketEvent*)event;
    switch(event->getType())
    {
        case SOCKET_CONNECT:
            AddNode(sock_event->getNode());
            break;
        case SOCKET_CLOSED:
            RemoveNode(sock_event->getNode());
            break;
        case SOCKET_READ_DATA:
            HandleNode((GameUser*)sock_event->getNode(),sock_event->getBytes(),sock_event->getSize());
            break;
    }
}

NetNode* SerHandler::getNode(SOCKET_T fd)
{
    return uMap.getValue(fd);
}

void SerHandler::AddNode(NetNode* node)
{
    if(uMap.has(node->getSockID()))
    {
        node->DisConnect();
        return;
    }
    uMap.put(node->getSockID(), (GameUser*)node);
}

void SerHandler::RemoveNode(NetNode* node)
{
    uMap.remove(node->getSockID());
    SAFE_DELETE(node);
}

void SerHandler::HandleNode(GameUser* node, char* bytes, size_t size)
{
    //TimeUtil::begin();
    if(node->isConnect())
    {
        node->LoadBytes(bytes, size);
        try{
            while(node->HasPacket())
            {
                node->ReadBegin();
                OnPacketHandler(node);
                node->ReadEnd();
            }
        }catch(...){
            node->DisConnect();
        }
    }
    //TimeUtil::end();
}

void SerHandler::OnPacketHandler(GameUser* node)
{
    Log::Info("packet: cmd=%d type=%d", node->getCmd(), node->getType());
    switch(node->getType())
    {
        case SERVER_WORLD_MESSAEGE:
            WorldMsg::getInstance()->OnPacketHandler(node);
            break;
        case SERVER_GAME_MESSAGE:
            GameManager::getInstance()->OnPacketHandler(node);
            break;
        default:
            WorldMsg::getInstance()->OnPacketHandler(node);
            break;
    }
}


void SerHandler::print()
{
    HashMap<SOCKET_T, GameUser*>::Iterator iter;
    std::string str;
    str += "SerHandler fds ={\n";
    for(iter = uMap.begin();iter!=uMap.end();iter++)
    {
        str += StringUtil::format("fd=%d\n",iter->second->getSockID());
    }
    str += "}";
    Log::Debug("%s",str.c_str());
}