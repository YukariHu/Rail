#pragma once
#include "MyVector2.h"
#include <functional>
#include "Camera.h"

class Bullet
{
public:
	Bullet() = default;
	Bullet(Vector2 firePos,Vector2 dir);
	Bullet(Vector2 firePos,Vector2 dir,int _targertID);
	~Bullet() = default;

	virtual void onUpdate();
	virtual bool checkCollision(Vector2 targertPos,Vector2 targertSize);
	virtual void onDraw(const Camera& camera);

	int getDamage();
protected:

	Vector2 pos;
	Vector2 size;
	
	Vector2 dir;
	float velocity;

	int damage;


	bool isEnableCollision = true;//当たり判定を有効にするか

	std::function<void()> callback;
public:
	bool isCanRemove = false;

	//0:player 1:boss
	int targetID;
};
