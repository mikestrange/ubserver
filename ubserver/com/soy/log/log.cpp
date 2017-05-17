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
static const int LOG_SIZE = 1024;
//默认打印等级
static int logLevel = 1;

void get_date_str(std::string& str)
{
    long ts = time(NULL);
    struct tm *ptm = localtime(&ts);
    int y,m,d,h,n,s;
    y   =   ptm-> tm_year+1900;     //年
    m   =   ptm-> tm_mon+1;             //月
    d   =   ptm-> tm_mday;               //日
    h   =   ptm-> tm_hour;               //时
    n   =   ptm-> tm_min;                 //分
    s   =   ptm-> tm_sec;                 //秒
    str = StringUtil::format("%d/%d/%d %d:%d:%d",y,m,d,h,n,s);
}

void Log::output(const char* log, const char* type)
{
    std::string str;
    //get_date_str(str);
    printf("%s%s%s\n", str.c_str(), type, log);
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
    Log::getInstance()->output(buf, LOG_LIST[LOG_TYPE_DEBUG]);
}

void Log::_Info(const char* fm, ...)
{
    if(logLevel > LOG_TYPE_INFO) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    Log::getInstance()->output(buf, LOG_LIST[LOG_TYPE_INFO]);
}

void Log::_Warn(const char* fm, ...)
{
    if(logLevel > LOG_TYPE_WARN) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    Log::getInstance()->output(buf, LOG_LIST[LOG_TYPE_WARN]);
}

void Log::_Error(const char* fm, ...)
{
    if(logLevel > LOG_TYPE_ERROR) return;
    STR_FORMAT(LOG_SIZE);
    AUTO_LOCK(Log::getInstance());
    Log::getInstance()->output(buf, LOG_LIST[LOG_TYPE_ERROR]);
    throw buf;
}


