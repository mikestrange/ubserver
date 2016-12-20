//
//  DBConnect.c
//  ubserver
//
//  Created by MikeRiy on 16/12/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "DBConnect.h"


DBConnect::DBConnect(DataBank* value)
:target(value)
{
    target->reconnect();
}


DBConnect::~DBConnect()
{
    target->close();
}

DataBank& DBConnect::SQL()const
{
    return *target;
}