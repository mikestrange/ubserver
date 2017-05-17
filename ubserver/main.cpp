//
//  main.cpp
//  ubserver
//
//  Created by MikeRiy on 16/11/9.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include <iostream>

#include "sha1.h"
#include "Network.h"
#include "log.h"
#include "string_util.h"
#include "input.h"

#include "DBServer.h"
#include "time_util.h"
#include "math_util.h"

#include "md5.h"
#include "runtime.h"

#include "WorldHandler.h"
#include "GateHandler.h"
#include "ini.h"

#include "WebNetwork.h"
#include "flash.h"
#include "WebRespond.h"
#include "memorys.h"
#include "TimePush.h"


//数据库服务器地址
const char* db_host = "120.77.149.74";
//服务器
const char* host = "127.0.0.1";
//开放端口
int gate_port = 8081;
int world_port = 9081;
//一个测试链接

void* thread_socket(void* args)
{
    //while(1){
    SOCKET_T fd = soy::connect("127.0.0.1", 8081);
    //--
    TimeUtil::begin();
    SocketHandler packet;
    //登录
    std::string password = "abc";
    std::string mac = "abc";
    packet.setBegin(SERVER_CMD_LOGIN);
    packet.writeByte(1);
    packet.writeUInt(10003);
    packet<<password<<mac;
    packet.WriteEnd();
    //聊天
    packet.setBegin(SERVER_CMD_CHAR_MSG);
    packet.writeByte(1);         //发送的类型
    packet.writeByte(0);      //发送方式
    packet.writeUInt(10003);          //发送者
    packet.writeString("我是谁");  //发送者名称
    packet.writeString("我只是个测试");
    packet.WriteEnd();
    TimeUtil::end();
    //进入房间
    //    bytes.setBegin(SERVER_CMD_GAME_ENTER, SERVER_GAME_MESSAGE, 101);
    //    bytes.WriteBegin();
    //    bytes.WriteEnd();
    //--
    if(fd > 0){
        NET_SEND(fd, packet);
        NET_CLOSE(fd);
    };
    //    usleep(1);};
    return 0;
}

void test_packet()
{
    WorldHandler::getInstance();
    auto cox = new NetContext(1);
    SocketHandler packet(cox);
    //登录
//    std::string password = "abc";
//    std::string mac = "abc";
//    packet.writeByte(1);
//    packet.writeUInt(10004);
//    packet<<password<<mac;
//    packet.reset();
//    WorldHandler::getInstance()->SendEvent(SERVER_CMD_LOGIN, &packet);
    //聊天
    packet.writeByte(1);                //发送的类型
    packet.writeByte(0);                //发送方式
    packet.writeUInt(1001);             //发送者
    packet.writeString("我是谁");        //发送者名称
    packet.writeString("我只是个测试");
    packet.reset();
    WorldHandler::getInstance()->SendEvent(SERVER_CMD_CHAR_MSG, &packet);
    SAFE_DELETE(cox);
    //
//    packet.writeInt(12);
//    packet.writeByte(12);
//    packet.reset();
//    WorldHandler::getInstance()->SendEvent(SERVER_CMD_HOOK_REG, &packet);
//    
//    packet.writeInt(10002);
//    packet.reset();
//    WorldHandler::getInstance()->SendEvent(SERVER_CMD_LOGOUT, &packet);
//    
//    packet.writeInt(12);
//    packet.reset();
//    WorldHandler::getInstance()->SendEvent(SERVER_CMD_HOOK_UNREG, &packet);
}

void vim_test()
{
    std::vector<int> *ver = new std::vector<int>;
    for(int i = 0; i< 1024*1024; i++)
    {
        ver->push_back(i);
    }
    delete ver;
}

void test22(){
    TimeUtil::begin();
    SocketHandler packet;
    //登录
    packet.setBegin(SERVER_CMD_LOGIN);
    for(int i =0;i<1024;i++){
        packet.writeByte(125);
    }
    packet.WriteEnd();
    TimeUtil::end();
}


class TimeSocket : public ITimeoutHandler
{
public:
    void OnTimeProcess(int type)override
    {
        thread_socket(0);
    }
};

TimePush mm_clock;


//输入
void vim_complete(ByteArray* array, int type)
{
    try{
        std::string str;
        array->readString(str);
        LOG_DEBUG("输入:%s", str.c_str());
        if(StringUtil::equal(str, "exit"))
        {
            LOG_DEBUG("[进程已完成]");
            exit(0);
        }else if(StringUtil::equal(str, "world")){
            soy::launch(world_port, WorldHandler::getInstance());
        }else if(StringUtil::equal(str, "gate")){
            soy::launch(gate_port, GateHandler::getInstance());
        }else if(StringUtil::equal(str, "print")){
            
        }else if(StringUtil::equal(str, "send")){
            //mm_clock.setEventDelegate(new TimeSocket);
            //mm_clock.start(0, 0);
            Thread::create(&thread_socket);
        }else if(StringUtil::equal(str, "sql")){
            DataQuery result;
            std::string sql;
            array->readString(sql);
            DBServer::getInstance()->find(result, sql.c_str());
            result.toString();
        }else if(StringUtil::equal(str, "test")){
            test_packet();
        }else if(StringUtil::equal(str, "swf")){
            flash_domain();
            //soy::launch(843, FlashHandler::getInstance());
        }else if(StringUtil::equal(str, "web")){
            soy::launch(9081, WebNetwork::getInstance());
        }else if(StringUtil::equal(str, "look")){
            trace("当前链接:%ld",WorldHandler::getInstance()->getCurrentSize());
        }else if(StringUtil::equal(str, "no")){
            vim_test();
        }else if(StringUtil::equal(str, "to")){
            
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

MemoryPool<char> m_ch;

//ini配置
void init()
{
    dictionary *ini = iniparser_load("./config.ini");
    std::cout<<ini<<std::endl;
//    
//    world_port = iniparser_getint(ini, "world:port", world_port);
//    gate_port = iniparser_getint(ini, "gate:port", gate_port);
//    trace("world port=%d gate port=%d",world_port, gate_port);
//    iniparser_freedict(ini);
    
    //test
}

void* input_func(void* args)
{
    epoll_input(block(ByteArray* data)
                {
                    RUN_SMAIN(&vim_complete, data, 0);
                });
    return 0;
}

int main(int argc, const char * argv[])
{
    init();
    TimeRunning::getInstance();
    //运行线程
    RunTime::getInstance()->launch();
    //服务器
    DBServer::getInstance()->launch(db_host);
    
    
    RUN_SMAIN(block(int b,int a){
        for(int i = 0;i<15;i++){
            test22();
        }
    }, 1, 2);
    //
    //set_key("/Users/MikeRiy/Downloads/iniparser/test/ressources/good_ini/spaced.ini","blanks","a1","123");
    //输入
    Thread::create(&input_func);
    //
    pthread_exit(0);
    return 0;
}
