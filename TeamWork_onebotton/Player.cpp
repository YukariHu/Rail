#include "Player.h"

Player::Player()
{
	color = WHITE;
	size = { 15.0f, 15.0f };
	pos = { 600.0f, 600.0f };
	velocity = { 1.0f / 180.0f, 1.0f / 180.0f };
	t_ = 0.0f;
	lineChange_ = false;

	startLine = { 0.0f,500.0f };
	endLine = { 1280.0f ,500.0f };
	startLine2 = { 0.0f, 600.0f };
	endLine2 = { 1280.0f ,600.0f };

	lineShift = false;
}

void Player::onInput(char* keys, char* prekeys)
{
	
	if (prekeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		if (lineChange_) {
			lineChange_ = false;
		} else {
			lineChange_ = true;
		}
	}

	
	if (keys[DIK_LSHIFT] != 0) {
		velocity = { 1.0f / 100.0f, 1.0f / 100.0f };
	} else {
		velocity = { 1.0f / 180.0f, 1.0f / 180.0f };
	}

	
}

void Player::onUpdate()
{
	Charactor::onUpdate();
	pos.x += 1.0f;


	if (t_ < 1.0f) {
		t_ += velocity.x;

		if (lineChange_ == false) {
			pos.x = (1 - t_) * startLine.x + t_ * endLine.x;
			pos.y = (1 - t_) * startLine.y + t_ * endLine.y;
		} else {
			pos.x = (1 - t_) * startLine2.x + t_ * endLine2.x;
			pos.y = (1 - t_) * startLine2.y + t_ * endLine2.y;
		}
	} else {
		t_ = 0.0f;
	}


}

void Player::onDraw()
{
	Novice::DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, color, kFillModeSolid);

	Novice::DrawLine(static_cast<int>(startLine.x), static_cast<int>(startLine.y), static_cast<int>(endLine.x), static_cast<int>(endLine.y), WHITE);
	Novice::DrawLine(static_cast<int>(startLine2.x), static_cast<int>(startLine2.y), static_cast<int>(endLine2.x), static_cast<int>(endLine2.y), WHITE);

}