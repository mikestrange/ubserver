//
//  SockEvent.c
//  ubserver
//
//  Created by MikeRiy on 16/11/17.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#include "SockEvent.h"

SocketEvent::SocketEvent(int type, NetSocket* client)
:m_type(type)
,m_client(client)
,m_bytes(NULL)
,m_size(0)
{
    
}

SocketEvent::SocketEvent(int type, NetSocket* client, char* bytes, size_t size)
:m_type(type)
,m_client(client)
,m_bytes(bytes)
,m_size(size)
{
    MemoryPool::getInstance()->alloc_copy(m_bytes, m_size);
}

SocketEvent::~SocketEvent()
{
    if(m_bytes)
    {
        if(!MemoryPool::getInstance()->share(m_bytes))
        {
            SAFE_DELETE(m_bytes);
        };
    }
}

void SocketEvent::OnTaskHandler()
{
    switch (m_type)
    {
        case SOCKET_EVENT_CLOSE:
            m_client->OnClose();
            break;
        case SOCKET_EVENT_READ:
            if(m_client->isConnect())
            {
                m_client->LoadBytes(m_bytes, m_size);
                try{
                    while(m_client->HasPacket())
                    {
                        m_client->ReadBegin();
                        m_client->OnPacketHandler();
                        m_client->ReadEnd();
                    }
                }catch(...){
                    m_client->Close();
                }
            }
            break;
    }
};