#pragma once
#include <Scene.h>
#include "BossA.h"
#include "Player.h"
#include "Bar.h"


class StageScene : public Scene
{
	public:
		

		StageScene() = default;
		StageScene(int _id);
		~StageScene();

		void onEnter() override;
		void onInput(char* keys,char* prekeys) override;
		void update() override;
		void draw(const Camera& camera) override;
		void onExit() override;

		void BulletListUpdate();
		void BulletListDraw(const Camera& camera);

		bool GetIsStart() const{ return isStart; };

	private:

		int id;
		int backGroundColor = 0x363636FF;

		int particleTime = 5;
		bool isStart = false;

		bool isOver = false;

		//UI
		Bar* bossHpBar = nullptr;
		Vector2 bossHpBarPos;
		Vector2 bossHpBarSize;

		Bar* playerHpBar = nullptr;
		Vector2 playerHpBarPos;
		Vector2 playerHpBarSize;

		Bar* dashBar = nullptr;
		Vector2 dashBarPos;
		Vector2 dashBarSize;

		int alpha_;
		int rad_;
};