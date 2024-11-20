#include "stageScene.h"
#include "sceneManager.h"
#include "resouresManager.h"
#include <Novice.h>
#include <vector>
#include "Bullet.h"



extern SceneManager sceneManager;
extern int windowHeight;
extern int windowWidth;

Charactor* boss = nullptr;
Charactor* player = nullptr;
std::vector<Bullet*> bulletList;


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

}

void StageScene::onInput(char* keys, char* prekeys)
{
	if (keys[DIK_BACK] && !prekeys[DIK_BACK])
	{
		sceneManager.switchScene(SceneManager::SceneType::StageSelect);
	}
	player->onInput(keys,prekeys);
}

void StageScene::update()
{
	boss->onUpdate();
	player->onUpdate();
	BulletListUpdate();
	//TODO:check collision
}

void StageScene::draw()
{
	Novice::DrawBox(0, 0, windowWidth, windowHeight, 0.0f, backGroundColor, kFillModeSolid);
	Novice::ScreenPrintf(0, 0, "stage:%d", id);

	boss->onDraw();
	player->onDraw();
	BulletListDraw();
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

void StageScene::BulletListDraw()
{
	for (auto bullet : bulletList)
	{
		bullet->onDraw();
	}
}

