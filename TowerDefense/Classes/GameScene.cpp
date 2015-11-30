//
//  GameScene.cpp
//  TowerDefense
//
//  Created by admin on 11/25/15.
//
//

#include "GameScene.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

GameScene* GameScene::_inst = nullptr;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

GameScene* GameScene::getInstance()
{
    return _inst;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->_inst = this;
    
    //    Size visibleSize = Director::getInstance()->getVisibleSize();
    //    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->_gameScene = CSLoader::createNode("Game/GameScene.csb");
    addChild(this->_gameScene);
    this->_pauseScene = CSLoader::createNode("Game/Pause/PauseScene.csb");
    addChild(this->_pauseScene);

    /*
    ** Game
    */
    auto button = this->_pauseScene->getChildByName<cocos2d::ui::Button*>("PauseButton");
    button->addTouchEventListener(CC_CALLBACK_2(GameScene::gamePause, this));

    /*
    ** Pause
    */
    button = this->_pauseScene->getChildByName<cocos2d::ui::Button*>("ResumeButton");
    button->addTouchEventListener(CC_CALLBACK_2(GameScene::gameResume, this));

    button = this->_pauseScene->getChildByName<cocos2d::ui::Button*>("RetryButton");
    button->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {

    });
    
    button = this->_pauseScene->getChildByName<cocos2d::ui::Button*>("MenuButton");
    button->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        Director::getInstance()->popScene();
    });
    
    this->gameResume(nullptr, cocos2d::ui::Widget::TouchEventType::BEGAN);
    this->scheduleUpdate();
    
    return true;
}

void GameScene::update(float dt)
{
    if (this->_pause)
        return;

    
}

void GameScene::gamePause(Ref *pSender, ui::Widget::TouchEventType type)
{
    this->_pause = true;
    this->_pauseScene->setVisible(true);
}

void GameScene::gameResume(Ref *pSender, ui::Widget::TouchEventType type)
{
    this->_pause = false;
    this->_pauseScene->setVisible(false);
}