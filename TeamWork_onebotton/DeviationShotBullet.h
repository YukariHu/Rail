#pragma once
#include "MyVector2.h"
#include <functional>
#include "Bullet.h"

class DeviationShotBullet : public Bullet
{
public:
	//targetIDはターゲットのID : 0 : player 1 : boss
	DeviationShotBullet(Vector2 firePos, Vector2 dir,int targetID);
	~DeviationShotBullet() = default;


	void onUpdate() override;
	void onDraw(const Camera& camera) override;


};

