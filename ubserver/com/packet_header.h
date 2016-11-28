//
//  packet_header.h
//  ubserver
//
//  Created by MikeRiy on 16/11/12.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef packet_header_h
#define packet_header_h

#include <stdio.h>
#include "global.h"
#include "data_array.h"

class PacketHeader : public IReader
{
private:
    MsgID cmd;              //命令号
    int32 type;             //消息类型(服务器类型)
    int32 view_id;          //自版本协议号(一个房间或者一个区域的id)
    int32 version;          //服务器版本号(可以不用管)
    //TOKEN_T token_id;       //用户识别标志(作为会话id)
    
public:
    PacketHeader()
    :cmd(0)
    ,type(0)
    ,view_id(0)
    ,version(0)
    {}
    
    virtual ~PacketHeader(){}
    
    virtual void setBegin(MsgID $cmd, int32 $type = 0, int32 $vid = 0, int32 $ver = 0)
    {
        cmd = $cmd;
        type = $type;
        view_id = $vid;
        version = $ver;
    }
    
    virtual void CopyBegin(PacketHeader& data)
    {
        cmd = data.cmd;
        type = data.type;
        version = data.version;
        view_id = data.view_id;
    }
    
public:
    MsgID getCmd()
    {
        return cmd;
    }
    
    int32 getType()
    {
        return type;
    }
    
    int32 getViewId()
    {
        return view_id;
    }
    
    int32 getVersion()
    {
        return version;
    }
    
    TOKEN_T getTokenId()
    {
        return 0;
    }
    
public:
    virtual void WriteTo(WriteBytes& bytes)override
    {
        bytes<<cmd<<type<<view_id<<version;
        //Log::debug("write %d %d %d %d", cmd, type, version, view_id);
    }
        
    virtual void ReadFor(ReadBytes& bytes)override
    {
        bytes>>cmd>>type>>view_id>>version;
        //Log::debug("read %d %d %d %d", cmd, type, version, view_id);
    }
};


#endif /* packet_header_h */
