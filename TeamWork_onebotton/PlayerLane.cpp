#include "PlayerLane.h"

PlayerLane::PlayerLane()
{
	lineChange_ = false;

	startLine = { 0.0f,500.0f };
	endLine = { 1280.0f ,500.0f };
	startLine2 = { 0.0f, 600.0f };
	endLine2 = { 1280.0f ,600.0f };

	lineShift = false;
}

void PlayerLane::update()
{
}

void PlayerLane::Draw()
{
}
