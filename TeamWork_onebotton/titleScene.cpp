#pragma once
#include "TitleScene.h"
#include <Novice.h>
#include <SceneManager.h>
extern SceneManager sceneManager;
extern int titleBackground;


void TitleScene::onInput(char* keys,char* prekeys)
{
	if (keys[DIK_SPACE] && !prekeys[DIK_SPACE])
	{
		sceneManager.switchScene(SceneManager::SceneType::StageSelect);
	}
}

void TitleScene::update()
{
}

void TitleScene::draw()
{
	Novice::DrawSprite(0, 0, titleBackground, 1.0f, 1.0f, 0.0f, WHITE);
}
