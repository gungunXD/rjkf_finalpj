#include <SFML/Graphics.hpp>
#include <random>
#include <assert.h>
#include <vector>
#include "MainCharacter.h"
#include "Monster.h"

/*************************************************************************************************
*
*										盒子怪物类的成员函数
*
**************************************************************************************************/


void Mons_Box::InitPrepare()
{
	Prepared = false;
	prepare.frame = 1;
	prepare.current_frame = 0;
	prepare.posi_image.push_back(IntRect{ 76,0,31,34 });
	prepare.image_num.push_back(1);
	prepare.posi_onscrn.push_back(Shift{ 0,0 });
}

void Mons_Box::InitAppear()
{
	Appeared = false;
	appear.frame = 6;
	appear.current_frame = 0;
	IntRect r[6];
	r[0] = IntRect{ 106,0,32,33 };//2
	r[1] = IntRect{ 217,0,35,55 };//2
	r[2] = IntRect{ 230,90,43,64 };//2
	r[3] = IntRect{ 165,51,65,101 };//2
	r[4] = IntRect{ 75,32,91,116 };//2
	r[5] = IntRect{ 0,0,76,148 };//2

	for (int i = 0; i < appear.frame; ++i)
		appear.posi_image.push_back(r[i]);

	appear.image_num = { 1,1,1,1,1,1 };

	for (int i = 0; i < appear.frame; ++i)
		appear.posi_onscrn.push_back(Shift{ 0, 0 });
}

void Mons_Box::InitWait()
{
	bInWait = false;
	wait.frame = 8;
	wait.current_frame = 0;
	IntRect r[8];
	r[0] = IntRect{ 69,0,75,164 };//1
	r[1] = IntRect{ 294,0,71,148 };//1
	r[2] = IntRect{ 238,149,79,146 };//1
	r[3] = IntRect{ 294,0,71,148 };//1
	r[4] = IntRect{ 90,163,68,159 };//1
	r[5] = IntRect{ 145,0,76,154 };//1
	r[6] = IntRect{ 1,172,88,166 };//1
	r[7] = IntRect{ 0,337,97,161 };//1

	for (int i = 0; i < wait.frame; ++i)
		wait.posi_image.push_back(r[i]);

	wait.image_num = { 0,0,0,0,0,0,0,0 };

	for (int i = 0; i < wait.frame; ++i)
		wait.posi_onscrn.push_back(Shift{ 0, 0 });
}

void Mons_Box::InitRun()
{
	bInRun = false;
	run.frame = 12;
	run.current_frame = 0;
	IntRect r[12];
	r[0] = IntRect{ 0,0,76,148 };//2
	r[1] = IntRect{ 75,32,91,116 };//2
	r[2] = IntRect{ 165,51,65,101 };//2
	r[3] = IntRect{ 165,51,65,101 };//2
	r[4] = IntRect{ 165,51,65,101 };//2
	r[5] = IntRect{ 75,32,91,116 };//2
	r[6] = IntRect{ 106,0,32,33 };//2
	r[7] = IntRect{ 217,0,35,55 };//2
	r[8] = IntRect{ 230,90,43,64 };//2
	r[9] = IntRect{ 165,51,65,101 };//2
	r[10] = IntRect{ 75,32,91,116 };//2
	r[11] = IntRect{ 0,0,76,148 };//2

	for (int i = 0; i < run.frame; ++i)
		run.posi_image.push_back(r[i]);

	run.image_num = { 1,1,1,1,1,1,1,1,1,1,1,1 };

	for (int i = 0; i < run.frame; ++i)
		run.posi_onscrn.push_back(Shift{ MONSTER_SPEED, 0 });
}

void Mons_Box::InitSingleAttack()
{
	bInSingleAttack = false;
	single_attack.frame = 6;
	single_attack.current_frame = 0;
	IntRect r[6];

	r[0] = IntRect{ 106,0,32,33 };//2
	r[1] = IntRect{ 217,0,35,55 };//2
	r[2] = IntRect{ 230,90,43,64 };//2
	r[3] = IntRect{ 165,51,65,101 };//2
	r[4] = IntRect{ 75,32,91,161 };//2
	r[5] = IntRect{ 0,0,76,148 };//2

	for (int i = 0; i < single_attack.frame; ++i)
		single_attack.posi_image.push_back(r[i]);

	single_attack.image_num = { 1,1,1,1,1,1 };

	for (int i = 0; i < single_attack.frame; ++i)
	{
		single_attack.posi_onscrn.push_back(Shift{ 0,0 });
	}
}

void Mons_Box::Prepare()
{
	if (!Prepared)
	{
		assert(t_monster.loadFromImage(Monster_image[prepare.image_num[prepare.current_frame]], prepare.posi_image[prepare.current_frame]));  //load texture
		monster.setTexture(t_monster);
		x = x + prepare.posi_onscrn[prepare.current_frame].x;
		y = y + prepare.posi_onscrn[prepare.current_frame].y;
		monster.setPosition(x, y + 170 - prepare.posi_image[prepare.current_frame].height);  //set monster position

		Prepared = true;
	}
}

void Mons_Box::Appear()
{
	if (!Appeared)
	{

		if (appear.current_frame < appear.frame)
		{
			assert(t_monster.loadFromImage(Monster_image[appear.image_num[appear.current_frame]], appear.posi_image[appear.current_frame]));  //load texture
			monster.setTexture(t_monster);

			x = x + appear.posi_onscrn[appear.current_frame].x;
			y = y + appear.posi_onscrn[appear.current_frame].y;
			monster.setPosition(x, y + 170 - appear.posi_image[appear.current_frame].height);  //set monster position
			appear.current_frame++;
		}
		else
		{
			appear.current_frame = 0;
			Appeared = true;
		}
	}
}

void Mons_Box::Wait()
{
	if (wait.current_frame < wait.frame)
	{
		assert(t_monster.loadFromImage(Monster_image[wait.image_num[wait.current_frame]], wait.posi_image[wait.current_frame]));  //load texture
		monster.setTexture(t_monster);

		x = x + wait.posi_onscrn[wait.current_frame].x;
		y = y + wait.posi_onscrn[wait.current_frame].y;
		monster.setPosition(x, y + 170 - wait.posi_image[wait.current_frame].height);  //set monster position
		wait.current_frame++;
	}
	else
	{
		wait.current_frame = 0;
		bInWait = false;
	}
}

void Mons_Box::Run(float hero_x)
{
	if (run.current_frame < run.frame)
	{
		assert(t_monster.loadFromImage(Monster_image[run.image_num[run.current_frame]], run.posi_image[run.current_frame]));  //load texture
		monster.setTexture(t_monster);

		if (hero_x - x > 10)
			x = x + run.posi_onscrn[run.current_frame].x;
		else if (hero_x - x < -10)
			x = x - run.posi_onscrn[run.current_frame].x;
		else
			x = x + abs(hero_x - x) / 5;

		if (x > WIN_WIDTH - 100)
			x = WIN_WIDTH - 100;

		y = y + run.posi_onscrn[run.current_frame].y;

		if (run.current_frame >= 6)
			monster.setPosition(x, y);  //set monster position
		else
			monster.setPosition(x, y + 170 - run.posi_image[run.current_frame].height);

		run.current_frame++;
	}
	else
	{
		bInRun = false;
		run.current_frame = 0;
	}
}

void Mons_Box::SingleAttack()
{

	if (single_attack.current_frame < single_attack.frame)
	{

		assert(t_monster.loadFromImage(Monster_image[single_attack.image_num[single_attack.current_frame]], single_attack.posi_image[single_attack.current_frame]));  //load texture
		monster.setTexture(t_monster);
		//	monster.setTextureRect(single_attack.posi_image[single_attack.current_frame]);

		x = x + single_attack.posi_onscrn[single_attack.current_frame].x;
		y = y + single_attack.posi_onscrn[single_attack.current_frame].y;

		/*	if (single_attack.image_num[single_attack.current_frame] == 1)
		{
		//monster.setOrigin(single_attack.posi_image[single_attack.current_frame].width / 2, single_attack.posi_image[single_attack.current_frame].height / 2);
		//2*float(r[i].width),float(r[i].height)/2
		monster.setPosition(x+2.* single_attack.posi_image[single_attack.current_frame].width, y+ single_attack.posi_image[single_attack.current_frame].height / 2.);  //set monster position
		monster.setRotation(90);
		}
		else
		{
		monster.setRotation(0);
		monster.setPosition(x, y);  //set monster position
		}*/

		monster.setPosition(x, y);  //set monster position

		single_attack.current_frame++;
	}
	else
	{
		//bInSingleAttack = false;
		single_attack.current_frame = 0;
	}
}

Attack* Mons_Box::Range_attack(float hero_x)
{
	static Attack *at = new Attack(x, y / 2, x < hero_x ? true : false, 10);

	at->Move();

	if (at->getOver())
		delete(at);

	return at;
}

/*************************************************************************************************
*
*										石锤怪物类的成员函数
*
**************************************************************************************************/

void Mons_Hummer::change_direction(float hero_x)
{
	//更改方向
	if (rand() % 10 < 6)	// 60% 概率走向人物
		direction = hero_x <= x ? true : false;
	else					// 40% 概率反向行走
		direction = hero_x <= x ? false : true;
}

void Mons_Hummer::InitPrepare()
{
	direction = rand() % 2;													//初始化方向随机

	Prepared = false;
	prepare.frame = 1;
	prepare.current_frame = 0;
	prepare.posi_image.push_back(IntRect{ 430,450,70,50 });					//透明图片
	prepare.image_num.push_back(0);
	prepare.posi_onscrn.push_back(Shift{ 0,0 });
}

void Mons_Hummer::InitAppear()
{
	Appeared = false;
	appear.frame = 1;
	appear.current_frame = 0;
	IntRect r[2];

	r[0] = IntRect{ 406,154,98,77 };//1										//向右
	r[1] = IntRect{ 8,154,98,77 };	//2										//向左

	appear.image_num.push_back(direction);
	appear.posi_onscrn.push_back(Shift{ 0, 0 });

	for (int i = 0; i < appear.frame * 2; ++i)
		appear.posi_image.push_back(r[i]);

	for (int i = 0; i < appear.frame * 2; ++i)
	{
		if (i < appear.frame)
			appear.image_num.push_back(0);
		else
			appear.image_num.push_back(1);
	}

	for (int i = 0; i < appear.frame * 2; ++i)
		appear.posi_onscrn.push_back(Shift{ 0, 0 });
}

void Mons_Hummer::InitWait()
{
	bInWait = false;
	wait.frame = 4;
	wait.current_frame = 0;
	IntRect r[8];

	r[0] = IntRect{ 406,154,98,77 };//1									//向右	
	r[1] = IntRect{ 406,154,98,77 };//1
	r[2] = IntRect{ 0,134,98,80 };//1
	r[3] = IntRect{ 0,134,98,80 };//1
	r[4] = IntRect{ 8,154,98,77 };//2									//向左
	r[5] = IntRect{ 8,154,98,77 };//2
	r[6] = IntRect{ 414,134,98,80 };//2
	r[7] = IntRect{ 414,134,98,80 };//2

	for (int i = 0; i < wait.frame * 2; ++i)
		wait.posi_image.push_back(r[i]);

	for (int i = 0; i < wait.frame * 2; ++i)
	{
		if (i < wait.frame)
			wait.image_num.push_back(0);
		else
			wait.image_num.push_back(1);
	}

	for (int i = 0; i < wait.frame * 2; ++i)
		wait.posi_onscrn.push_back(Shift{ 0, 0 });
}

void Mons_Hummer::InitRun()
{
	bInRun = false;
	run.frame = 9;
	run.current_frame = 0;
	IntRect r[18];

	r[0] = IntRect{ 406,154,98,77 };//1									//向右
	r[1] = IntRect{ 0,134,98,80 };	//1
	r[2] = IntRect{ 411,78,98,76 };	//1
	r[3] = IntRect{ 411,0,99,76 };	//1
	r[4] = IntRect{ 308,159,100,75 };//1
	r[5] = IntRect{ 311,0,98,78 };	//1
	r[6] = IntRect{ 210,0,100,78 };	//1
	r[7] = IntRect{ 309,79,100,78 };//1
	r[8] = IntRect{ 108,83,100,76 };//1

	r[9] = IntRect{ 8,154,98,77 };	//2									//向左
	r[10] = IntRect{ 414,134,98,80 };//2
	r[11] = IntRect{ 3,78,98,76 };	//2
	r[12] = IntRect{ 3,0,99,76 };	//2
	r[13] = IntRect{ 105,159,100,74 };//2
	r[14] = IntRect{ 103,0,98,78 };	//2
	r[15] = IntRect{ 202,0,100,78 };//2
	r[16] = IntRect{ 105,79,100,78 };//2
	r[17] = IntRect{ 304,83,100,76 };//2

	for (int i = 0; i < run.frame * 2; ++i)
		run.posi_image.push_back(r[i]);

	for (int i = 0; i < run.frame * 2; ++i)
	{
		if (i < run.frame)
			run.image_num.push_back(0);
		else
			run.image_num.push_back(1);
	}

	for (int i = 0; i < run.frame * 2; ++i)
	{
		if (i < run.frame)
			run.posi_onscrn.push_back(Shift{ MONSTER_SPEED, 0 });
		else
			run.posi_onscrn.push_back(Shift{ -MONSTER_SPEED, 0 });
	}
}

void Mons_Hummer::InitSingleAttack()
{
	bInSingleAttack = false;
	single_attack.frame = 15;
	single_attack.current_frame = 0;

	IntRect r[30];

	r[0] = IntRect{ 406,154,98,77 };//1									//向右
	r[1] = IntRect{ 97,160,96,68 };	//1
	r[2] = IntRect{ 0,0,110,84 };	//1
	r[3] = IntRect{ 211,80,100,88 };//1
	r[4] = IntRect{ 211,80,100,88 };//1
	r[5] = IntRect{ 211,80,100,88 };//1
	r[6] = IntRect{ 211,80,100,88 };//1
	r[7] = IntRect{ 211,80,100,88 };//1
	r[8] = IntRect{ 211,80,100,88 };//1
	r[9] = IntRect{ 0,213,98,68 };	//1
	r[10] = IntRect{ 193,217,94,70 };//1
	r[11] = IntRect{ 0,213,98,68 };	//1
	r[12] = IntRect{ 193,217,94,70 };//1
	r[13] = IntRect{ 0,213,98,68 };	//1
	r[14] = IntRect{ 193,217,94,70 };//1

	r[15] = IntRect{ 8,154,98,77 };	//2									//向左
	r[16] = IntRect{ 319,160,96,68 };//2
	r[17] = IntRect{ 402,0,110,84 };//2
	r[18] = IntRect{ 203,80,100,88 };//2
	r[19] = IntRect{ 203,80,100,88 };//2
	r[20] = IntRect{ 203,80,100,88 };//2
	r[21] = IntRect{ 203,80,100,88 };//2
	r[22] = IntRect{ 203,80,100,88 };//2
	r[23] = IntRect{ 203,80,100,88 };//2
	r[24] = IntRect{ 414,213,98,68 };//2
	r[25] = IntRect{ 225,217,94,70 };//2
	r[26] = IntRect{ 414,213,98,68 };//2
	r[27] = IntRect{ 225,217,94,70 };//2
	r[28] = IntRect{ 414,213,98,68 };//2
	r[29] = IntRect{ 225,217,94,70 };//2

	for (int i = 0; i < single_attack.frame * 2; ++i)
		single_attack.posi_image.push_back(r[i]);

	for (int i = 0; i < single_attack.frame * 2; ++i)
	{
		if (i < single_attack.frame)
			single_attack.image_num.push_back(0);
		else
			single_attack.image_num.push_back(1);
	}

	for (int i = 0; i < single_attack.frame * 2; ++i)
		single_attack.posi_onscrn.push_back(Shift{ 0, 0 });
}

void Mons_Hummer::Prepare()
{
	if (!Prepared)
	{
		assert(t_monster.loadFromImage(Monster_image[prepare.image_num[prepare.current_frame]], prepare.posi_image[prepare.current_frame]));  //load texture
		monster.setTexture(t_monster);
		x = x + prepare.posi_onscrn[prepare.current_frame].x;
		y = y + prepare.posi_onscrn[prepare.current_frame].y;
		monster.setPosition(x, y + 100 - prepare.posi_image[prepare.current_frame].height);  //set monster position

		Prepared = true;
	}
}

void Mons_Hummer::Appear()
{
	if (!Appeared)
	{
		if (appear.current_frame < appear.frame)
		{
			if (direction)	//向左
			{
				assert(t_monster.loadFromImage(Monster_image[appear.image_num[appear.current_frame + appear.frame]], appear.posi_image[appear.current_frame + appear.frame]));  //load texture
				monster.setTexture(t_monster);

				x = x + appear.posi_onscrn[appear.current_frame + appear.frame].x;
				y = y + appear.posi_onscrn[appear.current_frame + appear.frame].y;
				monster.setPosition(x, y + 100 - appear.posi_image[appear.current_frame + appear.frame].height);  //set monster position
			}
			else	//向右
			{
				assert(t_monster.loadFromImage(Monster_image[appear.image_num[appear.current_frame]], appear.posi_image[appear.current_frame]));  //load texture
				monster.setTexture(t_monster);

				x = x + appear.posi_onscrn[appear.current_frame].x;
				y = y + appear.posi_onscrn[appear.current_frame].y;
				monster.setPosition(x, y + 100 - appear.posi_image[appear.current_frame].height);  //set monster position
			}
			
			appear.current_frame++;
		}
		else
		{
			appear.current_frame = 0;
			Appeared = true;
		}
	}
}

void Mons_Hummer::Wait()
{
	if (wait.current_frame < wait.frame)
	{
		if (direction)	//向左
		{
			assert(t_monster.loadFromImage(Monster_image[wait.image_num[wait.current_frame + wait.frame]], wait.posi_image[wait.current_frame + wait.frame]));  //load texture
			monster.setTexture(t_monster);

			x = x + wait.posi_onscrn[wait.current_frame + wait.frame].x;
			y = y + wait.posi_onscrn[wait.current_frame + wait.frame].y;
			monster.setPosition(x, y + 100 - wait.posi_image[wait.current_frame + wait.frame].height);  //set monster position
		}
		else	//向右
		{
			assert(t_monster.loadFromImage(Monster_image[wait.image_num[wait.current_frame]], wait.posi_image[wait.current_frame]));  //load texture
			monster.setTexture(t_monster);

			x = x + wait.posi_onscrn[wait.current_frame].x;
			y = y + wait.posi_onscrn[wait.current_frame].y;
			monster.setPosition(x, y + 100 - wait.posi_image[wait.current_frame].height);  //set monster position
		}

		wait.current_frame++;
	}
	else
	{
		wait.current_frame = 0;
		bInWait = false;
	}
}

void Mons_Hummer::Run(float hero_x)
{

	if (abs(x - hero_x) < 50)
	{
		bInSingleAttack = true;
		bInRun = false;
		run.current_frame = 0;
	}
	else
	{


		if (run.current_frame < run.frame)
		{
			if (direction)	//向左
			{
				assert(t_monster.loadFromImage(Monster_image[run.image_num[run.current_frame + run.frame]], run.posi_image[run.current_frame + run.frame]));  //load texture
				monster.setTexture(t_monster);

				x = x + run.posi_onscrn[run.current_frame + run.frame].x;
				y = y + run.posi_onscrn[run.current_frame + run.frame].y;

				if (x < 0)
					x = 0;

				monster.setPosition(x, y + 100 - run.posi_image[run.current_frame + run.frame].height);  //set monster position
			}
			else	//向右
			{
				assert(t_monster.loadFromImage(Monster_image[run.image_num[run.current_frame]], run.posi_image[run.current_frame]));  //load texture
				monster.setTexture(t_monster);

				x = x + run.posi_onscrn[run.current_frame].x;
				y = y + run.posi_onscrn[run.current_frame].y;

				if (x > WIN_WIDTH - 100)
					x = WIN_WIDTH - 100;

				monster.setPosition(x, y + 100 - run.posi_image[run.current_frame].height);  //set monster position
			}
			run.current_frame++;
		}
		else
		{
			bInRun = false;
			run.current_frame = 0;
		}
	}
}

void Mons_Hummer::SingleAttack()
{
	if (single_attack.current_frame < single_attack.frame)
	{
		if (direction)	//向左
		{
			assert(t_monster.loadFromImage(Monster_image[single_attack.image_num[single_attack.current_frame + single_attack.frame]], 
											single_attack.posi_image[single_attack.current_frame + single_attack.frame]));  //load texture
			monster.setTexture(t_monster);

			x = x + single_attack.posi_onscrn[single_attack.current_frame + single_attack.frame].x;
			y = y + single_attack.posi_onscrn[single_attack.current_frame + single_attack.frame].y;

			monster.setPosition(x, y + 100 - single_attack.posi_image[single_attack.current_frame + single_attack.frame].height);  //set monster position
		}
		else	//向右
		{
			assert(t_monster.loadFromImage(Monster_image[single_attack.image_num[single_attack.current_frame]], single_attack.posi_image[single_attack.current_frame]));  //load texture
			monster.setTexture(t_monster);

			x = x + single_attack.posi_onscrn[single_attack.current_frame].x;
			y = y + single_attack.posi_onscrn[single_attack.current_frame].y;

			monster.setPosition(x, y + 100 - single_attack.posi_image[single_attack.current_frame].height);  //set monster position
		}

		single_attack.current_frame++;
	}
	else
	{
		bInSingleAttack = false;
		single_attack.current_frame = 0;
	}
}


/*************************************************************************************************
*
*										怪物攻击类的成员函数
*
**************************************************************************************************/

void Attack::Initial()
{
	assert(Attack_image.loadFromFile("attack01_1.png"));

	assert(t_attack.loadFromImage(Attack_image, IntRect{ 406,154,110,90 }));
	attack.setTexture(t_attack);
	attack.setOrigin(0, 0);

	attack.setPosition(x, y);

	frame = 4;
	current_frame = 0;
	IntRect r[8];

	r[0] = IntRect{ 0,161,95,47 };	//1									//向右
	r[1] = IntRect{ 0,116,95,47 };	//1
	r[2] = IntRect{ 0,61,96,54 };	//1
	r[3] = IntRect{ 3,4,96,54 };	//1

	r[4] = IntRect{ 0,161,95,47 };	//1									//向左
	r[5] = IntRect{ 0,116,95,47 };	//1
	r[6] = IntRect{ 0,61,96,54 };	//1
	r[7] = IntRect{ 3,4,96,54 };	//1

	for (int i = 0; i < frame * 2; ++i)
		posi_image.push_back(r[i]);

	for (int i = 0; i < frame * 2; ++i)
	{
		if (i < frame)
			image_num.push_back(0);
		else
			image_num.push_back(1);
	}
}

void Attack::Move()
{
	if (current_frame < frame)
	{
		if (direction)	//向左
		{
			assert(t_attack.loadFromImage(Attack_image, posi_image[current_frame + frame]));  //load texture
			attack.setTexture(t_attack);

			x -= speed;

			if (x < 0)	//x - posi_image[current_frame + frame].width < 0
				over = true;

			attack.setPosition(x, y + 100 - posi_image[current_frame + frame].height);  //set monster position
		}
		else	//向右
		{
			assert(t_attack.loadFromImage(Attack_image, posi_image[current_frame]));  //load texture
			attack.setTexture(t_attack);

			x += speed;

			if (x > WIN_WIDTH)  ////x + posi_image[current_frame + frame].width > WIN_WIDTH
				over = true;

			attack.setPosition(x, y + 100 - posi_image[current_frame + frame].height);  //set monster position
		}

		current_frame++;
	}
	else
	{
		current_frame = 0;
	}
}
