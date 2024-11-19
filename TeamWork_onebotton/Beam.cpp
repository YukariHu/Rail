#include "Beam.h"
#include "Novice.h"
#include "Easing.h"


extern float deltaTime;
Beam::Beam(Vector2 firePos, Vector2 _dir)
{
		this->pos = firePos;
		this->dir = _dir;

		currentWidth = 0.0f;
		size.x = 10.0f;//幅
		size.y = 1300.0f;//長さ
		damage = 1;

		color = WHITE;
		

		isAiming = true;
		aimTimer.set_one_shot(true);
		aimTimer.set_wait_time(1.0f);
		aimTimer.set_on_timeout([&]() {
			isAiming = false; 
			});
		
		lifeTimer.set_one_shot(true);
		lifeTimer.set_wait_time(1.0f);
		lifeTimer.set_on_timeout([&]() {
			isCanRemove = false;
			});
}

void Beam::onUpdate()
{
	//照準線表示
	if (isAiming) {
		aimTimer.on_update(deltaTime);

		float t = Easing::EaseInOut(aimTimer.get_progress());
		currentWidth = size.x * t;
	}
	else {
		lifeTimer.on_update(deltaTime);
	}
}

void Beam::onDraw()
{
	if (isAiming)
	{
		//Novice::DrawLine(static_cast<int>(pos.x),static_cast<int>(pos.y),);

		//横のビーム
		Novice::DrawBox(
			static_cast<int>(pos.x * dir.normalize().x),
			static_cast<int>(pos.y - currentWidth / 2 * dir.normalize().y),
			static_cast<int>(size.y),
			static_cast<int>(currentWidth),
			0.0f,
			color,
			kFillModeWireFrame
		);
	}
	else
	{
		Novice::DrawBox(
			static_cast<int>(pos.x * dir.normalize().x),
			static_cast<int>(pos.y - currentWidth / 2 * dir.normalize().y),
			static_cast<int>(size.y),
			static_cast<int>(currentWidth),
			0.0f,
			color,
			kFillModeSolid
		);
	}
}
