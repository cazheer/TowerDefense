#include "ShotUnit.h"
#include "ShotManager.h"
#include "AllyManager.h"
#include "WorldPosition.h"

USING_NS_CC;

ShotUnit::ShotUnit(int hp, int power, cocos2d::Vec2 pos, float speed, float attackSpeed) :
hp(hp), power(power), position(pos),
speed(speed), attackSpeed(attackSpeed), timeSinceLastAttack(0.0),
isMoving(false), isAttacking(false),
sprite(nullptr), layer(nullptr),
movementAction(nullptr), attackAction(nullptr)
{
}

ShotUnit::~ShotUnit()
{
}

void ShotUnit::takeDamage(int damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        Destroy();
		ShotManager::getInstance()->destroyUnit(this);
    }
}

bool ShotUnit::Initialize(cocos2d::Layer* layer)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    this->layer = layer;

    sprite = InitializeSprite();
    WorldPosition::worldToScreenPosition(position.x, position.y);
    sprite->setPosition(position.x, position.y);

    sprite->setScale(
        visibleSize.width / (SCREENCASE * sprite->getContentSize().width),
        visibleSize.height / (SCREENLINE * sprite->getContentSize().height)
        );

    attackAction =
        Sequence::create(
        RotateTo::create(attackSpeed / 3, 45),
        RotateTo::create(2 * attackSpeed / 3, -15),
        CallFunc::create([this]()
        {
            isAttacking = false;
        }),
        nullptr
        );

    return true;
}

void ShotUnit::Update(float deltaTime)
{
    if (!move(deltaTime))
        attack(deltaTime);
}

void ShotUnit::Destroy()
{
    if (layer && sprite)
        layer->removeChild(sprite);
}

bool ShotUnit::move(float deltaTime)
{
    auto x = sprite->getPositionX();
    auto y = sprite->getPositionY();

    WorldPosition::screenToWorldPosition(x, y);
    position.x = x;
    return true;
}

void ShotUnit::attack(float deltaTime)
{
    if (!isAttacking)
    {
        sprite->runAction(attackAction->clone());
        //AllyManager::getInstance()->attackUnit(power, position - 0.5, line);
        isAttacking = true;
    }
}
