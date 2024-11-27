#include "Novice.h"
#include "PlayerLane.h"

int GetLineColor(unsigned int red, unsigned int  green, unsigned int blue, int  alpha)
{
    //unsigned char top = 0x;
    int color = (red << 24) | (green << 16) | (blue << 8) | alpha;
    return color;
}

PlayerLane::PlayerLane()
{
    startLine = { 0.0f, 500.0f };
    endLine = { 1280.0f ,500.0f };
    startLine2 = { 0.0f, 650.0f };
    endLine2 = { 1280.0f ,650.0f };

    lineShift = false;
	alpha_ = 0;
}

void PlayerLane::update()
{

	if (lineShift) {
		alpha_ += 10;
		if (alpha_ >= 255) {
			alpha_ = 255;

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

			lineShift = false;
		}
	} else {
		alpha_-= 10;
		if (alpha_ <= 0) {

			alpha_ = 0;
		}
	}

}

void PlayerLane::Draw()
{
    Novice::DrawBox(0, 0, 1280, 720,0.0f, GetLineColor(255,255,255,alpha_), kFillModeSolid);
    Novice::DrawLine(static_cast<int>(startLine.x), static_cast<int>(startLine.y), static_cast<int>(endLine.x), static_cast<int>(endLine.y), WHITE);
    Novice::DrawLine(static_cast<int>(startLine2.x), static_cast<int>(startLine2.y), static_cast<int>(endLine2.x), static_cast<int>(endLine2.y), WHITE);
    
}
