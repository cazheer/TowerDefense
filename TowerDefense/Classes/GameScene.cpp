//
//  GameScene.cpp
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#include "GameScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Vec2 GameScene::posScreenToWorld(Vec2 screen)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    return Vec2(
        int(screen.x / visibleSize.width * CASE_X),
        int(screen.y / visibleSize.height * CASE_Y));
}

Vec2 GameScene::posWorldToScreen(Vec2 world)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    return Vec2(
        int(origin.x + world.x * visibleSize.width / CASE_X + 0.5f * visibleSize.width / CASE_X),
        int(origin.y + world.y * visibleSize.height / CASE_Y + 0.5f * visibleSize.height / CASE_Y));
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

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_GAME_MUSIC, true);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    ////////////////////////////////
    // 2. Initialize the pause menu
    InitializeValues();

    ////////////////////////////////
    // 3. Initialize the pause menu

    auto bgPauseItem = MenuItemImage::create(
        FILE_GAME_PAUSE_BACKGROUND,
        FILE_GAME_PAUSE_BACKGROUND);
    bgPauseItem->setScale(
        visibleSize.width / (bgPauseItem->getContentSize().width * 2),
        visibleSize.height / (bgPauseItem->getContentSize().height * 2));
    bgPauseItem->setPosition(origin + visibleSize / 2);

    // resume button
    auto resumeItem = MenuItemImage::create(
        FILE_GAME_PAUSE_RESUMEBUTTON_NORMAL,
        FILE_GAME_PAUSE_RESUMEBUTTON_SELECTED,
        CC_CALLBACK_0(GameScene::resumeGame, this));
    resumeItem->setScale(
        visibleSize.width / (resumeItem->getContentSize().width * 4),
        visibleSize.height / (resumeItem->getContentSize().height * 6));
    resumeItem->setPosition(Vec2(
        origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2 + resumeItem->getContentSize().height));

    auto retryItem = MenuItemImage::create(
        FILE_GAME_PAUSE_RETRYBUTTON_NORMAL,
        FILE_GAME_PAUSE_RETRYBUTTON_SELECTED,
        CC_CALLBACK_0(GameScene::retryGame, this));
    retryItem->setScale(
        visibleSize.width / (retryItem->getContentSize().width * 4),
        visibleSize.height / (retryItem->getContentSize().height * 6));
    retryItem->setPosition(Vec2(
        origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));

    // menu button
    auto menuItem = MenuItemImage::create(
        FILE_GAME_PAUSE_MENUBUTTON_NORMAL,
        FILE_GAME_PAUSE_MENUBUTTON_SELECTED,
        CC_CALLBACK_0(GameScene::menuGame, this));
    menuItem->setScale(
        visibleSize.width / (menuItem->getContentSize().width * 4),
        visibleSize.height / (menuItem->getContentSize().height * 6));
    menuItem->setPosition(Vec2(
        origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2 - resumeItem->getContentSize().height));

    optionMenu = Menu::create(
        bgPauseItem,
        resumeItem,
        retryItem,
        menuItem,
        nullptr);
    optionMenu->setPosition(Vec2::ZERO);
    this->addChild(optionMenu, 1);

    resumeGame();

    // end menu
    auto bgEnd = MenuItemImage::create(
        FILE_GAME_END_BACKGROUND,
        FILE_GAME_END_BACKGROUND);
    bgEnd->setScale(
        visibleSize.width / bgEnd->getContentSize().width,
        visibleSize.height / bgEnd->getContentSize().height);
    bgEnd->setPosition(origin + visibleSize / 2);

    auto retryButton = MenuItemImage::create(
        FILE_GAME_PAUSE_RETRYBUTTON_NORMAL,
        FILE_GAME_PAUSE_RETRYBUTTON_SELECTED,
        CC_CALLBACK_0(GameScene::retryGame, this));
    retryButton->setScale(
        visibleSize.width / (retryButton->getContentSize().width * 4),
        visibleSize.height / (retryButton->getContentSize().height * 6));
    retryButton->setPosition(origin + visibleSize / 2 - Vec2(0, retryButton->getContentSize().height) * 1.8);

    auto menuButton = MenuItemImage::create(
        FILE_GAME_PAUSE_MENUBUTTON_NORMAL,
        FILE_GAME_PAUSE_MENUBUTTON_SELECTED,   
        CC_CALLBACK_0(GameScene::menuGame, this));
    menuButton->setScale(
        visibleSize.width / (menuButton->getContentSize().width * 4),
        visibleSize.height / (menuButton->getContentSize().height * 6));
    menuButton->setPosition(origin + visibleSize / 2 - Vec2(0, retryButton->getContentSize().height) * 2.6);

    endMenu = Menu::create(
        bgEnd,
        retryButton,
        menuButton,
        nullptr);
    endMenu->setPosition(Vec2::ZERO);
    this->addChild(endMenu, 1);
    endMenu->setVisible(false);

    // option button
    auto button = MenuItemImage::create(
        FILE_GAME_PAUSE_PAUSEBUTTON_NORMAL,
        FILE_GAME_PAUSE_PAUSEBUTTON_SELECTED,
        CC_CALLBACK_0(GameScene::optionGame, this));
    button->setScale(
        visibleSize.width / (button->getContentSize().width * CASE_X),
        visibleSize.height / (button->getContentSize().height * CASE_Y));
    button->setPosition(posWorldToScreen(Vec2(CASE_X - 1, CASE_Y - 1)));

    auto menu = Menu::create(
        button,
        nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add background sprite
    auto background = Sprite::create(FILE_GAME_BACKGROUND);
    background->setScale(
        visibleSize.width / background->getContentSize().width,
        visibleSize.height / background->getContentSize().height);
    background->setPosition(Vec2(
        origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(background);

    //add images et string drag and drop
    for (auto i = 0; i < ALLYUNIT_NUMBER; i++)
    {
        auto str = ALLY_FOLDER + std::to_string(i + 1) + ".png";
        _dad[i] = Sprite::create(str);
        _dad[i]->setScale(
            visibleSize.width / (_dad[i]->getContentSize().width * CASE_X),
            visibleSize.height / (_dad[i]->getContentSize().height * CASE_Y));
        _dad[i]->setPosition(posWorldToScreen(Vec2(i + 1, 5)));
        this->addChild(_dad[i]);
        auto legend = Label::createWithTTF(std::to_string(_price[i]), FONTS, 12);
        legend->setColor(Color3B(0, 0, 0));
        legend->setPosition(posWorldToScreen(Vec2(i + 1, 5)) + Vec2(30, -50));
        this->addChild(legend);
    }

    // time
    _time = Label::createWithTTF("0 s", FONTS, 24);
    _time->setPosition(posWorldToScreen(Vec2(9, 5)));
    _time->setColor(Color3B(0, 0, 0));
    this->addChild(_time);

    // marks
    _mark_string = Label::createWithTTF("Mark: " + std::to_string(BEGIN_POINT) + " %", FONTS, 24);
    _mark_string->setPosition(posWorldToScreen(Vec2(7, 5)));
    _mark_string->setColor(Color3B(0, 0, 0));
    this->addChild(_mark_string);

    //drag and drop
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [this](Touch* touch, Event* event)
    {
        if (pause)
            return true;

        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto target = static_cast<Sprite*>(event->getCurrentTarget());

        //Get the position of the current point relative to the button
        auto locationInNode = target->convertToNodeSpace(touch->getLocation());

        //Check the click area
        for (auto i = 0; i < ALLYUNIT_NUMBER; i++)
        {
            if (_dad[i]->getBoundingBox().containsPoint(locationInNode))
            {
                auto str = ALLY_FOLDER + std::to_string(i + 1) + ".png";
                _selected = Sprite::create(str);
                _selected->setScale(
                    visibleSize.width / (_selected->getContentSize().width * CASE_X),
                    visibleSize.height / (_selected->getContentSize().height * CASE_Y));
                _selected->setPosition(posWorldToScreen(Vec2(1 + i, 6)));
                _selected->setOpacity(180);
                _selected_id = i;
                this->addChild(_selected);
                break;
            }
        }
        
        return true;
    };

    listener1->onTouchMoved = [this](Touch* touch, Event* event)
    {
        if (_selected)
        {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            auto locationInNode = target->convertToNodeSpace(touch->getLocation());
            auto mouse = posScreenToWorld(Vec2(locationInNode.x, locationInNode.y));
            _selected->setPosition(posWorldToScreen(Vec2(mouse.x, mouse.y)));
        }
    };

    listener1->onTouchEnded = [this](Touch* touch, Event* event)
    {
        if (_selected)
        {
            auto pos = posScreenToWorld(_selected->getPosition());
            if (pos.x > 0 && pos.x < TERRAIN_X + 1 && pos.y >= 0 && pos.y < TERRAIN_Y)
                createAlly(_selected_id, pos);
            this->removeChild(_selected);
            _selected = nullptr;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    this->scheduleUpdate();
    return true;
}

void GameScene::InitializeValues()
{
    _price[0] = 20;
    _price[1] = 25;
    _price[2] = 40;
    _price[3] = 30;
    _price[4] = 50;

    _spawn[0] = 35;
    _spawn[1] = 30;
    _spawn[2] = 20;
    _spawn[3] = 10;
    _spawn[4] = 5;

    _mark = BEGIN_POINT;
    _mark_timer = 0;

    timeSinceBegin = 0.0f;
    timer = 0.0f;

    _selected = nullptr;
}

bool GameScene::isEmptyPlace(Vec2 pos)
{
    for (size_t i = 0; i < _allies.size(); i++)
        if (posScreenToWorld(_allies[i]->sprite->getPosition()) == pos)
            return false;
    return true;
}

void GameScene::createAlly(int id, Vec2 pos)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (_mark - _price[id] > 0 && isEmptyPlace(pos))
    {
        auto ally = new Ally();
        auto str = ALLY_FOLDER + std::to_string(id + 1) + ".png";
        ally->sprite = Sprite::create(str);
        ally->sprite->setScale(
            visibleSize.width / (ally->sprite->getContentSize().width * CASE_X),
            visibleSize.height / (ally->sprite->getContentSize().height * CASE_Y));
        ally->sprite->setPosition(posWorldToScreen(pos));
        this->addChild(ally->sprite);
        ally->_count = 0.f;
        switch (id)
        {
        case 0:
            ally->_hp = 60;
            ally->_id_shot = 0;
            ally->_attack_speed = 1.0f;
            break;
        case 1:
            ally->_hp = 50;
            ally->_id_shot = 1;
            ally->_attack_speed = 1.2f;
            break;
        case 2:
            ally->_hp = 30;
            ally->_id_shot = 2;
            ally->_attack_speed = 2.5f;
            break;
        case 3:
            ally->_hp = 70;
            ally->_id_shot = 3;
            ally->_attack_speed = 1.0f;
            break;
        case 4:
            ally->_hp = 350;
            ally->_id_shot = -1;
            ally->_attack_speed = 0.0f;
            break;
        default:
            break;
        }
        addMark(-_price[id], pos);

        if (ally->_attack_speed)
            ally->sprite->runAction(
                RepeatForever::create(
                Sequence::create(
                ScaleBy::create(ally->_attack_speed / 2, 0.8f),
                ScaleBy::create(ally->_attack_speed / 2, 1.25f),
                nullptr)));
        _allies.push_back(ally);
    }
}

void GameScene::createEnemy(int id, Vec2 pos)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto enemy = new Enemy();
    auto str = ENEMY_FOLDER + std::to_string(id + 1) + ".png";
    enemy->sprite = Sprite::create(str);
    enemy->sprite->setScale(
        visibleSize.width / (enemy->sprite->getContentSize().width * CASE_X),
        visibleSize.height / (enemy->sprite->getContentSize().height * CASE_Y));
    enemy->sprite->setPosition(posWorldToScreen(pos));
    this->addChild(enemy->sprite);
    enemy->_count = 0;
    switch (id)
    {
    case 0:
        enemy->_attack_speed = 1.2f;
        enemy->_force = 35;
        enemy->_hp = 60;
        enemy->_speed = 2.0f;
        break;
    case 1:
        enemy->_attack_speed = 0.8f;
        enemy->_force = 20;
        enemy->_hp = 30;
        enemy->_speed = 5.0f;
        break;
    case 2:
        enemy->_attack_speed = 1.0f;
        enemy->_force = 30;
        enemy->_hp = 50;
        enemy->_speed = 1.5f;
        break;
    case 3:
        enemy->_attack_speed = 3.0f;
        enemy->_force = 40;
        enemy->_hp = 300;
        enemy->_speed = 0.5f;
        break;
    case 4:
        enemy->_attack_speed = 2.0f;
        enemy->_force = 100;
        enemy->_hp = 200;
        enemy->_speed = 0.7f;
        break;
    default:
        break;
    }
    _enemies.push_back(enemy);
}

void GameScene::createShot(int id, Vec2 pos)
{
    if (id < 0)
        return;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto shot = new Shot();
    auto str = SHOT_FOLDER + std::to_string(id + 1) + ".png";
    shot->sprite = Sprite::create(str);
    shot->sprite->setScale(
        visibleSize.width / (shot->sprite->getContentSize().width * CASE_X * 1.5),
        visibleSize.height / (shot->sprite->getContentSize().height * CASE_Y * 1.5));
    shot->sprite->setPosition(posWorldToScreen(pos));
    this->addChild(shot->sprite);
    switch (id)
    {
    case 0:
        shot->_force = 10;
        shot->_speed = 5.0f;
        break;
    case 1:
        shot->_force = 25;
        shot->_speed = 3.5f;
        break;
    case 2:
        shot->_force = 40;
        shot->_speed = 2.5f;
        break;
    case 3:
        shot->_force = 20;
        shot->_speed = 7.5f;
        break;
    default:
        break;
    }

    _shots.push_back(shot);
}

void GameScene::update(float deltaTime)
{
    if (pause)
        return;

    timeSinceBegin += deltaTime;
    _time->setString(std::to_string((int)timeSinceBegin) + " s");

    randomPoper(deltaTime);
    updateMark(deltaTime);
    updateAlly(deltaTime);
    updateShot(deltaTime);
    updateEnemies(deltaTime);
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
            _allies[i]->_count -= _allies[i]->_attack_speed;
            createShot(_allies[i]->_id_shot, posScreenToWorld(_allies[i]->sprite->getPosition()));
        }
    }
}

void GameScene::updateEnemies(float deltaTime)
{
    for (size_t i = 0; i < _enemies.size(); i++)
    {
        if (_enemies[i]->_hp <= 0)
        {
            addMark(POINT_WIN_KILL, posScreenToWorld(_enemies[i]->sprite->getPosition()));
            this->removeChild(_enemies[i]->sprite);
            _enemies.erase(_enemies.begin() + i);
            continue;
        }
        if (posScreenToWorld(_enemies[i]->sprite->getPosition()).x < 1)
        {
            addMark(-POINT_LOSE_PASS, posScreenToWorld(_enemies[i]->sprite->getPosition()));
            this->removeChild(_enemies[i]->sprite);
            _enemies.erase(_enemies.begin() + i);
            continue;
        }
        auto col = false;
        for (size_t j = 0; j < _allies.size(); j++)
        {
            if (_enemies[i]->sprite->getBoundingBox().intersectsRect(_allies[j]->sprite->getBoundingBox()))
            {
                col = true;
                _enemies[i]->_count += deltaTime;
                if (_enemies[i]->_count >= _enemies[i]->_attack_speed)
                    _allies[j]->_hp -= _enemies[i]->_force;
            }
        }
        if (!col)
            _enemies[i]->sprite->setPosition(_enemies[i]->sprite->getPosition() - Vec2(_enemies[i]->_speed, 0));
        else if (_enemies[i]->_count >= _enemies[i]->_attack_speed)
            _enemies[i]->_count -= _enemies[i]->_attack_speed;
    }
}

void GameScene::updateShot(float deltaTime)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    for (size_t i = 0; i < _shots.size(); i++)
    {
        auto col = false;
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
            }
            else
            {
                auto x = _shots[i]->_speed;
                _shots[i]->sprite->setPosition(_shots[i]->sprite->getPosition() + Vec2(x, 0));
            }
        }
    }
}

void GameScene::addMark(int i, Vec2 pos)
{
    _mark += i;
    if (_mark > 100)
        _mark = 100;
    else if (_mark <= 0)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(END_GAME_EFFECT);
        pause = true;
        endMenu->setVisible(true);
    }
    else
    {
        AddMark mark;
        mark.label = Label::createWithTTF((i > 0 ? "+" : "-") + std::to_string(i), FONTS, 24);
        mark.label->setColor(Color3B(0, 0, 0));
        mark.label->setPosition(posWorldToScreen(pos));
        mark.transparancy = 255;
        mark.sens = i > 0 ? 1 : -1;
        _add_mark.push_back(mark);
        this->addChild(mark.label);
    }
}

void GameScene::updateMark(float deltaTime)
{
    _mark_timer += deltaTime;
    if (_mark_timer > TIME_TO_POINT)
    {
        _mark_timer -= TIME_TO_POINT;
        addMark(POINT_WIN_TIME, Vec2(8, 4));
    }
    auto str = "Mark: " + std::to_string(_mark) + " %";
    _mark_string->setString(str);
    for (size_t i = 0; i < _add_mark.size(); i++)
    {
        _add_mark[i].transparancy -= deltaTime * 50;
        if (_add_mark[i].transparancy <= 0)
        {
            this->removeChild(_add_mark[i].label);
            _add_mark.erase(_add_mark.begin() + i);
        }
        else
        {
            _add_mark[i].label->setTextColor(Color4B(0, 0, 0, _add_mark[i].transparancy));
            _add_mark[i].label->setPositionY(_add_mark[i].label->getPositionY() + _add_mark[i].sens);
        }
    }
}

void GameScene::randomPoper(float deltaTime)
{
    auto timeToPop = timeToPopMax / (timeSinceBegin / 30.0f);

    timer += deltaTime;
    int var = (timeToPop - timer) * 100.0;
    if (var <= 0 || rand() % var == 0)
    {
        auto valueMax = 0;
        for (auto i = 0; i < ENEMYUNIT_NUMBER; i++)
            valueMax += _spawn[i];

        auto enemyId = rand() % valueMax;
        enemyId = enemyId / (60.0f / timeSinceBegin);
        for (auto i = 0; i < ENEMYUNIT_NUMBER; i++)
        {
            if (enemyId >= _spawn[i])
                enemyId -= _spawn[i];
            else
            {
                enemyId = i;
                break;
            }
        }
        if (enemyId >= ENEMYUNIT_NUMBER)
            enemyId = ENEMYUNIT_NUMBER - 1;

        timer = 0.0;
        createEnemy(enemyId, Vec2(11, rand() % 5));
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
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInT::create(1, scene));
}

void GameScene::optionGame()
{
    pause = !pause;
    if (pause)
        pauseGame();
    else
        resumeGame();
}

void GameScene::retryGame()
{
    auto scene = createScene();
    Director::getInstance()->replaceScene(TransitionFlipX::create(2, scene));
}