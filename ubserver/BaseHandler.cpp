//
//  BaseHandler.c
//  ubserver
//
//  Created by MikeRiy on 16/12/28.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "BaseHandler.h"

//class
BaseHandler::BaseHandler()
:m_connect(NULL)
,m_close(NULL)
,m_heartbeat(NULL)
,m_start(NULL)
,m_stop(NULL)
,m_packet(NULL)
{
    
}

void BaseHandler::setLoopCall(SOCKET_CALL $connect, SOCKET_CALL $close,
                              PACKET_CALL $packet, SOCKET_CALL $heartbeat,
                              SOCKET_CALL $start, SOCKET_CALL $stop)
{
    m_connect = $connect;
    m_close = $close;
    m_packet = $packet;
    m_heartbeat = $heartbeat;
    m_start = $start;
    m_stop = $stop;
}

void BaseHandler::setLoopCall(PACKET_CALL $packet, SOCKET_CALL $other)
{
    setLoopCall($other, $other, $packet, $other, $other, $other);
}

void BaseHandler::OnConnect(NetContext* context)
{
    RUN_SMAIN(m_connect, context, SOCKET_CONNECT);
}

void BaseHandler::OnClosed(NetContext* context)
{
    RUN_SMAIN(m_close, context, SOCKET_CLOSED);
}

void BaseHandler::OnHeartBeat(NetContext* context)
{
    RUN_SMAIN(m_heartbeat, context, SOCKET_HEARTBET);
}

void BaseHandler::OnPacket(SocketHandler* packet)
{
    RUN_SMAIN(m_packet, packet, SOCKET_READ_DATA);
}

void BaseHandler::OnStart(NetContext* context)
{
    RUN_SMAIN(m_start, context, SOCKET_LISTEN);
}

void BaseHandler::OnStop(NetContext* context)
{
    RUN_SMAIN(m_stop, context, SOCKET_OVEREND);
}
