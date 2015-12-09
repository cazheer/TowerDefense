//
//  EnemyUnit.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__EnemyUnit__
#define __TowerDefense__EnemyUnit__

#include "cocos2d.h"

class EnemyUnit
{
public:
    float position;
    int line;

    int hp;
    float speed;
    bool isMoving;

    cocos2d::Sprite* sprite;
    cocos2d::Layer* layer;

    cocos2d::Action* movementAction;
    cocos2d::Action* rotateAction;

    EnemyUnit(int line, int hp, float speed);
    virtual ~EnemyUnit();

    virtual bool Initialize(cocos2d::Layer* layer) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Destroy() = 0;

    void takeDamage(int damage);
    bool move(float deltaTime);
};

#endif