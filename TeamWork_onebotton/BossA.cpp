#include "BossA.h"
#include "BossAStateNode.h"
#include "Bullet.h"
#include "Beam.h"
#include "DeviationShotBullet.h"
#include "Player.h"

#define PI 3.1415926f
extern std::vector<Bullet*> bulletList;
extern Charactor* player;
//extern IdleState* idoleState;

BossA::BossA()
{
	color = 0xB6BBC4FF;
	size = { 60.0f, 60.0f };
	pos = { 400.0f, 300.0f };
	velocity = { 0.0f, 0.0f };

	alpha_ = 255;

	stateMachine.RegisterState("idle",new IdleState());
	
	stateMachine.RegisterState("circlefire", new CircleFireState());
	stateMachine.RegisterState("moveA",new MoveAState());
	
	stateMachine.RegisterState("StraightLineFire", new StraightLineFire());
	stateMachine.RegisterState("moveB", new MoveBState());
	
	stateMachine.RegisterState("RandomShotting", new RandomShotting());
	stateMachine.RegisterState("RandomShottingMove", new RandomShottingMoveState());
	
	stateMachine.RegisterState("DeviationShot", new DeviationShot());
	stateMachine.RegisterState("DeviationShotMove", new DeviationShotMoveState());

	stateMachine.RegisterState("BeamLeftToRight", new BeamLeftToRightState());
	stateMachine.RegisterState("BeamLeftToRightMove", new BeamLeftToRightMoveState());

	stateMachine.RegisterState("BeamLeftToRightX", new BeamLeftToRightXState());
	stateMachine.RegisterState("BeamLeftToRightXMove", new BeamLeftToRightXMoveState());

	stateMachine.RegisterState("BeamRail", new BeamRailState());

	stateMachine.RegisterState("BeamUpToDown", new BeamUpToDownState());
	stateMachine.RegisterState("BeamUpToDownMove", new BeamUpToDownMoveState());

	stateMachine.RegisterState("BeamCross", new BeamCrossState());
	stateMachine.RegisterState("BeamCrossMove", new BeamCrossMoveState());

	stateMachine.SetEntry("idle");
}



void BossA::onUpdate()
{
	stateMachine.onUpdate();
	Charactor::onUpdate();

	if (alpha_ <= 0) {

		alpha_ = 0;
	}

	if (stateMachine.GetCurrentStateName() == "idle") {
		// 次の攻撃を乱数で決定
		int attackChoice = rand() % 9; // 0〜8 の間でランダムな整数を取得

		// 乱数に応じて次の攻撃を決定
		switch (attackChoice) {
		case 0:
			stateMachine.SetEntry("moveA");
			break;
		case 1:
			stateMachine.SetEntry("moveB");
			break;
		case 2:
			stateMachine.SetEntry("RandomShottingMove");
			break;
		case 3:
			stateMachine.SetEntry("DeviationShotMove");
			break;
		case 4:
			stateMachine.SetEntry("BeamLeftToRightMove");
			break;
		case 5:
			stateMachine.SetEntry("BeamLeftToRightXMove");
			break;
		case 6:
			stateMachine.SetEntry("BeamRail");
			break;
		case 7:
			stateMachine.SetEntry("BeamUpToDownMove");
			break;
		case 8:
			stateMachine.SetEntry("BeamCrossMove");
			break;
		}
	}
}

void BossA::onDraw(const Camera& camera)
{
	Novice::DrawEllipse(static_cast<int>(pos.x+ camera.GetPos().x), static_cast<int>(pos.y + camera.GetPos().y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, 0xFFFFFFFF, kFillModeSolid);
	//Novice::ScreenPrintf(0,30,"%f",target->GetSize().x);
    
}


void BossA::CircleFire(int bulletNum)
{
for (int i = 0; i < 360; i += 360/ bulletNum)
	{
		Vector2 direction = { cosf(i * PI / 180.0f), sinf(i * PI / 180.0f) };
		Bullet* bullet = new Bullet(pos, direction);
		bulletList.push_back(bullet);
	}
}

void BossA::StraightFire()
{
	Vector2 direction = { -1.0f ,0.0f };
	Bullet* bullet = new Bullet(pos, direction);
	bulletList.push_back(bullet);
}

void BossA::RandomFire()
{
	Vector2 direction = { cosf(float(rand() % 180) * PI / float(rand() % 180)), sinf(float(rand() % 180)* PI / 180) };
	Bullet* bullet = new Bullet(pos, direction);
	bulletList.push_back(bullet);
}

void BossA::DeviationFire() {
	
	Vector2 playerPosition = player->Getposition(); 

	float predictionTime = 3.0f;
	Vector2 predictedPosition;
	predictedPosition.x = playerPosition.x + 1.0f * predictionTime;
	predictedPosition.y = playerPosition.y; 

	float angle = atan2(predictedPosition.y - pos.y, predictedPosition.x - pos.x);

	DeviationShotBullet* bullet = new DeviationShotBullet(pos, { angle, angle });
	bulletList.push_back(bullet);
}


void BossA::BeamFire()
{
	Vector2 direction = { 1.0f, 0.0f };
	Vector2 firepos = {-30.0f,300.0f};
	float lifeTime = 1.0f;
	Beam* beam = new Beam(firepos, direction,lifeTime);
	bulletList.push_back(beam);

}

//void BossA::MoveTo(Vector2 targetPos,float time)
//{
//	//使用缓动函数移动到目标位置
//	
//	 
//}

