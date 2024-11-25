#pragma once
#include <math.h>

namespace Easing {
	inline float Linear(float t) {
		return t;
	}

	inline float EaseIn(float t) {
		return t * t;
	}

	inline float EaseOut(float t) {
		return t * (2 - t);
	}

	inline float EaseInOut(float t) {
		return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
	}

	inline float EaseInOutCirc(float x) {
		return x < 0.5 ? 8 * x * x * x * x : 1 - float(pow(-2 * x + 2, 4) / 2);
	}

	inline float EaseOutExpo(float x){
		return x == 1 ? 1 : float(1 - pow(2, -10 * x));
	}
}
