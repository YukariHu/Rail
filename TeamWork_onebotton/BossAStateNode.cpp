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

extern float deltaTime;

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

	randNum = rand() % 9;
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

#pragma region StraightLineFire

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
	moveIndex = 2;
	moveRand = rand() % 2;
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
	boss->Setposition(startPos + (targetPos[moveRand] - startPos) * easeT);

	if (isMove == false)
	{
		currentMoveIndex++;
		boss->SwitchState("StraightLineFire");
	}
}
void MoveBState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		//boss->SwitchState("idle");
		currentMoveIndex = 0;
	}
}

#pragma endregion

#pragma region RandomShotting

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

#pragma endregion

#pragma region DeviationShot

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

#pragma endregion

#pragma region BeamLeftToRightState

BeamLeftToRightState::BeamLeftToRightState()
{
	fireCount = 40;
	timer.set_one_shot(false);
	timer.set_wait_time(0.1f);
	timer.set_on_timeout([&]()
		{
			currentFireCount++;
			//fire
			Beam* beam2 = new Beam({ 5.0f + currentFireCount * 40.0f , windowHeight + 20.0f}, { 0.0f, -1.0f },1.0f);
			bulletList.push_back(beam2);

		});
}

void BeamLeftToRightState::onEnter()
{
	isOver = false;
	currentFireCount = 0;
}

void BeamLeftToRightState::onUpdate()
{
	BossA* bossA = (BossA*)(boss);
	timer.on_update(deltaTime);

	if (currentFireCount >= fireCount)
	{
		bossA->SwitchState("idle");
	}
}



BeamLeftToRightMoveState::BeamLeftToRightMoveState()
{
	currentMoveIndex = 0;
	moveIndex = 1;

	targetPos = Vector2(50.0f, windowHeight / 2.0f);
	totalTime = 1.0f;

}
void BeamLeftToRightMoveState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
}

void BeamLeftToRightMoveState::onUpdate()
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
			boss->SwitchState("BeamLeftToRight");
			currentMoveIndex++;
		}

	}
}

void BeamLeftToRightMoveState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		currentMoveIndex = 0;
	}
}
#pragma endregion

#pragma region BeamLeftToRightXState

BeamLeftToRightXState::BeamLeftToRightXState()
{
	fireCount = 15;
	timer.set_one_shot(false);
	timer.set_wait_time(0.1f);
	timer.set_on_timeout([&]()
		{
			currentFireCount++;
			//fire
			if (currentFireCount % 2 == 1) {
				Beam* beam2 = new Beam({ -20.0f, -20.0f + currentFireCount * 50.0f }, { 1.0f, 0.0f }, 0.5f);

				bulletList.push_back(beam2);

			} 

			if(currentFireCount % 2 == 0){
				Beam* beam2 = new Beam({ windowWidth + 20.0f, -20.0f + currentFireCount * 50.0f }, { -1.0f, 0.0f }, 0.5f);

				bulletList.push_back(beam2);

			}
		});
}

void BeamLeftToRightXState::onEnter()
{
	isOver = false;
	currentFireCount = 0;
}

void BeamLeftToRightXState::onUpdate()
{
	BossA* bossA = (BossA*)(boss);
	timer.on_update(deltaTime);

	if (currentFireCount >= fireCount)
	{
		bossA->SwitchState("idle");
	}
}


BeamLeftToRightXMoveState::BeamLeftToRightXMoveState()
{
	currentMoveIndex = 0;
	moveIndex = 1;

	targetPos = Vector2(400.0f, 100.0f);
	totalTime = 1.0f;

}
void BeamLeftToRightXMoveState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
}

void BeamLeftToRightXMoveState::onUpdate()
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
			boss->SwitchState("BeamLeftToRightX");
			currentMoveIndex++;
		}

	}
}

void BeamLeftToRightXMoveState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		currentMoveIndex = 0;
	}
}

#pragma endregion

#pragma region BeamRailState

BeamRailState::BeamRailState()
{
	fireCount = 5;
	timer.set_one_shot(false);
	timer.set_wait_time(1.0f);
	timer.set_on_timeout([&]()
		{
			currentFireCount++;
			//fire
			randCount = rand() % 2;

			if (randCount == 0) {
				Beam* beam2 = new Beam({ (windowWidth / 2.0f) + 100.0f , -20.0f }, { 0.0f, 1.0f }, 0.2f);

				bulletList.push_back(beam2);

			}

			if (randCount == 1) {
				Beam* beam2 = new Beam({ (windowWidth / 2.0f) - 100.0f , -20.0f }, { 0.0f, 1.0f }, 0.2f);

				bulletList.push_back(beam2);

			}
		});

}

void BeamRailState::onEnter()
{
	isOver = false;
	currentFireCount = 0;

	randCount = rand() % 2;
}

void BeamRailState::onUpdate()
{
	BossA* bossA = (BossA*)(boss);
	timer.on_update(deltaTime);

	if (currentFireCount >= fireCount)
	{
		bossA->SwitchState("idle");
	}

}

#pragma endregion

#pragma region BeamUpToDownState

BeamUpToDownState::BeamUpToDownState()
{
	fireCount = 40;
	timer.set_one_shot(false);
	timer.set_wait_time(0.1f);
	timer.set_on_timeout([&]()
		{
			currentFireCount++;
			//fire
			Beam* beam2 = new Beam({ -10.0f + currentFireCount * 40.0f , -20.0f }, { 0.0f, 1.0f }, 0.2f);
			bulletList.push_back(beam2);

		});
}

void BeamUpToDownState::onEnter()
{
	isOver = false;
	currentFireCount = 0;
}

void BeamUpToDownState::onUpdate()
{
	BossA* bossA = (BossA*)(boss);
	timer.on_update(deltaTime);

	if (currentFireCount >= fireCount)
	{
		bossA->SwitchState("idle");
	}
}


BeamUpToDownMoveState::BeamUpToDownMoveState()
{
	currentMoveIndex = 0;
	moveIndex = 1;

	targetPos = Vector2(100.0f, windowHeight / 2.0f);
	totalTime = 1.0f;

}
void BeamUpToDownMoveState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
}

void BeamUpToDownMoveState::onUpdate()
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
			boss->SwitchState("BeamUpToDown");
			currentMoveIndex++;
		}

	}
}

void BeamUpToDownMoveState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		currentMoveIndex = 0;
	}
}

#pragma endregion

#pragma region BeamCrossState

BeamCrossState::BeamCrossState()
{
	fireCount = 40;
	timer.set_one_shot(false);
	timer.set_wait_time(0.1f);
	timer.set_on_timeout([&]()
		{
			currentFireCount++;
			//fire
			Beam* beam2 = new Beam({ -10.0f + currentFireCount * 40.0f , -20.0f }, { 0.0f, 1.0f }, 0.2f);
			bulletList.push_back(beam2);

			Beam* beam1 = new Beam({ -20.0f ,-10.0f + currentFireCount * 40.0f}, { 1.0f, 0.0f }, 0.2f);
			bulletList.push_back(beam1);
		});
}

void BeamCrossState::onEnter()
{
	isOver = false;
	currentFireCount = 0;
}

void BeamCrossState::onUpdate()
{
	BossA* bossA = (BossA*)(boss);
	timer.on_update(deltaTime);

	if (currentFireCount >= fireCount)
	{
		bossA->SwitchState("idle");
	}
}



BeamCrossMoveState::BeamCrossMoveState()
{
	currentMoveIndex = 0;
	moveIndex = 1;

	targetPos = Vector2(100.0f, 100.0f);
	totalTime = 1.0f;

}
void BeamCrossMoveState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
}

void BeamCrossMoveState::onUpdate()
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
			boss->SwitchState("BeamCross");
			currentMoveIndex++;
		}

	}
}

void BeamCrossMoveState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		currentMoveIndex = 0;
	}
}

#pragma endregion