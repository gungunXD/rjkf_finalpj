#include"Blood.h"

void Blood::SetPosition(Sprite& s, int direction, float sposi_x, float sposi_y)
{
	if (direction != 2 && direction != 1)
		return;
	if (direction == 1)
	{
		back_rec.left = sposi_x - FULL_BLOOD_WIDTH - 3;
		back_rec.top = sposi_y - 3 * BLOOD_HEIGHT - 2;
		back_rec.width = FULL_BLOOD_WIDTH + 6;
		back_rec.height = BLOOD_HEIGHT + 4;

		blood_rec.left = sposi_x - FULL_BLOOD_WIDTH;
		blood_rec.top = sposi_y - 3 * BLOOD_HEIGHT;
		blood_rec.width = blood_width;
		blood_rec.height = BLOOD_HEIGHT;
	}
	else if (direction == 2)
	{
		back_rec.left = sposi_x + s.getTextureRect().width + 6 - 3;
		back_rec.top = sposi_y - 3 * BLOOD_HEIGHT - 2;
		back_rec.width = FULL_BLOOD_WIDTH + 6;
		back_rec.height = BLOOD_HEIGHT + 4;

		blood_rec.left = sposi_x + s.getTextureRect().width + 6;
		blood_rec.top = sposi_y - 3 * BLOOD_HEIGHT;
		blood_rec.width = blood_width;
		blood_rec.height = BLOOD_HEIGHT;
	}
}

void Blood::DrawBlood(RenderWindow& win)
{
	//ºÚÉ«±³¾°
	back_shape.setFillColor(Color::Black);
	back_shape.setSize(Vector2f(back_rec.width, back_rec.height));
	back_shape.setPosition(back_rec.left, back_rec.top);

	//ÑªÌõ
	blood_shape.setFillColor(Color::Green); //Color(20,246,100,255)
	blood_shape.setSize(Vector2f(blood_rec.width, blood_rec.height));
	blood_shape.setPosition(blood_rec.left, blood_rec.top);

	win.draw(back_shape);
	win.draw(blood_shape);
}