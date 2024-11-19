#pragma once
#include <MyVector2.h>

float EaseInOut(float t) {
	return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
}