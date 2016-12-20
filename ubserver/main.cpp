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

#include "WorldMsg.h"
#include "NetSocket.h"
#include "DBServer.h"
#include "time_util.h"
#include "math_util.h"

#include "md5.h"
#include "PacketBuffer.h"
#include "WorldServer.h"

//const char* host = "120.77.149.74";
//const char* host = "116.62.5.118";
const char* host = "127.0.0.1";
const int port = 8081;

NetSocket m_socket;

void thread_socket()
{
    if(m_socket.isClosed())
    {
         m_socket.connect("127.0.0.1", port);
    }
    //--
    MsgHandler bytes;
    //登录
    bytes.setBegin(SERVER_CMD_LOGIN);
    bytes.writeByte(1);
    bytes.writeUInt(10002);
    bytes<<"abc"<<"adf";
    bytes.WriteEnd();
    //进入房间
//    bytes.setBegin(SERVER_CMD_GAME_ENTER, SERVER_GAME_MESSAGE, 101);
//    bytes.WriteBegin();
//    bytes.WriteEnd();
    //--
    m_socket.SendPacket(&bytes[0], bytes.wpos());
}

//输入
void vim_complete(ByteArray* array)
{
    try{
        std::string str;
        array->readString(str);
        LOG_DEBUG("输入:%s", str.c_str());
        if(StringUtil::equal(str, "exit"))
        {
            LOG_DEBUG("[进程已完成]");
            exit(0);
        }else if(StringUtil::equal(str, "run")){
            WorldServer::getInstance()->listener(port);
        }else if(StringUtil::equal(str, "print")){
            WorldServer::getInstance()->print();
        }else if(StringUtil::equal(str, "send")){
            thread_socket();
        }else if(StringUtil::equal(str, "sql")){
            DataQuery result;
            std::string sql;
            array->readString(sql);
            DBServer::getInstance()->find(result, sql.c_str());
            result.toString();
        }else if(StringUtil::equal(str, "cut")){
            std::string id;
            array->readString(id);
            int sockid = soy::parseInt(id);
            auto socket = WorldServer::getInstance()->getNode(sockid);
            if(socket)
            {
                socket->DisConnect();
            }
        }else if(StringUtil::equal(str, "out")){
            //system("kill %2");
        }
    }catch(...){
        LOG_DEBUG("[输入有误]");
    }
}

//用户id生成
void test()
{
    DataQuery result;
    DBConnect sql(DBServer::getInstance());
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
//    ByteStream stream;
//    stream.append(std::string("this is test"));
//    ByteStream stream2(stream);
//    std::cout<<stream2.contents()<<std::endl;
    //运行线程
    RunTime::getInstance()->launch();
    //服务器
    DBServer::getInstance()->launch("120.77.149.74");
    //输入
    epoll_input([](ByteArray* data)
                {
                    RUN_MAIN(NewBlock(data, &vim_complete));
                });
    pthread_exit(0);
    return 0;
}
