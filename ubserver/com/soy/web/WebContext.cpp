//
//  WebContext.c
//  ubserver
//
//  Created by MikeRiy on 17/1/3.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#include <unistd.h>
#include "WebContext.h"

//握手
static const int HANDSHARK_SIZE = 1024;

WebContext::WebContext(int fd):
NetContext(fd),
status_(WEBSOCKET_UNCONNECT),
header_map_()
{
}

WebContext::~WebContext()
{
}

bool WebContext::isHandsharked()const
{
    return status_ == WEBSOCKET_HANDSHARKED;
}

int WebContext::process(char* bytes)
{
    if(status_ == WEBSOCKET_UNCONNECT)
    {
        handshark(bytes);
        return 1;
    }
    request_.fetch_websocket_info(bytes);
    request_.packet(this);
    request_.print();
    return 0;
}

int WebContext::handshark(char* bytes)
{
    char request[HANDSHARK_SIZE] = {};
    status_ = WEBSOCKET_HANDSHARKED;
    fetch_http_info(bytes);
    size_t size = parse_str(request);
    return this->NetContext::SendPacket(request, size);
}

size_t WebContext::parse_str(char *request)
{
    strcat(request, "HTTP/1.1 101 Switching Protocols\r\n");
    strcat(request, "Connection: upgrade\r\n");
    strcat(request, "Sec-WebSocket-Accept: ");
    std::string server_key = header_map_["Sec-WebSocket-Key"];
    server_key += MAGIC_KEY;
    //
    SHA1 sha;
    unsigned int message_digest[5];
    sha.Reset();
    sha << server_key.c_str();
    
    sha.Result(message_digest);
    for (int i = 0; i < 5; i++)
    {
        message_digest[i] = htonl(message_digest[i]);
    }
    server_key = base64_encode(reinterpret_cast<const unsigned char*>(message_digest),20);
    server_key += "\r\n";
    strcat(request, server_key.c_str());
    strcat(request, "Upgrade: websocket\r\n\r\n");
    return strlen(request);
}


int WebContext::fetch_http_info(char* bytes)
{
    std::istringstream s(bytes);
    std::string request;
    
    std::getline(s, request);
    if (request[request.size()-1] == '\r') {
        request.erase(request.end()-1);
    } else {
        return -1;
    }
    std::string header;
    std::string::size_type end;
    while (std::getline(s, header) && header != "\r") {
        if (header[header.size()-1] != '\r') {
            continue; //end
        } else {
            header.erase(header.end()-1);	//remove last char
        }
        
        end = header.find(": ",0);
        if (end != std::string::npos) {
            std::string key = header.substr(0,end);
            std::string value = header.substr(end+2);
            header_map_[key] = value;
        }
    }
    return 0;
}

int WebContext::SendPacket(ByteArray &packet)
{
    WebRespond respond;
    respond.set_payload(packet);
    respond.packet();
    return this->NetContext::SendPacket(respond.contents(), respond.wpos());
}