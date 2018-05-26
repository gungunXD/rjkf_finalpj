#include <SFML/Graphics.hpp>
#include<time.h>
#include<vector>
#include<assert.h>
using namespace sf;
using namespace std;

#define WIN_WIDTH 796
#define WIN_HEIGHT 356

#define ORIGIN_X 200
#define ORIGIN_Y 100

#define RUN_SPEED 20
#define MONSTER_SPEED 10


struct Shift {
	float x;
	float y;
};

struct Skill {
	int frame;  //帧数
	int current_frame;
	vector<IntRect> posi_image;  //每一帧在输入图片上的位置
	vector<int> image_num; //哪张图片横的还是竖的555
	vector<Shift> posi_onscrn; //在屏幕上的偏移
};


class MainCharacter
{
private:
	float x;
	float y;
	Image MC_image[2];
//	int frame;

	Skill single_attack;
	Skill serial_attack;
	Skill run;

	bool bInSingleAttack;
	bool bInRun;
	bool bInSerialAttack;
	//Skill jumpandhit;
public:
	Sprite hero;
	Texture t_hero;

	Shift Position()
	{
		return Shift{ x, y };
	}

	void InitSingleAttack()
	{
		single_attack.frame = 10;
		single_attack.current_frame = 0;
		IntRect r[10];
		r[0] = IntRect{ 472,859,104,165 };//1
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
		r[9] = IntRect{ 1472,236,117,119 }; //1
 
		for (int i = 0; i < 10; ++i)
			single_attack.posi_image.push_back(r[i]);

		single_attack.image_num = { 0,0,0,1,1,1,0,0,0,0 };

		for (int i = 0; i < 10; ++i)
		{
			if (i >= 5 && i < 9)
				single_attack.posi_onscrn.push_back(Shift{ 0,85 });
			else if(i==3||i==9)
				single_attack.posi_onscrn.push_back(Shift{ 0,30 });
			else
				single_attack.posi_onscrn.push_back(Shift{ 0,0 });
		}
	}

	void InitRun()
	{
		run.frame = 6;
		run.current_frame = 0;
		IntRect r[6];
		r[0] = IntRect{ 688,454,105,154 };//1
		r[1] = IntRect{ 882,459,103,149 };//1
		r[2] = IntRect{ 971,315,106,145 };//1
		r[3] = IntRect{ 772,302,98,153 };//1
		r[4] = IntRect{ 985,462,105,146 };//1
		r[5] = IntRect{ 678,251,98,151 };//1

		for (int i = 0; i < run.frame; ++i)
			run.posi_image.push_back(r[i]);

		run.image_num = { 0,0,0,0,0,0 };

		for (int i = 0; i < run.frame; ++i)
			run.posi_onscrn.push_back(Shift{ RUN_SPEED, 0 });
		//	run.posi_onscrn.push_back(Shift{ ORIGIN_X, ORIGIN_Y });
	}

	MainCharacter() {
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

	void SingleAttack( ) {

		if (single_attack.current_frame < single_attack.frame)
		{
			assert(t_hero.loadFromImage(MC_image[single_attack.image_num[single_attack.current_frame]], single_attack.posi_image[single_attack.current_frame]));  //load texture
			hero.setTexture(t_hero,true);

			int xx = x + single_attack.posi_onscrn[single_attack.current_frame].x;  //不改变原来的xy
			int yy = y + single_attack.posi_onscrn[single_attack.current_frame].y;

			hero.setPosition(xx, yy);  //set hero position
			single_attack.current_frame++;
		}
		else
		{
			bInSingleAttack = false;
			single_attack.current_frame = 0;
		}
	}

	void Run() {
		if (run.current_frame < run.frame)
		{
			assert(t_hero.loadFromImage(MC_image[single_attack.image_num[single_attack.current_frame]], run.posi_image[run.current_frame]));  //load texture
			hero.setTexture(t_hero,true);

			x = x + run.posi_onscrn[run.current_frame].x;
			if (x > WIN_WIDTH)
				x -= WIN_WIDTH;
			y = y + run.posi_onscrn[run.current_frame].y;
			hero.setPosition(x, y);  //set hero position
			run.current_frame++;
		}
		else
		{
			bInRun = false;
			run.current_frame = 0;
		}
	}

	void Wait() {   //暂时的，之后改
		assert(t_hero.loadFromImage(MC_image[0], single_attack.posi_image[0]));  //load texture
		hero.setTexture(t_hero,true);
		hero.setPosition(x, y);  //set hero position
		run.current_frame++;
	}

	void set_bInSingleAttack() { bInSingleAttack = true; };
	void set_bInRun() { bInRun = true; }
	bool get_bInSingleAttack()const { return bInSingleAttack; }
	bool get_bInRun() const { return bInRun; }

//	void draw(RenderWindow* window) { window->draw(hero); }
};


class Monster {

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

	Shift Position()
	{
		return Shift{ x, y };
	}

	void InitPrepare()
	{
		Prepared = false;
		prepare.frame = 1;
		prepare.current_frame = 0;
		prepare.posi_image.push_back(IntRect{ 76,0,31,34 });
		prepare.image_num.push_back(1);
		prepare.posi_onscrn.push_back(Shift{ 0,0 });
	}

	void InitAppear()
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

	void InitWait()
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

	void InitRun()
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

	void InitSingleAttack()
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

	Monster()
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

	void Prepare()
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

	void Appear()
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

	void Wait()
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

	void Run(float hero_x)
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

	void SingleAttack()
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

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "GameDemo!");
	window.setFramerateLimit(30 );

	Texture t_bg;
	t_bg.loadFromFile("bg.png");
	Sprite sbackground(t_bg);

	MainCharacter MC;
	Monster M1;

//	MC.InitMC();

	sf::Clock clock;
	sf::Time timer1, timer2;
	sf::Time _3s = sf::seconds(3.0f);
	sf::Time start = clock.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Num0))
			MC.set_bInSingleAttack();

		if (Keyboard::isKeyPressed(Keyboard::D))
			MC.set_bInRun();

		if (MC.get_bInSingleAttack())
			MC.SingleAttack();

		else if (MC.get_bInRun())
			MC.Run();

		else
			MC.Wait();

		// Monster
		if (abs(M1.Position().x - MC.Position().x) < 250)
		{
			M1.Prepare();
		}

		if (abs(M1.Position().x - MC.Position().x) < 150)
		{
			M1.Appear();
		}

		if (M1.get_Appeared())
		{
			if (M1.get_bInRun())
				M1.Run(MC.Position().x);
			else
			{
				timer1 = clock.getElapsedTime();
				if (timer1 >= _3s + start)
				{
					M1.set_bInRun();
					clock.restart();
				}

				M1.Wait();
			}
		}

		window.draw(sbackground);
		window.draw(MC.hero);
		window.draw(M1.monster);
		window.display();
	}


	return 0;
}