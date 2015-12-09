#include "AllyUnit.h"
#include "AllyManager.h"

USING_NS_CC;

AllyUnit::AllyUnit(int position, int line, int hp) :
position(position), line(line), hp(hp), activate(true),
layer(nullptr), sprite(nullptr)
{
}

AllyUnit::~AllyUnit()
{
}

bool AllyUnit::Initialize(Layer* layer)
{
    this->layer = layer;
    sprite = InitializeSprite();
    layer->addChild(sprite);
    return InitializeData();
}

void AllyUnit::Destroy()
{
    layer->removeChild(sprite);
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

void AllyUnit::Activate(bool activate)
{
    this->activate = activate;
}

bool AllyUnit::Activate() const
{
    return activate;
}
