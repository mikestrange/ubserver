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
#include "memorys.h"
#include "network.h"
#include "GameManager.h"
#include "client.h"

class NetLink;

class SerEvent : public RunTask
{
private:
    int type;
    NetLink* m_link;
    char* bytes;
    size_t size;
public:
    SerEvent(int type, NetLink* link, char* bytes, size_t size);
    
    SerEvent(int type, NetLink* link);
    
    virtual ~SerEvent();
    //任务自己处理
    void OnTaskHandler()override;
    
    void OnPacketHandler(SocketHandler* client);
};


#endif /* SerTask_h */
