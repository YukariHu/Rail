#pragma once
#include "MyVector2.h"

class PlayerLane
{
public:
	PlayerLane();

	void update();
	void Draw();

	Vector2 startLine;
	Vector2 endLine;
	Vector2 startLine2;
	Vector2 endLine2;

	float startPointX[3] = { 0.0f,1280.0f / 2.0f - 100.0f,1280.0f / 2.0f + 100.0f };
	float startPointY[3] = { 500.0f,650.0f,0.0f };
	float endPointX[3] = { 1280.0f,1280.0f / 2.0f - 100.0f,1280.0f / 2.0f + 100.0f };
	float endPointY[3] = { 500.0f,650.0f,720.0f };
	bool lineShift;

	int alpha_;
};

