#include "Novice.h"
#include "SE.h"

SE::SE()
{
	startBGM = -1;
	bossBGM = -1;
	resultBGM = -1;
	clearBGM = -1;

	buttonSE = -1;

	playerShotSE = -1;
	playerDashSE = -1;
	playerLaneChangeSE = -1;
	damageSE = -1;
	bossBeam = -1;


	startHandle = Novice::LoadAudio("./bgm./titleBGM.mp3");
	bossHandle = Novice::LoadAudio("./bgm./bossBGM.mp3");
	resultHandle = Novice::LoadAudio("./bgm./resulte.mp3");
	clearHandle = Novice::LoadAudio("./bgm./clear.mp3");

	buttonHandle = Novice::LoadAudio("./se./button.mp3");

	playerShotHandle = Novice::LoadAudio("./se./playerShot.mp3");
	playerDashHandle = Novice::LoadAudio("./se./dash.mp3");
	playerLaneChangeHandle = Novice::LoadAudio("./se./bulaneChange.mp3");
	damageHandle = Novice::LoadAudio("./se./damage.mp3");
	bossBeamHandle = Novice::LoadAudio("./se./beam-2.mp3");
}

void SE::StartBGM()
{
	if (!Novice::IsPlayingAudio(startBGM)) {
		startBGM = Novice::PlayAudio(startHandle, 0, 0.5f);
	}
}

void SE::BossBGM()
{
}

void SE::ResultBGM()
{
}

void SE::ClearBGM()
{
}

void SE::ButtonSE()
{
}

void SE::PlayerShotSE()
{
}

void SE::PlayerDashSE()
{
}

void SE::PlayerLaneChangeSE()
{
}

void SE::DamageSE()
{
}

void SE::BossBeamSE()
{
}
