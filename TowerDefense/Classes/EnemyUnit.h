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
    int     hp;
    int     power;

    float   position;
    int     line;

    float   speed;
    float   attackSpeed;
    float   timeSinceLastAttack;

    bool    isMoving;
    bool    isAttacking;

    cocos2d::Sprite* sprite;
    cocos2d::Layer* layer;

    cocos2d::Action* movementAction;
    cocos2d::Action* attackAction;

    EnemyUnit(int hp, int power, int line, float speed, float attackSpeed);
    virtual ~EnemyUnit();

    virtual bool Initialize(cocos2d::Layer* layer);
    virtual cocos2d::Sprite* InitializeSprite() = 0;
    virtual void Update(float deltaTime);
    virtual void Destroy();

    void takeDamage(int damage);
    bool move(float deltaTime);
    void attack(float deltaTime);
};

#endif