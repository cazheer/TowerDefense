#include "MarkProducerAlly.h"

USING_NS_CC;

MarkProducerAlly::MarkProducerAlly(int position, int line) :
AllyUnit(position, line, 20),
productionSpeed(1.0), currentTime(0.0)
{
}

MarkProducerAlly::~MarkProducerAlly()
{
}

Sprite* MarkProducerAlly::InitializeSprite()
{
    return Sprite::create(SPRITE_MarkProducerAlly);
}

bool MarkProducerAlly::InitializeData()
{
    return true;
}

void MarkProducerAlly::Update(float deltaTime)
{
    if (!activate)
        return;

    currentTime += deltaTime;
    while (currentTime >= productionSpeed)
    {
        // Produce


        currentTime -= productionSpeed;
    }
}