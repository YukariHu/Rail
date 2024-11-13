#pragma once
#include "MyVector2.h"
#include <Novice.h>
#include "StateMachine.h"
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
	virtual void onDraw();

	virtual void onHurt(int damage);

	int GetHp();
	void Setposition(const Vector2& _pos);
	const Vector2& Getposition();
	void SetSize(const Vector2& _size);
	const Vector2& GetSize();

	void SetTarget(Charactor* _target);


	void SwitchState(const std::string& id);

protected:
	Vector2 size;
	Vector2 pos;
	Vector2 velocity;

	int color;//キャラクターの色
	int hp;
	bool isDead = false;

	bool isEnableCollisionBox = true;//当たり判定を有効にするか

	Charactor* target = nullptr;

	StateMachine stateMachine;
};