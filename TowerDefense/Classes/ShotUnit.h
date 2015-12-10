//
//  EnemyUnit.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__ShotUnit__
#define __TowerDefense__ShotUnit__

#include "cocos2d.h"

class ShotUnit
{
public:
    int     hp;
    int     power;

	cocos2d::Vec2   position;

    float   speed;
    float   attackSpeed;
    float   timeSinceLastAttack;

    bool    isMoving;
    bool    isAttacking;

    cocos2d::Sprite* sprite;
    cocos2d::Layer* layer;

    cocos2d::Action* movementAction;
    cocos2d::Action* attackAction;

	ShotUnit(int hp, int power, cocos2d::Vec2 pos, float speed, float attackSpeed);
    virtual ~ShotUnit();

    virtual bool Initialize(cocos2d::Layer* layer);
    virtual cocos2d::Sprite* InitializeSprite() = 0;
    virtual void Update(float deltaTime);
    virtual void Destroy();

    void takeDamage(int damage);
    bool move(float deltaTime);
    void attack(float deltaTime);
};

#endif