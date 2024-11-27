#pragma once
#include "MyVector2.h"

//使わない
class PlayerBullet
{
public:
	struct Shot {
		Vector2 pos;
		float speed;
		float radius;
		float t;
		bool isShot;
		int targetPosX;
		int targetPosY;
		Vector2 shotPos;
		Vector2 direction;
	};
	Shot shot[20] = {};

	int shotTimer;
	int coolTime;


public:
	PlayerBullet();

	void Update(Vector2 player);

	void Draw();
};

