#include "string_util.h"

namespace StringUtil
{
    std::string format(const char* fm, ...)
    {
        std::string ret;
        STR_FORMAT(1024);
        ret = buf;
        return ret;
    }
    
    bool equal(const char* src, const char* other)
    {
        return strcmp(src, other) == 0;
    }
    
    bool equal(std::string& src, const char* other)
    {
        return equal(src.c_str(), other);
    }
    
    bool scope(std::string &str, size_t left, size_t right)
    {
        return str.length() >= left && str.length() <= right;
    }
}


namespace soy
{
    int32 parseInt(const char* src)
    {
        return atof(src);
    }
    
    int32 parseInt(std::string& src)
    {
        return parseInt(src.c_str());
    }
    
    int64 parseInt64(const char* src)
    {
        int64 retval;
        retval = 0;
        for (; *src; src++)
        {
            retval = 10*retval + (*src - '0');
        }
        return retval;
    }
    
    int64 parseInt64(std::string& src)
    {
        return parseInt64(src.c_str());
    }
}

