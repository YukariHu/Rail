#include "DeviationShotBullet.h"
#include "Novice.h"

extern int windowHeight;
extern int windowWidth;
DeviationShotBullet::DeviationShotBullet(Vector2 firePos, Vector2 _dir)
{
	pos = firePos;
	dir = _dir;
	size = { 10.0f,10.0f };
	velocity = 10.0f;
	damage = 1;
	isCanRemove = false;
}
void DeviationShotBullet::onUpdate()
{
	pos.x += velocity * cosf(dir.x);
	pos.y += velocity * sinf(dir.y);

	if (pos.x > windowWidth || pos.x < 0.0f || pos.y > windowHeight || pos.y < 0.0f)
	{
		isCanRemove = true;
	}
}
void DeviationShotBullet::onDraw(const Camera& camera)
{
	const Vector2& cameraPos = camera.GetPos();
	Novice::DrawTriangle(static_cast<int>(pos.x - cameraPos.x), static_cast<int>(pos.y + size.y - cameraPos.y), static_cast<int>(pos.x + size.x - cameraPos.x), static_cast<int>(pos.y - size.y - cameraPos.y), static_cast<int>(pos.x - size.x - cameraPos.x), static_cast<int>(pos.y - size.y - cameraPos.y), WHITE, kFillModeSolid);
}