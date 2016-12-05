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