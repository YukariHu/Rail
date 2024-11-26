#pragma once
#include "MyVector2.h"
//火焰粒子
class FireParticle
{
public:
	FireParticle(Vector2 _pos, Vector2 _size, int _lifetime);
	~FireParticle() = default;

	void Update();
	void Draw();


	int GetColor(unsigned int red, unsigned int  green, unsigned int blue, int  alpha);
	bool isOver = false;

private:
	Vector2 pos;
	Vector2 size;
	Vector2 velocity;


	int lifeTime;
	int passedTime = 0;


	int color;
	int alpha;




};
