#include "PlayerBu.h"
extern int windowHeight;
extern int windowWidth;
PlayerBu::PlayerBu(Vector2 _firePos, Vector2 _targetPos)
{
	pos = _firePos;
	firePos = _firePos;
	dir = { 0.0f,0.0f };//使わない
	targetPos = _targetPos;
	targetID = 1;
	speed = 1.0f/30.0f;
	size = { 5.0f,5.0f };
	damage = 1;

	t = 0.0f;
}

void PlayerBu::onUpdate()
{
	t += speed;
	pos = firePos * (1.0f - t) + targetPos * t;

	if (pos.x > windowWidth || pos.x < 0.0f || pos.y > windowHeight || pos.y < 0.0f)
	{
		isCanRemove = true;
	}
}
