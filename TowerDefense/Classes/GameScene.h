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
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer
{
    static GameScene* _inst;
    
    bool _pause;
    
    Node* _gameScene;
    Node* _pauseScene;
    
public:
    static cocos2d::Scene* createScene();
    static GameScene* getInstance();
    
    virtual bool init() override;
    virtual void update(float dt) override;
    
    void gamePause(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void gameResume(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* defined(__TowerDefense__GameScene__) */
