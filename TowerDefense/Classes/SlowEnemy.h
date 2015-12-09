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

#define SLOWENEMY_SPRITE ""

class SlowEnemy : public EnemyUnit
{
    float timeSinceLastAttack;
    float attackSpeed;
    int power;

public:
    SlowEnemy(int line);
    virtual ~SlowEnemy();

    virtual bool Initialize(cocos2d::Layer* layer) override;
    virtual void Update(float deltaTime) override;
    virtual void Destroy() override;

    void attack(float deltaTime);
};

#endif