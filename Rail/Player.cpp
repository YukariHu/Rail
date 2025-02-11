#include "Player.h"
#include "PlayerBu.h"
extern int windowHeight;
extern int windowWidth;
extern float deltaTime;
extern std::vector<Bullet*> bulletList;

extern int playerShotSound;
extern int dashSound;
extern int laneChangeSound;

Player::Player()
{
	color = WHITE;
	size = { 15.0f, 15.0f };
	pos = { 600.0f, 600.0f };
	basicVelocity = { 1.0f / 200.0f, 1.0f / 200.0f };

	velocity = basicVelocity;
	maxHp = 100;
	hp = maxHp;

	canShot = false;

	t_ = 0.0f;
	lineChange_ = false;


	particl_ = new PlayerParticles();
	lane_ = new PlayerLane();

	
	//射撃クールダウン管理
	fireCoolTime = 0.08f;
	isCanFire = false;
	fireCoolTimer.set_one_shot(true);
	fireCoolTimer.set_wait_time(fireCoolTime);
	fireCoolTimer.set_on_timeout([&]() {
		isCanFire = true;
		fireCoolTimer.restart();
	});

	//ダッシュ管理
	dashCount = maxDashCount;
	dashVelocity = { 1.0f / 80.0f, 1.0f / 80.0f };
	dashCoolTimer.set_one_shot(true);
	dashCoolTimer.set_wait_time(dashCoolTime);
	dashCoolTimer.set_on_timeout([&]() {
		dashCount++;
		dashCoolTimer.restart();
		});

	dashTimer.set_one_shot(true);
	dashTimer.set_wait_time(dashTime);
	dashTimer.set_on_timeout([&]() {
		velocity = { basicVelocity };
		isDash = false;
		isBackDash = false;
		isEnableCollision = true;
		dashTimer.restart();
		});

}

void Player::onInput(char* keys, char* prekeys)
{
	
	if (prekeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		if (lineChange_) {
			lineChange_ = false;
		} else {
			lineChange_ = true;
		}
		Novice::PlayAudio(laneChangeSound, false, 1.0f);
		particl_->CreateChangeParticl(pos);
	}


	if (keys[DIK_C] != 0 && prekeys[DIK_C] == 0 || keys[DIK_LSHIFT] != 0 && prekeys[DIK_LSHIFT] == 0)
	{
		isDashDown = true;
	}

	if (keys[DIK_X] != 0 && prekeys[DIK_X] == 0)
	{
		isBackDashDown = true;
	}

	//射撃
	if (Novice::IsPressMouse(0) && canShot)
	{
		isFireDown = true;
	}

}

void Player::onUpdate()
{
	
	if (isDead)
	{
		return;
	}

	if (isDashDown && !isDash)
	{
		if (dashCount > 0)
		{
			Novice::PlayAudio(dashSound, false, 1.0f);
			dashCount--;
			isDash = true;
			isEnableCollision = false;
		}
	}

	if (isBackDashDown && !isDash)
	{
		if (dashCount > 0)
		{
			Novice::PlayAudio(dashSound, false, 1.0f);
			dashCount--;
			isBackDash = true;
			isEnableCollision = false;
			velocity = { -basicVelocity.x, -basicVelocity.y };
		}
	}

	if (isDash)
	{
		velocity = dashVelocity;
		dashTimer.on_update(deltaTime);
	}

	if (isBackDash)
	{
		velocity = dashVelocity * -0.4f;
		dashTimer.on_update(deltaTime);
	}

	if (dashCount < maxDashCount)
	{
		dashCoolTimer.on_update(deltaTime);
	}

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
		
	}
	lane_->update();
	particl_->Update(pos, lane_->startLine);

	if (isFireDown)
	{
		if (isCanFire)
		{
			Novice::PlayAudio(playerShotSound, false, 0.3f);
			isCanFire = false;
			int mousePosX, mousePosY;
			Novice::GetMousePosition(&mousePosX, &mousePosY);
			Vector2 mousePos = { static_cast<float>(mousePosX), static_cast<float>(mousePosY) };

			PlayerBu* playerBullet = new PlayerBu(pos, mousePos);
			bulletList.push_back(playerBullet);
		}

	}

	if (!isCanFire)
	{
		fireCoolTimer.on_update(deltaTime);
	}

	isFireDown = false;
	isDashDown = false;
	isBackDashDown = false;
	Charactor::onUpdate();

}

void Player::onDraw(const Camera& camera)
{

	const Vector2& cameraPos = camera.GetPos();

	if (isEnableCollision)
	{
		Novice::DrawEllipse(static_cast<int>(pos.x - cameraPos.x), static_cast<int>(pos.y - cameraPos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, WHITE, kFillModeSolid);
	}
	
	
	lane_->Draw();
	particl_->Draw();
}