//
//  GamePlayer.h
//  ubserver
//
//  Created by MikeRiy on 16/11/14.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef GamePlayer_h
#define GamePlayer_h

#include <stdio.h>
#include "global.h"
#include "packet_buffer.h"

class GamePlayer : public IReader
{
public:
    USER_T user_id;
    SEAT_T seat_id;
public:
    GamePlayer(PacketBuffer* bytes);
    virtual ~GamePlayer();
    
    void WriteTo(WriteBytes& bytes)override;
    void ReadFor(ReadBytes& bytes)override;
    
};

#endif /* GamePlayer_h */
