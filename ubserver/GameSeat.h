//
//  GameSeat.h
//  ubserver
//  游戏座位的逻辑
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GameSeat_h
#define GameSeat_h

#include <stdio.h>
#include "global.h"
#include "hashmap.h"

class GameSeat
{
private:
    SEAT_T seat_id;
    USER_T user_id;
    
public:
    GameSeat(USER_T uid);
    virtual ~GameSeat();
    
    SEAT_T StandUp();
    
    void SitDown(SEAT_T sid);
    
    bool isSitDown()const;
    
    bool isStand()const;
    
    USER_T getUserID()const;
    
    SEAT_T getSeatID()const;
};

#endif /* GameSeat_h */
