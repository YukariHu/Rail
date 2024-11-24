#pragma once
#include <MyVector2.h>
#include "timer.h"
class Bar
{
public:
	Bar(Vector2 _pos ,Vector2 _size,int _maxValue);
	~Bar() = default;


	void Draw();

private:
	int maxValue;
	int value;
	Vector2 pos;
	Vector2 size;
	
	int barColor;
	int backColor;
	int borderColor;

};
