#include "Shot1.h"

USING_NS_CC;

Shot1::Shot1(cocos2d::Vec2 pos) :
ShotUnit(40, 5, pos, 1.0, 1.0)
{
}

Shot1::~Shot1()
{
}

Sprite* Shot1::InitializeSprite()
{
    return Sprite::create(SPRITE_Shot1);
}