#include "ResouresManager.h"
int titleBackground;
int stageSelectBackground;
//int gameBackground_A;
//int gameBackground_B;
//int gameBackground_C;
int gameBackgroundHandler[3];
void ResouresManager::loadResoures()
{
	titleBackground = Novice::LoadTexture("./res/title.png");
	stageSelectBackground = Novice::LoadTexture("./res/stageSelect.png");
	gameBackgroundHandler[0] = Novice::LoadTexture("./res/gameBackgroundA.png");
	gameBackgroundHandler[1] = Novice::LoadTexture("./res/gameBackgroundB.png");
	gameBackgroundHandler[2] = Novice::LoadTexture("./res/gameBackgroundC.png");
}
