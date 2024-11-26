#include "DeviationShotBullet.h"
#include "Novice.h"

extern int windowHeight;
extern int windowWidth;
DeviationShotBullet::DeviationShotBullet(Vector2 firePos, Vector2 _dir, int _targetID)
{
	pos = firePos;
	dir = _dir;
	size = { 10.0f,10.0f };
	speed = 15.0f;
	velocity.x = speed * cosf(dir.x);
	velocity.y = speed * sinf(dir.y);
	damage = 1;
	isCanRemove = false;

	this->targetID = _targetID;
}
void DeviationShotBullet::onUpdate()
{
	
	Bullet::onUpdate();

}
void DeviationShotBullet::onDraw(const Camera& camera)
{
	const Vector2& cameraPos = camera.GetPos();
	Novice::DrawTriangle(static_cast<int>(pos.x - cameraPos.x), static_cast<int>(pos.y + size.y - cameraPos.y), static_cast<int>(pos.x + size.x - cameraPos.x), static_cast<int>(pos.y - size.y - cameraPos.y), static_cast<int>(pos.x - size.x - cameraPos.x), static_cast<int>(pos.y - size.y - cameraPos.y), WHITE, kFillModeSolid);
}