#include "Player.h"

Player::Player()
{
	color = WHITE;
	size = { 30.0f, 30.0f };
	pos = { 600.0f, 600.0f };
	velocity = { 0.0f, 0.0f };
}

void Player::onInput(char* keys, char* prekeys)
{
}

void Player::onUpdate()
{
	Charactor::onUpdate();
	pos.x += 1.0f;
}

void Player::onDraw(const Camera& camera)
{
	const Vector2& cameraPos = camera.GetPos();
	Novice::DrawEllipse(static_cast<int>(pos.x - cameraPos.x), static_cast<int>(pos.y - cameraPos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, WHITE, kFillModeSolid);
}