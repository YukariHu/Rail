#pragma once
class SE
{
public:
	SE();

	void StartBGM();
	void BossBGM();
	void ResultBGM();
	void ClearBGM();

	void ButtonSE();

	void PlayerShotSE();
	void PlayerDashSE();
	void PlayerLaneChangeSE();
	void DamageSE();
	void BossBeamSE();


	int startBGM;
	int bossBGM;
	int resultBGM;
	int clearBGM;

	int buttonSE;

	int playerShotSE;
	int playerDashSE;
	int playerLaneChangeSE;
	int damageSE;
	int bossBeamSE;


	int startHandle;
	int bossHandle;
	int resultHandle;
	int clearHandle;

	int buttonHandle;

	int playerShotHandle;
	int playerDashHandle;
	int playerLaneChangeHandle;
	int damageHandle;
	int bossBeamHandle;

};

