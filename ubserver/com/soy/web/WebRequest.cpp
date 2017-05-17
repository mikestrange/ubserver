//
//  WebRequest.c
//  ubserver
//
//  Created by MikeRiy on 17/1/3.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#include "WebRequest.h"

WebRequest::WebRequest():
fin_(),
opcode_(),
mask_(),
masking_key_(),
payload_length_(),
payload_()
{
}

WebRequest::~WebRequest(){
    
}

int WebRequest::fetch_websocket_info(char *msg)
{
    int pos = 0;
    fetch_fin(msg, pos);
    fetch_opcode(msg, pos);
    fetch_mask(msg, pos);
    fetch_payload_length(msg, pos);
    fetch_masking_key(msg, pos);
    return fetch_payload(msg, pos);
}

void WebRequest::print(){
    //打印字段
//    char bytes[payload_length_ + 1];
//    memcpy(bytes, payload_, payload_length_);
//    bytes[payload_length_] = '\0';
//    //
//    LOG_DEBUG("WEBSOCKET PROTOCOL\n"
//              "FIN: %d\n"
//              "OPCODE: %d\n"
//              "MASK: %d\n"
//              "PAYLOADLEN: %d\n"
//              "PAYLOAD: %s",
//              fin_, opcode_, mask_, payload_length_, bytes);
    //
    reset();
}


void WebRequest::packet(NetContext* context)
{
    context->LoadBytes(payload_, payload_length_);
}

void WebRequest::reset()
{
    fin_ = 0;
    opcode_ = 0;
    mask_ = 0;
    memset(masking_key_, 0, sizeof(masking_key_));
    payload_length_ = 0;
    memset(payload_, 0, sizeof(payload_));
}

int WebRequest::fetch_fin(char *msg, int &pos)
{
    fin_ = (uint8)msg[pos] >> 7;
    return 0;
}

int WebRequest::fetch_opcode(char *msg, int &pos)
{
    opcode_ = msg[pos] & 0x0f;
    pos++;
    return 0;
}

int WebRequest::fetch_mask(char *msg, int &pos)
{
    mask_ = (uint8)msg[pos] >> 7;
    return 0;
}

int WebRequest::fetch_masking_key(char *msg, int &pos)
{
    if(mask_ != 1) return 0;
    for(int i = 0; i < 4; i++)
    {
        masking_key_[i] = msg[pos + i];
    }
    pos += 4;
    return 0;
}

int WebRequest::fetch_payload_length(char *msg, int &pos)
{
    payload_length_ = msg[pos] & 0x7f;
    pos++;
    if(payload_length_ == 126){
        uint16_t length = 0;
        memcpy(&length, msg + pos, 2);
        pos += 2;
        payload_length_ = ntohs(length);
    }else if(payload_length_ == 127){
        uint32_t length = 0;
        memcpy(&length, msg + pos, 4);
        pos += 4;
        payload_length_ = ntohl(length);
    }
    return 0;
}

int WebRequest::fetch_payload(char *msg, int &pos)
{
    memset(payload_, 0, sizeof(payload_));
    if(mask_ != 1)
    {
        memcpy(payload_, msg + pos, payload_length_);
    }else {
        for(uint i = 0; i < payload_length_; i++){
            int j = i % 4;
            payload_[i] = msg[pos + i] ^ masking_key_[j];
        }
    }
    pos += payload_length_;
    return 0;
}