//
//  DBServer.c
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "DBServer.h"


STATIC_CLASS_INIT(DBServer);


void DBServer::launch(const char *host)
{
    const char *user = "root";
    const char *pswd = "123456";
    const char *table = "games";
    unsigned int port = 3306;
    setup(host, user, pswd, table, port);
}

bool DBServer::login_with_user(USER_T uid, std::string& password)
{
    DataQuery result;
    DBCoupler sql(this);
    MD5 md5(password);
    sql.SQL().findFormat(result, "select uid from account where uid = '%d' and pwd = '%s'", uid, md5.md5().c_str());
    return result.empty() == false;
}

bool DBServer::login_with_device(USER_T uid, std::string& device)
{
    DataQuery result;
    DBCoupler sql(this);
    sql.SQL().findFormat(result, "select uid from account where uid = '%d' and device = '%s'", uid, device.c_str());
    return result.empty() == false;
}

int64 DBServer::income_money(USER_T uid, int64 money)
{
    DataQuery result;
    DBCoupler sql(this);
    sql.SQL().findFormat(result, "select money from player where uid = '%d'", uid);
    //result.toString();
    if(!result.empty())
    {
        int64 value = UNIT::parseInt64(result["money"]->value) + money;
        if(value < 0) value = 0;
        sql.SQL().applyFormat("UPDATE player SET money = '%lld' where uid = '%d'", value, uid);
        return value;
    }
    return 0;
}