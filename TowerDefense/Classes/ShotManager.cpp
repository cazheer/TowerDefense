#include "ShotManager.h"
#include "Shot1.h"

ShotManager* ShotManager::instance = nullptr;

ShotManager::ShotManager() :
layer(nullptr)
{
}

ShotManager::~ShotManager()
{
}

ShotManager* ShotManager::getInstance()
{
    if (!instance)
        instance = new ShotManager;
    return instance;
}

bool ShotManager::Initialize(cocos2d::Layer* layer)
{

    this->layer = layer;

    // init funcs
    creatorFuncs.push_back([](cocos2d::Vec2 position)
    {
        return (ShotUnit*)new Shot1(position);
    });/*
    creatorFuncs.push_back([](int line)
    {
        return (EnemyUnit*)new NormalEnemy(line);
    });*/

    return true;
}

void ShotManager::Update(float deltaTime)
{
    for (auto it = unitsToDestroy.begin(); it != unitsToDestroy.end(); ++it)
    {
        units.remove(*it);
    }
    unitsToDestroy.clear();

    for (auto it = units.begin(); it != units.end(); ++it)
    {
        (*it)->Update(deltaTime);
    }
}

void ShotManager::createUnit(int type, cocos2d::Vec2 pos)
{

    auto unit = creatorFuncs.at(type)(pos);
    if (unit)
    {
		cocos2d::log("test");
        unit->Initialize(layer);
        units.push_back(unit);
    }
}

void ShotManager::attackUnit(int damage, ShotUnit* unit)
{
    unit->takeDamage(damage);
}

void ShotManager::destroyUnit(ShotUnit* unit)
{
    unitsToDestroy.push_back(unit);
}

void ShotManager::lineDamage(int damage, int position, int line)
{
    for (auto it = units.begin(); it != units.end(); ++it)
    {
        /*if ((*it)->line == line && (*it)->position >= (float)position)
        {
            attackUnit(damage, *it);
        }*/
    }
}

void ShotManager::splashDamage(int damage, int position, int line)
{
    for (auto it = units.begin(); it != units.end(); ++it)
    {
       /* if ((*it)->line == line && (*it)->position >= (float)position - 1.0 && (*it)->position <= (float)position + 1.0)
        {
            attackUnit(damage, *it);
        }*/
    }
}