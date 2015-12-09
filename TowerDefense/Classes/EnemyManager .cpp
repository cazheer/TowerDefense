#include "EnemyManager.h"
#include "AllyManager.h"
#include "SlowEnemy.h"

EnemyManager* EnemyManager::instance = nullptr;

EnemyManager::EnemyManager() :
layer(nullptr)
{
}

EnemyManager::~EnemyManager()
{
}

EnemyManager* EnemyManager::getInstance()
{
    if (!instance)
        instance = new EnemyManager;
    return instance;
}

bool EnemyManager::Initialize(cocos2d::Layer* layer)
{
    this->layer = layer;

    // init funcs
    creatorFuncs.push_back([](int line)
    {
        return (EnemyUnit*)new SlowEnemy(line);
    });

    return true;
}

void EnemyManager::Update(float deltaTime)
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

void EnemyManager::createUnit(int type, int line)
{
    if (line >= NUMBERLINE || type >= (int)creatorFuncs.size())
        return;

    auto unit = creatorFuncs.at(type)(line);
    if (unit)
    {
        unit->Initialize(layer);
        units.push_back(unit);
    }
}

void EnemyManager::attackUnit(int damage, EnemyUnit* unit)
{
    unit->takeDamage(damage);
}

void EnemyManager::destroyUnit(EnemyUnit* unit)
{
    unitsToDestroy.push_back(unit);
}

void EnemyManager::lineDamage(int damage, int position, int line)
{
    for (auto it = units.begin(); it != units.end(); ++it)
    {
        if ((*it)->line == line && (*it)->position >= (float)position)
        {
            attackUnit(damage, *it);
        }
    }
}

void EnemyManager::splashDamage(int damage, int position, int line)
{
    for (auto it = units.begin(); it != units.end(); ++it)
    {
        if ((*it)->line == line && (*it)->position >= (float)position - 1.0 && (*it)->position <= (float)position + 1.0)
        {
            attackUnit(damage, *it);
        }
    }
}