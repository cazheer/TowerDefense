//
//  MarkProducerAlly.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__MarkProducerAlly__
#define __TowerDefense__MarkProducerAlly__

#include "AllyUnit.h"

#define SPRITE_MarkProducerAlly ""

class MarkProducerAlly : public AllyUnit
{
    cocos2d::Layer* layer;
    cocos2d::Sprite* sprite;
    float productionSpeed;
    float currentTime;

public:
    MarkProducerAlly(int position, int line);
    ~MarkProducerAlly();

    virtual bool Initialize(cocos2d::Layer* layer);
    virtual void Update(float deltaTime);
    virtual void Destroy();
};

#endif