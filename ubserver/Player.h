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
#include "GameUser.h"
#include "GameManager.h"

class GameManager;
class GameUser;

class Player
{
private:
    GameUser* m_sock;
private:
    USER_T user_id;
    TABLE_ID view_id;
    
public:
    Player(USER_T uid, GameUser* sock);
    
    virtual ~Player();

    void LinkSocket(GameUser* node);
    
    void UnLinkSocket();
    
    bool isLinkSocket()const;
    
    GameUser* getSocket()const;
    
public:
    
    void ExitRoom();
    
    bool EnterRoom(TABLE_ID tid);
    
    USER_T getUserID()const;
};

#endif /* Player_h */
