#pragma once
#include "Bullet.h"
#include "timer.h"
class Beam : public Bullet
{
public:
	Beam(Vector2 firePos, Vector2 dir) ;
	~Beam() = default;


	void onUpdate() override;
    void onDraw() override;

private:
	is
};