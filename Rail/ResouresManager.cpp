#include "ResouresManager.h"
int titleBackground;
int stageSelectBackground;
//int gameBackground_A;
//int gameBackground_B;
//int gameBackground_C;
int gameBackgroundHandler[3];

//audio
int beamSound;
int buttonSound;
int dashSound;
int playerShotSound;
int damageSound;
int laneChangeSound;

void ResouresManager::loadResoures()
{
	beamSound = Novice::LoadAudio("./se/beam-2.wav");
	buttonSound = Novice::LoadAudio("./se/button.mp3");
	dashSound = Novice::LoadAudio("./se/dash.mp3");
	playerShotSound = Novice::LoadAudio("./se/playerShot.mp3");
	damageSound = Novice::LoadAudio("./se/damage.mp3");
	laneChangeSound = Novice::LoadAudio("./se/laneChange.mp3");
}
