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
	bossBeamSE = -1;


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
	if (!Novice::IsPlayingAudio(bossBGM)) {
		bossBGM = Novice::PlayAudio(bossHandle, 0, 0.5f);
	}
}

void SE::ResultBGM()
{
	if (!Novice::IsPlayingAudio(resultBGM)) {
		resultBGM = Novice::PlayAudio(resultHandle, 0, 0.5f);
	}
}

void SE::ClearBGM()
{
	if (!Novice::IsPlayingAudio(clearBGM)) {
		clearBGM = Novice::PlayAudio(clearHandle, 0, 0.5f);
	}
}

void SE::ButtonSE()
{
	if (!Novice::IsPlayingAudio(buttonSE)) {
		buttonSE = Novice::PlayAudio(buttonHandle, 0, 0.5f);
	}
}

void SE::PlayerShotSE()
{
	if (!Novice::IsPlayingAudio(playerShotSE)) {
		playerShotSE = Novice::PlayAudio(playerShotHandle, 0, 0.5f);
	}
}

void SE::PlayerDashSE()
{
	Novice::StopAudio(playerDashSE);

	if (!Novice::IsPlayingAudio(playerDashSE)) {
		playerDashSE = Novice::PlayAudio(playerDashHandle, 0, 0.5f);
	}
}

void SE::PlayerLaneChangeSE()
{
	if (!Novice::IsPlayingAudio(playerLaneChangeSE)) {
		playerLaneChangeSE = Novice::PlayAudio(playerLaneChangeHandle, 0, 0.5f);
	}
}

void SE::DamageSE()
{
	if (!Novice::IsPlayingAudio(damageSE)) {
		damageSE = Novice::PlayAudio(damageHandle, 0, 0.5f);
	}
}

void SE::BossBeamSE()
{
	if (!Novice::IsPlayingAudio(bossBeamSE)) {
		bossBeamSE = Novice::PlayAudio(bossBeamHandle, 0, 0.5f);
	}
}
