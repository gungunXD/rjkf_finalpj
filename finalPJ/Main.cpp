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

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "GameDemo!");
	window.setFramerateLimit(100 );

	Texture t_bg;
	t_bg.loadFromFile("bg.png");
	Sprite sbackground(t_bg);

	MainCharacter MC;

//	MC.InitMC();

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

		window.draw(sbackground);
		window.draw(MC.hero);
		window.display();
	}


	return 0;
}