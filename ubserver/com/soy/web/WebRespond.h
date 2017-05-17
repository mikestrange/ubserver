//
//  WebRespond.h
//  ubserver
//
//  Created by MikeRiy on 17/1/3.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef WebRespond_h
#define WebRespond_h

#include <stdio.h>
#include "global.h"
#include "ByteArray.h"

#include "WebRequest.h"

class WebRespond : public ByteArray
{
public:
    WebRespond();
public:
    void set_fin(uint8 val);
    void set_opcode(uint8 val);
    void set_mask(uint8 val);
    void set_masking_key(const uint8* keys);
    void set_payload(int8* msg, size_t size);
    void set_payload(ByteArray& bytes);
    void packet();
    void reset();
private:
    uint8 fin_;
    uint8 opcode_;
    uint8 mask_;
    uint8 masking_key_[4];
    uint64 payload_length_;
    char payload_[WEB_RESULT_MAX];
};

#endif /* WebRespond_h */
