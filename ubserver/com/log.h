//
//  log.h
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef log_h
#define log_h

#include <stdio.h>
#include <iostream>
#include "global.h"

#include "lock.h"

#define LOG_DEBUG       Log::getLogger(1)
#define LOG_INFO        Log::getLogger(2)
#define LOG_WARN        Log::getLogger(3)
#define LOG_ERROR       Log::getLogger(4)
#define LOG_END         "\n"

class Log : private Locked
{
    STATIC_CLASS(Log);
public:
    Log& setLogger(int lv);
    
    Log& operator <<(const char* v);
    
    template <class V>
    Log& operator <<(V v)
    {
        std::cout<<v;
        return *this;
    };
    
public:
    static Log& getLogger(int lv);
};

#endif /* log_h */
