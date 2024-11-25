#include "Bar.h"
#include  "Novice.h"
#include "Blend.h"
#include "Easing.h"

extern float deltaTime;
Bar::Bar(Vector2 _pos, Vector2 _borderSize, int _maxValue , int _barColor)
{
	pos = _pos;

	borderSize = _borderSize;
	barSize = borderSize;
	residualBarSize = barSize;
	preResidualBarSize = residualBarSize;
	borderWidth = 3;
	borderColor = WHITE;
	maxValue = float(_maxValue);
	value = maxValue;

	barColor = _barColor;
	backColor = GetColor(255, 255, 255, 40);


	isResidualTimeStart = false;
	isMoveStart = false;
	residualTimer.set_one_shot(true);
	residualTimer.set_wait_time(0.2f);
	residualTimer.set_on_timeout(
		[this]() {
			isResidualTimeStart = false;
			preResidualBarSize = residualBarSize;
			targetResidualBarSize = barSize.x;
			isMoveStart = true;
		}
	);

	moveTimer.set_one_shot(true);
	moveTimer.set_wait_time(0.1f);
	moveTimer.set_on_timeout(
		[this]() {

			isMoveStart = false;
			moveTimer.restart();
			residualBarSize.x = barSize.x;
		}
	);

}

Bar::Bar(Vector2 _pos, Vector2 _borderSize, int _maxValue, int _barColor, int _borderColor, int _borderWidth)
{
	pos = _pos;

	borderSize = _borderSize;
	barSize = borderSize;
	residualBarSize = barSize;
	preResidualBarSize = residualBarSize;
	borderWidth = _borderWidth;
	borderColor = _borderColor;
	maxValue = float(_maxValue);
	value = maxValue;

	barColor = _barColor;
	backColor = GetColor(255, 255, 255, 40);


	isResidualTimeStart = false;
	isMoveStart = false;
	residualTimer.set_one_shot(true);
	residualTimer.set_wait_time(0.2f);
	residualTimer.set_on_timeout(
		[this]() {
			isResidualTimeStart = false;
			preResidualBarSize = residualBarSize;
			targetResidualBarSize = barSize.x;
			isMoveStart = true;
		}
	);

	moveTimer.set_one_shot(true);
	moveTimer.set_wait_time(0.1f);
	moveTimer.set_on_timeout(
		[this]() {

			isMoveStart = false;
			moveTimer.restart();
			residualBarSize.x = barSize.x;
		}
	);
}

void Bar::Update(int _value)
{
	float preValue = value;
	value = float(_value);
	barSize.x = borderSize.x * (value / maxValue);

	//残存hpのバーの処理
	if (preValue > value/* && !isMoveStart*/)
	{
		isResidualTimeStart = true;
		residualTimer.restart();
	}

	

	if (isResidualTimeStart)
	{
		residualTimer.on_update(deltaTime);
	}

	if (isMoveStart)
	{
		
		float easT =  moveTimer.get_progress();
		if (easT <= 0.0f)
		{
			easT = 0.0f;
		}

		if (easT >= 1.0f)
		{
			easT = 1.0f;
		}

		residualBarSize.x = preResidualBarSize.x + (targetResidualBarSize - preResidualBarSize.x) * easT;
		moveTimer.on_update(deltaTime);
	}
	
	if (value < 0)
	{
		value = 0;
	}
	
}

void Bar::Draw()
{
	Novice::DrawBox(int(pos.x), int(pos.y), int(borderSize.x), int(borderSize.y), 0.0f, backColor,kFillModeSolid);
	Novice::DrawBox(int(pos.x), int(pos.y),int(residualBarSize.x), int(residualBarSize.y),0.0f,WHITE,kFillModeSolid);
	Novice::DrawBox(int(pos.x), int(pos.y), int(barSize.x), int(barSize.y), 0.0f, barColor, kFillModeSolid);

	for (int  i = 0; i < borderWidth; i++)
	{
		Novice::DrawBox(int(pos.x) - i, int(pos.y) - i, int(borderSize.x) + i * 2, int(borderSize.y) + i * 2, 0.0f, borderColor, kFillModeWireFrame);
	}

}
