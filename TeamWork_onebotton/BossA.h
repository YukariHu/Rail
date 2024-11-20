#pragma once
#include "Charactor.h"

class BossA : public Charactor
{
public:
	BossA();
	~BossA() = default;

	void onUpdate() override;
	void onDraw() override;

	void CircleFire(int bulletNum);
	void StraightFire();
	void RandomFire();

	void BeamFire();
	void MoveTo(Vector2 targetPos,float time);

	void DeviationFire();
private:
	
	int alpha_;
	
};
