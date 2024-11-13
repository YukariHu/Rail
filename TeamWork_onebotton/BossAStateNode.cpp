#include "BossAStateNode.h"
#include "BossA.h"
#include "Bullet.h"
extern Charactor* boss;
extern Charactor* player;
extern std::vector<Bullet*> bulletList;

float deltaTime = 1.0f / 60.0f;

IdleState::IdleState()
{
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
	{
			boss->SwitchState("circlefire");
	});

}

void IdleState::onEnter()
{
	timer.set_wait_time(3.0f);
	timer.restart();
}

void IdleState::onUpdate()
{
	timer.on_update(deltaTime);

}


CircleFireState::CircleFireState()
{

	timer.set_one_shot(false);
	timer.set_on_timeout([&]()
	{
		currentFireCount++;
	});

	if (currentFireCount == fireCount)
	{
		boss->SwitchState("idle");
	}
	
}

void CircleFireState::onEnter()
{
	timer.set_wait_time(0.5f);
	timer.restart();
}
void CircleFireState::onUpdate()
{
	timer.on_update(deltaTime);
}
void CircleFireState::onExit()
{
	currentFireCount = 0;
}