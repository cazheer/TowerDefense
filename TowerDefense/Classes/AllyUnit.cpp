#include "AllyUnit.h"
#include "AllyManager.h"

AllyUnit::AllyUnit(int position, int line, int hp) :
    position(position), line(line), hp(hp)
{
}

AllyUnit::~AllyUnit()
{
}

void AllyUnit::takeDamage(int damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        Destroy();
        AllyManager::getInstance()->destroyUnit(position, line);
    }
}