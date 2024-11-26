#pragma once
#include "MyVector2.h"
#include "Charactor.h"
#include "PlayerParticles.h"
#include "PlayerBullet.h"
#include "PlayerLane.h"
#include "timer.h"

class Player : public Charactor
{
public:
	Player();
	~Player() = default;

	void onInput(char* keys, char* prekeys) override;
	void onUpdate() override;
	void onDraw(const Camera& camera) override;

	float t_;
	bool lineChange_;


	PlayerParticles* particl_ = nullptr;
	PlayerLane* lane_ = nullptr;

private:
	//射撃クールダウン管理
	bool isCanFire;
	Timer fireCoolTimer;
	float fireCoolTime;
	bool isFireDown = false;

};
