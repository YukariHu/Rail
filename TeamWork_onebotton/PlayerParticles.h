#pragma once
#include "MyVector2.h"

class PlayerParticles
{
public:
	struct Particl
	{
		Vector2 pos;
		int speed;
		int radius;
		bool isAlive;
	};
	Particl particl[100] = {};

	PlayerParticles();

	void Update(Vector2 pos, Vector2 startLine);
	void Draw();

	
};

