#pragma once
#include "Charactor.h"

class Player : public Charactor
{
public:
	Player();
	~Player() = default;


	void onUpdate() override;
	void onDraw() override;
	Vector2 GetVelocity() const;
private:

};
