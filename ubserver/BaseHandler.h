//
//  BaseHandler.h
//  ubserver
//
//  Created by MikeRiy on 16/12/28.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef BaseHandler_h
#define BaseHandler_h

#include "SocketHandler.h"
#include "CmdDefined.h"
#include "Network.h"
#include "runtime.h"
#include "EventBase.h"
#include "SocketHandler.h"
#include "event.h"


//服务器处理
class BaseHandler : public INetHandler, public EventSet<SocketHandler*>
{
private:
    typedef void(*SOCKET_CALL)(NetContext*, int);
    typedef void(*PACKET_CALL)(SocketHandler*, int);
protected:
    SOCKET_CALL m_connect;
    SOCKET_CALL m_close;
    SOCKET_CALL m_start;
    SOCKET_CALL m_stop;
    SOCKET_CALL m_heartbeat;
    PACKET_CALL m_packet;
public:
    BaseHandler();
    
    void setLoopCall(SOCKET_CALL $connect, SOCKET_CALL $close,
                     PACKET_CALL $packet, SOCKET_CALL $heartbeat,
                     SOCKET_CALL $start, SOCKET_CALL $stop);
    
    void setLoopCall(PACKET_CALL $packet, SOCKET_CALL $other);
public:
    void OnConnect(NetContext* context)override;
    void OnClosed(NetContext* context)override;
    void OnStart(NetContext* context)override;
    void OnStop(NetContext* context)override;
    void OnHeartBeat(NetContext* context)override;
    //读要区分
    void OnPacket(SocketHandler* packet)override;
};

#endif /* BaseHandler_h */
