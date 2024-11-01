#include "BossA.h"

BossA::BossA()
{
	color = 0xE066FFFF;
	size = { 80.0f, 80.0f };
	pos = { 400.0f, 300.0f };
	velocity = { 0.0f, 0.0f };
}

void BossA::onUpdate()
{
	stateMachine.onUpdate();
	Charactor::onUpdate();
}

void BossA::onDraw()
{
	Novice::DrawEllipse(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.x), 0.0f, color, kFillModeSolid);
}
