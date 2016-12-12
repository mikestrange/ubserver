//
//  UserObj.c
//  ubserver
//
//  Created by MikeRiy on 16/12/8.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "UserObj.h"

UserObj::UserObj(USER_T uid)
:user_id(uid)
,money(0)
,exp(0)
,vipexp(0)
,viptype(0)
,is_result(false)
{
    
}

bool UserObj::result()
{
    if(is_result) return true;
    //
    DataQuery result;
    DBCoupler sql(DBServer::getInstance());
    sql.SQL().findFormat(result, "select * from player where uid = '%d'", user_id);
    //
    if(!result.empty())
    {
        money = UNIT::parseInt64(result["money"]->value);
        exp = UNIT::parseInt(result["exp"]->value);
        vipexp = UNIT::parseInt(result["vipexp"]->value);
        viptype = UNIT::parseInt(result["viptype"]->value);
        uname = result["name"]->value;
        is_result = true;
    }
    return is_result;
}

void UserObj::update_money(int32 value)
{
    money = DBServer::getInstance()->income_money(user_id, value);
}