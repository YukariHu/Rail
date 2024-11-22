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

	int GetAttackNum() { return randNum; };

private:
	Timer timer;

	Vector2 topPos;
	Vector2 bottomPos;
	float speed;
	float dir;

	int randNum;
};

//class MoveToCenter

//ボスは4つのポイントを順番に移動する
class MoveAState : public StateNode
{
public:
	MoveAState();
	~MoveAState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	int moveIndex;
	int currentMoveIndex;

	Vector2 targetPos[5];
	Vector2 startPos;

	float totalTime;
	float passTime;
	bool isMove;

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


class StraightLineFire : public StateNode
{
public:
	StraightLineFire();
	~StraightLineFire() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	Timer timer;
	//撃つ回数
	int fireCount;
	int currentFireCount;


	float totalTime;
	float passTime;
	bool isMove;
};


class MoveBState : public StateNode
{
public:
	MoveBState();
	~MoveBState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	int moveIndex;
	int currentMoveIndex;

	Vector2 targetPos[2];
	Vector2 startPos;

	float totalTime;
	float passTime;
	bool isMove;
	int moveRand;
};

class RandomShotting : public StateNode
{
public:
	RandomShotting();
	~RandomShotting() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	Timer timer;
	//撃つ回数
	int fireCount;
	int currentFireCount;


	float totalTime;
	float passTime;
	bool isMove;
};

class RandomShottingMoveState : public StateNode
{
public:
	RandomShottingMoveState();
	~RandomShottingMoveState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	int moveIndex;
	int currentMoveIndex;

	Vector2 targetPos;
	Vector2 startPos;

	float totalTime;
	float passTime;
	bool isMove;

};

class DeviationShot : public StateNode
{
public:
	DeviationShot();
	~DeviationShot() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	Timer timer;
	//撃つ回数
	int fireCount;
	int currentFireCount;


	float totalTime;
	float passTime;
	bool isMove;
};

class DeviationShotMoveState : public StateNode
{
public:
	DeviationShotMoveState();
	~DeviationShotMoveState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	int moveIndex;
	int currentMoveIndex;

	Vector2 targetPos;
	Vector2 startPos;

	float totalTime;
	float passTime;
	bool isMove;

};

class BeamLeftToRightState : public StateNode
{
public:
	BeamLeftToRightState();
	~BeamLeftToRightState() = default;

	void onEnter() override;
	void onUpdate() override;

private:
	Timer timer;
	//撃つ回数
	int fireCount;
	int currentFireCount;

	bool isOver;
};


class BeamLeftToRightMoveState : public StateNode
{
public:
	BeamLeftToRightMoveState();
	~BeamLeftToRightMoveState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	int moveIndex;
	int currentMoveIndex;

	Vector2 targetPos;
	Vector2 startPos;

	float totalTime;
	float passTime;
	bool isMove;

};

class BeamLeftToRightXState : public StateNode
{
public:
	BeamLeftToRightXState();
	~BeamLeftToRightXState() = default;

	void onEnter() override;
	void onUpdate() override;

private:
	Timer timer;
	//撃つ回数
	int fireCount;
	int currentFireCount;

	bool isOver;
};

class BeamLeftToRightXMoveState : public StateNode
{
public:
	BeamLeftToRightXMoveState();
	~BeamLeftToRightXMoveState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	int moveIndex;
	int currentMoveIndex;

	Vector2 targetPos;
	Vector2 startPos;

	float totalTime;
	float passTime;
	bool isMove;

};

class BeamRailState : public StateNode
{
public:
	BeamRailState();
	~BeamRailState() = default;

	void onEnter() override;
	void onUpdate() override;

private:
	Timer timer;
	//撃つ回数
	int fireCount;
	int currentFireCount;

	bool isOver;

	int randCount;
};

class BeamUpToDownState : public StateNode
{
public:
	BeamUpToDownState();
	~BeamUpToDownState() = default;

	void onEnter() override;
	void onUpdate() override;

private:
	Timer timer;
	//撃つ回数
	int fireCount;
	int currentFireCount;

	bool isOver;
};

class BeamUpToDownMoveState : public StateNode
{
public:
	BeamUpToDownMoveState();
	~BeamUpToDownMoveState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	int moveIndex;
	int currentMoveIndex;

	Vector2 targetPos;
	Vector2 startPos;

	float totalTime;
	float passTime;
	bool isMove;

};


class BeamCrossState : public StateNode
{
public:
	BeamCrossState();
	~BeamCrossState() = default;

	void onEnter() override;
	void onUpdate() override;

private:
	Timer timer;
	//撃つ回数
	int fireCount;
	int currentFireCount;

	bool isOver;
};


class BeamCrossMoveState : public StateNode
{
public:
	BeamCrossMoveState();
	~BeamCrossMoveState() = default;

	void onEnter() override;
	void onUpdate() override;
	void onExit() override;
private:

	int moveIndex;
	int currentMoveIndex;

	Vector2 targetPos;
	Vector2 startPos;

	float totalTime;
	float passTime;
	bool isMove;

};