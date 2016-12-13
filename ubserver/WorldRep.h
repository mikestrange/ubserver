//
//  WorldRep.h
//  ubserver
//
//  Created by MikeRiy on 16/12/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef WorldRep_h
#define WorldRep_h

#include <stdio.h>
#include "global.h"
#include "GameUser.h"

class GameUser;

class WorldRep
{
    STATIC_CLASS(WorldRep);
public:
    static void HeartBead(GameUser* sock);
    static void Login(GameUser* sock, int8 code);
    static void Logout(GameUser* sock, int8 code);
    
};

#endif /* WorldRep_h */
