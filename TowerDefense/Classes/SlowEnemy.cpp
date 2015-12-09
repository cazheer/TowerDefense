#include "SlowEnemy.h"
#include "AllyManager.h"
#include "WorldPosition.h"

SlowEnemy::SlowEnemy(int line) :
EnemyUnit(line, 40, 0.5),
//layer(nullptr), sprite(nullptr),
timeSinceLastAttack(0.0), attackSpeed(1), power(5)
{
}

SlowEnemy::~SlowEnemy()
{
}

bool SlowEnemy::Initialize(cocos2d::Layer* layer)
{
    this->layer = layer;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // init sprite
    sprite = cocos2d::Sprite::create(SLOWENEMY_SPRITE);

    float x = position;
    float y = line;
    WorldPosition::worldToScreenPosition(x, y);
    sprite->setPosition(x, y);
    sprite->setScale(
        visibleSize.width / (sprite->getContentSize().width * SCREENCASE),
        visibleSize.height / (sprite->getContentSize().height * SCREENLINE));

    layer->addChild(sprite);

    return true;
}

void SlowEnemy::Update(float deltaTime)
{
    if (!move(deltaTime))
    {
        attack(power);
    }
}

void SlowEnemy::Destroy()
{
    layer->removeChild(sprite);
}

void SlowEnemy::attack(float deltaTime)
{
    timeSinceLastAttack -= deltaTime;
    if (timeSinceLastAttack <= 0.0)
    {
        timeSinceLastAttack = attackSpeed;
        AllyManager::getInstance()->attackUnit(power, position, line);
    }
}
