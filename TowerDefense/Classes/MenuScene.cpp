//
//  MenuScene.cpp
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#include "MenuScene.h"
#include "GameScene.h"
#include "OptionScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = create();
    
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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add background sprite
    auto background = Sprite::create(FILE_MENU_BACKGROUND);
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    background->setPosition(Vec2(
        origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(background);

    // Play button
    auto playItem = MenuItemImage::create(
        FILE_MENU_PLAYBUTTON_NORMAL,
        FILE_MENU_PLAYBUTTON_SELECTED,
        CC_CALLBACK_0(MenuScene::startGame, this));
    playItem->setScale(
        visibleSize.width / (playItem->getContentSize().width * 4),
        visibleSize.height / (playItem->getContentSize().height * 10));

    playItem->setPosition(
        Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 6));

    // Exit Button
    auto exitItem = MenuItemImage::create(
        FILE_MENU_EXITBUTTON_NORMAL,
        FILE_MENU_EXITBUTTON_SELECTED,
        CC_CALLBACK_0(MenuScene::exitGame, this));
    exitItem->setScale(
        visibleSize.width / (exitItem->getContentSize().width * 10),
        visibleSize.height / (exitItem->getContentSize().height * 10));

    exitItem->setPosition(
        Vec2(origin.x + visibleSize.width * 0.9 + 16,
        origin.y + visibleSize.height * 0.9 - 16));
    
    // Option Button
    auto optionItem = MenuItemImage::create(
        FILE_MENU_OPTIONBUTTON_NORMAL,
        FILE_MENU_OPTIONBUTTON_SELECTED,
        CC_CALLBACK_0(MenuScene::optionGame, this));
    optionItem->setScale(
        visibleSize.width / (optionItem->getContentSize().width * 10),
        visibleSize.height / (optionItem->getContentSize().height * 10));

    optionItem->setPosition(
        Vec2(origin.x + visibleSize.width * 0.8 + 16,
        origin.y + visibleSize.height * 0.9 - 16));

    // create menu, it's an autorelease object
    auto menu = Menu::create(
        playItem,
        optionItem,
        exitItem,
        nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void MenuScene::startGame()
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MenuScene::optionGame()
{
    auto scene = OptionScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MenuScene::exitGame()
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}