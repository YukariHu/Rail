#pragma once
#include "MyVector2.h"
class Bullet
{
public:
	Bullet() = default;
	~Bullet() = default;

	void Update();

private:

	Vector2 pos;
	Vector2 size;
	Vector2 velocity;
	float speed;

};
