#include "MarkProducerAlly.h"
#include "AllyManager.h"
#include "WorldPosition.h"

MarkProducerAlly::MarkProducerAlly(int position, int line) :
AllyUnit(position, line, 20),
layer(nullptr), sprite(nullptr),
productionSpeed(1.0), currentTime(0.0)
{
}

MarkProducerAlly::~MarkProducerAlly()
{
}

bool MarkProducerAlly::Initialize(cocos2d::Layer* layer)
{
    this->layer = layer;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    sprite = cocos2d::Sprite::create(SPRITE_MarkProducerAlly);
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

void MarkProducerAlly::Update(float deltaTime)
{
    currentTime += deltaTime;
    while (currentTime >= productionSpeed)
    {
        // Produce


        currentTime -= productionSpeed;
    }
}

void MarkProducerAlly::Destroy()
{
    layer->removeChild(sprite);
}
