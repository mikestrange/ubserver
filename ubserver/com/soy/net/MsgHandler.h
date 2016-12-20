//
//  MsgHeader.h
//  ubserver
//
//  Created by MikeRiy on 16/12/16.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef MsgHeader_h
#define MsgHeader_h

#include "PacketBuffer.h"

class MsgHandler : public PacketBuffer
{
private:
    MsgID cmd;              //命令号
    int32 type;             //消息类型(服务器类型)
    int32 view_id;          //自版本协议号(一个房间或者一个区域的id)
    int32 version;          //服务器版本号(可以不用管)
    
public:
    MsgHandler();
    
    MsgHandler(ByteArray& packet, size_t pos, size_t size);
    
    virtual ~MsgHandler();
    
    virtual void setBegin(MsgID $cmd, int32 $type = 0, int32 $vid = 0, int32 $ver = 0);
    
    virtual void CopyBegin(MsgHandler& data);
    
public:
    MsgID getCmd();
    
    int32 getType();
    
    int32 getViewId();
    
    int32 getVersion();
    
public:
    virtual void WriteTo(ByteStream& bytes)override;
    
    virtual void ReadFor(ByteStream& bytes)override;
};

#endif /* MsgHeader_h */
