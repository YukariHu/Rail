#include "stageScene.h"
#include "sceneManager.h"
#include "resouresManager.h"
#include <Novice.h>



extern SceneManager sceneManager;
extern int windowHeight;
extern int windowWidth;

StageScene::StageScene(int _id)
{
	id = _id;
}

void StageScene::onEnter()
{
	boss = new BossA();
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
}

void StageScene::draw()
{
	Novice::DrawBox(0, 0, windowWidth, windowHeight, 0.0f, backGroundColor, kFillModeSolid);
	Novice::ScreenPrintf(0, 0, "%d", id);

	boss->onDraw();
}
