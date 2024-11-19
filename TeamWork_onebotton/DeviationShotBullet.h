#pragma once
#include "MyVector2.h"
#include <functional>

class DeviationShotBullet
{
public:
	DeviationShotBullet() = default;
	DeviationShotBullet(Vector2 firePos, Vector2 dir);
	~DeviationShotBullet() = default;

	virtual void onUpdate();
	virtual void onDraw();
protected:

	Vector2 pos;
	Vector2 size;

	Vector2 dir;
	float velocity;

	int damage;

	std::function<void()> callback;
public:
	bool isCanRemove = false;


};

