#include "Bullet.h"
#include "Novice.h"

extern int windowHeight;
extern int windowWidth;
Bullet::Bullet(Vector2 firePos, Vector2 _dir)
{
	pos = firePos;
	dir = _dir;
	size = { 10.0f,10.0f };
	velocity = 10.0f;
	damage = 1;
	isCanRemove = false;
}
void Bullet::onUpdate()
{
	pos.x += velocity * dir.x;
	pos.y += velocity * dir.y;

	if (pos.x > windowWidth || pos.x < 0.0f || pos.y > windowHeight || pos.y < 0.0f)
	{
		isCanRemove = true;
	}
}
void Bullet::onDraw()
{
	Novice::DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y),static_cast<int>(size.x), static_cast<int>(size.y),0.0f,WHITE,kFillModeSolid);
}