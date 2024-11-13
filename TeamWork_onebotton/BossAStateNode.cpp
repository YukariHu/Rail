#include "BossAStateNode.h"
#include "BossA.h"
#include "Bullet.h"
#include "Easing.h"
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
	speed = 2.0f;
	dir = 1;

}
void IdleState::onEnter()
{
	timer.set_wait_time(2.0f);
	timer.restart();
	topPos = boss->Getposition() + Vector2(0,30.0f);
	bottomPos = boss->Getposition() + Vector2(0, 30.0f);

}
void IdleState::onUpdate()
{
	//Vector2 velocity = { 0,3.0f };
	timer.on_update(deltaTime);
	//让boss在topPos和bottomPos间移动
	boss->Setposition(boss->Getposition() + Vector2(0, speed)* dir);
	if (boss->Getposition().y > bottomPos.y || boss->Getposition().y < topPos.y)
	{
		dir *= -1;
	}


}

CircleFireState::CircleFireState()
{
	fireCount = 3;
	currentFireCount = 0;
	
	timer.set_one_shot(false);
	timer.set_on_timeout([&]()
	{
		currentFireCount++;
		bulletNum += 1;
		//fire
		BossA* bossA = (BossA*)(boss);
		bossA->CircleFire(bulletNum);
	});

}
void CircleFireState::onEnter()
{
	bulletNum = 3;
	timer.set_wait_time(0.5f);
	timer.restart();
}
void CircleFireState::onUpdate()
{
	timer.on_update(deltaTime);

	if (currentFireCount >= fireCount)
	{
		boss->SwitchState("moveA");
	}

}
void CircleFireState::onExit()
{
	currentFireCount = 0;
	bulletNum = 3;
}


MoveAState::MoveAState()
{
	currentMoveIndex = 0;
	moveIndex = 3;
	
	targetPos[0] = Vector2(100, 100);
	targetPos[1] = Vector2(500, 100);
	targetPos[2] = Vector2(500, 500);
	targetPos[3] = Vector2(100, 500);

	totalTime = 1.0f;

}
void MoveAState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
}
void MoveAState::onUpdate()
{
	passTime += deltaTime;
	float t = passTime / totalTime;
	if (t >= 1.0f)
	{
		t = 1.0f;
		isMove = false;
	}
	float easeT = EaseInOut(t);
	boss->Setposition(startPos + (targetPos[moveIndex] - startPos) * easeT);

	if (isMove == false)
	{
		currentMoveIndex++;
		boss->SwitchState("circlefire");
	}
}
void MoveAState::onExit()
{
}
