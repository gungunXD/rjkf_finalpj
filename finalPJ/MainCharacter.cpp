#include"MainCharacter.h"

MainCharacter::MainCharacter() :direction(1) {
	assert(MC_image[0].loadFromFile("torchhead.png"));
	assert(MC_image[1].loadFromFile("torchhead2.png"));

	InitSingleAttack();
	InitRun();

	//frame = 0;
	bInSingleAttack = false;
	bInSerialAttack = false;
	bInRun = false;

	assert(t_hero.loadFromImage(MC_image[0], IntRect{ 472,859,104,165 }));
	hero.setTexture(t_hero);
	hero.setOrigin(0, 0);

	x = ORIGIN_X;
	y = ORIGIN_Y;
	hero.setPosition(x, y);

	//window.draw(hero);
}

void MainCharacter::InitSingleAttack()
{
	single_attack.frame_image[0].loadFromFile("singleattack_frame_right.png");
	single_attack.frame_image[1].loadFromFile("singleattack_frame_left.png");

	single_attack.frame = 10;
	single_attack.current_frame = 0;
	IntRect r[10];
	/*	r[0] = IntRect{ 472,859,104,165 };//1
	r[1] = IntRect{ 661,859,104,165 };//1
	r[2] = IntRect{ 863,152,113,152 };//1
	r[3] = IntRect{ 923,828,101,129 };//2
	r[4] = IntRect{ 0,1151,145,133 };//2
	r[5] = IntRect{ 0,576,165,85 };//2
	//	r[3]=IntRect{ 830,0,126,99 };//2  rotate
	//	r[4]= IntRect{ 1152,872,130,149 };//2
	//	r[5]= IntRect{ 572,857,90,167 };//2
	r[6] = IntRect{ 571,0,154,82 };//1
	r[7] = IntRect{ 1867,847,106,83 };//1
	r[8] = IntRect{ 503,604,148,89 }; //1
	r[9] = IntRect{ 1472,236,117,119 }; //1*/

	r[0] = IntRect{ 0,0,150,165 };  //1540  1690-150
	r[1] = IntRect{ 150,0,150,165 };  //1390  1690-300
	r[2] = IntRect{ 300,0,150,165 };  //1240  1690-450
	r[3] = IntRect{ 450,0,150,165 };  //1090  1690-600
	r[4] = IntRect{ 600,0,150,165 };  //940  1690-750
	r[5] = IntRect{ 750,0,210,165 };  //730  1690-750-210
	r[6] = IntRect{ 960,0,210,165 };  //520  1690-750-210-210
	r[7] = IntRect{ 1170,0,150,165 };  //370  1690-750-210-210-150
	r[8] = IntRect{ 1320,0,200,165 };  //170  1690-750-210-210-150-200
	r[9] = IntRect{ 1520,0,170,165 };  //0

	for (int i = 0; i < 10; ++i)
		single_attack.posi_image.push_back(r[i]);

	//	single_attack.image_num = { 0,0,0,1,1,1,0,0,0,0 };

	for (int i = 0; i < 10; ++i)
	{
		single_attack.posi_onscrn.push_back(Shift{ float(r[i].width - 150) ,0 });
	}

	single_attack.rgloss[0].loadFromFile("rgloss6_ud.png");
	single_attack.rgloss[1].loadFromFile("rgloss1.png");
	single_attack.rgloss[2].loadFromFile("rgloss4_ud.png");
	single_attack.rgloss[3].loadFromFile("rgloss5_ud.png");
	single_attack.rgloss[4].loadFromFile("rgloss2.png");
	single_attack.rgloss[5].loadFromFile("rgloss3.png");
	//single_attack.rgloss[6].loadFromFile("rgloss5.png");
	//single_attack.rgloss[7].loadFromFile("rgloss6.png");
}

void MainCharacter::InitRun()
{
	run.frame_image[0].loadFromFile("run_frame_right.png");
	run.frame_image[1].loadFromFile("run_frame_left.png");
	run.frame = 6;
	run.current_frame = 0;
	IntRect r[6];
	/*r[0] = IntRect{ 688,454,105,154 };//1
	r[1] = IntRect{ 882,459,103,149 };//1
	r[2] = IntRect{ 971,315,106,145 };//1
	r[3] = IntRect{ 772,302,98,153 };//1
	r[4] = IntRect{ 985,462,105,146 };//1
	r[5] = IntRect{ 678,251,98,151 };//1*/

	r[0] = IntRect{ 0,0,115,155 };
	r[1] = IntRect{ 115,0,115,155 };
	r[2] = IntRect{ 230,0,115,155 };
	r[3] = IntRect{ 345,0,115,155 };
	r[4] = IntRect{ 450,0,115,155 };
	r[5] = IntRect{ 575,0,115,155 };


	for (int i = 0; i < run.frame; ++i)
		run.posi_image.push_back(r[i]);

	run.image_num = { 0,0,0,0,0,0 };

	for (int i = 0; i < run.frame; ++i)
		run.posi_onscrn.push_back(Shift{ RUN_SPEED, 0 });
	//	run.posi_onscrn.push_back(Shift{ ORIGIN_X, ORIGIN_Y });
}

void MainCharacter::SingleAttack(RenderWindow& win) {

	if (single_attack.current_frame < single_attack.frame)
	{
		/*			assert(t_hero.loadFromImage(MC_image[single_attack.image_num[single_attack.current_frame]], single_attack.posi_image[single_attack.current_frame]));  //load texture
		hero.setTexture(t_hero,true);

		int xx = x + single_attack.posi_onscrn[single_attack.current_frame].x;  //不改变原来的xy
		int yy = y + single_attack.posi_onscrn[single_attack.current_frame].y;

		hero.setPosition(xx, yy);  //set hero position

		if (single_attack.current_frame >= 3 && single_attack.current_frame <= 8)
		{
		single_attack.srgloss.setTexture(single_attack.rgloss[single_attack.current_frame - 3],true);
		single_attack.srgloss.setPosition(x + 150, y-30);
		win.draw(single_attack.srgloss);
		}

		mc_blood.SetPosition(hero, direction, x, y);
		mc_blood.DrawBlood(win);

		single_attack.current_frame++;*/

		int findex;
		int xx, yy;

		if (direction == 1)
		{
			findex = single_attack.current_frame;
			assert(t_hero.loadFromImage(single_attack.frame_image[0], single_attack.posi_image[findex]));  //load texture  //frame_image[0]是往右
			hero.setTexture(t_hero, true);
			xx = x;
			yy = y;

			if (single_attack.current_frame >= 3 && single_attack.current_frame <= 8)
			{
				single_attack.srgloss.setTexture(single_attack.rgloss[single_attack.current_frame - 3], true);
				single_attack.srgloss.setPosition(x + 150, y - 30);
				win.draw(single_attack.srgloss);
			}
		}

		if (direction == 2)
		{
			findex = single_attack.current_frame;

			//反过来的框图位置不太一样，这一段调整一下
			IntRect r = single_attack.posi_image[findex];
			int bias = 0;
			for (int i = 0; i <= single_attack.current_frame; ++i)
			{
				bias += single_attack.posi_image[i].width;
			}
			r.left = 1690 - bias;

			assert(t_hero.loadFromImage(single_attack.frame_image[1], r));  //load texture  //frame_image[0]是往右
			hero.setTexture(t_hero, true);
			xx = x - single_attack.posi_onscrn[findex].x;  //保持右准线对齐，这样腿才是齐的
			yy = y + single_attack.posi_onscrn[findex].y;
		}

		hero.setPosition(xx, yy);  //set hero position
		single_attack.current_frame++;
		mc_blood.SetPosition(hero, direction, x, y);
		mc_blood.DrawBlood(win);
	}
	else
	{
		bInSingleAttack = false;
		single_attack.current_frame = 0;
	}
}

void MainCharacter::Run(RenderWindow& win) {
	if (run.current_frame < run.frame)
	{
		int findex;

		if (direction == 1)
		{
			findex = run.current_frame;
			assert(t_hero.loadFromImage(run.frame_image[0], run.posi_image[findex]));  //load texture  //frame_image[0]是往右
			hero.setTexture(t_hero, true);
			x = x + run.posi_onscrn[findex].x;
			y = y + run.posi_onscrn[findex].y;
			if (x > WIN_WIDTH) //超出地图
				x -= WIN_WIDTH;
		}

		if (direction == 2)
		{
			findex = run.frame - 1 - run.current_frame;
			assert(t_hero.loadFromImage(run.frame_image[1], run.posi_image[findex]));  //load texture  //frame_image[0]是往右
			hero.setTexture(t_hero, true);
			x = x - run.posi_onscrn[findex].x;
			y = y + run.posi_onscrn[findex].y;
			if (x < 0) //超出地图
				x += WIN_WIDTH;
		}
		//assert(t_hero.loadFromImage(MC_image[single_attack.image_num[single_attack.current_frame]], run.posi_image[run.current_frame]));  //load texture
		//	x = x + run.posi_onscrn[run.current_frame].x;
		//	y = y + run.posi_onscrn[run.current_frame].y;

		hero.setPosition(x, y);  //set hero position
		run.current_frame++;
		mc_blood.SetPosition(hero, direction, x, y);
		mc_blood.DrawBlood(win);
	}
	else
	{
		bInRun = false;
		run.current_frame = 0;
	}
}

void MainCharacter::Wait(RenderWindow& win) {
	if (direction == 1) //朝右
	{
		assert(t_hero.loadFromImage(single_attack.frame_image[0], single_attack.posi_image[0]));  //load texture
	}
	else if (direction == 2) //朝左
	{
		IntRect r = single_attack.posi_image[0];
		r.left = 1690 - 150;
		assert(t_hero.loadFromImage(single_attack.frame_image[1], r));  //load texture
	}

	hero.setTexture(t_hero, true);
	hero.setPosition(x, y);  //set hero position
	mc_blood.SetPosition(hero, direction, x, y);
	mc_blood.DrawBlood(win);
	run.current_frame++;
}
