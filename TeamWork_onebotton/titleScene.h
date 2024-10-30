#pragma once
#include <Scene.h>
class TitleScene : public Scene
{
public:
		TitleScene() = default;
		~TitleScene() = default;


		void onInput(char* keys,char* prekeys) override;
		void update() override;

		void draw() override;
		
private:
};