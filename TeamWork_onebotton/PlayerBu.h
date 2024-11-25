#pragma once
#include "Bullet.h"
class PlayerBu : public Bullet
{
public:
	PlayerBu(Vector2 firePos,Vector2 _targetPos);
	~PlayerBu() = default;


	void onUpdate() override;
	//void onDraw(const Camera& camera) override;
private:
	float t;
	Vector2 targetPos;
	Vector2 firePos;
};
