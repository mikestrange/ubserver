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
        return str.length()>=left && str.length() <= right;
    }
}


namespace Basal
{
    int parseInt(const char* src)
    {
        return atof(src);
    }
    
    int parseInt(std::string& src)
    {
        return parseInt(src.c_str());
    }
}

