//
//  log.h
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef log_h
#define log_h

#include <iostream>

#include "global.h"
#include "lock.h"
#include "string_util.h"

class Log : private Locked
{
    STATIC_CLASS(Log);
public:
    void setLevel(int lv);
    
    int getLevel()const;
    
    void output(const char* log, const char* type);
    
public:
    static void _Debug(const char* fm, ...);
    
    static void _Info(const char* fm, ...);
    
    static void _Warn(const char* fm, ...);
    
    static void _Error(const char* fm, ...);
};

#define LOG_DEBUG(fm, args...) Log::_Debug(fm, ##args)
#define LOG_INFO(fm, args...) Log::_Info(fm, ##args)
#define LOG_WARN(fm, args...) Log::_Warn(fm, ##args)
#define LOG_ERROR(fm, args...) Log::_Error(fm, ##args)

#endif /* log_h */
