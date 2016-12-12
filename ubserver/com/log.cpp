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
//一个log最长字段
static const int LOG_SIZE = 512;
//默认打印等级
static int logLevel = 1;

static void output(const char* log, const char* type)
{
    printf("[%s]%s\n", type, log);
}

void Log::setLogLevel(int lv)
{
    logLevel = lv;
}

void Log::Debug(const char* fm, ...)
{
    if(logLevel > LOG_DEBUG) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    output(buf, LOG_LIST[logLevel]);
}

void Log::Info(const char* fm, ...)
{
    if(logLevel > LOG_INFO) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    output(buf, LOG_LIST[logLevel]);
}

void Log::Warn(const char* fm, ...)
{
    if(logLevel > LOG_WARN) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    output(buf, LOG_LIST[logLevel]);
}

void Log::Error(const char* fm, ...)
{
    if(logLevel > LOG_ERROR) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    output(buf, LOG_LIST[logLevel]);
}


