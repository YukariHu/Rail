#include "BossA.h"
#include "BossAStateNode.h"
#include "Bullet.h"
#include "Beam.h"
#include "DeviationShotBullet.h"
#include "Player.h"

#define PI 3.1415926f
extern std::vector<Bullet*> bulletList;

BossA::BossA()
{
	color = 0xB6BBC4FF;
	size = { 60.0f, 60.0f };
	pos = { 400.0f, 300.0f };
	velocity = { 0.0f, 0.0f };

	stateMachine.RegisterState("idle",new IdleState());
	stateMachine.RegisterState("circlefire", new CircleFireState());
	stateMachine.RegisterState("moveA",new MoveAState());
	stateMachine.RegisterState("StraightLineFire", new StraightLineFire());
	stateMachine.RegisterState("moveB", new MoveBState());
	stateMachine.RegisterState("RandomShotting", new RandomShotting());
	stateMachine.RegisterState("RandomShottingMove", new RandomShottingMoveState());
	stateMachine.RegisterState("DeviationShot", new DeviationShot());
	stateMachine.RegisterState("DeviationShotMove", new DeviationShotMoveState());

	stateMachine.SetEntry("DeviationShotMove");
}



void BossA::onUpdate()
{
	stateMachine.onUpdate();
	Charactor::onUpdate();
}

void BossA::onDraw()
{
	Novice::DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, color, kFillModeSolid);
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
	Player *player = new Player();

	Vector2 playerPosition = player->Getposition();
	Vector2 playerVelocity = player->GetVelocity(); 

	float predictionTime = 1.0f;
	Vector2 predictedPosition;
	predictedPosition.x = playerPosition.x + playerVelocity.x * predictionTime;
	predictedPosition.y = playerPosition.y; 

	float angle = atan2(predictedPosition.y - pos.y, predictedPosition.x - pos.x);

	DeviationShotBullet* bullet = new DeviationShotBullet(pos, { angle, angle });
	bulletList.push_back(bullet);
}


//void BossA::MoveTo(Vector2 targetPos,float time)
//{
//	//使用缓动函数移动到目标位置
//	
//	 
//}

