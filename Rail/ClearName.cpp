#include "ClearName.h"

clearName::clearName() :
	width_(30)
{
}

clearName::~clearName()
{
}

void clearName::Init()
{
}

void clearName::Update()
{
}

void clearName::Draw()
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == 1) {
				Novice::DrawBox(430 + (j * width_), 100 + (i * width_), width_, width_, 0.0f, WHITE, kFillModeSolid);
			}
		}
	}
}
