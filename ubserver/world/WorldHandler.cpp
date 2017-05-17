//
//  WorldHandler.c
//  ubserver
//
//  Created by MikeRiy on 16/12/27.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "WorldHandler.h"

//class
STATIC_CLASS_INIT(WorldHandler);

static void w_test(MsgID cmd, SocketHandler* packet, int mtype)
{
    
}

//登录(登录服务器发送过来的数据，世界服务器保存有用信息，其他的发送给网关服务器)
static void w_login(MsgID cmd, SocketHandler* packet, int mtype)
{
    //数据读取
    uint8 type = packet->readByte();
    USER_T uid = packet->readUInt();
    std::string pass_word;
    std::string device_id;
    packet->readString(pass_word);
    packet->readString(device_id);
    LOG_DEBUG("login input uid=%d pws=%s device=%s", uid, pass_word.c_str(), device_id.c_str());
    bool is_check = false;
    //登录类型
    if(type == 1){
        //密码登录
        //is_check = DBServer::getInstance()->login_with_user(uid, pass_word);
    }else if(type == 2){
        //设备登录
        //is_check = DBServer::getInstance()->login_with_device(uid, device_id);
    }
    //是否获取到数据
    if(is_check)
    {
        RoObject* player = new RoObject(uid, packet->getContext(), type);
        //注册
        RoObject* before = ObjectCollect::getInstance()->RegObject(uid, player);
        //不要重复登录
        if(before)
        {
            WorldRep::Logout(before->getContext(), 1);
            //删除之前元素
            SAFE_DELETE(before);
        }
        //登录成功
        WorldRep::Login(packet->getContext(), 0);
    }else{
        LOG_WARN("log error no match uid or pwd");
        WorldRep::Login(packet->getContext(), 2);
    }
}

//不包括私聊
static void w_chat(MsgID cmd, SocketHandler* packet, int mtype)
{
    //TABLE_ID chat_id = packet->getViewId();   //聊天房间id
    uint8 type = packet->readByte();            //聊天类型
    uint8 waytype = packet->readByte();         //派送方式 1世界，2频道..
    USER_T uid = packet->readUInt();            //说话人id
    std::string user_name;
    packet->readString(user_name);              //发送人名称
    std::string msg_content;
    packet->readString(msg_content);
    //可以推送到聊天服务器
    WorldRep::ChatMsg(packet->getContext(), type, waytype, uid, user_name, msg_content);
    LOG_INFO("聊天:type=%d,way=%d,uid=%d,uname=%s,content=%s", type, waytype, uid, user_name.c_str(), msg_content.c_str());
}

//退出登录(需要校正登录regid)
static void w_logout(MsgID cmd, SocketHandler* packet, int mtype)
{
    USER_T uid = packet->readUInt();
    RoObject* player = ObjectCollect::getInstance()->UnRegObject(uid);
    if(player)
    {
        //发送退出登录
        WorldRep::Logout(player->getContext(), 0);
    }
    //
    SAFE_DELETE(player);
}

//节点注册和取消
static void w_hookmsg(MsgID cmd, SocketHandler* packet, int mtype)
{
    int32 hook_id = packet->readInt();
    if(cmd == SERVER_CMD_HOOK_UNREG){
        HookManager::getInstance()->UnRegister(hook_id);
    }else{
        int8 ser_type = packet->readByte();
        HookManager::getInstance()->Register(hook_id, packet->getContext(), ser_type);
    }
}

//获取服务器时间
static void w_get_sys_time(MsgID cmd, SocketHandler* packet, int mtype)
{
    WorldRep::SysTime(packet->getContext());
}

static void w_online_info(MsgID cmd, SocketHandler* packet, int mtype)
{
    
}

//handles
static void world_sendto_gate(SocketHandler* packet)
{
    
}

static void world_sendto_game(SocketHandler* packet)
{
    
}

static void world_sendto_bat(SocketHandler* packet)
{
    
}

static void packet_handler(SocketHandler* packet, int type)
{
    try{
        packet->ReadBegin();
        //
        switch(packet->getType())
        {
            case SERVER_GATE_MESSAGE:
                world_sendto_gate(packet);
                break;
            case SERVER_WORLD_MESSAEGE:
                WorldHandler::getInstance()->SendEvent(packet->getCmd(), packet, packet->getType());
                break;
            case SERVER_GAME_MESSAGE:
                world_sendto_game(packet);
                break;
            case SERVER_BAT_MESSAGE:
                world_sendto_bat(packet);
                break;
            default:
                WorldHandler::getInstance()->SendEvent(packet->getCmd(), packet, packet->getType());
                break;
        }
    }catch(...){
        packet->getContext()->DisConnect();
    }
    SAFE_DELETE(packet);
}

static void close_handler(NetContext* context)
{
    //取消挂钩的注册
    HookManager::getInstance()->UnRegister(context);
    //删除节点所有的注册用户
    ObjectCollect::getInstance()->CloseObject(context);
    //释放
    //SAFE_DELETE(context);
}

static void socket_handler(NetContext* context, int type)
{
    switch(type)
    {
        case SOCKET_LISTEN:
            break;
        case SOCKET_OVEREND:
            SAFE_DELETE(context);
            break;
        case SOCKET_CONNECT:
            WorldHandler::getInstance()->Add();
            break;
        case SOCKET_CLOSED:
            close_handler(context);
            WorldHandler::getInstance()->Pop();
            WorldHandler::getInstance()->die_context(context);
            break;
        case SOCKET_HEARTBET:
            WorldRep::HeartBead(context);
            break;
    }
}


WorldHandler::WorldHandler()
:current_size(0)
{
    //回执
    setLoopCall(packet_handler, socket_handler);
    //事件
    AddEvent(SERVER_CMD_TEST, w_test);
    AddEvent(SERVER_CMD_LOGIN, w_login);
    AddEvent(SERVER_CMD_LOGOUT, w_logout);
    AddEvent(SERVER_CMD_CHAR_MSG, w_chat);
    //
    AddEvent(SERVER_CMD_HOOK_REG, w_hookmsg);
    AddEvent(SERVER_CMD_HOOK_UNREG, w_hookmsg);
    //
    AddEvent(SERVER_CMD_GET_LINE_INFO, w_online_info);
    //
    AddEvent(SERVER_CMD_GET_PING, w_get_sys_time);
}

long WorldHandler::getCurrentSize()const
{
    return current_size;
}

void WorldHandler::Add()
{
    current_size++;
}

void WorldHandler::Pop()
{
    current_size--;
}







