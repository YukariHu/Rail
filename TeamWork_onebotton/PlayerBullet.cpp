#include "Novice.h"
#include "PlayerBullet.h"

//使わない
PlayerBullet::PlayerBullet()
{
	for (int i = 0; i < 20; i++) {
		shot[i] = {
			{ -100.0f,-100.0f },
			1.0f / 30.0f,
			5.0f,
			0.0f,
			false,
			-100,-100,
			{ -100.0f,-100.0f }
		};
	}

	shotTimer = 0;
	coolTime = 5;
}

void PlayerBullet::Update(Vector2 player)
{
	if (shotTimer == 0) {
		if (Novice::IsPressMouse(0)) {
			for (int i = 0; i < 20; i++) {
				if (shot[i].isShot == false) {
					shot[i].pos.x = player.x;
					shot[i].pos.y = player.y;
					shot[i].shotPos.x = player.x;
					shot[i].shotPos.y = player.y;
					Novice::GetMousePosition(&shot[i].targetPosX, &shot[i].targetPosY);
					shot[i].isShot = true;
					shotTimer = coolTime;
					break;
				}
			}
		}
	} else {
		if (shotTimer > 0) {
			shotTimer--;
		}
	}


	for (int i = 0; i < 20; i++) {
		if (shot[i].isShot) {
			shot[i].t += shot[i].speed;

			shot[i].pos.x = (1 - shot[i].t) * shot[i].shotPos.x + shot[i].t * shot[i].targetPosX;
			shot[i].pos.y = (1 - shot[i].t) * shot[i].shotPos.y + shot[i].t * shot[i].targetPosY;

			if (shot[i].pos.x < 0 || shot[i].pos.y < 0 ||
				shot[i].pos.x > 1280 || shot[i].pos.y > 720) {
				shot[i].pos.x = -100;
				shot[i].pos.y = -100;
				shot[i].t = 0.0f;
				shot[i].isShot = false;
			}
		}
	}

}


void PlayerBullet::Draw()
{
	for (int i = 0; i < 20; i++) {
		if (shot[i].isShot) {
			Novice::DrawEllipse(static_cast<int>(shot[i].pos.x), static_cast<int>(shot[i].pos.y), 
				static_cast<int>(shot[i].radius), static_cast<int>(shot[i].radius), 0.0f, WHITE, kFillModeSolid);
		}
	}
}
