#pragma once
#include <Scene.h>
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


		//画像
		int img_backgroung = 0;
};