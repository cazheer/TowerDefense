#include "NormalEnemy.h"

USING_NS_CC;

NormalEnemy::NormalEnemy(int line) :
EnemyUnit(40, 5, line, 1.0, 1.0)
{
}

NormalEnemy::~NormalEnemy()
{
}

Sprite* NormalEnemy::InitializeSprite()
{
    return Sprite::create(SPRITE_NormalEnemy);
}