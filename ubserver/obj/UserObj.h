//
//  UserObj.h
//  ubserver
//
//  Created by MikeRiy on 16/12/8.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef UserObj_h
#define UserObj_h

#include <stdio.h>
#include "global.h"
#include "DBServer.h"

class UserObj
{
public:
    USER_T user_id;
    int64 money;
    int32 exp;
    int32 vipexp;
    int32 viptype;
    std::string uname;
    //玩家的信息
    UserObj(USER_T uid);
    
private:
    bool is_result;

public:
    bool result();
    
    void update_money(int32 value);
};

#endif /* UserObj_h */
