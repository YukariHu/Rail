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
	void onDraw(const Camera& camera) override;


};

