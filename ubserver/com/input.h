//
//  input.h
//  ubserver
//
//  Created by MikeRiy on 16/11/11.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef input_h
#define input_h

#include <iostream>
#include <stdio.h>

#include "data_array.h"
#include "log.h"

//class method
void analytic(DataArray *array, const char* bytes, int size)
{
    array->clear();
    int sub_len = 0;
    int prev_pos = 0;
    for(int i = 0; i < size; i++)
    {
        if(memcmp(&bytes[i], ",", 1) == 0)
        {
            char byte[sub_len + 1];
            memcpy(byte, &bytes[prev_pos], sub_len);
            byte[sub_len] = '\0';
            array->WriteChars(byte, sub_len + 1);
            //argLen++;
            prev_pos = i + 1;
            sub_len = 0;
        }else{
            sub_len++;
        }
        //最后
        if(i == size - 1 && sub_len > 0)
        {
            char byte[sub_len + 1];
            memcpy(byte, &bytes[prev_pos], sub_len);
            byte[sub_len] = '\0';
            array->WriteChars(byte, sub_len + 1);
            //argLen++;
        }
    }
}

#define MAX_INPUT 1024

template <class FUN>
void epoll_input(FUN fun)
{
    DataArray input_data;
    std::string str;
    while(getline(std::cin, str))
    {
        analytic(&input_data, str.c_str(), (int)str.length());
        try{
            fun(&input_data);
        }catch(...){
            LOG_DEBUG<<"#@input handle error"<<LOG_END;
        }
        str.clear();
    };
    LOG_DEBUG<<"input exit!"<<LOG_END;
}

#endif /* input_h */
