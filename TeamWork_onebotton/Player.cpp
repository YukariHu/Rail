#include "Player.h"

Player::Player()
{
	color = WHITE;
	size = { 15.0f, 15.0f };
	pos = { 600.0f, 600.0f };
	velocity = { 1.0f / 180.0f, 1.0f / 180.0f };
	t_ = 0.0f;
	lineChange_ = false;

	startLineX = 0.0f;
	startLineY = 500.0f;
	endLineX = 1280.0f;
	endLineY = 500.0f;

	startLineX2 = 0.0f;
	startLineY2 = 600.0f;
	endLineX2 = 1280.0f;
	endLineY2 = 600.0f;

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
			pos.x = (1 - t_) * startLineX + t_ * endLineX;
			pos.y = (1 - t_) * startLineY + t_ * endLineY;
		} else {
			pos.x = (1 - t_) * startLineX2 + t_ * endLineX2;
			pos.y = (1 - t_) * startLineY2 + t_ * endLineY2;
		}
	} else {
		t_ = 0.0f;
	}


}

void Player::onDraw()
{
	Novice::DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, color, kFillModeSolid);

	Novice::DrawLine(static_cast<int>(startLineX), static_cast<int>(startLineY), static_cast<int>(endLineX), static_cast<int>(endLineY), WHITE);
	Novice::DrawLine(static_cast<int>(startLineX2), static_cast<int>(startLineY2), static_cast<int>(endLineX2), static_cast<int>(endLineY2), WHITE);

}