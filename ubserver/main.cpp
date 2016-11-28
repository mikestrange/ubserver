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

#include "clock.h"
#include "DBServer.h"
#include "time_util.h"
#include "netsock.h"

//const char* host = "116.62.5.118";
const char* host = "127.0.0.1";
const int port = 8080;

NetSocket m_socket;

void* thread_event(void* arg)
{
    SOCKET_T serid = network::listener(port);
    if(serid > 0)
    {
        network::epoll_server(serid, SerHandler::getInstance());
    }
    return 0;
}

void* thread_socket(void* arg)
{
    m_socket.Connect(host, port);
    //--
    PacketBuffer bytes;
    //登录
    bytes.setBegin(SERVER_CMD_LOGIN);
    bytes.WriteBegin();
    bytes.writeUint32(10001);
    bytes.writeString("abc");
    bytes.WriteEnd();
//    //进入房间
    bytes.setBegin(SERVER_CMD_GAME_ENTER, SERVER_GAME_MESSAGE, 101);
    bytes.WriteBegin();
    bytes.WriteEnd();
    //下注
    for(int i = 0;i<30;i++)
    {
        bytes.setBegin(SERVER_CMD_TIGER_GBET, SERVER_GAME_MESSAGE, 101);
        bytes.WriteBegin();
        bytes.writeInt8(1+i%8);
        bytes.writeUint32(100);
        bytes.WriteEnd();
    }
    m_socket.SendPacket(bytes);
    return 0;
}

//输入
void vim_complete(DataArray* array)
{
    try{
        std::string str;
        str = array->readString();
        LOG_DEBUG<<"输入:"<<str<<LOG_END;
        if(StringUtil::equal(str, "exit"))
        {
            LOG_DEBUG<<"[进程已完成]"<<LOG_END;
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
        LOG_DEBUG<<"[输入有误]"<<LOG_END;
    }
}


int main(int argc, const char * argv[])
{
    RunTime::getInstance()->launch();
    //--
    epoll_input([](DataArray* data)
    {
        RUN_MAIN(NewBlock(data, &vim_complete));
    });
    return 0;
}
