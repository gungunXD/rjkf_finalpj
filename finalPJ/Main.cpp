#include <SFML/Graphics.hpp>
#include"Monster.h"
#include"MainCharacter.h"
using namespace sf;
using namespace std;

#define WIN_WIDTH 796
#define WIN_HEIGHT 356



int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "GameDemo!");
	window.setFramerateLimit(30); 

	Texture t_bg;
	t_bg.loadFromFile("bg.png");
	Sprite sbackground(t_bg);

	MainCharacter MC;
	Mons_Box M1;

//	MC.InitMC();

	sf::Clock clock;
	sf::Time timer1, timer2;
	sf::Time _3s = sf::seconds(3.0f);
	sf::Time start = clock.restart();

	while (window.isOpen())
	{
		window.draw(sbackground);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Num0))
			MC.set_bInSingleAttack();

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			MC.set_direction(1);
			MC.set_bInRun();
		}
		else if(Keyboard::isKeyPressed(Keyboard::A))
		{
			MC.set_direction(2);
			MC.set_bInRun();
		}

		if (MC.get_bInSingleAttack())
			MC.SingleAttack(window);

		else if (MC.get_bInRun())
			MC.Run(window);

		else
			MC.Wait(window);

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

		window.draw(MC.hero);
		window.draw(M1.monster);
		window.display();
	}


	return 0;
}