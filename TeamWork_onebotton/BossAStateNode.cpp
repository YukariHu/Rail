#include "BossAStateNode.h"
#include "BossA.h"
#include "Bullet.h"
#include "Beam.h"
#include "Easing.h"

extern Charactor* boss;
extern Charactor* player;
extern std::vector<Bullet*> bulletList;

extern int windowHeight;
extern int windowWidth;

float deltaTime = 1.0f / 60.0f;

#pragma region IdleState
IdleState::IdleState()
{
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
	{
			boss->SwitchState("beamFire");
	});
	speed = 2.0f;
	dir = 1;

}
void IdleState::onEnter()
{
	timer.set_wait_time(1.0f);
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
#pragma endregion


#pragma region CircleFireState
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
#pragma endregion


#pragma region MoveAState
MoveAState::MoveAState()
{
	currentMoveIndex = 0;
	moveIndex = 4;
	
	targetPos[0] = Vector2(200, 150);
	targetPos[1] = Vector2(200, static_cast<float>(windowHeight - 150));
	targetPos[2] = Vector2(static_cast<float>(windowWidth - 150), static_cast<float>(windowHeight - 150));
	targetPos[3] = Vector2(static_cast<float>(windowWidth - 150), 150);
	targetPos[4] = Vector2(static_cast<float>(windowWidth / 2), static_cast<float>(windowHeight / 2));

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

	float easeT = Easing::EaseInOut(t);
	boss->Setposition(startPos + (targetPos[currentMoveIndex] - startPos) * easeT);

	if (t >= 1.0f)
	{
		t = 1.0f;
		isMove = false;
	}
	if (isMove == false)
	{
		
		if(currentMoveIndex >= moveIndex)
		{
			
			boss->SwitchState("idle");
		}
		else
		{
			boss->SwitchState("circlefire");
			currentMoveIndex++;
		}
		
	}
}
void MoveAState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		currentMoveIndex = 0;
	}
}
#pragma endregion


StraightLineFire::StraightLineFire()
{
	fireCount = 1;
	currentFireCount = 0;

	timer.set_one_shot(false);
	timer.set_on_timeout([&]()
		{
			currentFireCount++;
			//fire
			BossA* bossA = (BossA*)(boss);
			bossA->StraightFire();
		}
	);
}
void StraightLineFire::onEnter()
{

	passTime = 0.0f;
	isMove = true;
	timer.set_wait_time(0.2f);
	timer.restart();

}
void StraightLineFire::onUpdate()
{

	timer.on_update(deltaTime);

	if (currentFireCount >= fireCount)
	{
		boss->SwitchState("moveB");
	}
}
void StraightLineFire::onExit()
{
	currentFireCount = 0;
}

#pragma region BeamFireState
BeamFireState::BeamFireState()
{
	fireCount = 3;
	timer.set_one_shot(false);
	timer.set_wait_time(0.5f);
	timer.set_on_timeout([&]()
		{
			currentFireCount++;
			//fire
			//Beam* beam = new Beam({-20.0f, 20 + currentFireCount * 80.0f}, { 1.0f,0.0f, });
			//bulletList.push_back(beam);
			Beam* beam2 = new Beam({ windowWidth + 20.0f, 20 + currentFireCount * 120.0f }, { -1.0f,0.0f });
			bulletList.push_back(beam2);

			//Beam* beam3 = new Beam({ 20.0f + currentFireCount * 100.0f, -20.0f }, { 0.0f,1.0f, });
			//bulletList.push_back(beam3);
		});
}
void BeamFireState::onEnter()
{
	isOver = false;
	currentFireCount = 0;

}
void BeamFireState::onUpdate()
{
	BossA* bossA = (BossA*)(boss);
	timer.on_update(deltaTime);
	//bossA->BeamFire();
	if (currentFireCount >= fireCount)
	{
		bossA->SwitchState("idle");
	}

}
#pragma endregion


MoveBState::MoveBState()
{
	currentMoveIndex = 0;

	targetPos[0] = Vector2(1180, 600.0f);
	targetPos[1] = Vector2(1180, 400.0f);

	totalTime = 0.5f;

}
void MoveBState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
	moveIndex = rand() % 2;
}
void MoveBState::onUpdate()
{
	passTime += deltaTime;
	float t = passTime / totalTime;
	if (t >= 1.0f)
	{
		t = 1.0f;
		isMove = false;
	}
	float easeT = Easing::EaseInOut(t);
	boss->Setposition(startPos + (targetPos[moveIndex] - startPos) * easeT);

	if (isMove == false)
	{
		currentMoveIndex++;
		boss->SwitchState("StraightLineFire");
	}
}
void MoveBState::onExit()
{
}

RandomShotting::RandomShotting()
{
	fireCount = 60;
	currentFireCount = 0;

	timer.set_one_shot(false);
	timer.set_on_timeout([&]()
		{
			currentFireCount++;
			//fire
			BossA* bossA = (BossA*)(boss);
			bossA->RandomFire();
		}
	);
}

void RandomShotting::onEnter()
{
	passTime = 0.0f;
	isMove = true;
	timer.set_wait_time(0.08f);
	timer.restart();
}

void RandomShotting::onUpdate()
{
	timer.on_update(deltaTime);

	if (currentFireCount >= fireCount)
	{
		boss->SwitchState("RandomShottingMove");
	}
}

void RandomShotting::onExit()
{
	currentFireCount = 0;
}

RandomShottingMoveState::RandomShottingMoveState()
{
	currentMoveIndex = 0;
	moveIndex = 1;

	targetPos = Vector2(1280 / 2, 100);

	totalTime = 1.0f;
}

void RandomShottingMoveState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
}

void RandomShottingMoveState::onUpdate()
{
	passTime += deltaTime;
	float t = passTime / totalTime;

	float easeT = Easing::EaseInOut(t);
	boss->Setposition(startPos + (targetPos - startPos) * easeT);

	if (t >= 1.0f)
	{
		t = 1.0f;
		isMove = false;
	}
	if (isMove == false)
	{

		if (currentMoveIndex >= moveIndex)
		{

			boss->SwitchState("idle");
		} else
		{
			boss->SwitchState("RandomShotting");
			currentMoveIndex++;
		}

	}
}

void RandomShottingMoveState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		currentMoveIndex = 0;
	}
}

DeviationShot::DeviationShot()
{
	fireCount = 10;
	currentFireCount = 0;

	timer.set_one_shot(false);
	timer.set_on_timeout([&]()
		{
			currentFireCount++;
			//fire
			BossA* bossA = (BossA*)(boss);
			bossA->DeviationFire();
		}
	);
}

void DeviationShot::onEnter()
{
	passTime = 0.0f;
	isMove = true;
	timer.set_wait_time(1.0f);
	timer.restart();
}

void DeviationShot::onUpdate()
{
	timer.on_update(deltaTime);

	if (currentFireCount >= fireCount)
	{
		boss->SwitchState("DeviationShotMove");
	}
}

void DeviationShot::onExit()
{
	currentFireCount = 0;
}

DeviationShotMoveState::DeviationShotMoveState()
{
	currentMoveIndex = 0;
	moveIndex = 1;

	targetPos = Vector2(1280 / 2, 100);

	totalTime = 1.0f;
}

void DeviationShotMoveState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
}

void DeviationShotMoveState::onUpdate()
{

	passTime += deltaTime;
	float t = passTime / totalTime;

	float easeT = Easing::EaseInOut(t);
	boss->Setposition(startPos + (targetPos - startPos) * easeT);

	if (t >= 1.0f)
	{
		t = 1.0f;
		isMove = false;
	}
	if (isMove == false)
	{

		if (currentMoveIndex >= moveIndex)
		{

			boss->SwitchState("idle");
		} else
		{
			boss->SwitchState("DeviationShot");
			currentMoveIndex++;
		}

	}
}

void DeviationShotMoveState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		currentMoveIndex = 0;
	}
}
