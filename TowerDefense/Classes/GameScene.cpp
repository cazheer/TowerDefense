//
//  GameScene.cpp
//  TowerDefense
//
//  Created by admin on 11/25/15.
//
//

#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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

GameScene::GameScene() :
_pause(false), cocos2d::Layer()
{
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
    
    this->_gameScene = CSLoader::createNode("GameScene.csb");
    addChild(this->_gameScene);
    this->_pauseScene = CSLoader::createNode("PauseScene.csb");
    addChild(this->_pauseScene);
    
    auto button = this->_pauseScene->getChildByName<cocos2d::ui::Button*>("ResumeButton");
    button->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
                                  {
                                      if (GameScene::getInstance())
                                          GameScene::getInstance()->resume();
                                  });
    
    button = this->_pauseScene->getChildByName<cocos2d::ui::Button*>("MenuButton");
    button->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
                                  {
                                      
                                  });
    
    button = this->_pauseScene->getChildByName<cocos2d::ui::Button*>("ExitButton");
    button->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
                                  {
                                      Director::getInstance()->end();
                                      
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                                      exit(0);
#endif
                                  });
    
    this->scheduleUpdate();
    
    return true;
}

void GameScene::update(float dt)
{
    if (this->_pause)
        return;

    
}

void GameScene::pause()
{
    this->_pause = true;
    this->_pauseScene->setVisible(true);
}

void GameScene::resume()
{
    this->_pause = false;
    this->_pauseScene->setVisible(false);
}