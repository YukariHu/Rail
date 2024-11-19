#include "Beam.h"
extern float deltaTime;
Beam::Beam(Vector2 firePos, Vector2 _dir)
{
		this->pos = firePos;
		this->dir = _dir;

		size.x = 10.0f;//幅
		size.y = 1300.0f;//長さ
		damage = 1;

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
	}
	else {
		lifeTimer.on_update(deltaTime);
	}
}

void Beam::onDraw()
{
	if (isAiming)
	{

	}
}
