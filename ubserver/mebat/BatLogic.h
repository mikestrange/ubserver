//
//  BatLogic.h
//  ubserver
//
//  Created by MikeRiy on 17/1/5.
//  Copyright © 2017年 MikeRiy. All rights reserved.
//

#ifndef BatLogic_h
#define BatLogic_h

#include "global.h"
#include "hashmap.h"
#include "hashlist.h"
#include "BatPlayer.h"
#include "SocketHandler.h"
#include "CmdDefined.h"
#include "BatAtom.h"
#include "physics.h"

class BatLogic
{
private:
    uint32 bat_id;
    uint8 game_state;
    
private:
    //英雄
    HashMap<USER_T, BatPlayer*> playerMap;
    //释放的元素
    HashList<BatAtom*> atomList;
    //中立列表
    
public:
    BatLogic(uint32 bid);
    
    virtual ~BatLogic();
    
    void Launch();
    
    int Windup();
    
    int JoinPlayer(BatPlayer* player);
    
    int ExitPlayer(USER_T uid);
    
public://技能的释放
    void MoveTo(USER_T uid, int16 x, int16 y, uint8 mid = 0);
    //释放技能(非指向型技能)(也可以是绑定不动的技能,BUFF等)
    void ReleaseSkill(USER_T uid, int16 sid, int16 angle = 0);
    //区域技能(未指定区域无效)
    void ReleaseSkill(USER_T uid, int16 sid, Rect* rect);
    //群指定技能(必中技能延迟伤害表现)
    void ReleaseSkill(USER_T uid, int16 sid, int16 count, USER_T uids[]);
    //单指定技能(非必中技能后台计算范围)
    void ReleaseSkill(USER_T uid, int16 sid, USER_T aim);
    
public:
    //刷新角色
    void Update(BatPlayer* player);
    
    void StartGame();
    
    void OverGame();
};

#endif /* BatLogic_h */
