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
}

void StageScene::update()
{
	boss->onUpdate();
	player->onUpdate();
}

void StageScene::draw()
{
	Novice::DrawBox(0, 0, windowWidth, windowHeight, 0.0f, backGroundColor, kFillModeSolid);
	Novice::ScreenPrintf(0, 0, "stage:%d", id);

	boss->onDraw();
	player->onDraw();  
}

void StageScene::onExit()
{
	delete boss;
	boss = nullptr;
	delete player;
	player = nullptr;
}

