#include "EnemyUnit.h"
#include "EnemyManager.h"
#include "AllyManager.h"
#include "WorldPosition.h"

EnemyUnit::EnemyUnit(int line, int hp, float speed) :
position(0.0f), line(line), hp(hp), speed(speed), isMoving(false)
{
    /*
    movementAction = cocos2d::MoveTo::create((NUMBERCASE + 1 - position) * 2.0 / speed, cocos2d::Vec2(x, y));
    rotateAction =
        cocos2d::RepeatForever::create(
        cocos2d::Sequence::create(
        cocos2d::RotateTo::create(1.0, 15),
        cocos2d::RotateTo::create(1.0, -15),
        nullptr)
        );

        */
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

bool EnemyUnit::move(float deltaTime)
{
    float x, y;
    sprite->getPosition(&x, &y);
    WorldPosition::screenToWorldPosition(x, y);

    position = x;

    auto unitIt = AllyManager::getInstance()->units.find(std::pair<int, int>(position, line));
    if (unitIt == AllyManager::getInstance()->units.end())
    {
        if (!isMoving)
        {
            // Action
            x = NUMBERCASE + 0.5;
            y = line;
            WorldPosition::worldToScreenPosition(x, y);
            


            isMoving = true;
        }
        return true;
    }

    //if (isMoving)
    //    sprite->stopAction();

}