#pragma once
#include <Scene.h>

class StageSelectScene : public Scene
{
	public:
	StageSelectScene() = default;
	~StageSelectScene() = default;

	void onEnter() override;
	void onInput(char* keys,char* prekeys) override;
	void update() override;
	void draw() override;
	//void onExit() override;

};