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

//ser type
enum
{
    SERVER_GATE_MESSAGE = 1,//1
    SERVER_WORLD_MESSAEGE,//2
    SERVER_GAME_MESSAGE,//3
    SERVER_BAT_MESSAGE,
};


//cmds
enum{
    SERVER_CMD_TEST = 10,
    SERVER_CMD_HEARTBEAT = 11,
    SERVER_CMD_GET_LINE_INFO = 12,  //获取在线人数信息
    SERVER_CMD_GET_PING,            //获取服务器时间
    //
    SERVER_CMD_HOOK_REG = 20,
    SERVER_CMD_HOOK_UNREG,
    //登录
    SERVER_CMD_LOGIN = 101,
    SERVER_CMD_LOGOUT,
    //签到
    SERVER_CMD_TIME_REWARD = 200,
    SERVER_CMD_GET_SIGNIN_INFO,//签到信息
    SERVER_CMD_SIGNIN_REWARD,//领取
    //聊天
    SERVER_CMD_CHAR_MSG = 301,
    //房间
    SERVER_CMD_GAME_ROOM_DATA = 1000,
    SERVER_CMD_GAME_ENTER,
    SERVER_CMD_GAME_ENTER_ERROR,
    SERVER_CMD_GAME_EXIT,
    SERVER_CMD_GAME_SITDOWN,
    SERVER_CMD_GAME_STAND,
};


//tiger cmds
enum TIGER_GAME_CMDS
{
    SERVER_CMD_TIGER_GSTART = 2001,
    SERVER_CMD_TIGER_GSTOP,
    SERVER_CMD_TIGER_GBET,
    SERVER_CMD_TIGER_GRESULT,
    SERVER_CMD_TIGER_GPOT_CHIPS,
};

enum MEBAT_GAME_CMDS
{
    SERVER_CLIENT_BAT_JOIN = 3001,
    SERVER_CLIENT_BAT_PLAYER_MOVE,
    SERVER_CLIENT_BAT_RELEASE_SKILL,
    SERVER_CLIENT_BAT_EXIT,
};

#endif /* CmdDefined_h */


