//
//  Menu.h
//  TowerDefense
//
//  Created by admin on 11/20/15.
//
//

#ifndef __TowerDefense__MenuScene__
#define __TowerDefense__MenuScene__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif /* defined(__TowerDefense__MenuScene__) */
