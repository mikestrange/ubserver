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

#include "DBServer.h"
#include "time_util.h"
#include "netsock.h"

#include "md5.h"

//const char* host = "120.77.149.74";
//const char* host = "116.62.5.118";
const char* host = "127.0.0.1";
const int port = 8081;

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
    m_socket.Connect("127.0.0.1", port);
    //--
    PacketBuffer bytes;
    //登录
    bytes.setBegin(SERVER_CMD_LOGIN);
    bytes.WriteBegin();
    bytes.writeInt8(102);
    bytes.writeUint32(10001);
    bytes.writeString("abc");
    bytes.WriteEnd();
    //进入房间
    bytes.setBegin(SERVER_CMD_GAME_ENTER, SERVER_GAME_MESSAGE, 101);
    bytes.WriteBegin();
    bytes.WriteEnd();
    //
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
        }else if(StringUtil::equal(str, "sql")){
            DataQuery result;
            std::string sql;
            sql = array->readString();
            DBServer::getInstance()->find(result, sql.c_str());
            result.toString();
        }else if(StringUtil::equal(str, "cut")){
            std::string id;
            id = array->readString();
            int sockid = UNIT::parseInt(id);
            auto socket = SerHandler::getInstance()->GetClient(sockid);
            if(socket)
            {
                socket->Disconnect();
            }
        }else if(StringUtil::equal(str, "out")){
            //system("kill %2");
        }
    }catch(...){
        LOG_DEBUG<<"[输入有误]"<<LOG_END;
    }
}

void start_server(int argc)
{
    thread_event(0);
}

//用户id生成
void test()
{
    DataQuery result;
    DBCoupler sql(DBServer::getInstance());
    int min = 100000;
    int max = 110000;
    const int len = max - min;
    int ran[len];
    //初始化
    for(int i = 0;i<len;i++)
    {
        ran[i] = min + i;
    }
    //随机算法
    for(int i = 0;i<len;i++)
    {
        int r = Math::Random(len);
        int temp = ran[0];
        ran[0] = ran[r];
        ran[r] = temp;
    }
    //开始插入
    for(int i = 0;i<len;i++)
    {
        //std::cout<<ran[i]<<",";
        //sql.SQL().applyFormat("INSERT INTO  `openreg` (`uid`)VALUES ('%d')", ran[i]);
    }
    printf("LOGEND\n");
    //sql.SQL().applyFormat("INSERT INTO  `openreg` (`uid`)VALUES ('%d')", 123213);
}

int main(int argc, const char * argv[])
{
//    PacketBuffer* bytes = new PacketBuffer();
//    bytes->self()<<"abc ";
//    MD5 md5(bytes->readString());
//    std::cout<<md5.md5()<<std::endl;
//    std::cout<<md5.md5()<<std::endl;
//    
    RunTime::getInstance()->launch();
    DBServer::getInstance()->launch(host);
    //--
    epoll_input([](DataArray* data)
                {
                    RUN_MAIN(NewBlock(data, &vim_complete));
                });
    pthread_exit(0);
    return 0;
}
