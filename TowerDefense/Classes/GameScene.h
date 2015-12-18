//
//  GameScene.h
//  TowerDefense
//
//  Created by admin on 12/2/15.
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
# define    BACKGROUND_GAME_MUSIC   "music/bg.mp3"
# define    END_GAME_EFFECT         "music/end.mp3"

# define    FILE_GAME_BACKGROUND                  "background.png"
# define    FILE_GAME_PAUSE_BACKGROUND            "PauseBackground.png"
# define    FILE_GAME_END_BACKGROUND              "EndBackground.jpg"
# define    FILE_GAME_PAUSE_RESUMEBUTTON_NORMAL   "ContinueButton.png"
# define    FILE_GAME_PAUSE_RESUMEBUTTON_SELECTED "ContinueButton.png"
# define    FILE_GAME_PAUSE_MENUBUTTON_NORMAL     "BackToMenuButton.png"
# define    FILE_GAME_PAUSE_MENUBUTTON_SELECTED   "BackToMenuButton.png"
# define    FILE_GAME_PAUSE_PAUSEBUTTON_NORMAL    "PauseButton.png"
# define    FILE_GAME_PAUSE_PAUSEBUTTON_SELECTED  "PauseButton.png"
# define    FILE_GAME_PAUSE_RETRYBUTTON_NORMAL    "RetryButton.png"
# define    FILE_GAME_PAUSE_RETRYBUTTON_SELECTED  "RetryButton.png"

# define    FONTS               "fonts/Marker Felt.ttf"

# define    TIME_TO_POP         4.2f
# define    TIME_TO_POINT       2.0f

# define    CASE_X              12
# define    CASE_Y              6
# define    TERRAIN_X           10
# define    TERRAIN_Y           5

# define    BEGIN_POINT         50
# define    POINT_WIN_KILL      10
# define    POINT_WIN_TIME      5
# define    POINT_LOSE_PASS     25

# define    ALLY_FOLDER         "ally/"
# define    ALLYUNIT_NUMBER     5
# define    ENEMY_FOLDER        "enemy/"
# define    ENEMYUNIT_NUMBER    5
# define    SHOT_FOLDER         "shot/"
# define    SHOT_NUMBER         4

class GameScene : public cocos2d::Layer
{
    ////////////////////////////////////
    // Public Functions

public:
    virtual bool init() override;
    virtual void update(float deltaTime) override;
    static cocos2d::Scene* createScene();

    ////////////////////////////////////
    // Private structures

private:
    struct AddMark
    {
        cocos2d::Label*     label;
        float               transparancy;
        int                 sens;
    };
    struct Ally
    {
        cocos2d::Sprite*    sprite;
        float               _attack_speed;
        float               _hp;
        int                 _id_shot;
        float               _count;
    };
    struct Enemy
    {
        cocos2d::Sprite*    sprite;
        float               _attack_speed;
        int                 _force;
        int                 _hp;
        float               _speed;
        float               _count;
    };
    struct Shot
    {
        cocos2d::Sprite*    sprite;
        int                 _force;
        float               _speed;
    };

    ////////////////////////////////////
    // Private Functions

private:
    /*
    ** Callback functions
    */
    void pauseGame();
    void resumeGame();
    void menuGame();
    void optionGame();
    void retryGame();

    /*
    ** Create and initialize functions
    */
    void createAlly(int id, cocos2d::Vec2 pos);
    void createShot(int id, cocos2d::Vec2 pos);
    void createEnemy(int id, cocos2d::Vec2 pos);
    void addMark(int i, cocos2d::Vec2 pos);

    /*
    ** Update functions
    */
    void updateAlly(float deltaTime);
    void updateShot(float deltaTime);
    void updateEnemies(float deltaTime);
    void updateMark(float deltaTime);

    /*
    ** Utility functions
    */
    void InitializeValues();

    bool isEmptyPlace(cocos2d::Vec2);
    void randomPoper(float deltaTime);

    cocos2d::Vec2 posWorldToScreen(cocos2d::Vec2 world);
    cocos2d::Vec2 posScreenToWorld(cocos2d::Vec2 screen);

    /*
    ** function from cocos::Layer
    */
    CREATE_FUNC(GameScene);

    ////////////////////////////////////
    // Private Variables
    
private:
    cocos2d::Label*         _time;
    double                  timeSinceBegin;
    bool                    pause;
    cocos2d::Menu*          optionMenu;
    cocos2d::Menu*          endMenu;
    //pop enemies
    float                   timeToPopMax = TIME_TO_POP;
    float                   timer;
    //drag and drop
    cocos2d::Sprite*        _dad[ALLYUNIT_NUMBER];
    cocos2d::Sprite*        _selected;
    int                     _selected_id;
    //objects
    std::vector<Ally*>      _allies;
    std::vector<Enemy*>     _enemies;
    std::vector<Shot*>      _shots;
    // prices
    int                     _price[ALLYUNIT_NUMBER];
    // possibility of spawning
    int                     _spawn[ENEMYUNIT_NUMBER];
    // marks
    cocos2d::Label*         _mark_string;
    int                     _mark;
    float                   _mark_timer;
    std::vector<AddMark>    _add_mark;
};

#endif /* defined(__TowerDefense__GameScene__) */
