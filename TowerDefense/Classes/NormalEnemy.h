//
//  NormalEnemy.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__NormalEnemy__
#define __TowerDefense__NormalEnemy__

#include "EnemyUnit.h"

#define SPRITE_NormalEnemy ""

class NormalEnemy : public EnemyUnit
{
public:
    NormalEnemy(int line);
    virtual ~NormalEnemy();

    virtual cocos2d::Sprite* InitializeSprite() override;
};

#endif