//
//  SerHandler.h
//  ubserver
//
//  Created by MikeRiy on 16/12/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef SerHandler_h
#define SerHandler_h

#include <stdio.h>
#include "NetServer.h"
#include "hashmap.h"
#include "GameUser.h"
#include "CmdDefined.h"

#include "WorldMsg.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "WorldRep.h"

class SerHandler : public NetServer
{
    STATIC_CLASS(SerHandler);
private:
    HashMap<SOCKET_T, GameUser*> uMap;
    
public:
    NetNode* create_node()override;
public:
    void OnEvent(EventBase* event)override;
    
    void print();
    
    NetNode* getNode(SOCKET_T fd);
    
private:
    void AddNode(NetNode* node);
    
    void RemoveNode(NetNode* node);
    
    void HandleNode(GameUser* node, char* bytes, size_t size);
    
    void OnPacketHandler(GameUser* node);
};

#endif /* SerHandler_h */
