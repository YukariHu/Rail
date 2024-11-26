#pragma once
#include "ClearScene.h"
#include <SceneManager.h>
#include <Novice.h>

extern int stageSelectBackground;
extern SceneManager sceneManager;

void ClearScene::onEnter()
{
}

void ClearScene::onInput(char* keys, char* prekeys)
{
	if (keys[DIK_BACK] && !prekeys[DIK_BACK])
	{
		sceneManager.switchScene(SceneManager::SceneType::Title);
	}

	if (keys[DIK_RIGHT] && !prekeys[DIK_RIGHT])
	{
		if (sceneManager.selectedStage < sceneManager.stageNum - 1)
		{
			sceneManager.selectedStage++;
		}
	}
	if (keys[DIK_LEFT] && !prekeys[DIK_LEFT])
	{
		if (sceneManager.selectedStage > 0) 
		{
			sceneManager.selectedStage--;
		}
	}
	if (keys[DIK_SPACE] && !prekeys[DIK_SPACE])
	{
		sceneManager.switchScene(SceneManager::SceneType::Game);
	}
}

void ClearScene::update()
{
}

void ClearScene::draw(const Camera& camera)
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xCAC9A1FF, kFillModeSolid);

	Novice::DrawLine(0, 720 / 2, 1280, 720 / 2, 0x4A505FFF);

	Novice::DrawEllipse(1280 / 2 + (int)camera.GetPos().x, 720 / 2, 20, 20, 0.0f, 0x4A505FFF, kFillModeSolid);

	Novice::ScreenPrintf(0,0,"select:-> <- stageId %d", sceneManager.selectedStage);
}
