#include "BossAStateNode.h"
#include "BossA.h"
#include "Bullet.h"
#include "Beam.h"
#include "Easing.h"
#include "Player.h"

#define PI 3.1415926f

extern Charactor* boss;
extern Charactor* player;
extern std::vector<Bullet*> bulletList;
extern Camera mainCamera;

extern int windowHeight;
extern int windowWidth;

extern float deltaTime;

#pragma region IdleState

IdleState::IdleState()
{
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			
		});

	speed = 2.0f;
	dir = 1;
	moveStateIndex = 0;
}

void IdleState::onEnter()
{
	timer.set_wait_time(1.0f);
	timer.restart();
	topPos = boss->Getposition() + Vector2(0, 30.0f);
	bottomPos = boss->Getposition() + Vector2(0, 30.0f);

	moveStateIndex = rand() % 4;
	dynamic_cast<Player*>(player)->canShot = true;
}

void IdleState::onUpdate()
{
	timer.on_update(deltaTime);
	boss->Setposition(boss->Getposition() + Vector2(0, speed) * dir);
	if (boss->Getposition().y > bottomPos.y || boss->Getposition().y < topPos.y)
	{
		dir *= -1;
	}

	if (dynamic_cast<BossA*>(boss)->GetisPhase1()) {
		switch (moveStateIndex)
		{
		case 0:
			boss->SwitchState("moveB");
			break;
		case 1:
			boss->SwitchState("RandomShottingMove");
			break;
		case 2:
			boss->SwitchState("DeviationShotMove");
			break;
		case 3:
			boss->SwitchState("BeamLeftToRightMove");
			break;
		}
	} else{
		switch (moveStateIndex)
		{
		case 0:
			boss->SwitchState("MoveBeamRail");
			break;
		case 1:
			boss->SwitchState("BeamCrossMove");
			break;
		case 2:
			boss->SwitchState("BeamLeftToRightXMove");
			break;
		case 3:
			boss->SwitchState("BeamUpToDownMove");
			break;
		}
	}

}

#pragma endregion

FirstState::FirstState()
{
	currentMoveIndex = 0;
	targetPos = Vector2(1280.0f / 2.0f, 100.0f);
	totalTime = 5.0f;
}

void FirstState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
	attackCompleted = false;
	moveIndex = 2;
	
}

void FirstState::onUpdate()
{
	passTime += deltaTime;
	float t = passTime / totalTime;
	if (t >= 1.0f)
	{
		t = 1.0f;
		isMove = false;
	}

	float easeT = Easing::EaseInOut(t);
	boss->Setposition(startPos + (targetPos - startPos) * easeT);

	if (!isMove && !attackCompleted) // 移動が完了したら攻撃
	{
		attackCompleted = true;
		boss->SwitchState("idle");
	}
}

void FirstState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		currentMoveIndex = 0;
	}

}

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
		boss->SwitchState("idle");
	}

}
void CircleFireState::onExit()
{
	currentFireCount = 0;
	bulletNum = 3;
}

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
		if (currentMoveIndex >= moveIndex)
		{
			
			BossA* bossA = (BossA*)(boss);
			int bulletNum = 3;
			bossA->CircleFire(bulletNum); 
			boss->SwitchState("CircleFire"); 
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

#pragma region MoveBState

MoveBState::MoveBState()
{
	currentMoveIndex = 0;
	targetPos[0] = Vector2(1180, 650.0f);
	targetPos[1] = Vector2(1180, 500.0f);
	totalTime = 0.5f;
	count = 0;
}

void MoveBState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
	attackCompleted = false;
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

	if (!isMove && !attackCompleted) // 移動が完了したら攻撃
	{
		attackCompleted = true;
		BossA* bossA = (BossA*)(boss);
		bossA->StraightFire(); 
	}

	if (attackCompleted)
	{
		
		if (count < 5) 
		{
			
			boss->SwitchState("moveB");
			count++;
			attackCompleted = false;  
		} else
		{
			boss->SwitchState("idle");
			count = 0;
		}
	}

	if (!isMove && attackCompleted)  
	{
		count++; 
		attackCompleted = false;
	}
}

void MoveBState::onExit()
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
	timer.set_wait_time(0.02f);
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
	fireCount = 5;
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
	timer.set_wait_time(0.5f);
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
	timer.set_wait_time(0.08f);
	timer.set_on_timeout([&]()
		{
			mainCamera.Shack(5.0f, 0.2f);
			currentFireCount++;
			//fire
			Beam* beam2 = new Beam({ 5.0f + currentFireCount * 50.0f , windowHeight + 20.0f}, { 0.0f, -1.0f },1.0f,0);
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
				Beam* beam2 = new Beam({ -20.0f, -20.0f + currentFireCount * 50.0f }, { 1.0f, 0.0f }, 0.5f,0);

				bulletList.push_back(beam2);
				mainCamera.Shack(5.0f, 0.2f);
			} 

			if(currentFireCount % 2 == 0){
				Beam* beam2 = new Beam({ windowWidth + 20.0f, -20.0f + currentFireCount * 50.0f }, { -1.0f, 0.0f }, 0.5f,0);

				bulletList.push_back(beam2);
				mainCamera.Shack(5.0f, 0.2f);
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
				Beam* beam2 = new Beam({ (windowWidth / 2.0f) + 100.0f , -20.0f }, { 0.0f, 1.0f }, 0.2f,0);

				bulletList.push_back(beam2);
				mainCamera.Shack(5.0f, 0.2f);
			}

			if (randCount == 1) {
				Beam* beam2 = new Beam({ (windowWidth / 2.0f) - 100.0f , -20.0f }, { 0.0f, 1.0f }, 0.2f,0);

				bulletList.push_back(beam2);
				mainCamera.Shack(5.0f, 0.2f);
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


#pragma region MoveBeamRailState



MoveBeamRailState::MoveBeamRailState()
{
	currentMoveIndex = 0;
	moveIndex = 1;

	targetPos = Vector2(1080.0f, 720.0f / 2.0f);
	totalTime = 1.0f;

}
void MoveBeamRailState::onEnter()
{
	startPos = boss->Getposition();
	passTime = 0.0f;
	isMove = true;
}

void MoveBeamRailState::onUpdate()
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
			boss->SwitchState("BeamRail");
			currentMoveIndex++;
		}

	}
}

void MoveBeamRailState::onExit()
{
	if (currentMoveIndex >= moveIndex)
	{
		currentMoveIndex = 0;
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
			Beam* beam2 = new Beam({ -10.0f + currentFireCount * 40.0f , -20.0f }, { 0.0f, 1.0f }, 0.2f,0);
			bulletList.push_back(beam2);
			mainCamera.Shack(5.0f, 0.2f);
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

	targetPos = Vector2(1180.0f, windowHeight / 2.0f);
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
			Beam* beam2 = new Beam({ -10.0f + currentFireCount * 40.0f , -20.0f }, { 0.0f, 1.0f }, 0.2f,0);
			bulletList.push_back(beam2);

			Beam* beam1 = new Beam({ -20.0f ,-10.0f + currentFireCount * 40.0f}, { 1.0f, 0.0f }, 0.2f,0);
			bulletList.push_back(beam1);

			mainCamera.Shack(5.0f, 0.2f);
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

#pragma region DeadState
DeadState::DeadState()
{
	deadTimer.set_wait_time(deadTime);
	deadTimer.set_one_shot(true);
	deadTimer.set_on_timeout([&]()
		{
			
			boss->SetIsDead(true);
		});


}
void DeadState::onEnter()
{
	
	deadTimer.restart();
	mainCamera.Shack(3.0f,3.0f);
	
}
void DeadState::onUpdate()
{
	deadTimer.on_update(deltaTime);
	

	if (deadTimer.get_progress() < 0.5f)
	{
		boss->SetSize(boss->GetSize() - Vector2(0.1f, 0.1f));
		//移动到中心位置

	}
	else
	{
		boss->SetIsblender(false);
	}

}
#pragma endregion