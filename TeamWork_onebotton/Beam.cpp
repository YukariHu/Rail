#include "Beam.h"
#include "Novice.h"
#include "Easing.h"


extern float deltaTime;
Beam::Beam(Vector2 firePos, Vector2 _dir, float lifeTime)
{
		this->dir = _dir;
		this->pos = firePos;
		this->lifeTime = lifeTime;

		maxSize.x = 1400.0f;//長さ
		maxSize.y = 30.0f;//幅
		size.x = 0.0f;//長さ
		size.y = 0.0f;//幅


		damage = 1;

		color = WHITE;
		
		isEnable = false;


		isAiming = true;
		aimTimer.set_one_shot(true);
		aimTimer.set_wait_time(1.0f);
		aimTimer.set_on_timeout([&]() {
			isAiming = false; 
			isEnable = true;
			});
		
		lifeTimer.set_one_shot(true);
		lifeTimer.set_wait_time(lifeTime);
		lifeTimer.set_on_timeout([&]() {
			isOver = true;
			isEnable = false;
			});

		isOver = false;
		overTimer.set_one_shot(true);
		overTimer.set_wait_time(0.2f);
		overTimer.set_on_timeout([&]() {
			isCanRemove = true;
			});
}

void Beam::onUpdate()
{


	//照準線表示
	if (isAiming) {
		aimTimer.on_update(deltaTime);

		float easT = Easing::EaseInOut(aimTimer.get_progress());

		if (easT > 1.0f)
		{
			easT = 1.0f;
		}
		size.x = maxSize.x * easT * 3.0f;
		size.y = maxSize.y * easT ;
	}
	else {
		lifeTimer.on_update(deltaTime);
		if (isOver)
		{
			overTimer.on_update(deltaTime);
			float easT = Easing::EaseInOutCirc(overTimer.get_progress());
			size.y = maxSize.y * (1 - easT);
		}
	}

}

void Beam::onDraw(const Camera& camera)
{
	(void)camera;
	if (dir.x == 1.0f)
	{
		if (isAiming)
		{
			//Novice::DrawLine(static_cast<int>(pos.x),static_cast<int>(pos.y),);

			//横のビーム
			Novice::DrawBox(
				static_cast<int>(pos.x),
				static_cast<int>(pos.y - size.y / 2),
				static_cast<int>(size.x),
				static_cast<int>(size.y),
				0.0f,
				0xFFFFFF08,
				kFillModeSolid

			);
		}
		if (!isAiming && !isOver)
		{
			Novice::DrawBox(
				static_cast<int>(pos.x),
				static_cast<int>(pos.y - maxSize.y / 2),
				static_cast<int>(maxSize.x),
				static_cast<int>(maxSize.y),
				0.0f,
				color,
				kFillModeSolid
			);
		}
		if (isOver)
		{
			Novice::DrawBox(
				static_cast<int>(pos.x),
				static_cast<int>(pos.y - size.y / 2),
				static_cast<int>(maxSize.x),
				static_cast<int>(size.y),
				0.0f,
				color,
				kFillModeSolid
			);
		}
	}
	else
	{
		if (isAiming)
		{
			//Novice::DrawLine(static_cast<int>(pos.x),static_cast<int>(pos.y),);

			//横のビーム
			Novice::DrawBox(
				static_cast<int>(pos.x - size.x),
				static_cast<int>(pos.y - size.y / 2),
				static_cast<int>(size.x),
				static_cast<int>(size.y),
				0.0f,
				0xFFFFFF08,
				kFillModeSolid

			);
		}
		if (!isAiming && !isOver)
		{
			Novice::DrawBox(
				static_cast<int>(pos.x - maxSize.x),
				static_cast<int>(pos.y - maxSize.y / 2),
				static_cast<int>(maxSize.x),
				static_cast<int>(maxSize.y),
				0.0f,
				color,
				kFillModeSolid
			);
		}
		if (isOver)
		{
			Novice::DrawBox(
				static_cast<int>(pos.x - maxSize.x),
				static_cast<int>(pos.y - size.y / 2),
				static_cast<int>(maxSize.x),
				static_cast<int>(size.y),
				0.0f,
				color,
				kFillModeSolid
			);
		}
	}

	if (dir.y == 1.0f)
	{
		if (isAiming) {
		//縦のビーム
			Novice::DrawBox(
				static_cast<int>(pos.x - size.y / 2),
				static_cast<int>(pos.y),
				static_cast<int>(size.y),
				static_cast<int>(size.x),
				0.0f,
				0xFFFFFF08,
				kFillModeSolid
			);
		}
		if (!isAiming && !isOver)
		{
			Novice::DrawBox(
				static_cast<int>(pos.x - maxSize.y / 2),
				static_cast<int>(pos.y),
				static_cast<int>(maxSize.y),
				static_cast<int>(maxSize.x),
				0.0f,
				color,
				kFillModeSolid
			);
		}
		if (isOver)
		{
			Novice::DrawBox(
				static_cast<int>(pos.x - size.y / 2),
				static_cast<int>(pos.y),
				static_cast<int>(size.y),
				static_cast<int>(maxSize.x),
				0.0f,
				color,
				kFillModeSolid
			);
		}
	}
	else
	{
		if (isAiming) {
			//縦のビーム
			Novice::DrawBox(
				static_cast<int>(pos.x - size.y / 2),
				static_cast<int>(pos.y - size.x),
				static_cast<int>(size.y),
				static_cast<int>(size.x),
				0.0f,
				0xFFFFFF08,
				kFillModeSolid
			);
		}
		if (!isAiming && !isOver)
		{
			Novice::DrawBox(
				static_cast<int>(pos.x - maxSize.y / 2),
				static_cast<int>(pos.y - maxSize.x),
				static_cast<int>(maxSize.y),
				static_cast<int>(maxSize.x),
				0.0f,
				color,
				kFillModeSolid
			);
		}
		if (isOver)
		{
			Novice::DrawBox(
				static_cast<int>(pos.x - size.y / 2),
				static_cast<int>(pos.y - size.x),
				static_cast<int>(size.y),
				static_cast<int>(maxSize.x),
				0.0f,
				color,
				kFillModeSolid
			);
		}
	}
	
	
}
