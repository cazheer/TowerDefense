#include "SimpleAttackAlly.h"
USING_NS_CC;

SimpleAttackAlly::SimpleAttackAlly(int position, int line) :
AllyUnit(position, line, 20),
productionSpeed(1.0), currentTime(0.0)
{
}

SimpleAttackAlly::~SimpleAttackAlly()
{
}

Sprite* SimpleAttackAlly::InitializeSprite()
{
    return Sprite::create(SPRITE_SimpleAttackAlly);
}

bool SimpleAttackAlly::InitializeData()
{
    return true;
}

void SimpleAttackAlly::Update(float deltaTime)
{

	//ShotManager::getInstance()->createUnit(0, cocos2d::Vec2(position, line));
    if (!activate)
        return;

    currentTime += deltaTime;
    while (currentTime >= productionSpeed)
    {
        // Produce

		
        currentTime -= productionSpeed;
    }
}