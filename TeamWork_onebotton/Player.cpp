#include "Player.h"
extern int windowHeight;
extern int windowWidth;
Player::Player()
{
	color = WHITE;
	size = { 15.0f, 15.0f };
	pos = { 600.0f, 600.0f };
	velocity = { 1.0f / 180.0f, 1.0f / 180.0f };
	t_ = 0.0f;
	lineChange_ = false;

	particl_ = new PlayerParticles();
	bullet_ = new PlayerBullet();
	lane_ = new PlayerLane();
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
		lane_->lineShift = true;
	}

}

void Player::onUpdate()
{
	Charactor::onUpdate();

	if (t_ < 1.0f) {
		t_ += velocity.x;

		if (lineChange_ == false) {
			pos.x = (1 - t_) * lane_->startLine.x + t_ * lane_->endLine.x;
			pos.y = (1 - t_) * lane_->startLine.y + t_ * lane_->endLine.y;
		} else {
			pos.x = (1 - t_) * lane_->startLine2.x + t_ * lane_->endLine2.x;
			pos.y = (1 - t_) * lane_->startLine2.y + t_ * lane_->endLine2.y;
		}
	} else {
		t_ = 0.0f;
		lane_->update();
	}

	particl_->Update(pos, lane_->startLine);

	bullet_->Update(pos);


}

void Player::onDraw(const Camera& camera)
{
	const Vector2& cameraPos = camera.GetPos();
	Novice::DrawEllipse(static_cast<int>(pos.x - cameraPos.x), static_cast<int>(pos.y - cameraPos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, WHITE, kFillModeSolid);
	
	lane_->Draw();
	particl_->Draw();
	bullet_->Draw();
}