#pragma once
#include "MyVector2.h"

class PlayerParticles
{
public:
	struct MoveParticl
	{
		Vector2 pos;
		int speed;
		int radius;
		bool isAlive;
	};
	MoveParticl moveParticl[100] = {};

	struct ChangeParticl
	{
		Vector2 pos;
		Vector2 direction;
		int speed;
		int radius;
		float radian;
		bool isAlive;
	};
	ChangeParticl changeParticl[5] = {};


	PlayerParticles();

	void CreateChangeParticl(Vector2 pos);
	void Update(Vector2 pos, Vector2 startLine);
	void Draw();

	
};

