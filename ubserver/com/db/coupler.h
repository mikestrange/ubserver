//
//  coupler.h
//  ubserver
//
//  Created by MikeRiy on 16/12/2.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef coupler_h
#define coupler_h

#include <stdio.h>
#include "data_bank.h"

class DataBank;

class DBCoupler
{
private:
    DataBank* target;
public:
    DBCoupler(DataBank* value);
    
    virtual ~DBCoupler();
    
    DataBank& SQL()const;
    
};

#endif /* coupler_h */
