#include "Bullet.h"
#include "Novice.h"

extern int windowHeight;
extern int windowWidth;
Bullet::Bullet(Vector2 firePos, Vector2 _dir)
{
	pos = firePos;
	dir = _dir;
	size = { 10.0f,10.0f };
	speed = 10.0f;

	velocity = { speed * dir.x,speed * dir.y };
	
	damage = 4;
	isCanRemove = false;
	targetID = 0;
}
Bullet::Bullet(Vector2 firePos, Vector2 dir, int _targertID)
{
	pos = firePos;
	dir = dir;
	size = { 10.0f,10.0f };
	speed = 10.0f;

	velocity = { speed * dir.x,speed * dir.y };
	damage = 1;
	isCanRemove = false;
	targetID = _targertID;
}
void Bullet::onUpdate()
{
	pos.x += velocity.x;
	pos.y += velocity.y;

	if (pos.x > windowWidth || pos.x < 0.0f || pos.y > windowHeight || pos.y < 0.0f)
	{
		isCanRemove = true;
	}
}
bool Bullet::checkCollision(Vector2 targertPos, Vector2 targertSize)
{
	if (isEnableCollision)
	{
		if ((pos - targertPos).length() <= targertSize.x + size.x)
		{
			isCanRemove = true;
			return true;
		}
	}
	return false;
}
void Bullet::onDraw(const Camera& camera)
{
	(void)camera;
	const Vector2& cameraPos = camera.GetPos();
	Novice::DrawEllipse(static_cast<int>(pos.x - cameraPos.x), static_cast<int>(pos.y - cameraPos.y),static_cast<int>(size.x), static_cast<int>(size.y),0.0f,WHITE,kFillModeSolid);
}

int Bullet::getDamage()
{
	return damage;
}
