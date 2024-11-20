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

	if (prekeys[DIK_1] == 0 && keys[DIK_1] != 0) {
		lineShift = true;
	}

}

void Player::onUpdate()
{
	Charactor::onUpdate();


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

		if (lineShift) {
			lineShift = false;

			
			if (startLine.x == 0.0f) {
				startLine.x = startPointX[1];
				startLine2.x = startPointX[2];
				endLine.x = endPointX[1];
				endLine2.x = endPointX[2];

				startLine.y = startPointY[2];
				startLine2.y = startPointY[2];
				endLine.y = endPointY[2];
				endLine2.y = endPointY[2];

				
			} else {
				startLine.x = startPointX[0];
				startLine2.x = startPointX[0];
				endLine.x = endPointX[0];
				endLine2.x = endPointX[0];

				startLine.y = startPointY[0];
				startLine2.y = startPointY[1];
				endLine.y = endPointY[0];
				endLine2.y = endPointY[1];
			}
		}
	}


}

void Player::onDraw()
{
	Novice::DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, color, kFillModeSolid);

	Novice::DrawLine(static_cast<int>(startLine.x), static_cast<int>(startLine.y), static_cast<int>(endLine.x), static_cast<int>(endLine.y), WHITE);
	Novice::DrawLine(static_cast<int>(startLine2.x), static_cast<int>(startLine2.y), static_cast<int>(endLine2.x), static_cast<int>(endLine2.y), WHITE);

}