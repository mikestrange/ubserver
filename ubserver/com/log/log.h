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

typedef enum
{
    LOG_NONE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
}LOG_LEVEL;

class Log : private Locked
{
    STATIC_CLASS(Log);
public:
    void setLogLevel(int lv);
    
    static void Debug(const char* fm, ...);
    
    static void Info(const char* fm, ...);
    
    static void Warn(const char* fm, ...);
    
    static void Error(const char* fm, ...);
};

#endif /* log_h */
