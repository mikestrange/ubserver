//
//  CmdDefined.h
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef CmdDefined_h
#define CmdDefined_h

#include <stdio.h>


enum
{
    SERVER_WORLD_MESSAEGE = 1,
    SERVER_GAME_MESSAGE,
};

enum{
    SERVER_CMD_LOGIN = 101,
    SERVER_CMD_LOGOUT,
    
    SERVER_CMD_GAME_ENTER = 1001,
    SERVER_CMD_GAME_EXIT,
    SERVER_CMD_GAME_SITDOWN,
    SERVER_CMD_GAME_STAND,
    
};


#endif /* CmdDefined_h */


