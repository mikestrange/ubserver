//
//  log.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "log.h"

STATIC_CLASS_INIT(Log);

const char* LOG_LIST[] = {"[NONE]", "[DEBUG]","[INFO]","[WARN]","[ERROR]"};

Log& Log::getLogger(int lv)
{
    return Log::getInstance()->setLogger(lv);
}

Log& Log::setLogger(int lv)
{
    //lock();
    std::cout<<LOG_LIST[lv];
    return *this;
}

Log& Log::operator <<(const char* v)
{
    if(v == LOG_END)
    {
        std::cout<<std::endl;
        //unlock();
    }else{
        std::cout<<v;
    }
    return *this;
};