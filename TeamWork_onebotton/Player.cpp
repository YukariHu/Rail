#include "Player.h"

Player::Player()
{
	color = WHITE;
	size = { 30.0f, 30.0f };
	pos = { 600.0f, 600.0f };
	velocity = { 0.0f, 0.0f };
}

void Player::onUpdate()
{
	Charactor::onUpdate();
}

void Player::onDraw()
{
	Novice::DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, color, kFillModeSolid);
}

