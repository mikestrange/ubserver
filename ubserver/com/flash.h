//
//  flash.h
//  ubserver
//
//  Created by MikeRiy on 16/12/29.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef flash_h
#define flash_h

#include <stdio.h>
#include "Network.h"


class FlashHandler : public INetHandler
{
    STATIC_CLASS(FlashHandler);
public:
    void OnReadHandler(NetContext* context, char* bytes, size_t size)override;
    //服务器的退出
    void OnStop(NetContext* context)override;
    //关闭一个连接
    void OnClosed(NetContext* context)override;
};

void flash_domain();


#endif /* flash_h */
