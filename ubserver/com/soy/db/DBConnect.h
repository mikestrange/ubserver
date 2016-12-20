//
//  DBConnect.h
//  ubserver
//
//  Created by MikeRiy on 16/12/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef DBConnect_h
#define DBConnect_h

#include "data_bank.h"

class DataBank;

class DBConnect
{
private:
    DataBank* target;
public:
    DBConnect(DataBank* value);
    
    virtual ~DBConnect();
    
    DataBank& SQL()const;
    
};

#endif /* DBConnect_h */
