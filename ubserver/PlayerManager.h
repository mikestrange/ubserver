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

class PlayerManager
{
    STATIC_CLASS(PlayerManager);
    
private:
    HashMap<USER_T, Player*> hash;
public:
    bool AddPlayer();
    void DelPlayer();
};

#endif /* PlayerManager_h */
