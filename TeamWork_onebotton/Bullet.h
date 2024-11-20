#pragma once
#include "MyVector2.h"
#include <functional>
#include "Camera.h"

class Bullet
{
public:
	Bullet() = default;
	Bullet(Vector2 firePos,Vector2 dir);
	~Bullet() = default;

	virtual void onUpdate();
	virtual void onDraw(const Camera& camera);
protected:

	Vector2 pos;
	Vector2 size;
	
	Vector2 dir;
	float velocity;

	int damage;
	

	std::function<void()> callback;
public:
	bool isCanRemove = false;
};
