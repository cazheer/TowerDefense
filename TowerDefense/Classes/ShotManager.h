//
//  ShotManager.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__ShotManager__
#define __TowerDefense__ShotManager__

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <vector>
#include <list>
#include "ShotUnit.h"
#include "cocos2d.h"

#define MAX_TYPE_SHOT 1
#define NUMBERLINE 5
class ShotManager
{
    ShotManager();
    ~ShotManager();

    cocos2d::Layer* layer;

    static ShotManager* instance;
    std::vector<ShotUnit* (*)(cocos2d::Vec2)> creatorFuncs;
    std::list<ShotUnit*> units;
    std::list<ShotUnit*> unitsToDestroy;

public:
    static ShotManager* getInstance();

    void createUnit(int type, cocos2d::Vec2 pos);
    void attackUnit(int damage, ShotUnit* unit);
    void destroyUnit(ShotUnit* unit);

    void lineDamage(int damage, int position, int line);
    void splashDamage(int damage, int position, int line);

    bool Initialize(cocos2d::Layer* layer);
    void Update(float deltaTime);
};

#endif