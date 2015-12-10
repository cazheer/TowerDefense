//
//  NormalEnemy.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__Shot1__
#define __TowerDefense__Shot1__

#include "ShotUnit.h"

#define SPRITE_Shot1 "fireball.png"

class Shot1 : public ShotUnit
{
public:
	Shot1(cocos2d::Vec2 pos);
    virtual ~Shot1();

    virtual cocos2d::Sprite* InitializeSprite() override;
};

#endif