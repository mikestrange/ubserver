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
#include "coupler.h"
#include "string_util.h"
#include "md5.h"

class DBServer : public DataBank
{
    STATIC_CLASS(DBServer);
public:
    void launch(const char *host);
    
    bool login_with_user(USER_T uid, std::string& password);
    
    bool login_with_device(USER_T uid, std::string& device);
    
    int64 income_money(USER_T uid, int64 money);
    
    bool user_info(USER_T uid);
};

#endif /* DBServer_h */
