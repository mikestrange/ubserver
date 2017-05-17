//
//  WebRequest.h
//  ubserver
//
//  Created by MikeRiy on 17/1/3.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef WebRequest_h
#define WebRequest_h

#include "log.h"
#include "Network.h"
#include "base64.h"
#include "string_util.h"
//

class WebRequest
{
public:
    WebRequest();
    virtual ~WebRequest();
    int fetch_websocket_info(char *msg);
    void print();
    void reset();
    void packet(NetContext* context);
private:
    int fetch_fin(char *msg, int &pos);
    int fetch_opcode(char *msg, int &pos);
    int fetch_mask(char *msg, int &pos);
    int fetch_masking_key(char *msg, int &pos);
    int fetch_payload_length(char *msg, int &pos);
    int fetch_payload(char *msg, int &pos);
private:
    uint8 fin_;
    uint8 opcode_;
    uint8 mask_;
    uint8 masking_key_[4];
    uint64 payload_length_;
    char payload_[WEB_RESULT_MAX];
};

#endif /* WebRequest_h */
