#include "titleName.h"

titleName::titleName():
	width_(15)
{
}

titleName::~titleName()
{
}

void titleName::Init()
{
}

void titleName::Update()
{
}

void titleName::Draw()
{
	for (int i = 0; i < map.size();i++) {
		for (int j = 0; j < map[i].size();j++) {
			if (map[j][i] == 1) {
				Novice::DrawBox(j * width_, i * width_, width_, width_, 0.0f, WHITE, kFillModeSolid);
			}
		}
	}
}
