//
//  log.c
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "log.h"

STATIC_CLASS_INIT(Log);


Log& Log::getLogger(int lv)
{
    return Log::getInstance()->setLogger(lv);
}