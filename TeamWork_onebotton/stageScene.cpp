#include "stageScene.h"
#include "sceneManager.h"
#include "resouresManager.h"
#include <Novice.h>
extern int gameBackgroundHandler[];
extern SceneManager sceneManager;
//extern ResouresManager resouresManager;
StageScene::StageScene(int _id)
{
	id = _id;
	
}

void StageScene::onEnter()
{
	img_backgroung = gameBackgroundHandler[id];
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
}

void StageScene::draw()
{
	Novice::DrawSprite(0, 0, img_backgroung, 1.0f, 1.0f, 0.0f, WHITE);
	//Novice::ScreenPrintf(0, 0, "%d", id);
}
