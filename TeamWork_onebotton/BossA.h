#pragma once
#include "Charactor.h"
#include "timer.h"

class BossA : public Charactor
{
public:
	BossA();
	~BossA() = default;

	void onUpdate() override;
	void onDraw(const Camera& camera) override;
	void onHurt(int damage) override;


	void CircleFire(int bulletNum);
	void StraightFire();
	void RandomFire();

	void EyeUpdate();

	void BeamFire();
	void MoveTo(Vector2 targetPos,float time);

	void DeviationFire();
	
	int GetCurrentStage();
private:
	
	//Bossの階段
	//Boss当前前的阶段
	int currentStage;
	int maxStage = 2;
	
	//eye
	Vector2 eyePos;
	Vector2 eyeDir;
	Vector2 eyeSize;
	Vector2 maxEyeSize;
	int eyeColor;
	float eyeAngle;
	Timer blinkTimer;//まばたきのタイマー
	Timer blinkInterval;//まばたきの間隔
	bool isBlink;

	


	
};
