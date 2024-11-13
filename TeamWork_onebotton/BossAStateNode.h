#pragma once
#include "timer.h"
#include "StateNode.h"
#include "MyVector2.h"


class IdleState : public StateNode
{
public:
	IdleState();
	~IdleState() = default;

	void onEnter() override;
	void onUpdate() override;

private:
	Timer timer;

	Vector2 topPos;
	Vector2 bottomPos;
	float speed;
	float dir;

};

class MoveAState : public StateNode
{
public:
	MoveAState();
	~MoveAState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	int moveCount;
	int currentMoveCount;

	Vector2 targetPos[4];

};


class BossAimState : public StateNode
{
public:
	BossAimState();
	~BossAimState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:
	Timer timer;
};

class CircleFireState : public StateNode
{
public:
	CircleFireState();
	~CircleFireState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	Timer timer;
	//CircleFireの回数
	int fireCount;
	int currentFireCount;

	//毎回circleFireの弾の数
	int bulletNum;
};

