#include "Novice.h"
#include "PlayerLane.h"

PlayerLane::PlayerLane()
{

	startLine = { 0.0f,500.0f };
	endLine = { 1280.0f ,500.0f };
	startLine2 = { 0.0f, 600.0f };
	endLine2 = { 1280.0f ,600.0f };

	lineShift = false;
}

void PlayerLane::update()
{

	if (lineShift) {
		lineShift = false;


		if (startLine.x == 0.0f) {
			startLine.x = startPointX[1];
			startLine2.x = startPointX[2];
			endLine.x = endPointX[1];
			endLine2.x = endPointX[2];

			startLine.y = startPointY[2];
			startLine2.y = startPointY[2];
			endLine.y = endPointY[2];
			endLine2.y = endPointY[2];


		} else {
			startLine.x = startPointX[0];
			startLine2.x = startPointX[0];
			endLine.x = endPointX[0];
			endLine2.x = endPointX[0];

			startLine.y = startPointY[0];
			startLine2.y = startPointY[1];
			endLine.y = endPointY[0];
			endLine2.y = endPointY[1];
		}
	}



}

void PlayerLane::Draw()
{
	Novice::DrawLine(static_cast<int>(startLine.x), static_cast<int>(startLine.y), static_cast<int>(endLine.x), static_cast<int>(endLine.y), WHITE);
	Novice::DrawLine(static_cast<int>(startLine2.x), static_cast<int>(startLine2.y), static_cast<int>(endLine2.x), static_cast<int>(endLine2.y), WHITE);

}
