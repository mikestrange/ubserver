//
//  BatPlayer.h
//  ubserver
//
//  Created by MikeRiy on 17/1/5.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef BatPlayer_h
#define BatPlayer_h

#include "global.h"
#include "ByteArray.h"
#include "time_util.h"


class BatPlayer : public IReader
{
public:
    USER_T user_id;
    //位置，区域
    uint8 camp_id;      //阵营
    uint8 map_id;
    uint8 state;        //状态
    int16 x;
    int16 y;
public:
    TIME_T state_time;
    TIME_T begin_time;
public:
    BatPlayer();
    
    BatPlayer(ByteStream& bytes);
    //移动角色
    void MoveTo(int16 x, int16 y, uint8 mid = 0);
    //
    void UpdateState(int8 val);
    //
    void UpdateTime();
    //
    void ReadCode(ByteStream& bytes)override;
};

#endif /* BatPlayer_h */
