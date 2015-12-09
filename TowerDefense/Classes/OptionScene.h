//
//  OptionScene.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__OptionScene__
#define __TowerDefense__OptionScene__

#include "cocos2d.h"

class OptionScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(OptionScene);
};

#endif /* defined(__TowerDefense__OptionScene__) */
