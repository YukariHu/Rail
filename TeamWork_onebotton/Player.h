#pragma once
#include "MyVector2.h"
#include "Charactor.h"
#include "PlayerParticles.h"
#include "PlayerBullet.h"
#include "PlayerLane.h"

class Player : public Charactor
{
public:
	Player();
	~Player() = default;

	void onInput(char* keys, char* prekeys) override;
	void onUpdate() override;
	void onDraw(const Camera& camera) override override;

	float t_;
	bool lineChange_;

	PlayerParticles* particl_;

	PlayerBullet* bullet_;

	PlayerLane* lane_;

private:

};
