#pragma once
#include <Scene.h>

class ClearScene : public Scene
{
	public:
	ClearScene() = default;
	~ClearScene() = default;

	void onEnter() override;
	void onInput(char* keys,char* prekeys) override;
	void update() override;
	void draw() override;
	//void onExit() override;

	private:

};