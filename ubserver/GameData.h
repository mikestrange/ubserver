//
//  GameData.h
//  ubserver
//  房间的游戏数据
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GameData_h
#define GameData_h

#include <stdio.h>
#include "global.h"

class GameData
{
public:
    TABLE_ID table_id;          //房间id
    int16 table_type;           //房间类型
    int16 table_rule;           //房间规则类型
    
    int16 max_players;          //可以容纳最大人数
    int8 seat_max;              //最大座位数
    
    int32 chip_base;            //牌局倍数
    int32 enter_min_chip;       //进入下限
    //动态
    int8 current_seat;          //当前坐下人数
    int16 current_players;      //当前房间人数(包含坐下)
    
    GameData(TABLE_ID a1, int16 a2, int16 a3,
             int16 a4, int8 a5,
             int32 a6, int32 a7,
             int8 a8 = 0, int16 a9 = 0);
    
    virtual ~GameData();
};

#endif /* GameData_h */
