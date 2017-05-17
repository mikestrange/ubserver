//
//  GateHandler.c
//  ubserver
//
//  Created by MikeRiy on 16/12/27.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GateHandler.h"

static void gate_sendto_world(SocketHandler* packet)
{
    
}

static void gate_sendto_game(SocketHandler* packet)
{
    
}

static void packet_handler(SocketHandler* packet, int type)
{
    try{
        packet->ReadBegin();
        //
        switch(packet->getType())
        {
            case SERVER_GATE_MESSAGE:
                GateHandler::getInstance()->SendEvent(packet->getCmd(), packet, packet->getType());
                break;
            case SERVER_WORLD_MESSAEGE:
                gate_sendto_world(packet);
                break;
            case SERVER_GAME_MESSAGE:
                gate_sendto_game(packet);
                break;
            default:
                GateHandler::getInstance()->SendEvent(packet->getCmd(), packet, packet->getType());
                break;
        }
    }catch(...){
        
    }
    SAFE_DELETE(packet);
}

static void socket_handler(NetContext* context, int type)
{
    switch(type)
    {
        case SOCKET_LISTEN:
            break;
        case SOCKET_OVEREND:
            SAFE_DELETE(context);
            break;
        case SOCKET_CONNECT:
            break;
        case SOCKET_CLOSED:
            SAFE_DELETE(context);
            break;
        case SOCKET_HEARTBET:
            GateRep::HeartBead(context);
            break;
    }
}

//class
STATIC_CLASS_INIT(GateHandler);

GateHandler::GateHandler()
{
    //回执
    setLoopCall(packet_handler, socket_handler);
    //
    
}

NetContext* GateHandler::alloc_context(SOCKET_T fd)
{
    return new GameUser(fd);
}