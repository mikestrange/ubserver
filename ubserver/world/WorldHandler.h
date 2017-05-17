//
//  WorldHandler.h
//  ubserver
//
//  Created by MikeRiy on 16/12/27.
//  Copyright © 2016年 MikeRiy. All rights reserved.
//

#ifndef WorldHandler_h
#define WorldHandler_h

#include "BaseHandler.h"

#include "DBServer.h"
#include "WorldRep.h"
#include "ObjectCollect.h"
#include "NetContext.h"
#include "HookManager.h"

class WorldHandler : public BaseHandler
{
    STATIC_CLASS(WorldHandler);
private:
    long current_size;
    HashMap<int, HookNode*> m_hookmap;
public:
    WorldHandler();
    
    long getCurrentSize()const;
    
    void Add();
    
    void Pop();
};

#endif /* WorldHandler_h */
