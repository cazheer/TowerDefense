//
//  MenuScene.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
//
//

#ifndef     __TowerDefense__MenuScene__
# define    __TowerDefense__MenuScene__

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "cocos2d.h"

/////////////////////
// MY CLASS DEFINE //
/////////////////////
# define    FILE_MENU_BACKGROUND            "KeimyungBackground.jpg"
# define    FILE_MENU_PLAYBUTTON_NORMAL     "PlayButton.png"
# define    FILE_MENU_PLAYBUTTON_SELECTED   "PlayButton.png"
# define    FILE_MENU_OPTIONBUTTON_NORMAL   "SettingsButton.png"
# define    FILE_MENU_OPTIONBUTTON_SELECTED "SettingsButton.png"
# define    FILE_MENU_EXITBUTTON_NORMAL     "ExitButton.png"
# define    FILE_MENU_EXITBUTTON_SELECTED   "ExitButton.png"

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;

    void startGame();
    void optionGame();
    void exitGame();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif /* defined(__TowerDefense__MenuScene__) */
