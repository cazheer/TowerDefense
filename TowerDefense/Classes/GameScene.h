//
//  GameScene.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef __TowerDefense__GameScene__
#define __TowerDefense__GameScene__

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "cocos2d.h"

/////////////////////
// MY CLASS DEFINE //
/////////////////////
# define    FILE_GAME_PAUSE_BACKGROUND            ""
# define    FILE_GAME_PAUSE_RESUMEBUTTON_NORMAL   ""
# define    FILE_GAME_PAUSE_RESUMEBUTTON_SELECTED ""
# define    FILE_GAME_PAUSE_MENUBUTTON_NORMAL     ""
# define    FILE_GAME_PAUSE_MENUBUTTON_SELECTED   ""

class GameScene : public cocos2d::Layer
{
    bool pause;
    cocos2d::Menu* optionMenu;

public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    virtual void update(float deltaTime) override;

    // pause gestion
    void pauseGame();
    void resumeGame();
    void menuGame();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* defined(__TowerDefense__GameScene__) */
