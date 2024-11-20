#pragma once
#include "MyVector2.h"
#include "Charactor.h"

class Player : public Charactor
{
public:
	Player();
	~Player() = default;

	void onInput(char* keys, char* prekeys) override;
	void onUpdate() override;
	void onDraw() override;

	float t_;
	bool lineChange_;

	
	Vector2 startLine;
	Vector2 endLine;

	Vector2 startLine2;
	Vector2 endLine2;

	float startPointX[3] = { 0.0f,150.0f,250.0f };
	float startPointY[3] = { 500.0f,600.0f,0.0f };
	float endPointX[3] = { 1280.0f,150.0f,250.0f };
	float endPointY[3] = { 500.0f,600.0f,720.0f };
	bool lineShift;

private:

};
