#pragma once
#include "MyVector2.h"
#include <functional>
#include "Bullet.h"

class DeviationShotBullet : public Bullet
{
public:
	DeviationShotBullet(Vector2 firePos, Vector2 dir);
	~DeviationShotBullet() = default;


	void onUpdate() override;
	void onDraw() override;

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

