//
//  WorldServer.c
//  ubserver
//
//  Created by MikeRiy on 16/12/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "WorldServer.h"

STATIC_CLASS_INIT(WorldServer);

NetNode* WorldServer::create_node()
{
    return new HookNode();
}

void WorldServer::OnEvent(EventBase *event)
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
            OnPacketHandler(sock_event);
            break;
        case SOCKET_HEARTBET:
            WorldRep::HeartBead(sock_event->getNode());
            break;
    }
}

NetNode* WorldServer::getNode(SOCKET_T fd)
{
    return uMap.getValue(fd);
}

void WorldServer::AddNode(NetNode* node)
{
    if(uMap.has(node->getSockID()))
    {
        node->DisConnect();
        return;
    }
    uMap.put(node->getSockID(), node);
}

void WorldServer::RemoveNode(NetNode* node)
{
    uMap.remove(node->getSockID());
    //所有链接点
    //ObjectCollect::getInstance()->CloseNode(node->getSockID());
    //--
    SAFE_DELETE(node);
}


void WorldServer::OnPacketHandler(SocketEvent* event)
{
    MsgHandler* message = event->getMessage();
    LOG_INFO("packet: cmd=%d type=%d", message->getCmd(), message->getType());
    try{
        switch(message->getType())
        {
            case SERVER_WORLD_MESSAEGE:
                WorldMsg::getInstance()->OnPacketHandler(event);
                break;
            case SERVER_GAME_MESSAGE:
                //ZoneMsg::getInstance()->OnPacketHandler(event);
                break;
            default:
                WorldMsg::getInstance()->OnPacketHandler(event);
                break;
        }
    }catch(...){
        LOG_WARN("this socket read error fd = %d", event->getNode()->getSockID());
    }
}


void WorldServer::print()
{
    HashMap<SOCKET_T, NetNode*>::Iterator iter;
    std::string str;
    str += "SerHandler fds ={\n";
    for(iter = uMap.begin();iter!=uMap.end();iter++)
    {
        str += StringUtil::format("fd=%d\n",iter->second->getSockID());
    }
    str += "}";
    LOG_DEBUG("%s",str.c_str());
}