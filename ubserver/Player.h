//
//  Player.h
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include "global.h"
#include "client.h"
#include "GameManager.h"

class GameManager;

class Player
{
private:
    SocketHandler* _sock;
public:
    USER_T user_id;
    SOCKET_T sock_id;
    TABLE_ID view_id;
    
    Player(USER_T uid, SocketHandler* sock);

    SocketHandler* getSocket()const;
    
    virtual ~Player();
    
    void ExitRoom();
    
    bool EnterRoom(TABLE_ID tid);
};

#endif /* Player_h */
