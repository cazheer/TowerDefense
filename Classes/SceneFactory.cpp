#include "SceneFactory.h"
#include "StartScene.h"
#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

SceneFactory::SceneFactory() :
levels({"level_00.lvl"})
{
}


SceneFactory::~SceneFactory()
{
}


SceneFactory* SceneFactory::getInstance()
{
    if (!instance)
        instance = new SceneFactory();
    return instance;
}


Scene* SceneFactory::createScene(SceneType type, int difficulty)
{
    switch (type)
    {
    case SceneType::START:
        return createStartScene();
    case SceneType::MENU:
        return createMenuScene();
    case SceneType::GAME:
        return createGameScene(difficulty);
    default:
        return NULL;
    }
}


Scene* SceneFactory::createStartScene()
{
    return StartScene::createScene();
}

Scene* SceneFactory::createMenuScene()
{
    return MenuScene::createScene();
}

Scene* SceneFactory::createGameScene(int difficulty)
{
    if (difficulty < 0 || difficulty >= levels.size())
        return NULL;

    Scene* scene = GameScene::createScene();
    GameScene::setLevel(levels[difficulty]);

    return scene;
}
