#pragma once
#include <MyVector2.h>
#include "timer.h"

class Bar
{
public:
	Bar(Vector2 _pos ,Vector2 _borderSize, int _maxValue,int barColor);
	Bar(Vector2 _pos, Vector2 _borderSize, int _maxValue, int barColor , int _borderColor, int _borderWidth);
	~Bar() = default;

	void Update(int _value);
	void Draw();

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
	Timer moveTimer;//残存hpのバーを移動する時間

	Timer recoveryTimer;//回復する時間

	bool isResidualTimeStart;
	bool isMoveStart;

};
