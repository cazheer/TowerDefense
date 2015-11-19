#ifndef __SCENE_FACTORY__
#define __SCENE_FACTORY__

#include "cocos2d.h"
#include <vector>
#include <string>

enum SceneType
{
    START,
    MENU,
    GAME
};

class SceneFactory
{
    static SceneFactory* instance;

    std::vector<std::string> levels;

    SceneFactory();
    ~SceneFactory();

    cocos2d::Scene* createStartScene();
    cocos2d::Scene* createMenuScene();
    cocos2d::Scene* createGameScene(int difficulty);

public:
    static SceneFactory* getInstance();

    cocos2d::Scene* createScene(SceneType type, int difficulty = 0);
};

#endif // __SCENE_FACTORY__