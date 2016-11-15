//
//  SerTask.h
//  ubserver
//  服务器的任务处理
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef SerTask_h
#define SerTask_h

#include <stdio.h>
#include "runtime.h"
#include "client.h"
#include "SerHandler.h"
#include "WorldMsg.h"
#include "memory_pool.h"
#include "network.h"
#include "GameManager.h"
#include "client.h"

class SerTask : public RunTask
{
private:
    int type;
    SOCKET_T fd;
    char* bytes;
    size_t size;
public:
    SerTask(int type, SOCKET_T fd, char* bytes, size_t size);
    
    SerTask(int type, SOCKET_T fd);
    
    virtual ~SerTask();
    //任务自己处理
    void OnTaskHandler()override;
    
    void OnPacketHandler(SocketHandler* client);
};


#endif /* SerTask_h */
