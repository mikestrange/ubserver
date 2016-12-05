//
//  coupler.c
//  ubserver
//
//  Created by MikeRiy on 16/12/2.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "coupler.h"


DBCoupler::DBCoupler(DataBank* value)
:target(value)
{
    target->reconnect();
}


DBCoupler::~DBCoupler()
{
    target->close();
}


DataBank& DBCoupler::SQL()const
{
    return *target;
}