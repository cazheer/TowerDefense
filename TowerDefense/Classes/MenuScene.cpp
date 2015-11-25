//
//  Menu.cpp
//  TowerDefense
//
//  Created by admin on 11/20/15.
//
//

#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto rootNode = CSLoader::createNode("MenuScene.csb");
    addChild(rootNode);
    
    auto button = rootNode->getChildByName<cocos2d::ui::Button*>("StartButton");
    button->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        
    });
    
    button = rootNode->getChildByName<cocos2d::ui::Button*>("OptionButton");
    button->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        
    });
    
    button = rootNode->getChildByName<cocos2d::ui::Button*>("ExitButton");
    button->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
    {
        Director::getInstance()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    });
    
    return true;
}

