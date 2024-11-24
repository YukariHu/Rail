#include "Bar.h"
#include  "Novice.h"

Bar::Bar(Vector2 _pos, Vector2 _size, int _maxValue)
{
	pos = _pos;
	size = _size;
	maxValue = _maxValue;
	value = _maxValue;
}

void Bar::Draw()
{
	Novice::DrawBox(int(pos.x), int(pos.y), int(size.x), int(size.y), 0.0f, {},kFillModeSolid);
}
