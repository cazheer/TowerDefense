#include "AllyManager.h"

AllyManager* AllyManager::instance = nullptr;

AllyManager::AllyManager() :
layer(nullptr)
{
}

AllyManager::~AllyManager()
{
}

AllyManager* AllyManager::getInstance()
{
    if (!instance)
        instance = new AllyManager;
    return instance;
}

bool AllyManager::Initialize(cocos2d::Layer* layer)
{
    this->layer = layer;
    return true;
}

void AllyManager::Update(float deltaTime)
{
    for (auto it = unitsToDestroy.begin(); it != unitsToDestroy.end(); ++it)
    {
        units.erase(*it);
    }
    unitsToDestroy.clear();

    for (auto it = units.begin(); it != units.end(); ++it)
    {
        it->second->Update(deltaTime);
    }
}

void AllyManager::createUnit(int type, int positionX, int positionY)
{
    if (positionX >= NUMBERCASE || positionY >= NUMBERLINE || type >= (int)creatorFuncs.size())
        return;

    auto position = std::pair<int, int>(positionX, positionY);
    if (units.find(position) != units.end())
        return;

    auto unit = creatorFuncs.at(type)(positionX, positionY);
    if (unit)
    {
        unit->Initialize(layer);
        units.insert(std::pair<std::pair<int, int>, AllyUnit*>(position, unit));
    }
}

void AllyManager::attackUnit(int damage, int positionX, int positionY)
{
    if (positionX >= NUMBERCASE || positionY >= NUMBERLINE)
        return;

    auto position = std::pair<int, int>(positionX, positionY);
    auto unit = units.find(position);

    if (unit == units.end())
        return;

    unit->second->takeDamage(damage);
}

void AllyManager::destroyUnit(int positionX, int positionY)
{
    if (positionX >= NUMBERCASE || positionY >= NUMBERLINE)
        return;

    auto position = std::pair<int, int>(positionX, positionY);
    unitsToDestroy.push_back(position);
}