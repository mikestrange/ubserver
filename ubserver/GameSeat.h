//
//  GameSeat.h
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GameSeat_h
#define GameSeat_h

#include <stdio.h>
#include "global.h"

class GameSeat
{
public:
    SEAT_T seat_id;
    USER_T user_id;
public:
    GameSeat();
    virtual ~GameSeat();
    
};

#endif /* GameSeat_h */
