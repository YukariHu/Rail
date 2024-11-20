#pragma once
#include "Bullet.h"
#include "timer.h"

class Beam : public Bullet
{
public:
	//水平または垂直にしか発射できない
	//fireposは発射位置、dirは発射方向 x:水平、y:垂直
	Beam(Vector2 firePos, Vector2 dir, float lifeTime) ;
	~Beam() = default;


	void onUpdate() override;
    void onDraw() override;

private:
	Timer aimTimer;
	Timer lifeTimer;
	Timer overTimer;

	float lifeTime;
	
	bool isAiming;
	bool isOver;
	bool isEnable;//衝突判定を有効にするかどうか
	int color;

	//int renderType;
	Vector2 maxSize;

};