#include "WorldPosition.h"
#include "AllyManager.h"
#include "cocos2d.h"

USING_NS_CC;

void WorldPosition::worldToScreenPosition(float& x, float& y)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    x += 1.5;
    y += 0.5;

    x *= visibleSize.width / SCREENCASE;
    y *= visibleSize.height / SCREENLINE;
}

void WorldPosition::screenToWorldPosition(float& x, float& y)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    x /= visibleSize.width / SCREENCASE;
    y /= visibleSize.height / SCREENLINE;

    x -= 1.5;
    y -= 0.5;
}
