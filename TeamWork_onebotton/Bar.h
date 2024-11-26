#pragma once
#include <MyVector2.h>
#include "timer.h"
#include "Camera.h"
class Bar
{
public:
	Bar(Vector2 _pos ,Vector2 _borderSize, int _maxValue,int barColor);
	Bar(Vector2 _pos, Vector2 _borderSize, int _maxValue, int barColor , int _borderColor, int _borderWidth, float _recoveryTime);
	~Bar() = default;

	void Update(int _value);
	void Draw();

	void Draw(Camera camera);

	void SetrecoveryTime(float _recoveryTime) { recoveryTime = _recoveryTime; }

private:
	float maxValue;
	float value;
	Vector2 pos;
	Vector2 borderSize;
	Vector2 barSize;

	int borderWidth;

	Vector2 residualBarSize;//残存hpのバー
	Vector2 preResidualBarSize;//残存hpのバーの前のサイズ
	float targetResidualBarSize;//残存hpのバーの目標サイズ
	
	int barColor;
	int backColor;
	int borderColor;

	Timer residualTimer;//残存hpのバーを表示する時間
	bool isResidualTimeStart;

	Timer moveTimer;//残存hpのバーを移動する時間
	bool isMoveStart;

	Timer recoveryTimer;//回復する時間
	bool isRecoveryTimeStart;
	float recoveryTime = 0.2f;
	float startbarSize = 0.0f;
	float targetBarSize = 0.0f;
	

	//回復パーティクル 制作中
	Timer recoveryParticleTimer;
	bool isRecoveryParticleStart = false;

};
