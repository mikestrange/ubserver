//
//  string_utils.h
//  ubserver
//
//  Created by MikeRiy on 16/11/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef string_utils_h
#define string_utils_h

#include <stdio.h>
#include <string>
#include <string.h>

#include "global.h"

namespace StringUtil
{
    std::string format(const char* fm, ...);
    
    bool equal(const char* src, const char* other);
    
    bool equal(std::string& src, const char* other);
    
    bool scope(std::string &str, size_t left, size_t right);
}

#define parseByte(v) (v - '\0')

namespace UNIT
{
    int parseInt(const char* src);
    
    int parseInt(std::string& src);
}

#endif /* string_utils_h */
