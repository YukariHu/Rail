#pragma once
#include "MyVector2.h"
#include <Novice.h>
#include "StateMachine.h"
#include "Camera.h"
class Charactor
{
public:
	Charactor() = default;
	~Charactor() = default;

	virtual void onInput(char* keys, char* prekeys) {
	(void)keys;
	(void)prekeys;
	};
	virtual void onUpdate();
	virtual void onDraw(const Camera& camera);

	virtual void Collision();

	virtual void onHurt(int damage);

	int GetHp();
	void Setposition(const Vector2& _pos);
	const Vector2& Getposition();
	void SetSize(const Vector2& _size);
	const Vector2& GetSize();
	const int GetColor() const { return color; }

	void SetTarget(Charactor* _target);

	void SwitchState(const std::string& id);

protected:
	Vector2 size;
	Vector2 pos;
	Vector2 velocity;

	//0:player 1:boss
	//当たり判定の時使う
	int id;

	int color;//キャラクターの色
	int hp;
	int maxHp;
	bool isDead = false;

	bool isEnableCollision = true;//当たり判定を有効にするか

	Charactor* target = nullptr;

	StateMachine stateMachine;
};