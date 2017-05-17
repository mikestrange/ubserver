//
//  base64.h
//  ubserver
//
//  Created by MikeRiy on 16/12/31.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef base64_h
#define base64_h

#include <iostream>
#include "global.h"

namespace soy
{
    //编码加密
    void base64_encode(std::string const &str, std::string& result);
    //解码解密
    void base64_decode(std::string const& encoded_string, std::string& result);
}

//test
void base64_test();

#endif /* base64_h */
