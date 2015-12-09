//
//  AllyUnit.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__AllyUnit__
#define __TowerDefense__AllyUnit__

#include "cocos2d.h"

class AllyUnit
{
protected:
    int position;
    int line;

    int hp;

    bool activate;

    cocos2d::Layer* layer;
    cocos2d::Sprite* sprite;

public:
    AllyUnit(int position, int line, int hp);
    virtual ~AllyUnit();

    bool Initialize(cocos2d::Layer* layer);
    virtual bool InitializeData() = 0;
    virtual cocos2d::Sprite* InitializeSprite() = 0;
    virtual void Update(float deltaTime) = 0;
    void Destroy();

    void takeDamage(int damage);

    void Activate(bool activate);
    bool Activate() const;
};

#endif