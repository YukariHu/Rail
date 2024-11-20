#pragma once
#include "StageSelectScene.h"
#include <SceneManager.h>
#include <Novice.h>

extern int stageSelectBackground;
extern SceneManager sceneManager;

void StageSelectScene::onEnter()
{
}

void StageSelectScene::onInput(char* keys, char* prekeys)
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

void StageSelectScene::update()
{
}

void StageSelectScene::draw(const Camera& camera)
{
	(void)camera;
	Novice::DrawSprite(0,0, stageSelectBackground,1.0f,1.0f,0.0f,WHITE);
	Novice::ScreenPrintf(0,0,"select:-> <- stageId %d", sceneManager.selectedStage);
}
