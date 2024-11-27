#pragma once
#include "Bullet.h"
#include "timer.h"

class Beam : public Bullet
{
public:
	//水平または垂直にしか発射できない
	//fireposは発射位置、dirは発射方向 x:水平、y:垂直 lifeTimeはビームの持続時間 targetIDはターゲットのID :0:player 1:boss
	//Beam(Vector2 firePos, Vector2 dir, float lifeTime);
	Beam(Vector2 firePos, Vector2 dir, float lifeTime, int targetID);
	~Beam() = default;


	void onUpdate() override;
	bool checkCollision(Vector2 targertPos, Vector2 targertSize) override;
    void onDraw(const Camera& camera) override;

private:
	Timer aimTimer;
	Timer lifeTimer;
	Timer overTimer;

	float lifeTime;
	
	bool isAiming;
	bool isOver;
	int color;

	//int renderType;
	Vector2 maxSize;

};