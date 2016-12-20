//
//  WorldServer.h
//  ubserver
//
//  Created by MikeRiy on 16/12/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef WorldServer_h
#define WorldServer_h

#include "hashmap.h"
#include "NetServer.h"

#include "CmdDefined.h"

#include "HookNode.h"
#include "WorldMsg.h"
#include "WorldRep.h"
#include "ObjectCollect.h"

//区块服务器
#include "ZoneMsg.h"

class WorldServer : public NetServer
{
    STATIC_CLASS(WorldServer);
private:
    HashMap<SOCKET_T, NetNode*> uMap;
    
public:
    NetNode* create_node()override;
public:
    void OnEvent(EventBase* event)override;
    
    void print();
    
    NetNode* getNode(SOCKET_T fd);
    
private:
    void AddNode(NetNode* node);
    
    void RemoveNode(NetNode* node);
    
    void OnPacketHandler(SocketEvent* event);
};


#endif /* WorldServer_h */
