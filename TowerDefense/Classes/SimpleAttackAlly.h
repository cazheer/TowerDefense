//
//  SimpleAttackAlly.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__SimpleAttackAlly__
#define __TowerDefense__SimpleAttackAlly__

#include "AllyUnit.h"

#define SPRITE_SimpleAttackAlly "allies/2.png"

class SimpleAttackAlly : public AllyUnit
{
    float productionSpeed;
    float currentTime;

public:
    SimpleAttackAlly(int position, int line);
    ~SimpleAttackAlly();

    virtual bool InitializeData() override;
    virtual cocos2d::Sprite* InitializeSprite() override;
    virtual void Update(float deltaTime) override;
};

#endif