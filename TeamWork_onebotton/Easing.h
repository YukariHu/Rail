#pragma once
#include <MyVector2.h>
Vector2 lerp(Vector2 startPos, Vector2 endPos, float time)
{
	return startPos + (endPos - startPos) * time;
}