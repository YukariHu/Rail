#pragma once
#include "Charactor.h"
#include "timer.h"
#include <FireParticle.h>

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

	void BeamFire();//使っていない
	void MoveTo(Vector2 targetPos,float time);//使っていない

	void DeviationFire();
	
	bool GetisPhase1() { return isphase1; }


private:
	
	int alpha_;
	//Bossの階段
	//Boss当前前的阶段
	bool isphase1 = true;
	
	//eye
	Vector2 eyePos;
	Vector2 eyeDir;
	Vector2 eyeSize;
	Vector2 maxEyeSize;
	int eyeColor;
	float eyeAngle;

	Timer blinkTimer;//まばたきのタイマー
	bool isBlink;
	Timer blinkInterval;//まばたきの間隔
	

	//fire Particle
	std::vector<FireParticle> fireParticles;

	Timer fireRespawnTimer;
	float fireRespawnInterval = 0.06f;


	bool isStop = false;
	

	
};
