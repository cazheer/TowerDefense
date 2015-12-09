//
//  EnemyManager.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__EnemyManager__
#define __TowerDefense__EnemyManager__

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <vector>
#include <list>
#include "EnemyUnit.h"
#include "cocos2d.h"

#define MAX_TYPE_ENEMY 2

class EnemyManager
{
    EnemyManager();
    ~EnemyManager();

    cocos2d::Layer* layer;

    static EnemyManager* instance;
    std::vector<EnemyUnit* (*)(int)> creatorFuncs;
    std::list<EnemyUnit*> units;
    std::list<EnemyUnit*> unitsToDestroy;

public:
    static EnemyManager* getInstance();

    void createUnit(int type, int line);
    void attackUnit(int damage, EnemyUnit* unit);
    void destroyUnit(EnemyUnit* unit);

    void lineDamage(int damage, int position, int line);
    void splashDamage(int damage, int position, int line);

    bool Initialize(cocos2d::Layer* layer);
    void Update(float deltaTime);
};

#endif