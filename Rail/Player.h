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

	const int GetDashCount() const { return dashCount; }

	float t_;
	bool lineChange_;


	PlayerParticles* particl_ = nullptr;
	PlayerLane* lane_ = nullptr;

	bool canShot;

private:
	Vector2 basicVelocity;


	//射撃クールダウン管理
	bool isCanFire;
	Timer fireCoolTimer;
	float fireCoolTime;
	bool isFireDown = false;

	//ダッシュ管理
	int maxDashCount = 4;
	int dashCount;
	Timer dashCoolTimer;
	float dashCoolTime = 1.0f;
	
	Timer dashTimer;
	float dashTime = 0.1f;
	bool isDash = false;
	bool isDashDown = false;
	Vector2 dashVelocity;

	bool isBackDash = false;
	bool isBackDashDown = false;


};
