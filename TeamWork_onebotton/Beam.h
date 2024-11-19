#pragma once
#include "Bullet.h"
class Beam : public Bullet
{
public:
	Beam(Vector2 firePos, Vector2 dir);
	~Beam();
};