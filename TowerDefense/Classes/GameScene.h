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

#define		TIME_TO_POP 4.2f
#define		CASE_X 12
#define		CASE_Y 6
class GameScene : public cocos2d::Layer
{
	public:
    virtual bool init() override;
    virtual void update(float deltaTime) override;
    static cocos2d::Scene* createScene();
private:

	struct Ally {
		cocos2d::Sprite *sprite;
		float _attack_speed;
		float _hp;
		int _id_shot;
		float _count;
	};

	struct Enemy {
		cocos2d::Sprite *sprite;
		float _attack_speed;
		float _force;
		float _hp;
		float _speed;
		float _count;
	};

	struct Shot {
		cocos2d::Sprite *sprite;
		float _force;
		float _speed;
	};
private:
    void pauseGame();
    void resumeGame();
    void menuGame();
    void randomPoper(float deltaTime);
	cocos2d::Vec2 posWordToScreen(cocos2d::Vec2 word);
	cocos2d::Vec2 posScreenToWord(cocos2d::Vec2 screen);

	void createAlly(int id, cocos2d::Vec2 pos);
	void createShot(int id, cocos2d::Vec2 pos);
	void createEnemy(int id, cocos2d::Vec2 pos);

	void updateAlly(float deltaTime);
	void updateShot(float deltaTime);
	void updateEnemies(float deltaTime);
private:
    double timeSinceBegin;
    bool pause;
    cocos2d::Menu* optionMenu;
    CREATE_FUNC(GameScene);
	//pop enemies
    float timeToPopMax = TIME_TO_POP;
    float timer;
	//drag and drop
	cocos2d::Sprite *_dad[2];
	cocos2d::Sprite *_selected;
	int _selected_id;
	//objects
	std::vector<Ally*>		_allies;
	std::vector<Enemy*>		_enemies;
	std::vector<Shot*>		_shots;
};

#endif /* defined(__TowerDefense__GameScene__) */
