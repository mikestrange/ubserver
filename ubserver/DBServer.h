//
//  DBServer.h
//  ubserver
//
//  Created by MikeRiy on 16/11/15.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef DBServer_h
#define DBServer_h

#include <stdio.h>
#include "global.h"
#include "data_bank.h"

class DBServer : public DataBank
{
    STATIC_CLASS(DBServer);
public:
    void launch(const char *host);
};

#endif /* DBServer_h */
