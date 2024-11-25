#include "BossA.h"
#include "BossAStateNode.h"
#include "Bullet.h"
#include "Beam.h"
#include "DeviationShotBullet.h"
#include "Player.h"
#include "Easing.h"

#define PI 3.1415926f
extern std::vector<Bullet*> bulletList;
extern Charactor* player;
//extern IdleState* idoleState;

extern float deltaTime;

BossA::BossA()
{
	color = 0x008B8BFF;
	size = { 60.0f, 60.0f };
	pos = { 400.0f, 300.0f };
	velocity = { 0.0f, 0.0f };
	id = 1;
	
	currentStage = 1;

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
	 
	//bossの目
	maxEyeSize = { 15.0f, 20.0f };
	eyeSize = { maxEyeSize.x, maxEyeSize.y };
	eyePos = { 0.0f, 0.0f };
	eyeColor = WHITE;
	eyeAngle = 0.0f;
	isBlink = false;
	blinkInterval.set_one_shot(true);
	blinkInterval.set_wait_time(3.0f);
	blinkInterval.set_on_timeout(
		[this]() {
			isBlink = true;
			blinkTimer.restart();
		}
	);

	blinkTimer.set_one_shot(true);
	blinkTimer.set_wait_time(0.3f);
	blinkTimer.set_on_timeout(
		[this]() {
			isBlink = false;
			blinkInterval.restart();
			eyeSize = maxEyeSize;
		}
	);
}
	


void BossA::onUpdate()
{
	stateMachine.onUpdate();
	EyeUpdate();
	Charactor::onUpdate();

	if (alpha_ <= 0) {

		alpha_ = 0;
	}
}

void BossA::onDraw(const Camera& camera)
{
	const Vector2& cameraPos = camera.GetPos();
	Novice::DrawEllipse(static_cast<int>(pos.x - cameraPos.x), static_cast<int>(pos.y - cameraPos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, color, kFillModeSolid);
	Novice::DrawEllipse(static_cast<int>(pos.x + eyePos.x - cameraPos.x), static_cast<int>(pos.y + eyePos.y - cameraPos.y), static_cast<int>(eyeSize.x), static_cast<int>(eyeSize.y), eyeAngle, eyeColor, kFillModeSolid);
    
}

void BossA::onHurt(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		
		isDead = true;
	}

}


void BossA::CircleFire(int bulletNum)
{
for (int i = 0; i < 360; i += 360/ bulletNum)
	{
		Vector2 direction = { cosf(i * PI / 180.0f), sinf(i * PI / 180.0f) };
		Bullet* bullet = new Bullet(pos, direction,0);
		bulletList.push_back(bullet);
	}
}

void BossA::StraightFire()
{
	Vector2 direction = { -1.0f ,0.0f };
	Bullet* bullet = new Bullet(pos, direction,0);
	bulletList.push_back(bullet);
}

void BossA::RandomFire()
{
	Vector2 direction = { cosf(float(rand() % 180) * PI / float(rand() % 180)), sinf(float(rand() % 180)* PI / 180) };
	Bullet* bullet = new Bullet(pos, direction,0);
	bulletList.push_back(bullet);
}

void BossA::EyeUpdate()
{
	//眼睛在Boss的Size内朝着玩家移动
	//目がボスのサイズ内でプレイヤーに向かって移動する
	Vector2 playerPos = player->Getposition();
	Vector2 direction = playerPos - pos;
	direction = direction.normalize();
	
	eyePos = direction * (size.x / 2);

	//根据direction旋转眼睛
	//方向に応じて目を回転する
	eyeAngle = atan2(direction.y, direction.x);

	if (isBlink)
	{
		blinkTimer.on_update(deltaTime);
		float easT = Easing::EaseInOutCirc(blinkTimer.get_progress());
		eyeSize.x = eyeSize.x * (1 - easT);
	}
	else
	{
		blinkInterval.on_update(deltaTime);

	}
	
}

void BossA::DeviationFire() {
	
	Vector2 playerPosition = player->Getposition(); 

	float predictionTime = 3.0f;
	Vector2 predictedPosition;
	predictedPosition.x = playerPosition.x + 1.0f * predictionTime;
	predictedPosition.y = playerPosition.y; 

	float angle = atan2(predictedPosition.y - pos.y, predictedPosition.x - pos.x);

	DeviationShotBullet* bullet = new DeviationShotBullet(pos, { angle, angle },0);
	bulletList.push_back(bullet);
}

int BossA::GetCurrentStage()
{
	return currentStage;
}


void BossA::BeamFire()
{
	Vector2 direction = { 1.0f, 0.0f };
	Vector2 firepos = {-30.0f,300.0f};
	float lifeTime = 1.0f;
	Beam* beam = new Beam(firepos, direction,lifeTime,0);
	bulletList.push_back(beam);

}

