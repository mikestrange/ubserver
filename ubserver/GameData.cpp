//
//  GameData.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "GameData.h"

GameData::GameData(TABLE_ID a1, int16 a2, int16 a3,
                   int16 a4, int8 a5,
                   int32 a6, int32 a7,
                   int8 a8, int16 a9)
:table_id(a1)
,table_type(a2)
,table_rule(a3)

,max_players(a4)
,seat_max(a5)
,chip_base(a6)
,enter_min_chip(a7)
,current_seat(a8)
,current_players(a9)
{
    
}


GameData::~GameData()
{
    
}