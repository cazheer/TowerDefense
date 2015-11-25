//
//  GameScene.h
//  TowerDefense
//
//  Created by admin on 11/25/15.
//
//

#ifndef __TowerDefense__GameScene__
#define __TowerDefense__GameScene__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
    GameScene();
    static GameScene* _inst;
    
    bool _pause;
    
    Node* _gameScene;
    Node* _pauseScene;
    
public:
    static cocos2d::Scene* createScene();
    static GameScene* getInstance();
    
    virtual bool init();
    virtual void update(float dt);
    
    void pause();
    void resume();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* defined(__TowerDefense__GameScene__) */
