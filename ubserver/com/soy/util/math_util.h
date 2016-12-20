//
//  math_util.h
//  ubserver
//
//  Created by MikeRiy on 16/11/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef math_util_h
#define math_util_h

#include <stdio.h>
#include <stdlib.h>
#include "time_util.h"


namespace Math
{
    void SRandom();
    
    //0-(a-1)
    int Random(int a);
    
    //a1 - a2
    int Random(int a1, int a2);
}



#endif /* math_util_h */
