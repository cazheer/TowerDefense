//
//  GameScene.cpp
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#include "GameScene.h"

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

    resumeGame();

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
		_dad[i]->setScale(0.09f, 0.09f);
		_dad[i]->setPosition(posWordToScreen(Vec2(1 + i, 5)));
		this->addChild(_dad[i]);
	}

    timeSinceBegin = 0.0f;
    timer = 0.0f;

	//drag and drop
	auto listener1 = EventListenerTouchOneByOne::create();
	// trigger when you push down
	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
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
				_selected->setScale(0.09f, 0.09f);
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
	Ally *ally = new Ally();
	std::string str = "allies/" + std::to_string(id + 1) + ".png";
	ally->sprite = Sprite::create(str);
	ally->sprite->setScale(0.09f, 0.09f);
	ally->sprite->setPosition(posWordToScreen(pos));
	this->addChild(ally->sprite);
	ally->_count = 0.f;
	switch (id)
	{
	case 0:
		ally->_hp = 100;
		ally->_id_shot = 0;
		ally->_attack_speed = 1.f;
		break;
	case 1:
		ally->_hp = 50;
		ally->_id_shot = 1;
		ally->_attack_speed = 2.f;
		break;
	default:
		break;
	}
	_allies.push_back(ally);
}

void GameScene::createShot(int id, cocos2d::Vec2 pos)
{
	Shot *ally = new Shot();
	std::string str = "shot/" + std::to_string(id + 1) + ".png";
	ally->sprite = Sprite::create(str);
	ally->sprite->setScale(1.f, 1.f);
	ally->sprite->setPosition(posWordToScreen(pos));
	this->addChild(ally->sprite);
	switch (id)
	{
	case 0:
		ally->_force = 10;
		ally->_speed = 5.0f;
		break;
	case 1:
		ally->_force = 25;
		ally->_speed = 3.5f;
		break;
	default:
		break;
	}
	_shots.push_back(ally);
}

void GameScene::createEnemy(int id, cocos2d::Vec2 pos)
{
	Enemy *enemy = new Enemy();
	std::string str = "allies/" + std::to_string(id + 1) + ".png";
	enemy->sprite = Sprite::create(str);
	enemy->sprite->setScale(0.09f, 0.09f);
	enemy->sprite->setPosition(posWordToScreen(pos));
	this->addChild(enemy->sprite);
	enemy->_count = 0;
	switch (id)
	{
	case 0:
		enemy->_attack_speed = 1.f;
		enemy->_force = 10.f;
		enemy->_hp = 50;
		enemy->_speed = 2.f;
		break;
	case 1:
		enemy->_attack_speed = 1.f;
		enemy->_force = 10.f;
		enemy->_hp = 50;
		enemy->_speed = 3.f;
		break;
	default:
		break;
	}
	_enemies.push_back(enemy);
}

void GameScene::updateAlly(float deltaTime)
{
	for (size_t i = 0; i < _allies.size(); i++)
	{
		if (_allies[i]->_hp <= 0)
		{
			this->removeChild(_allies[i]->sprite);
			_allies.erase(_allies.begin() + i);
			continue;
		}
		_allies[i]->_count += deltaTime;
		if (_allies[i]->_count >= _allies[i]->_attack_speed)
		{
			_allies[i]->_count = 0;
			createShot(_allies[i]->_id_shot, posScreenToWord((_allies[i]->sprite->getPosition())));
			//createShot(_allies[i]->_id_shot, Vec2(2, 2));
		}
	}
}

void GameScene::updateShot(float deltaTime)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (size_t i = 0; i < _shots.size(); i++)
	{
		bool col = false;
		for (size_t j = 0; j < _enemies.size(); j++)
		{
			if (_shots[i]->sprite->getBoundingBox().intersectsRect(_enemies[j]->sprite->getBoundingBox()))
			{
				col = true;
				_enemies[j]->_hp -= _shots[i]->_force;
				this->removeChild(_shots[i]->sprite);
				_shots.erase(_shots.begin() + i);
				break;
			}
		}
		if (!col)
		{
			if (_shots[i]->sprite->getPosition().x >  visibleSize.width)
			{
				this->removeChild(_shots[i]->sprite);
				_shots.erase(_shots.begin() + i);
				continue;
			}
			else
			{
				float x = _shots[i]->_speed;
				_shots[i]->sprite->setPosition(_shots[i]->sprite->getPosition() + Vec2(x, 0));
			}
		}
	}
}


void GameScene::updateEnemies(float deltaTime)
{
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->_hp <= 0)
		{
			this->removeChild(_enemies[i]->sprite);
			_enemies.erase(_enemies.begin() + i);
			continue;
		}
		else if (posScreenToWord(_enemies[i]->sprite->getPosition()).x < 1)
		{
			log("un énemi est passé");
			this->removeChild(_enemies[i]->sprite);
			_enemies.erase(_enemies.begin() + i);
			continue;
		}
		bool col = false;
		for (size_t j = 0; j < _allies.size(); j++)
		{
			if (_enemies[i]->sprite->getBoundingBox().intersectsRect(_allies[j]->sprite->getBoundingBox()))
			{
				col = true;
				_enemies[i]->_count += deltaTime;
				if (_enemies[i]->_count >= _enemies[i]->_attack_speed)
				{
					_allies[j]->_hp -= _enemies[i]->_force;
				}
			}
		}
		if (!col)
		{
			float x = _enemies[i]->_speed;
			_enemies[i]->sprite->setPosition(_enemies[i]->sprite->getPosition() - Vec2(x, 0));
		}
	}
}

void GameScene::update(float deltaTime)
{
    if (pause)
        return;
	updateAlly(deltaTime);
	updateShot(deltaTime);
	updateEnemies(deltaTime);
	randomPoper(deltaTime);
    //timeSinceBegin += deltaTime;

    //
}

void GameScene::randomPoper(float deltaTime)
{
    timer += deltaTime;
	int var = (timeToPopMax - timer) * 100.0;
    if (var <= 0 || rand() % var == 0)
    {
        timer = 0.0;
		createEnemy(rand() % 2, Vec2(11, rand() % 5));
		//createEnemy(0, Vec2(2, 10));
		//EnemyManager::getInstance()->createUnit(rand() % MAX_TYPE_ENEMY, rand() % NUMBERLINE);
    }
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