#include "FireFlower.h"

FireFlower::FireFlower() :
	pos_({ 0, 0 }), direction_({ -1.0f, 0.3f }), rad_(4.0f), velocity_(7.0f), oscillation_(0.0f), alive_(true)
{
}

FireFlower::~FireFlower()
{
}

void FireFlower::Init(const Vector2& direction)
{
	pos_ = {};
}

void FireFlower::Update()
{
}

void FireFlower::Draw()
{
}

bool FireFlower::IsAlive() const
{
	return false;
}
