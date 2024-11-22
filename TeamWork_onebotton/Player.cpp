#include "Player.h"
extern int windowHeight;
extern int windowWidth;
Player::Player()
{
	color = WHITE;
	size = { 30.0f, 30.0f };
	pos = { 600.0f, 600.0f };
	velocity = { 2.0f, 0.0f };
}

void Player::onUpdate()
{
	Charactor::onUpdate();


	if (pos.x > windowWidth || pos.x < 0)
	{
		velocity.x *= -1;
	}
	pos.x += velocity.x;
}

void Player::onDraw(const Camera& camera)
{
	const Vector2& cameraPos = camera.GetPos();
	Novice::DrawEllipse(static_cast<int>(pos.x - cameraPos.x), static_cast<int>(pos.y - cameraPos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, WHITE, kFillModeSolid);
}