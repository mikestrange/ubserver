//
//  GamePuzzle.h
//  ubserver
//  老虎机主要算法
//  Created by MikeRiy on 16/11/17.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GamePuzzle_h
#define GamePuzzle_h

#include <stdio.h>

//苹果1，橘子2，哈密瓜3，铃铛4，西瓜5，星6，七7，鬼8
static const int MAX_BET = 24;
static const int MAX_TYPE = 8;
static const int TIGER_BET_LIST[MAX_BET] = {10,20,60,120,5,2,15,20,2,0,5,2,10,20,2,40,5,15,2,30,2,0,5,2};
static const int TIGER_TYPE_LIST[MAX_BET] = {2, 4,8, 8,  1,1,3, 5, 5,0,1,2,2, 4, 7,7, 1,3, 3, 6,6,0,1,4};

class GamePuzzle
{
public:
};

#endif /* GamePuzzle_h */
