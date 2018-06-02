#ifndef  __Blood_H__
#define __Blood_H__

#include <SFML/Graphics.hpp>
#include<vector>
using namespace sf;
using namespace std;

#define FULL_BLOOD_VALUE 100
#define FULL_BLOOD_WIDTH 60
#define BLOOD_HEIGHT 6

class Blood {
private:
	IntRect back_rec;  //背景黑条的位置和大小
	IntRect blood_rec;  //血条的位置和大小
	RectangleShape back_shape;
	RectangleShape blood_shape;

	int blood_value;  //blood width = blood_value / FULL_BLOOD_VALUE *FULL_BLOOD_WIDTH
	int blood_width;

public:

	Blood() :back_rec(0, 0, 0, 0), blood_rec(0, 0, 0, 0), back_shape(Vector2f(0, 0)), blood_shape(Vector2f(0, 0)), blood_value(0), blood_width(FULL_BLOOD_WIDTH) {};

	void SetPosition(Sprite& s, int direction, float sposi_x, float sposi_y);

	void DrawBlood(RenderWindow& win);

};

#endif // ! __Blood_H__

