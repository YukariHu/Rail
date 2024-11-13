#pragma once
#include <MyVector2.h>
Vector2 lerp(Vector2 startPos, Vector2 endPos, float time)
{
	return startPos + (endPos - startPos) * time;
}

float EaseInOut(float t) {
	return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
}