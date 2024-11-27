#include "titleName.h"

titleName::titleName():
	width_(30)
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
			if (map[i][j] == 1) {
				Novice::DrawBox(250 + (j * width_), 150 + (i * width_), width_, width_, 0.0f, WHITE, kFillModeSolid);
			}
		}
	}


}
