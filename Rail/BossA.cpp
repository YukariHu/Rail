#include "BossA.h"
#include "BossAStateNode.h"
#include "Bullet.h"
#include "Beam.h"
#include "DeviationShotBullet.h"
#include "Player.h"
#include "Easing.h"
#include "SceneManager.h"

#define PI 3.1415926f
extern std::vector<Bullet*> bulletList;
extern Charactor* player;
//extern IdleState* idoleState;

extern SceneManager sceneManager;

extern float deltaTime;

BossA::BossA()
{
	color = 0x008B8BFF;
	size = { 60.0f, 60.0f };
	pos = { 1280.0f / 2.0f, -100.0f };
	velocity = { 0.0f, 0.0f };
	id = 1;
	maxHp = 150;
	hp = maxHp;

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
	stateMachine.RegisterState("MoveBeamRail", new MoveBeamRailState());

	stateMachine.RegisterState("BeamUpToDown", new BeamUpToDownState());
	stateMachine.RegisterState("BeamUpToDownMove", new BeamUpToDownMoveState());

	stateMachine.RegisterState("BeamCross", new BeamCrossState());
	stateMachine.RegisterState("BeamCrossMove", new BeamCrossMoveState());

	stateMachine.RegisterState("First", new FirstState());


	stateMachine.RegisterState("Dead",new DeadState());


	stateMachine.SetEntry("First");

	 
	//bossの目
	maxEyeSize = { 15.0f, 20.0f };
	eyeSize = { maxEyeSize.x, maxEyeSize.y };
	eyePos = { 0.0f, 0.0f };
	eyeColor = WHITE;
	eyeAngle = 0.0f;
	isBlink = false;
	blinkInterval.set_one_shot(true);
	blinkInterval.set_wait_time(4.0f);
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

	fireRespawnTimer.set_wait_time(fireRespawnInterval);
	fireRespawnTimer.set_one_shot(false);
	fireRespawnTimer.set_on_timeout([&]() {

		fireParticles.push_back(FireParticle({ pos.x,pos.y + 2.0f }, { size.x + 5.0f,size.y + 5.0f }, 60));
		if (isStop)
		{
			for (int i = 0; i < 360; i += 360 / 30)
			{
				Vector2 direction = { cosf(i * PI / 180.0f), sinf(i * PI / 180.0f) };
				fireParticles.push_back(FireParticle(pos, size, 60, direction));
			}
		}
		});

}
	


void BossA::onUpdate()
{
	if (!isStop)
	{
		
		EyeUpdate();
		Charactor::onUpdate();

		if (alpha_ <= 0) {

			alpha_ = 0;
		}
		
	}
	fireRespawnTimer.on_update(deltaTime);
	stateMachine.onUpdate();


	
	//火焰粒子更新并检查是否销毁 日语：火の粒子を更新し、破壊されたかどうかを確認します
	auto it = fireParticles.begin();
	while (it != fireParticles.end()) {
		it->Update();
		if (it->isOver) {

			it = fireParticles.erase(it);
		}
		else {
			++it;
		}
	}



}

void BossA::onDraw(const Camera& camera)
{
	const Vector2& cameraPos = camera.GetPos();
	for (auto& fireParticle : fireParticles)
	{
		fireParticle.Draw();
	}
	if (isBlender)
	{
		Novice::DrawEllipse(static_cast<int>(pos.x - cameraPos.x), static_cast<int>(pos.y - cameraPos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, color, kFillModeSolid);
		Novice::DrawEllipse(static_cast<int>(pos.x + eyePos.x - cameraPos.x), static_cast<int>(pos.y + eyePos.y - cameraPos.y), static_cast<int>(eyeSize.x), static_cast<int>(eyeSize.y), eyeAngle, eyeColor, kFillModeSolid);

	}
	
}

void BossA::onHurt(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		if (isphase1)
		{
			isphase1 = false;
			dynamic_cast<Player*>(player)->lane_->lineShift = true;
			hp = maxHp;
		}
		else
		{
			//isDead = true;
			isStop = true;
			stateMachine.SwitchTo("Dead");
		}
		
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
	isBlink = true;
	blinkTimer.restart();
	Vector2 direction = { -1.0f ,0.0f };
	Bullet* bullet = new Bullet(pos, direction,0);
	bulletList.push_back(bullet);
}

void BossA::RandomFire()
{
	float angle = float(rand() % 360);  
	Vector2 direction = { cosf(angle * PI / 180.0f), sinf(angle * PI / 180.0f) };

	Bullet* bullet = new Bullet(pos, direction, 0);
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

	float predictionTime = 250.0f;
	Vector2 predictedPosition;
	predictedPosition.x = playerPosition.x + 1.0f * predictionTime;
	predictedPosition.y = playerPosition.y; 

	float angle = atan2(predictedPosition.y - pos.y, predictedPosition.x - pos.x);

	DeviationShotBullet* bullet = new DeviationShotBullet(pos, { angle, angle },0);
	bulletList.push_back(bullet);
}


//使っていない
void BossA::BeamFire()
{
	Vector2 direction = { 1.0f, 0.0f };
	Vector2 firepos = {-30.0f,300.0f};
	float lifeTime = 1.0f;
	Beam* beam = new Beam(firepos, direction,lifeTime,0);
	bulletList.push_back(beam);

}

