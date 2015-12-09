//
//  GameScene.cpp
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#include "GameScene.h"
#include "AllyManager.h"
#include "EnemyManager.h"

USING_NS_CC;

Scene* GameScene::createScene()
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
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    ////////////////////////////////
    // 2. Initialize the pause menu

    // resume button
    auto resumeItem = MenuItemImage::create(
        FILE_GAME_PAUSE_RESUMEBUTTON_NORMAL,
        FILE_GAME_PAUSE_RESUMEBUTTON_SELECTED,
        CC_CALLBACK_0(GameScene::resume, this));

    resumeItem->setPosition(
        Vec2(origin.x + visibleSize.width / 2 - resumeItem->getContentSize().width / 2,
        origin.y + visibleSize.height / 2));

    // menu button
    auto menuItem = MenuItemImage::create(
        FILE_GAME_PAUSE_MENUBUTTON_NORMAL,
        FILE_GAME_PAUSE_MENUBUTTON_SELECTED,
        CC_CALLBACK_0(GameScene::menuGame, this));

    resumeItem->setPosition(
        Vec2(origin.x + visibleSize.width / 2 - menuItem->getContentSize().width / 2,
        origin.y + visibleSize.height / 2 + resumeItem->getContentSize().height * 2));

    optionMenu = Menu::create(
        nullptr);
    this->addChild(optionMenu, 1);

    resume();

    ////////////////////////////////
    // 3. Initialize the game data
    AllyManager::getInstance()->Initialize(this);
    EnemyManager::getInstance()->Initialize(this);

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float deltaTime)
{
    if (pause)
        return;

    AllyManager::getInstance()->Update(deltaTime);
    EnemyManager::getInstance()->Update(deltaTime);
}

void GameScene::pauseGame()
{
    pause = true;
    optionMenu->setVisible(true);
}

void GameScene::resumeGame()
{
    pause = false;
    optionMenu->setVisible(false);
}

void GameScene::menuGame()
{

}