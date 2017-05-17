//
//  physics.h
//  ubserver
//
//  Created by MikeRiy on 17/1/6.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef physics_h
#define physics_h

#include "global.h"

class Rect
{
public:
    int32 x;
    int32 y;
    int32 width;
    int32 height;
    
    Rect(int32 x = 0, int32 y = 0, int32 width = 0, int32 height = 0)
    :x(x)
    ,y(y)
    ,width(width)
    ,height(height)
    {
        
    };
};



class Point2D
{
public:
    int32 x;
    int32 y;
    
    Point2D(int32 x = 0, int32 y = 0)
    :x(x)
    ,y(y)
    {
        
    };
};


#endif /* physics_h */
