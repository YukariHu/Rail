#include "TitleLine.h"

void TitleLine::Init()
{
    lineLength_ = 0;
}

void TitleLine::Update(int time)
{
    lineLength_ = time;
}

void TitleLine::Draw()
{
    Novice::DrawLine(0, 600, lineLength_, 600, WHITE);
}
