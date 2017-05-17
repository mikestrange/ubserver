//
//  WebRespond.c
//  ubserver
//
//  Created by MikeRiy on 17/1/3.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#include "WebRespond.h"

WebRespond::WebRespond()
:fin_()
,opcode_()
,mask_()
,masking_key_()
,payload_length_()
,payload_()
{
    set_fin(1);
    set_opcode(2);
    set_mask(0);
    //set_masking_key((const uint8*)"afds");
    //set_payload("0123456789\0",11);
    //
    //packet();
}

void WebRespond::set_fin(uint8 val)
{
    fin_ = val;
}

void WebRespond::set_opcode(uint8 val)
{
    opcode_ = val;
}

void WebRespond::set_mask(uint8 val)
{
    mask_ = val;
}

void WebRespond::set_masking_key(const uint8* keys)
{
    memcpy(masking_key_, keys, 4);
}

void WebRespond::set_payload(int8* bytes, size_t size)
{
    payload_length_ = size;
    memcpy(payload_, bytes, size);
}

void WebRespond::set_payload(ByteArray& bytes)
{
    set_payload((int8*)bytes.contents(), (size_t)bytes.wpos());
}

void WebRespond::reset()
{
    memset(payload_, 0, sizeof(payload_));
}

void WebRespond::packet()
{
    uint8 r4 = fin_<<7;
    r4 |= opcode_ & 0x0f;
    writeUByte(r4);
    uint8 m1 = mask_<<7;
    //超出的长度
    if(payload_length_ < 126){
        m1 |= payload_length_ & 0x7f;
        writeUByte(m1);
    }else if(payload_length_ >= 126 && payload_length_ < UINT16_MAX){
        m1 |= 126;
        writeUByte(m1);
        writeShort(payload_length_ & 0xffff);
    }else{
        m1 |= 127;
        writeUByte(m1);
        writeInt((int32)payload_length_);
    }
    //加密
    if(mask_ == 1){
        for(int i = 0;i < 4; i++)
        {
            writeByte(masking_key_[i]);
        }
        for(int k = 0;k < payload_length_; k++)
        {
            int j = k%4;
            writeByte(payload_[k] ^ masking_key_[j]);
        }
    }else{
        for(int i = 0; i < payload_length_; i++)
        {
            writeByte(payload_[i]);
        }
    }
    //测试
    if(/* DISABLES CODE */ (false)){
        WebRequest request;
        request.fetch_websocket_info((char*)this->contents());
        request.print();
    }
}