#include "stageScene.h"
#include "sceneManager.h"
#include "resouresManager.h"
#include <Novice.h>
#include <vector>
#include "Bullet.h"
#include "BackParticleManager.h"


extern SceneManager sceneManager;
extern int windowHeight;
extern int windowWidth;

extern Camera mainCamera;

Charactor* boss = nullptr;
Charactor* player = nullptr;
std::vector<Bullet*> bulletList;

BackParticleManager backParticle;

StageScene::StageScene(int _id)
{
	id = _id;
}

StageScene::~StageScene()
{
	
}

void StageScene::onEnter()
{
	boss = new BossA();
	player = new Player();

	boss->SetTarget(player);


	for (int i = 0; i < 20; ++i) {  
		backParticle.Create({ -1.0f, 0.0f });  
	}
	isStart = true;
}

void StageScene::onInput(char* keys, char* prekeys)
{
	if (keys[DIK_BACK] && !prekeys[DIK_BACK])
	{
		sceneManager.switchScene(SceneManager::SceneType::StageSelect);
	}

	if (keys[DIK_SPACE] && !prekeys[DIK_SPACE])
	{
		mainCamera.Shack(5,0.3f);
	}
}

void StageScene::update()
{
	mainCamera.onUpdate();
	boss->onUpdate();
	player->onUpdate();
	BulletListUpdate();
	//TODO:check collision

	backParticle.Update();

	//**********particle
	particleTime--;
	if (particleTime <= 0) {
		backParticle.Create({ -1.0f, 1.0f });
		particleTime = 5;
		
	}

}

void StageScene::draw(const Camera& camera)
{
	(void)camera;

	Novice::DrawBox(0, 0, windowWidth, windowHeight, 0.0f, backGroundColor, kFillModeSolid);
	Novice::ScreenPrintf(0, 0, "stage:%d", id);

	backParticle.Draw();

	boss->onDraw(camera);
	player->onDraw(camera);
	BulletListDraw(camera);
}

void StageScene::onExit()
{
	delete boss;
	boss = nullptr;
	delete player;
	player = nullptr;

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

