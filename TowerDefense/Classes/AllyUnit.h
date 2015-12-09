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

public:
    AllyUnit(int position, int line, int hp);
    virtual ~AllyUnit();

    virtual bool Initialize(cocos2d::Layer* layer) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Destroy() = 0;

    void takeDamage(int damage);
};

#endif