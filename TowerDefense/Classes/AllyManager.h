//
//  AllyManager.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__AllyManager__
#define __TowerDefense__AllyManager__

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <vector>
#include <list>
#include <map>
#include "AllyUnit.h"
#include "cocos2d.h"

/////////////////////
// MY CLASS DEFINE //
/////////////////////
#define SCREENCASE 12
#define SCREENLINE 6

#define NUMBERCASE 10
#define NUMBERLINE 5

#define MAX_TYPE_ALLY 1

class AllyManager
{
    AllyManager();
    ~AllyManager();

    cocos2d::Layer* layer;
    static AllyManager* instance;
    std::vector<AllyUnit* (*)(int, int)> creatorFuncs;
    std::list<std::pair<int, int>> unitsToDestroy;

public:
    std::map<std::pair<int, int>, AllyUnit*> units;

    static AllyManager* getInstance();

    void createUnit(int type, int positionX, int positionY);
    void attackUnit(int damage, int positionX, int positionY);
    void destroyUnit(int positionX, int positionY);

    bool Initialize(cocos2d::Layer* layer);
    void Update(float deltaTime);
};

#endif