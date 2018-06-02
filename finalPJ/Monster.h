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
*								���﹥����
*
****************************************************************************/

struct Attack {

private:
	float x;																//ͼ�εĺ�����
	float y;																//ͼ�ε�������
	bool direction;															//�����ƶ��ķ��� : 0 ���ң� 1 ����
	int speed;																//�������ٶ�
	bool over;																//���������ı�־

	Image Attack_image;														//�ز�ͼƬ
	int frame;																//֡��
	int current_frame;														//��ǰ����ʾ��֡��
	vector<IntRect> posi_image;												//ÿһ֡������ͼƬ�ϵ�λ��
	vector<int> image_num;													//ÿһ֡����ͼƬ�����

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
*								����Ļ���
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
*								���ӹ�����
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
*								ʯ��������
*
****************************************************************************/

class Mons_Hummer : public Monster {

private:
	float x;
	float y;
	bool direction;															//����0�����ң� 1������
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
	void change_direction(float);													//һ��ʱ��֮�ڸı��н�����

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