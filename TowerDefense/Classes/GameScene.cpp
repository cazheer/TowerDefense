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

cocos2d::Vec2 GameScene::posScreenToWord(cocos2d::Vec2 screen)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return Vec2(int(screen.x / visibleSize.width * CASE_X),
		int(screen.y / visibleSize.height * CASE_Y));
}

cocos2d::Vec2 GameScene::posWordToScreen(cocos2d::Vec2 word)
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return Vec2(origin.x + word.x * visibleSize.width / CASE_X + 0.5f * visibleSize.width / CASE_X,
		origin.y + word.y * visibleSize.height / CASE_Y + 0.5f * visibleSize.height / CASE_Y);
}

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

	// add background sprite
	auto background = Sprite::create(FILE_GAME_BACKGROUND);
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(background);

	//add images
	for (int i = 0; i < 2; i++)
	{
		std::string str = "allies/" + std::to_string(i + 1) + ".png";
		_dad[i] = Sprite::create(str);
		_dad[i]->setScale(0.1f,0.1f);
		_dad[i]->setPosition(posWordToScreen(Vec2(1 + i, 5)));
		this->addChild(_dad[i]);
	}
	
    ////////////////////////////////
    // 3. Initialize the game data
    AllyManager::getInstance()->Initialize(this);
    EnemyManager::getInstance()->Initialize(this);



	//drag and drop
	auto listener1 = EventListenerTouchOneByOne::create();
	log("test mouse");
	// trigger when you push down
	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		log("mouse pressed");
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		//Get the position of the current point relative to the button
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());

		//Check the click area
		for (int i = 0; i < 2; i++)
		{
			if (_dad[i]->getBoundingBox().containsPoint(locationInNode))
			{
				std::string str = "allies/" + std::to_string(i + 1) + ".png";
				_selected = Sprite::create(str);
				_selected->setScale(0.1f, 0.1f);
				_selected->setPosition(posWordToScreen(Vec2(1 + i, 6)));
				_selected->setOpacity(180);
				_selected_id = i;
				this->addChild(_selected);
				break;
			}
		}
		
		return true;
	};

	listener1->onTouchMoved = [this](Touch* touch, Event* event) {
		if (_selected != NULL)
		{
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Vec2 mouse = posScreenToWord(Vec2(locationInNode.x, locationInNode.y));
			_selected->setPosition(posWordToScreen(Vec2(mouse.x, mouse.y)));
		}
	};

	listener1->onTouchEnded = [this](Touch* touch, Event* event) {
		if (_selected != NULL)
		{
			Vec2 pos = posScreenToWord(_selected->getPosition());
			if (pos.x > 0 && pos.x < 11 && pos.y >= 0 && pos.y < 5)
				createAlly(_selected_id, pos);
			this->removeChild(_selected);
			_selected = NULL;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    this->scheduleUpdate();
    return true;
}

void GameScene::createAlly(int id, cocos2d::Vec2 pos)
{
	GameScene::Units unit;
	std::string str = "allies/" + std::to_string(id + 1) + ".png";
	unit.sprite = Sprite::create(str);
	unit.sprite->setScale(0.1f, 0.1f);
	unit.sprite->setPosition(posWordToScreen(pos));
	this->addChild(unit.sprite);
	//_allies.push_back(unit);


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