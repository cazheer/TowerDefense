#include "EnemyUnit.h"
#include "EnemyManager.h"
#include "AllyManager.h"
#include "WorldPosition.h"

USING_NS_CC;

EnemyUnit::EnemyUnit(int hp, int power, int line, float speed, float attackSpeed) :
hp(hp), power(power),
position(NUMBERCASE + 0.5), line(line),
speed(speed), attackSpeed(attackSpeed), timeSinceLastAttack(0.0),
isMoving(false), isAttacking(false),
sprite(nullptr), layer(nullptr),
movementAction(nullptr), attackAction(nullptr)
{
}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::takeDamage(int damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        Destroy();
        EnemyManager::getInstance()->destroyUnit(this);
    }
}

bool EnemyUnit::Initialize(cocos2d::Layer* layer)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    this->layer = layer;

    sprite = InitializeSprite();

    float x = position, y = line;
    WorldPosition::worldToScreenPosition(x, y);
    sprite->setPosition(x, y);

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

void EnemyUnit::Update(float deltaTime)
{
    if (!move(deltaTime))
        attack(deltaTime);
}

void EnemyUnit::Destroy()
{
    if (layer && sprite)
        layer->removeChild(sprite);
}

bool EnemyUnit::move(float deltaTime)
{
    auto x = sprite->getPositionX();
    auto y = sprite->getPositionY();

    WorldPosition::screenToWorldPosition(x, y);
    position = x;
    auto it = AllyManager::getInstance()->units.find(
        std::pair<int, int>(x - 0.5, y));
    if (it != AllyManager::getInstance()->units.end())
    {
        if (isMoving)
        {
            sprite->stopAction(movementAction);
            isMoving = false;
        }
        return false;
    }

    if (isAttacking)
    {
        sprite->stopAction(attackAction);
        isAttacking = false;
    }

    if (!isMoving)
    {
        x = -0.5;
        y = line;
        WorldPosition::worldToScreenPosition(x, y);

        movementAction =
            Spawn::create(
            Sequence::create(
            MoveTo::create((position + 0.5) * 2.0f / speed, Vec2(x, y)),
            CallFunc::create([]()
            {
                // end game
            }),
            nullptr
            ),
            RepeatForever::create(
            Sequence::create(
            RotateTo::create(3.0, 15),
            RotateTo::create(3.0, -15),
            nullptr
            )
            ),
            nullptr
            );

        sprite->runAction(movementAction);
        isMoving = true;
    }
    return true;
}

void EnemyUnit::attack(float deltaTime)
{
    if (!isAttacking)
    {
        sprite->runAction(attackAction->clone());
        AllyManager::getInstance()->attackUnit(power, position - 0.5, line);
        isAttacking = true;
    }
}
