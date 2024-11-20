#pragma once
#include "timer.h"
#include "MyVector2.h"


class Camera
{
public:
	Camera()
	{
		shakeTimer.set_one_shot(true);
		shakeTimer.set_on_timeout([&]() {
			isShake = false; 
			Reset();
			
			});
	};
	~Camera() = default;

	void Reset()
	{
		pos = Vector2(0, 0);
	}

	void onUpdate()
	{
		shakeTimer.on_update(deltaTime);
		if (isShake)
		{
			pos.x = (-50 + rand() % 100) / 50.0f * shakePower;
			pos.y = (-50 + rand() % 100) / 50.0f * shakePower;
		}
	}

	void Shack(float power, float time)
	{
		shakePower = power;
		shakeTimer.set_wait_time(time);
		shakeTimer.restart();
		isShake = true;
	}

	const Vector2& GetPos() const
	{
		return pos;
	}
private:
	Vector2 pos;
	Timer shakeTimer;
	float shakePower = 0;
	bool isShake = false;

	float deltaTime = 1.0f / 60.0f;
};
