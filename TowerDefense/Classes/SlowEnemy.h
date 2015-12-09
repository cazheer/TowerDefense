//
//  SlowEnemy.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__SlowEnemy__
#define __TowerDefense__SlowEnemy__

#include "EnemyUnit.h"

#define SPRITE_SlowEnemy ""

class SlowEnemy : public EnemyUnit
{
public:
    SlowEnemy(int line);
    virtual ~SlowEnemy();

    virtual cocos2d::Sprite* InitializeSprite() override;
};

#endif