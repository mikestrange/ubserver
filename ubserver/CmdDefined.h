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

//types
enum
{
    SERVER_WORLD_MESSAEGE = 1,
    SERVER_GAME_MESSAGE,
};


//cmds
enum{
    SERVER_CMD_TEST = 1,
    
    SERVER_CMD_HEARTBEAT = 11,
    
    SERVER_CMD_LOGIN = 101,
    SERVER_CMD_LOGOUT,
    
    SERVER_CMD_GAME_ROOM_DATA = 1000,
    SERVER_CMD_GAME_ENTER,
    SERVER_CMD_GAME_EXIT,
    SERVER_CMD_GAME_SITDOWN,
    SERVER_CMD_GAME_STAND,
    
};

enum TIGER_GAME_CMDS
{
    SERVER_CMD_TIGER_GSTART = 2001,
    SERVER_CMD_TIGER_GSTOP,
    SERVER_CMD_TIGER_GBET,
    SERVER_CMD_TIGER_GRESULT,
    SERVER_CMD_TIGER_GPOT_CHIPS,
};
#endif /* CmdDefined_h */


