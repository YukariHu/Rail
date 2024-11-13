#pragma once
#include <Scene.h>
#include "BossA.h"
#include "Player.h"


class StageScene : public Scene
{
	public:
		

		StageScene() = default;
		StageScene(int _id);
		~StageScene();

		void onEnter() override;
		void onInput(char* keys,char* prekeys) override;
		void update() override;
		void draw() override;
		void onExit() override;

		void BulletListUpdate();
		void BulletListDraw();

	private:

		int id;
		int backGroundColor = 0x363636FF;
		


};