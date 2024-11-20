#pragma once
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

	
	float startLineX;
	float startLineY;
	float endLineX;
	float endLineY;

	float startLineX2;
	float startLineY2;
	float endLineX2;
	float endLineY2;

	bool lineShift;

private:

};
