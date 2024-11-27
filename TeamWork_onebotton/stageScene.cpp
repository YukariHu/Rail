#include "stageScene.h"
#include "sceneManager.h"
#include "resouresManager.h"
#include <Novice.h>
#include <vector>
#include "Bullet.h"
#include "BackParticleManager.h"
#include "Blend.h"

extern SceneManager sceneManager;
extern int windowHeight;
extern int windowWidth;

extern Camera mainCamera;



Charactor* boss = nullptr;
Charactor* player = nullptr;
std::vector<Bullet*> bulletList;

BackParticleManager backParticle;


float SLerp(float start, float end, float t)
{
	return start + t * (end - start);
}

StageScene::StageScene(int _id)
{
	id = _id;
	bossHpBarPos = { 5.0f,0.0f };
	bossHpBarSize = { windowWidth - 10.0f,20.0f };

	playerHpBarPos = { 30.0f,windowHeight - 50.0f };
	playerHpBarSize = { 140.0f,15.0f };

	dashBarPos = { 25.0f,windowHeight - 30.0f };
	dashBarSize = { 180.0f,15.0f };

	alpha_ = 0;
	rad_ = 1500;
	bgmHandle = Novice::LoadAudio("./bgm/bossBGM.mp3");
	bgmPlayHandle = -1;
}

StageScene::~StageScene()
{
	
}

void StageScene::onEnter()
{
	boss = new BossA();
	player = new Player();

	bossHpBar = new Bar(bossHpBarPos,bossHpBarSize,boss->GetHp(), GetColor(255, 48, 48, 255), WHITE,4, 1.0f);//  255, 106, 106
	playerHpBar = new Bar(playerHpBarPos, playerHpBarSize, player->GetHp(), GetColor(0, 205,102, 255));//0, 255,127
	
	dashBar = new Bar(dashBarPos, dashBarSize, dynamic_cast<Player*>(player)->GetDashCount(), GetColor(255,215, 0, 255), GetColor(0, 205, 102, 000),1,0.2f);//0, 255,127
	
	boss->SetTarget(player);
	//player.ge


	for (int i = 0; i < 20; ++i) {
		backParticle.Create({ -1.0f, 0.0f }, isStart);  
	}
	isStart = true;

	particleTime = 5;
	rad_ = 1500;
	isOver = false;
	alpha_ = 0;
	bgmPlayHandle = -1;
}

void StageScene::onInput(char* keys, char* prekeys)
{
	player->onInput(keys, prekeys);
}

void StageScene::update()
{
	if (Novice::IsPlayingAudio(bgmPlayHandle) == 0 || bgmPlayHandle == -1)
	{
		bgmPlayHandle = Novice::PlayAudio(bgmHandle, 1, 0.5f);
	}

	mainCamera.onUpdate();
	BulletListUpdate();
	boss->onUpdate();
	player->onUpdate();
	

	//*********bar
	bossHpBar->Update(boss->GetHp());
	playerHpBar->Update(player->GetHp());
	dashBar->Update(dynamic_cast<Player*>(player)->GetDashCount());

	//**********particle
	backParticle.Update();
	particleTime--;
	if (particleTime <= 0) {
		backParticle.Create({ -1.0f, 1.0f },isStart);
		particleTime = 5;
		
	}

	//********isOver
	if (boss->GetIsDead() || player->GetIsDead())
	{
		isOver = true;
		//当たり判定無効にする
		player->SetIsEnableCollision(false);
		boss->SetIsEnableCollision(false);
		
	}

	if (isOver && boss->GetIsDead())
	{
		sceneManager.switchScene(SceneManager::SceneType::Claer);
		Novice::StopAudio(bgmPlayHandle);
	}

	if (player && player->GetHp() <= 0 && alpha_ == 255)
	{
		sceneManager.switchScene(SceneManager::SceneType::Title);
		Novice::StopAudio(bgmPlayHandle);
	}

	//***************
	if (boss && boss->GetHp() <= 0 || player && player->GetHp() <= 0) {
		alpha_+= 2;
		if (alpha_ >= 255) {
			alpha_ = 255;
		}
	}

	rad_ = (int)SLerp((float)rad_, 0.0f, 0.05f);
}

void StageScene::draw(const Camera& camera)
{
	Novice::DrawBox(0, 0, windowWidth, windowHeight, 0.0f, backGroundColor, kFillModeSolid);

	backParticle.Draw(camera);
	BulletListDraw(camera);
	player->onDraw(camera);
	boss->onDraw(camera);

	bossHpBar->Draw();
	playerHpBar->Draw();
	dashBar->Draw();

	//hp数字を表示
	//Novice::ScreenPrintf(5, 5, "BossHP:%d", boss->GetHp());
	//Novice::ScreenPrintf(5, 20, "PlayerHP:%d", player->GetHp());
	


	
	if (boss && boss->GetHp() <= 0) {
		Novice::DrawBox(0, 0, windowWidth, windowHeight, 0.0f, GetColor(255, 255, 255, alpha_), kFillModeSolid);
	} else if (player && player->GetHp() <= 0) {
		Novice::DrawBox(0, 0, windowWidth, windowHeight, 0.0f, GetColor(0, 0, 0, alpha_), kFillModeSolid);
	}


	Novice::DrawEllipse(-100, windowHeight / 2, rad_, rad_, 0.0f, WHITE, kFillModeSolid);

	//表示guide	
	for (int i = 0; i < guide.size();i++) {
		for (int j = 0; j < guide[i].size();j++) {
			if (guide[i][j] == 1) {
				Novice::DrawBox(guidePosX + (j * guideWidth), guidePosY + (i * guideWidth), guideWidth, guideWidth, 0.0f, WHITE, kFillModeSolid);
			}
		}
	}
}

void StageScene::onExit()
{
	delete boss;
	boss = nullptr;
	delete player;
	player = nullptr;

	delete bossHpBar;
	bossHpBar = nullptr;

	delete playerHpBar;
	playerHpBar = nullptr;

	delete dashBar;
	dashBar = nullptr;


	for (auto bullet : bulletList)
	{
		delete bullet;
	}
	bulletList.clear();
}

void StageScene::BulletListUpdate()
{
	for (auto bullet : bulletList)
	{
		bullet->onUpdate();
	}

	for (int i = 0;i < bulletList.size();i++)
	{
		Bullet* bullet = bulletList[i];
		if (bulletList[i]->isCanRemove)
		{
			std::swap(bulletList[i], bulletList.back());
			bulletList.pop_back();
			delete bullet;
		}
	}


}

void StageScene::BulletListDraw(const Camera& camera)
{
	for (auto bullet : bulletList)
	{
		bullet->onDraw(camera);
	}
}

