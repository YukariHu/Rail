#pragma once
#include "Charactor.h"
#include "StateMachine.h"
class BossA : public Charactor
{
public:
	BossA();
	~BossA();

	void onUpdate() override;
	void onDraw() override;

private:
	StateMachine stateMachine;
};
