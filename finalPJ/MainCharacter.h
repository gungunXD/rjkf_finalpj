#ifndef __MainCharacter_H__
#define __MainCharacter_H__

#include <SFML/Graphics.hpp>
#include<time.h>
#include<vector>
#include<assert.h>
#include"Blood.h"
using namespace sf;
using namespace std;

#define WIN_WIDTH 796
#define WIN_HEIGHT 356

#define ORIGIN_X 200
#define ORIGIN_Y 100

#define RUN_SPEED 20
#define MONSTER_SPEED 10

#define FULL_BLOOD_VALUE 100
#define FULL_BLOOD_WIDTH 60
#define BLOOD_HEIGHT 6

struct Shift {
	float x;
	float y;
};

struct Skill {
	int frame;  //֡��
	int current_frame;
	Image frame_image[2];  //�¼ӵ�
	vector<IntRect> posi_image;  //ÿһ֡������ͼƬ�ϵ�λ��
	vector<int> image_num; //����ͼƬ��Ļ�������555
	vector<Shift> posi_onscrn; //����Ļ�ϵ�ƫ��
	Texture rgloss[6];
	Sprite srgloss;
};

class MainCharacter
{
private:
	float x;
	float y;
	Image MC_image[2];
	int direction; //2��1��
				   //	int frame;

	Skill single_attack;
	Skill serial_attack;
	Skill run;

	bool bInSingleAttack;
	bool bInRun;
	bool bInSerialAttack;
	//Skill jumpandhit;

	Blood mc_blood;

public:
	Sprite hero;
	Texture t_hero;

	Shift Position()
	{
		return Shift{ x, y };
	}

	MainCharacter();

	void InitSingleAttack();

	void InitRun();

	void SingleAttack(RenderWindow& win);

	void Run(RenderWindow& win);

	void Wait(RenderWindow& win);

	void set_bInSingleAttack() { bInSingleAttack = true; };
	void set_bInRun() { bInRun = true; }
	bool get_bInSingleAttack() const { return bInSingleAttack; }
	bool get_bInRun() const { return bInRun; }

	void set_direction(int d) { direction = d; }
	int get_direction()const { return direction; }

	//	void draw(RenderWindow* window) { window->draw(hero); }
};


#endif