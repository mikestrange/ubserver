//
//  GameUser.h
//  ubserver
//  1对1的连接
//  Created by MikeRiy on 16/12/28.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GameUser_h
#define GameUser_h

#include <stdio.h>
#include "NetContext.h"

class GameUser : public NetContext
{
public:
    GameUser(SOCKET_T fd);
};

#endif /* GameUser_h */
