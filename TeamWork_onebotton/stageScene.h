#pragma once
#include <Scene.h>
#include "BossA.h"
class StageScene : public Scene
{
	public:
		StageScene() = default;
		StageScene(int _id);
		~StageScene() = default;

		void onEnter() override;
		void onInput(char* keys,char* prekeys) override;
		void update() override;
		void draw() override;
		//void onExit() override;

	private:
		int id;
		int backGroundColor = 0x363636FF;

		Charactor* boss = nullptr;
};