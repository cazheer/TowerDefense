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
# define    FILE_GAME_BACKGROUND            "bg.png"
# define    FILE_GAME_PAUSE_BACKGROUND            ""
# define    FILE_GAME_PAUSE_RESUMEBUTTON_NORMAL   ""
# define    FILE_GAME_PAUSE_RESUMEBUTTON_SELECTED ""
# define    FILE_GAME_PAUSE_MENUBUTTON_NORMAL     ""
# define    FILE_GAME_PAUSE_MENUBUTTON_SELECTED   ""

#define		CASE_X 12
#define		CASE_Y 6
class GameScene : public cocos2d::Layer
{
    double timeSinceBegin;
    bool pause;
    cocos2d::Menu* optionMenu;
	struct Units {
		cocos2d::Sprite *sprite;
		float _speed;
		float _attack_speed;
		float _force;
		float _hp;
	};
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    virtual void update(float deltaTime) override;
    // pause gestion
    void pauseGame();
    void resumeGame();
    void menuGame();
	void createAlly(int id, cocos2d::Vec2 pos);
	cocos2d::Vec2 posWordToScreen(cocos2d::Vec2 word);
	cocos2d::Vec2 posScreenToWord(cocos2d::Vec2 screen);
    CREATE_FUNC(GameScene);

private:
    // pop enemies
    float timeToPopMax;
    float timer;

public:
    void randomPoper(float deltaTime);

private:
	cocos2d::Sprite *_dad[2];
	std::vector<Units> _allies;
	std::vector<Units> _enemies;
	cocos2d::Sprite *_selected;
	int _selected_id;
};

#endif /* defined(__TowerDefense__GameScene__) */
