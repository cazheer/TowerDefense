#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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

void GameScene::setLevel(std::string& level)
{
    _level = level;
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
    
    auto rootNode = CSLoader::createNode("GameScene.csb");
    addChild(rootNode);

    _paused = false;
    this->scheduleUpdate();

    return true;
}


void GameScene::update(float deltaTime)
{
    if (!_paused)
        gameLoop(deltaTime);
    else
        pauseLoop(deltaTime);
}

// Called when the game is running
void GameScene::gameLoop(float deltaTime)
{

}

// Called when the game is paused
// Display inGameMenu
void GameScene::pauseLoop(float deltaTime)
{

}