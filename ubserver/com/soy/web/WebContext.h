//
//  WebContext.h
//  ubserver
//
//  Created by MikeRiy on 17/1/3.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef WebContext_h
#define WebContext_h

#include <map>
#include <iostream>
#include <sstream>

#include "base64.h"
#include "sha1.h"
//
#include "Network.h"
#include "NetContext.h"
#include "WebRequest.h"
#include "WebRespond.h"

#define MAGIC_KEY "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

class WebRequest;
class NetContext;

enum WEBSOCKET_STATUS
{
    WEBSOCKET_UNCONNECT = 0,
    WEBSOCKET_HANDSHARKED = 1,
};

typedef std::map<std::string, std::string> HEADER_MAP;

class WebContext : public NetContext
{
public:
    WebContext(int fd);
    virtual ~WebContext();
public:
    //一个协议头
    bool isHandsharked()const;
    //处理头
    int process(char* bytes);
    //
    int SendPacket(ByteArray& packet)override;
private:
    int handshark(char* bytes);
    size_t parse_str(char *request);
    int fetch_http_info(char* bytes);
private:
    WEBSOCKET_STATUS status_;
    HEADER_MAP header_map_;
    WebRequest request_;
};

#endif /* WebContext_h */
