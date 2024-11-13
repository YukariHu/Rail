#pragma once
#include "timer.h"
#include "StateNode.h"


class IdleState : public StateNode
{
public:
	IdleState();
	~IdleState() = default;

	void onEnter() override;
	void onUpdate() override;

private:
	Timer timer;

};

class MoveState : public StateNode
{
public:
	MoveState();
	~MoveState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	const float speed = 2.0f;

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
	int fireCount = 5;
	int currentFireCount = 0;
};

