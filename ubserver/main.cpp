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
#include "DBServer.h"


//const char* host = "116.62.5.118";
const char* host = "127.0.0.1";


void* thread_event(void* arg)
{
    SOCKET_T serid = network::listener(8080);
    if(serid > 0)
    {
        network::epoll_server(serid, SerHandler::getInstance(), 1024);
    }
    return 0;
}

void* thread_socket(void* arg)
{
    SOCKET_T fd = network::connect(host, 8080);
    PacketBuffer bytes;
    bytes.setBegin(SERVER_CMD_LOGIN);
    bytes.WriteBegin();
    bytes.writeUint32(10001);
    bytes.writeString("abc");
    bytes.WriteEnd();
    
    NET_SEND_PACKET(fd, &bytes);
    NET_CLOSE(fd);
    return 0;
}

//输入
void vim_complete(DataArray* array)
{
    try{
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
            Thread::create(&thread_socket);
        }else if(StringUtil::equal(str, "db")){
            DBServer::getInstance()->launch("116.62.5.118");
        }else if(StringUtil::equal(str, "sql")){
            DataQuery result;
            std::string sql;
            sql = array->readString();
            DBServer::getInstance()->find(result, sql.c_str());
            result.toString();
        }
    }catch(...){
        std::cout<<"[输入有误]"<<std::endl;
    }
}

Keeper kep(0,1);

int main(int argc, const char * argv[])
{
    //
    RunTime::getInstance()->launch();
    //
    epoll_input([](DataArray* data)
    {
        RUN_MAIN(NewBlock(data, &vim_complete));
    });
    return 0;
}
