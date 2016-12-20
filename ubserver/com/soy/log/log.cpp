//
//  log.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "log.h"

STATIC_CLASS_INIT(Log);

typedef enum
{
    LOG_TYPE_NONE,
    LOG_TYPE_DEBUG,
    LOG_TYPE_INFO,
    LOG_TYPE_WARN,
    LOG_TYPE_ERROR
}LOG_LEVEL;

const char* LOG_LIST[] = {"[NONE]", "[DEBUG]","[INFO]","[WARN]","[ERROR]"};
//一个log最长字段
static const int LOG_SIZE = 512;
//默认打印等级
static int logLevel = 1;

void Log::output(const char* log, const char* type)
{
    printf("%s%s\n", type, log);
}

void Log::setLevel(int lv)
{
    logLevel = lv;
}

int Log::getLevel()const
{
    return logLevel;
}

void Log::_Debug(const char* fm, ...)
{
    if(logLevel > LOG_TYPE_DEBUG) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    Log::getInstance()->output(buf, LOG_LIST[logLevel]);
}

void Log::_Info(const char* fm, ...)
{
    if(logLevel > LOG_TYPE_INFO) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    Log::getInstance()->output(buf, LOG_LIST[logLevel]);
}

void Log::_Warn(const char* fm, ...)
{
    if(logLevel > LOG_TYPE_WARN) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    Log::getInstance()->output(buf, LOG_LIST[logLevel]);
}

void Log::_Error(const char* fm, ...)
{
    if(logLevel > LOG_TYPE_ERROR) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    Log::getInstance()->output(buf, LOG_LIST[logLevel]);
    throw "print error";
}


