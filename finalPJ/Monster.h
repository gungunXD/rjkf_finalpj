#ifndef		Monster_h
#define		Monster_h

#include <SFML/Graphics.hpp>
#include <assert.h>
#include <vector>
#include "MainCharacter.h"

#define		MONSTER_SPEED		10

using namespace sf;
using namespace std;


/****************************************************************************
*
*								怪物攻击类
*
****************************************************************************/

struct Attack {

private:
	float x;																//图形的横坐标
	float y;																//图形的纵坐标
	bool direction;															//攻击移动的方向 : 0 向右； 1 向左
	int speed;																//攻击的速度
	bool over;																//攻击结束的标志

	Image Attack_image;														//素材图片
	int frame;																//帧数
	int current_frame;														//当前的显示的帧数
	vector<IntRect> posi_image;												//每一帧在输入图片上的位置
	vector<int> image_num;													//每一帧所在图片的序号

public:
	Sprite attack;
	Texture t_attack;

	Attack(float cx, float cy, bool direct, int sp = 10) {
		x = cx;
		y = cy;
		direction = direct;
		speed = sp;
		over = false;
	}
	~Attack() { }

	void Initial();
	void Move();
	void setOver() { over = true; }
	bool getOver() { return over; }
};

/****************************************************************************
*
*								怪物的基类
*
****************************************************************************/

class Monster {

public:
	Sprite	monster;
	Texture t_monster;

	virtual Shift Position() = 0;

	virtual void InitPrepare() = 0;
	virtual void InitAppear() = 0;
	virtual void InitWait() = 0;
	virtual void InitRun() = 0;
	virtual void InitSingleAttack() = 0;

	virtual void Prepare() = 0;
	virtual void Appear() = 0;
	virtual void Wait() = 0;
	virtual void Run(float) = 0; 
	virtual void SingleAttack() = 0;

};


/****************************************************************************
*
*								盒子怪物类
*
****************************************************************************/

class Mons_Box : public Monster{

private:
	float x;
	float y;
	Image Monster_image[2];

	Skill prepare;
	Skill appear;
	Skill wait;
	Skill run;
	Skill single_attack;

	bool Prepared;
	bool Appeared;
	bool bInWait;
	bool bInRun;
	bool bInSingleAttack;

public:
	Sprite monster;
	Texture t_monster;

	Mons_Box()
	{
		assert(Monster_image[0].loadFromFile("monster01_1.png"));
		assert(Monster_image[1].loadFromFile("monster01_2.png"));

		InitPrepare();
		InitAppear();
		InitRun();
		InitWait();
		InitSingleAttack();

		assert(t_monster.loadFromImage(Monster_image[0], IntRect{ 350,350,100,170 }));
		monster.setTexture(t_monster);
		monster.setOrigin(0, 0);

		x = 500;
		y = 100;
		monster.setPosition(x, y);
	}

	Shift Position() { return Shift{ x, y }; }

	void InitPrepare();
	void InitAppear();
	void InitWait();
	void InitRun();
	void InitSingleAttack();

	void Prepare();
	void Appear();
	void Wait();
	void Run(float);
	void SingleAttack();
	Attack* Range_attack(float);

	//void set_Prepared() { Prepared = true; };
	//void set_Appeared() { Appeared = true; };
	void set_bInwait() { bInWait = true; }
	void set_bInRun() { bInRun = true; }
	//void set_bInSingleAttack() { bInSingleAttack = true; };
	//bool get_bInPrepare() { return bInPrepare; };
	bool get_Appeared() { return Appeared; };
	bool get_bInwait() { return bInWait; }
	bool get_bInRun() { return bInRun; }
	//bool get_bInSingleAttack() { return bInSingleAttack; };
};


/****************************************************************************
*
*								石锤怪物类
*
****************************************************************************/

class Mons_Hummer : public Monster {

private:
	float x;
	float y;
	bool direction;															//方向：0（向右） 1（向左）
	Image Monster_image[2];

	Skill prepare;
	Skill appear;
	Skill wait;
	Skill run;
	Skill single_attack;

	bool Prepared;
	bool Appeared;
	bool bInWait;
	bool bInRun;
	bool bInSingleAttack;

public:
	Sprite monster;
	Texture t_monster;

	Mons_Hummer()
	{
		assert(Monster_image[0].loadFromFile("monster03_1.png"));
		assert(Monster_image[1].loadFromFile("monster03_2.png"));

		InitPrepare();
		InitAppear();
		InitRun();
		InitWait();
		InitSingleAttack();

		assert(t_monster.loadFromImage(Monster_image[0], IntRect{ 406,154,110,90 }));
		monster.setTexture(t_monster);
		monster.setOrigin(0, 0);

		x = 400;
		y = 165;
		monster.setPosition(x, y);
	}

	Shift Position() { return Shift{ x, y }; }
	void change_direction(float);													//一段时间之内改变行进方向

	void InitPrepare();
	void InitAppear();
	void InitWait();
	void InitRun();
	void InitSingleAttack();

	void Prepare();
	void Appear();
	void Wait();
	void Run(float);
	void SingleAttack();

	//void set_Prepared() { Prepared = true; };
	//void set_Appeared() { Appeared = true; };
	void set_bInwait() { bInWait = true; }
	void set_bInRun() { bInRun = true; }
	void set_bInSingleAttack() { bInSingleAttack = true; };
	//bool get_bInPrepare() { return bInPrepare; };
	bool get_Appeared() { return Appeared; };
	bool get_bInwait() { return bInWait; }
	bool get_bInRun() { return bInRun; }
	bool get_bInSingleAttack() { return bInSingleAttack; };
};

#endif