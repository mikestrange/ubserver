//
//  main.cpp
//  ubserver
//
//  Created by MikeRiy on 16/11/9.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include <iostream>

#include "network.h"
#include "log.h"
#include "string_util.h"
#include "input.h"

#include "SerHandler.h"
#include "WorldMsg.h"
#include "GameManager.h"

#include "keeper.h"


//const char* host = "116.62.5.118";
const char* host = "127.0.0.1";


void* thread_event(void* arg)
{
    SOCKET_T serid = network::listener(8080);
    if(serid > 0)
    {
        network::epoll_server(serid, SerHandler::getInstance(), 1023);
    }
    return 0;
}

void* thread_event2(void* arg)
{
    SOCKET_T fd = network::connect(host, 8080);
    PacketBuffer bytes;
    bytes.setBegin(SERVER_CMD_LOGIN);
    bytes.WriteBegin();
    bytes<<"这是一个励志的故事";
    bytes.WriteEnd();
    
    while(1)
    {
        NET_SEND_PACKET(fd, &bytes);
        sleep(1);
    }
    //NET_CLOSE(fd);
}

//输入
void vim_complete(DataArray* array)
{
    std::string str;
    str = array->readString();
    std::cout<<"输入:"<<str<<std::endl;
    if(StringUtil::equal(str, "exit"))
    {
        std::cout<<"[进程已完成]"<<std::endl;
        exit(0);
    }else if(StringUtil::equal(str, "run")){
        Thread::create(&thread_event);
    }else if(StringUtil::equal(str, "print")){
        SerHandler::getInstance()->Print();
    }else if(StringUtil::equal(str, "send")){
        Thread::create(&thread_event2);
    }
}

Keeper kep(0,1);

int main(int argc, const char * argv[])
{
    RunTime::getInstance()->launch();
    kep.restart(10000);
    //
    epoll_input([](DataArray* data)
    {
        RUN_MAIN(NewBlock(data, &vim_complete));
    });
    return 0;
}
