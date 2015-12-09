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
    float productionSpeed;
    float currentTime;

public:
    MarkProducerAlly(int position, int line);
    ~MarkProducerAlly();

    virtual bool InitializeData() override;
    virtual cocos2d::Sprite* InitializeSprite() override;
    virtual void Update(float deltaTime) override;
};

#endif