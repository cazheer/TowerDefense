#include "SlowEnemy.h"

USING_NS_CC;

SlowEnemy::SlowEnemy(int line) :
EnemyUnit(40, 5, line, 0.5, 0.5)
{
}

SlowEnemy::~SlowEnemy()
{
}

Sprite* SlowEnemy::InitializeSprite()
{
    return Sprite::create(SPRITE_SlowEnemy);
}