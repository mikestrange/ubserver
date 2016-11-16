//
//  PlayerManager.h
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef PlayerManager_h
#define PlayerManager_h

#include <stdio.h>
#include "global.h"
#include "hashmap.h"
#include "Player.h"
#include "packet_buffer.h"
#include "SerHandler.h"

#include "log.h"

class PlayerManager
{
    STATIC_CLASS(PlayerManager);
    
private:
    HashMap<USER_T, Player*> m_players;
public:
    bool AddPlayer(Player* player);
    
    void DelPlayer(USER_T uid);
    
    void SendPlayer(USER_T uid, PacketBuffer& buffer);
};

#endif /* PlayerManager_h */
